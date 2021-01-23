#include "../../../uWebSockets/src/App.h"
#include "../../../uWebSockets/examples/helpers/Middleware.h"
#include "../../../uWebSockets/examples/helpers/AsyncFileStreamer.h"

int main()
{
    int port = 3000;
    std::string root = ".";
    AsyncFileStreamer asyncFileStreamer(root);

    auto app = uWS::App().get("/*", [&asyncFileStreamer](auto *res, auto *req) {
            serveFile(res, req);
            asyncFileStreamer.streamFile(res, req->getUrl());
        });

    app.listen(port, [port, root](auto *token) {
            if (token) {
                std::cout << "Serving " << root << " over HTTP a " << port << std::endl;
            }
        });
    
    app.run();


}