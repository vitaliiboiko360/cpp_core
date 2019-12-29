#include <boost/asio.hpp>

class Client
{
public:
    Client(boost::asio::io_service& io_service, int16_t port)
    : _socket(io_service)
    {}
    
private:
    boost::asio::ip::tcp::socket _socket;
};