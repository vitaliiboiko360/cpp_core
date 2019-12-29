#include <boost/asio.hpp>
#include <iostream>

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
  typedef boost::shared_ptr<Connection> pointer;

  static pointer create(boost::asio::io_service& io_service)
  {
    return pointer(new Connection(io_service));
  }

  boost::asio::ip::tcp::socket& socket()
  {
    return _socket;
  }

  void write(const std::string& buffer)
  {
    boost::shared_ptr<std::string> sbuff = std::make_shared<std::string>(buffer);
    boost::asio::async_write(_socket, boost::asio::buffer(sbuff.get()),
        boost::bind(&Connection::handle_write, shared_from_this(),
          sbuff,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  void read()
  {
    boost::shared_ptr<std::string> sbuff = std::make_shared<std::string>(0, 128);
    boost::asio::async_read(_socket, boost::asio::buffer(sbuff.get()),
      boost::bind(&Connection::handle_read, shared_from_this(),
          sbuff,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

private:
  Connection(boost::asio::io_service& io_service)
    : _socket(io_service)
  {
  }

  void handle_write(boost::shared_ptr<std::string> buff, const boost::system::error_code& err, size_t bwritten)
  {
    if (!err)
    {
			if (buff->size() != bwritten)
			{
				write(buff->substr(bwritten, buff->size()));
			}
			else
			{
				read();
			}
    }
    else
    {
      std::cerr << err.message() << std::endl;
    }
  }

  void handle_write(boost::shared_ptr<std::string> buff, const boost::system::error_code& err, size_t bread)
  {
    if (!err)
    {
      std::cout << *buff << std::endl;
    }
    else
    {
      std::cerr << err.message() << std::endl;
    }
  }

  boost::asio::ip::tcp::socket _socket;
};

class Server
{
public:
  Server(boost::asio::io_service &srv)
    : _srv(srv)
    , _socket(srv)
  {}

  void handle_accept(Connection::pointer connection, const boost::system::error_code& error)
  {
    if (!error)
    {
      connection->write("accepted");
    }

    start_accept();
  }

private:
    void start_accept()
    {
        auto connection = Connection::create(_srv);
        _acceptor.async_accept(connection->socket(), boost::bind(&MyServer::handle_accept, this, connection,  boost::asio::placeholders::error));
    }

  boost::asio::io_service &_srv;
  boost::asio::ip::tcp::socket _socket;
  boost::asio::ip::tcp::acceptor _acceptor;
	
};
