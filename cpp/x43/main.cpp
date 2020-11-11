#include "App.h"

int main()
{
    struct PerSocketData {

    };

    uWS::App().ws<PerSocketData>("/*", {
                /* Settings */
                .compression = uWS::SHARED_COMPRESSOR,
                .maxPayloadLength = 16 * 1024,
                .idleTimeout = 10,
                .maxBackpressure = 1 * 1024 * 1024,
                /* Handlers */
                .open = [](auto *ws) {

                },
                .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
                    std::cout<<message<<std::endl;
                    ws->send(message, opCode);
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
            }).listen(9001, [](auto *token) {
                if (token) {
                    std::cout << "Thread " << std::this_thread::get_id() << " listening on port " << 9001 << std::endl;
                } else {
                    std::cout << "Thread " << std::this_thread::get_id() << " failed to listen on port 9001" << std::endl;
                }
            }).run();

}