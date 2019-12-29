#include <cstdlib>
#include <cctype>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

// using boost::asio::ip::tcp;

// class session
//   : public std::enable_shared_from_this<session>
// {
// public:
//   session(tcp::socket socket)
//     : socket_(std::move(socket))
//   {
//   }

//   void start()
//   {
//     do_read();
//   }

// private:
//   void do_read()
//   {
//     auto self(shared_from_this());
//     socket_.async_read_some(boost::asio::buffer(data_, max_length),
//         [this, self](boost::system::error_code ec, std::size_t length)
//         {
//           if (!ec)
//           {
//             do_write(length);
//           }
//         });
//   }

//   void do_write(std::size_t length)
//   {
//     do_upper_case(length);
//     auto self(shared_from_this());
//     boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
//         [this, self](boost::system::error_code ec, std::size_t /*length*/)
//         {
//           if (!ec)
//           {
//             do_read();
//           }
//         });
//   }

//   void do_upper_case(std::size_t length)
//   {
//       int i = 0;
//       while(data_[i])
//       {
//           data_[i] = std::toupper(data_[i]);
//           ++i;
//           if(i == length)
//           {
//             //std::cout<<"LOG: do_upper_case: counter was hit "<<i<<" times\n";
//             break;
//           }
//       }
//       std::cout<<"LOG: do_upper_case(length= "<<length<<") \n";
//   }

//   tcp::socket socket_;
//   enum { max_length = 1024 };
//   char data_[max_length];
// };

// class server
// {
// public:
//   server(boost::asio::io_context& io_context, short port)
//     : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
//   {
//     do_accept();
//   }

// private:
//   void do_accept()
//   {
//     acceptor_.async_accept(
//         [this](boost::system::error_code ec, tcp::socket socket)
//         {
//           if (!ec)
//           {
//             std::make_shared<session>(std::move(socket))->start();
//           }

//           do_accept();
//         });
//   }

//   tcp::acceptor acceptor_;
// };

// int main(int argc, char* argv[])
// {
//   try
//   {
//     if (argc != 2)
//     {
//       std::cerr << "Usage: async_tcp_echo_server <port>\n";
//       return 1;
//     }

//     boost::asio::io_context io_context;

//     server s(io_context, std::atoi(argv[1]));

//     io_context.run();
//   }
//   catch (std::exception& e)
//   {
//     std::cerr << "Exception: " << e.what() << "\n";
//   }

//   return 0;
// }

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

class MyServer
{
public:
  MyServer(oost::asio::io_service &srv)
    : _srv(srv)
    , _socket(srv)
  {

  }

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
      _acceptor.async_accept(connection->socket(), boost::bind(&MyServer::handle_accept, this,      connection,  boost::asio::placeholders::error));
    }

  boost::asio::io_service &_srv;
  boost::asio::ip::tcp::socket _socket;
  boost::asio::ip::tcp::acceptor _acceptor;
};

class MyClient
{

};

int main()
{
  boost::asio::io_service srv;

  std::thread server_thread([&srv]()
  { 
      MyServer server(srv);
      for (server.has_connections());
      connection = get_connection();

      connection->write("");
      connection->read();
  });
  
  std::thread client_thread([&srv]()
  { 
      MyClient client(srv);
      client.write();
      client.read();
  });

  int ret = srv.run();

  server_thread.join();
  client_thread.join();

  return;
}