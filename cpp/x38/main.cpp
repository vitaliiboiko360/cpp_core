#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <locale>
#include <string>
#include <thread>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Echoes back all received WebSocket messages
void
do_session(tcp::socket socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-sync");
            }));

        // Accept the websocket handshake
        ws.accept();
        auto& f = std::use_facet<std::ctype<char>>(std::locale());
        int iteration_count{ 0 };
        for(;;)
        {
            // This buffer will hold the incoming message
            beast::flat_buffer buffer;

            // Read a message
            ws.read(buffer);
            char* p = static_cast<char*>(buffer.data().data());

            for(int i=0; i<buffer.size(); i++)
            {   
                p[i] = f.toupper(p[i]);
            }
            // Echo the message back
            ws.text(ws.got_text());
            ws.write(buffer.data());

            std::cout<<"#"<<iteration_count++<<"iter ended\n";
        }
    }
    catch(beast::system_error const& se)
    {
        // This indicates that the session was closed
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    try
    {
        // Check command line arguments.
        // if (argc != 3)
        // {
        //     std::cerr <<
        //         "Usage: websocket-server-sync <address> <port>\n" <<
        //         "Example:\n" <<
        //         "    websocket-server-sync 0.0.0.0 8080\n";
        //     return EXIT_FAILURE;
        // }
        auto const address = net::ip::make_address("0.0.0.0");
        const uint16_t port = 15000;

        // The io_context is required for all I/O
        net::io_context ioc{1};

        // The acceptor receives incoming connections
        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread(
                &do_session,
                std::move(socket)).detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}