#include "../../../uWebSockets/src/App.h"
#include "../../../uWebSockets/src/HttpParser.h"
#include "helpers/Middleware.h"
#include "helpers/AsyncFileStreamer.h"
#include <atomic>
#include <vector>
#include <iostream>
#include <string>
#include <regex>

std::atomic<int> g_id_counter{ 1 };

struct PerSocketData {
    int _id{ -1 };
};

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
                        ._id = g_id_counter.fetch_add(1)
                    }, req->getHeader("sec-websocket-key"),
                        req->getHeader("sec-websocket-protocol"),
                        req->getHeader("sec-websocket-extensions"),
                        context);
                },
                .open = [&websockets](auto *ws) {
                    std::cout<<"open ws id "<< static_cast<PerSocketData *>(ws->getUserData())->_id << std::endl;
                    websockets.push_back(ws);
                },
                .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
                    ws->send(message, opCode);
                    std::cout<<"message "<<message<<std::endl;
                },
                .drain = [](auto *ws) {
                    /* Check getBufferedAmount here */
                },
                .ping = [](auto *ws) {

                },
                .pong = [](auto *ws) {

                },
                .close = [](auto *ws, int code, std::string_view message) {
                    std::cout<<"close ws id "<<static_cast<PerSocketData *>(ws->getUserData())->_id << std::endl;
                }
            });

        app.listen(port, [port, root](auto *token) {
            if (token) {
                std::cout << "Serving " << root << " over HTTP a " << port << std::endl;
            }
        }); 

        app.run();
    }};
    
    // while(true)
    // {
    //     std::string msg{R"(<svg width="100" height="100">
    //                     <circle cx="50" cy="50" r="40" stroke="green" stroke-width="4" fill="{COLOR}" />
    //                     </svg>)"};
    //     std::string msg_out;               
    //     switch(std::rand() % 3)
    //     {
    //         case 0: msg_out = R"(<svg width="100" height="100">
    //                     <circle cx="50" cy="50" r="40" stroke="green" stroke-width="4" fill="red" />
    //                     </svg>)";
    //         case 1: msg_out = R"(<svg width="100" height="100">
    //                     <circle cx="50" cy="50" r="40" stroke="green" stroke-width="4" fill="green" />
    //                     </svg>)";
    //         default: msg_out = R"(<svg width="100" height="100">
    //                     <circle cx="50" cy="50" r="40" stroke="green" stroke-width="4" fill="blue" />
    //                     </svg>)";
    //     }
        
    //     for(auto& w : websockets)
    //     {
    //         w->send(msg_out, uWS::OpCode::TEXT);
    //     }
    //     //send(msg, uWS::OpCode::TEXT);
    //     std::this_thread::sleep_for(std::chrono::duration<double>(1000));
    // }

    std::cout<<"after t1 created\n";
    
    t1.join();
    return 0;
}