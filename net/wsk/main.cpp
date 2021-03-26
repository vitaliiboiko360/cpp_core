
#include <atomic>
#include <vector>
#include <iostream>
#include <string>
#include <regex>

#include "../../../uWebSockets/src/App.h"
#include "../../../uWebSockets/src/HttpParser.h"
#include "helpers/Middleware.h"
#include "helpers/AsyncFileStreamer.h"

#include "drawing.h"

const bool SSL{false};
std::atomic<int> g_id_counter{ 1 };

struct PerSocketData {
    bool _is_active{false};
    int _id{ -1 };
};

std::string replace(const std::string& str, const std::string& from, const std::string& to) {
    std::string ret{str};
    size_t start_pos = ret.find(from);
    if(start_pos == std::string::npos)
        return ret;
    
    return ret.replace(start_pos, from.length(), to);
}

int get_websocket_id(uWS::WebSocket<SSL, true>* ws)
{
    return static_cast<PerSocketData *>(ws->getUserData())->_id;
}

void set_websocket_state(uWS::WebSocket<SSL, true>* ws, bool is_active)
{
    static_cast<PerSocketData *>(ws->getUserData())->_is_active = is_active;
}

bool get_websocket_state(uWS::WebSocket<SSL, true>* ws)
{
    return static_cast<PerSocketData *>(ws->getUserData())->_is_active;
}

int main()
{
    
    int port = 3000;
    std::string root = "./html";
    AsyncFileStreamer asyncFileStreamer(root);

    const bool SSL{false};
    std::vector<uWS::WebSocket<SSL, true>*> websockets;

    std::thread t1{[&port, &root, &asyncFileStreamer, &websockets](){
        auto app = uWS::App().get("/*", [&asyncFileStreamer](auto *res, auto *req) {
            //auto url = req->getUrl();
            auto offset = res->getWriteOffset();
            asyncFileStreamer.streamFile(res, req->getUrl());
            if(res->getWriteOffset() == offset)
            {
                res->writeStatus("404 Not Found");
                res->tryEnd("");
                std::cout<<req->getUrl()<<std::endl;
                return;
            }
            serveFile(res, req);
        });

        app.ws<PerSocketData>("/*", {
                /* Settings */
                .compression = uWS::DISABLED,
                .maxPayloadLength = 16 * 1024,
                .idleTimeout = 10,
                .maxBackpressure = 1 * 1024 * 1024,
                /* Handlers */
                .upgrade = [](auto *res, auto *req, auto *context) {
                        res->template upgrade<PerSocketData>({
                        /* We initialize PerSocketData struct here */
                        ._is_active = true,
                        ._id = g_id_counter.fetch_add(1)
                    }, req->getHeader("sec-websocket-key"),
                        req->getHeader("sec-websocket-protocol"),
                        req->getHeader("sec-websocket-extensions"),
                        context);
                },
                .open = [&websockets](auto *ws) {
                    std::cout<<"open ws id "<< get_websocket_id(ws) << std::endl;
                    websockets.push_back(ws);
                },
                .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
                    ws->send(message, opCode);
                    std::cout<<"message from id "<<get_websocket_id(ws)<<" : "<<message<<std::endl;
                },
                .drain = [](auto *ws) {
                    /* Check getBufferedAmount here */
                },
                .ping = [](auto *ws) {

                },
                .pong = [](auto *ws) {

                },
                .close = [](auto *ws, int code, std::string_view message) {
                    set_websocket_state(ws, false);
                    std::cout<<"close ws id "<<get_websocket_id(ws)<< std::endl;
                }
            });

        app.listen(port, [port, root](auto *token) {
            if (token) {
                std::cout << "Serving " << root << " over HTTP a " << port << std::endl;
            }
        }); 

        app.run();
    }};

    drawing drawing_1;
    std::cout<<drawing_1.get_drawing()<<std::endl;

    
    // while(true)
    // {
    //     std::string msg{R"(<svg width="100" height="100">
    //                     <circle cx="50" cy="50" r="40" stroke="black" stroke-width="4" fill="{COLOR}" />
    //                     </svg>)"};

    //     std::string square{R"_(<svg width="400" height="100">
    //                     <rect width="400" height="100" style="fill:{COLOR};stroke-width:10;stroke:rgb(0,0,0)" />
    //                     </svg>)_"};

    //     std::string msg_out;  
    //     int i = std::rand() % 3;



    //     std::cout<<"passed to switch i="<<i<<std::endl;             
    //     switch(i)
    //     {
    //         case 0: msg_out = replace(msg, "{COLOR}", "red");
    //                 break;
    //         case 1: msg_out = replace(square, "{COLOR}", "green");;
    //                 break;
    //         default: msg_out = drawing_1.get_drawing();
    //     }
        
    //     std::cout<<"websocket.size()= "<<websockets.size()<<std::endl;
    //     for(auto w : websockets)
    //     {
    //         if(get_websocket_state(w))
    //         {
    //             w->send(msg_out, uWS::OpCode::TEXT);
    //             std::cout<<"sent to ws: "<<get_websocket_id(w)<<std::endl;
    //         }
    //     }
        
    //     //send(msg, uWS::OpCode::TEXT);
    //     std::this_thread::sleep_for(std::chrono::seconds(5));
    // }

    // std::cout<<"after t1 created\n";
    
    t1.join();
    return 0;
}