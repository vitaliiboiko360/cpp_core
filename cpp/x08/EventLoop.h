
#include "/usr/local/include/boost/asio.hpp"

class EventLoop
{
public:
    void init();
    void run();

private:
    asio::ip::address m_ip_addr = asio::ip::address_v4::any();
    std::unique_ptr<asio::ip::tcp::endpoint> m_p_endpoint;
};