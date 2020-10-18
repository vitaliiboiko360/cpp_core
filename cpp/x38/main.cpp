
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/algorithm/string.hpp>
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

uint8_t get_rand_color_value()
{
    return std::rand() % 256;
}

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
        
        const std::string svg = R"_(<svg width="100" height="100"><circle cx="50" cy="50" r="40" style="fill:rgb(0,0,{fill_blue});stroke-width:3;stroke:rgb(0,0,0)"/></svg>)_";
        const std::string rplcmnt = "{fill_blue}";

        int iteration_count{ 0 };
        for(;;)
        {   
            beast::flat_buffer buffer;
            // blocks
            //ws.read(buffer);
            ws.text(ws.got_text());
            // blocks 
            auto msg = boost::algorithm::replace_first_copy(svg, rplcmnt, std::to_string(get_rand_color_value()));
            ws.write(boost::asio::buffer(msg));
            sleep(1);
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
        auto const address = net::ip::make_address("0.0.0.0");
        const uint16_t port = 15000;

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            tcp::socket socket{ioc};

            // block
            acceptor.accept(socket);

            // move socket to session
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