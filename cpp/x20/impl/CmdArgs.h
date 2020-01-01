
#include <string>
#include <vector>
#include <map>
#include <cstdlib>

class CmdArgs
{
public:
    CmdArgs(int argc, char argv[])
    {
        if(argc < 3)
            PrintUsageToConsole();
        ParseCmdArgs(argc, argv);
    }

    void PrintUsageToConsole(); 
    void PrintUsageToConsole(const char * cStrMessage); 

    std::vector<std::string>& GetParam()
    {
        return m_Arguments;
    }

    enum class ApplicationType
    {
        Unknown,
        Server,
        Client
    };
    
    ApplicationType GetType() const
    {
        return m_type;
    }
    
    

private:
    std::vector<std::string> m_Arguments;

    uint16_t m_port;
    std::string m_host;
    ApplicationType m_type{ ApplicationType::Unknown };

    void ParseCmdArgs(int argc, char argv[])
    {
        for(int i=1; i<argc; ++i)
            m_Arguments.push_back({argv[i]});

        if(m_Arguments.size() < 2)
            PrintUsageToConsole();

        if(m_Arguments[1] == "-c")
            m_type = ApplicationType::Client;
        else if(m_Arguments[1] == "-s")
            m_type = ApplicationType::Server;
        else
            PrintUsageToConsole("Invalid First Argument");

        if(m_type == ApplicationType::Server)
            m_host = m_Arguments[2];
        
        if(m_type == ApplicationType::Client)
            m_port = std::atoi(m_Arguments[2].c_str());
        
    }
};