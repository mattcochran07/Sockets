#ifndef INCLUDE_H__
#define INCLUDE_H__

#include <vector>
#include <string>

enum SocketTypes
{
    SOCKET_NONE,
    UDP_SOCKET,
    TCP_SOCKET,
    NUM_SOCKET_TYPES
};

struct CommandLineArgs
{
    int sendPort;
    int recvPort;
    std::string ip;
    bool tfSend;
    bool tfRecv;
    int socketType;
    bool tfTcpServer;

    CommandLineArgs()
    {
        sendPort = 5005;
        recvPort = 5005; // ports much match to send stream through
        ip = "127.0.0.1";
        tfSend = false;
        tfRecv = false;
        socketType = SOCKET_NONE;
        tfTcpServer = false;
    }
};

std::vector<std::string> argvToVector(int argc, char** argv);
void parseCommandLine(struct CommandLineArgs& commandLine, std::vector<std::string>& args);

#endif // INCLUDE_H__