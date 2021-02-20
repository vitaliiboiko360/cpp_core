#include "../../../uWebSockets/src/App.h"
#include "../../../uWebSockets/src/HttpParser.h"
#include "helpers/Middleware.h"
#include "helpers/AsyncFileStreamer.h"
#include <atomic>
#include <iostream>
#include <string>

std::atomic<int> g_id_counter{ 1 };

struct PerSocketData {
    int _id{ -1 };
};

int main()
{
    int port = 3000;
    std::string root = "./html";
    AsyncFileStreamer asyncFileStreamer(root);

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
            .open = [](auto *ws) {
                std::cout<<"open ws id "<< static_cast<PerSocketData *>(ws->getUserData())->_id << std::endl;
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

            }
        });

    app.listen(port, [port, root](auto *token) {
        if (token) {
            std::cout << "Serving " << root << " over HTTP a " << port << std::endl;
        }
    }); 

    app.run();

    return 0;
}