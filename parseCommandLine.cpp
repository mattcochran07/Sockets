#include <iostream>

#include <include.h>

void printCommandLineArgs(struct CommandLineArgs& commandLine);
std::string socketType(int socketType);

void parseCommandLine(struct CommandLineArgs& commandLine, std::vector<std::string>& args)
{
    for (unsigned i = 0; i < args.size(); i++)
    {
        if (args[i] == "-send")
        {
            commandLine.tfSend = true;
        }
        else if (args[i] == "-recv")
        {
            commandLine.tfRecv = true;
        }
        else if (args[i] == "-ip")
        {
            commandLine.ip = args[++i];
        }
        else if (args[i] == "-send_port")
        {
            commandLine.sendPort = atoi(args[++i].c_str());
        }
        else if (args[i] == "-recv_port")
        {
            commandLine.recvPort = atoi(args[++i].c_str());
        }
        else if (args[i] == "-udp")
        {
            commandLine.socketType = UDP_SOCKET;
        }
        else if (args[i] == "-tcp_server")
        {
            commandLine.tfTcpServer = true;
        }
        else if (args[i] == "-tcp")
        {
            commandLine.socketType = TCP_SOCKET;
        }
        else if (args[i] == "-h" || args[i] == "--help")
        {
            std::cout << "Command Line options are:" << std::endl;
            std::cout << "\t-send" << std::endl;
            std::cout << "\t-recv" << std::endl;
            std::cout << "\t-ip" << std::endl;
            std::cout << "\t-send_port []" << std::endl;
            std::cout << "\t-recv_port []" << std::endl;
            std::cout << "\t-udp" << std::endl;
            std::cout << "\t-tcp" << std::endl;
        }
    }
    // printCommandLineArgs(commandLine);
}

void printCommandLineArgs(struct CommandLineArgs& commandLine)
{
    std::cout << std::boolalpha << "Command Line Args set to:" << std::endl
              << "tfSend     " << commandLine.tfSend << std::endl
              << "tfRecv     " << commandLine.tfRecv << std::endl
              << "ip         " << commandLine.ip << std::endl
              << "send_port  " << commandLine.sendPort << std::endl
              << "recv_port  " << commandLine.recvPort << std::endl
              << "socketType " << socketType(commandLine.socketType) << std::endl;
}

std::string socketType(int socketType)
{
    switch (socketType)
    {
        case SOCKET_NONE:
            return "";
        case UDP_SOCKET:
            return "UDP";
        case TCP_SOCKET:
            return "TCP";
    }
    return "";
}