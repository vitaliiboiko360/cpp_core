#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <cstdlib>

using namespace boost;
using namespace std;

void check_error_code(system::error_code &e);

int main(int argc, char* argv[])
{
    
    if(argc != 2)
    {
        cerr << "Usage: client <host>" << endl;
        return 1;
    }

    system::error_code ec;
    uint16_t port_num = 3333;

    asio::io_context io_context;
    asio::ip::tcp::socket socket(io_context);
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "3333", ec);
    check_error_code(ec);

    asio::connect(socket, endpoints, ec);
    check_error_code(ec);

    for(;;)
    {
        array<char, 128> buffer;
        size_t len = socket.read_some(asio::buffer(buffer), ec);
        if(ec == asio::error::eof)
            break; // Connection closed cleanly by peer.
        else
            check_error_code(ec);
        
        cout.write(buffer.data(), len);
    }

    return 0;
}

void check_error_code(system::error_code &e)
{
    if(e.value() != 0)
    {
        cout
            << "er code= " << e.value() << "\n"
            << "message= " << e.message() << endl;
        exit(e.value());
    }
    return;
}