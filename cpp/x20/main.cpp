#include <impl/CmdArgs.h>
#include <impl/Server.h>
#include <impl/Client.h>
#include <boost/asio.hpp>

int main(int argc, char argv[])
{
    CmdArgs args(argc, argv);

    if(args.GetType() == CmdArgs::ApplicationType::Client)
    {
        Client client(argv[1]);
        return client.run();
    }

    if(args.GetType() == CmdArgs::ApplicationType::Server)
    {
        boost::
        Server server(argv[1], argv[2]);
        return server.run();
    }

    return 0;
}