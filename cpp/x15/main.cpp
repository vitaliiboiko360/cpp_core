#include <string>
#include <iostream>
#include "/usr/local/include/boost/asio.hpp"

int main()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    boost::system::error_code ec;

    boost::asio::ip::address ip_address = 
        boost::asio::ip::address::from_string(raw_ip_address, ec);

    if(ec.value() != 0)
    {
        std::cout 
            << "failed to parse the ip address: "
            << ec.value() << ". message: "<<ec.message();
        return ec.value();
    }

    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

    std::cout<<"wow\n";
    return 0;
}