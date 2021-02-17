#include "../../../uWebSockets/src/App.h"
#include "../../../uWebSockets/src/HttpParser.h"
#include "helpers/Middleware.h"
#include "helpers/AsyncFileStreamer.h"

int main()
{
    int port = 3000;
    std::string root = "./html";
    AsyncFileStreamer asyncFileStreamer(root);

    auto app = uWS::App().get("/*", [&asyncFileStreamer](auto *res, auto *req) {
            
            //auto url = req->getUrl();
            asyncFileStreamer.streamFile(res, req->getUrl());
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