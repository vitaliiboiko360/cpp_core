#include "../../../uWebSockets/src/App.h"
#include "../../../uWebSockets/src/HttpParser.h"
#include "helpers/Middleware.h"
#include "helpers/AsyncFileStreamer.h"
#include <iostream>

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

    app.listen(port, [port, root](auto *token) {
            if (token) {
                std::cout << "Serving " << root << " over HTTP a " << port << std::endl;
            }
        });
    
    app.run();

    return 0;
}