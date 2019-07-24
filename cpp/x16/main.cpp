#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <ctime>

using namespace boost;
using namespace std;

void check_error_code(system::system_error &e);
string make_daytime_string();

int main(int argc, char** argv)
{
    
    asio::io_context io_context;
    system::error_code ec;

    uint16_t port_num = 3333;
    asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port_num));

    for(;;)
    {
        asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);
        string message = make_daytime_string();

        asio::write(socket, asio::buffer(message), ec);
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

string make_daytime_string()
{
    time_t now = std::time(0);
    return std::ctime(&now);
}