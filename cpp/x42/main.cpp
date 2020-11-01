
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

const int Y_MAX = 600;
const int X_MAX = 800;
const std::string svg = {R"_(<svg height="600" width="800">
                <g>
                    <defs>
                        <radialGradient id="grad1" cx="50%" cy="50%" r="50%" fx="50%" fy="50%">
                        <stop offset="0%" style="stop-color:rgb(255,255,255);
                        stop-opacity:0" />
                        <stop offset="100%" style="stop-color:rgb(0,0,255);stop-opacity:1" />
                        </radialGradient>
                    </defs>
                    <ellipse cx="{CX}" cy="{CY}" rx="85" ry="55" fill="url(#grad1)" />
                    <text x="{CX}" y="{CY}" fill="black">{TEXT}</text>
                </g>
                </svg>)_"};

int get_rand_value(int upper_limit)
{
    return std::rand() % upper_limit;
}

std::vector<std::pair<int, int>> xy = {{400, 200}, {600, 400}, {400, 600}, {200, 400}};

bool replace(std::string& str, const std::string& from, const std::string& to) 
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replace_all(std::string& str, const std::string& from, const std::string& to) 
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
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

        char i{ 0 };
        uint64_t count{ 0 };
        for(;;)
        {   
            beast::flat_buffer buffer;
            // blocks
            //ws.read(buffer);
            ws.text(ws.got_text());

            i >= 4 ? i=0 : i=i;

            auto msg{ svg };
            replace_all(msg, "{CY}", std::to_string(xy[i].first));
            replace_all(msg, "{CX}", std::to_string(xy[i].second));
            replace(msg, "{TEXT}", std::to_string(count++));

            // blocks 
            ws.write(boost::asio::buffer(msg));

            i += 1;
            sleep(1);
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