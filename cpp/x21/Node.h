#include <unistd.h>

void StartNode()
{
    char* argv [] = { "/usr/bin/node", "server.js", (char*)0 };
    char* env [] = { (char*)0 };

    execve(argv[0], argv, env); 
}