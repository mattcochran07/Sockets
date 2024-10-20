#include <iostream>

#include <include.h>
#include <sockets/UdpSocket.h>
#include <sockets/TcpSocketClient.h>
#include <sockets/TcpSocketServer.h>

struct CommandLineArgs commandLine;

int main(int argc, char** argv)
{
    std::vector<std::string> argvVec = argvToVector(argc, argv);
    parseCommandLine(commandLine, argvVec);

    commandLine.tfTcpServer = true;
    Socket* socket;
    if (commandLine.socketType == UDP_SOCKET)
    {
        socket = new UdpSocket(commandLine.sendPort, commandLine.recvPort, commandLine.ip);
    }
    else if (commandLine.socketType == TCP_SOCKET)
    {
        socket = new TcpSocketClient(commandLine.sendPort, commandLine.recvPort, commandLine.ip);
    }
    else if (commandLine.tfTcpServer)
    {
        socket = new TcpSocketServer(commandLine.sendPort, commandLine.recvPort, commandLine.ip);
        std::cout << "tcp socket constructor finished" << std::endl;
    }
    if (!socket) return -1;

    if (commandLine.tfSend)
    {
        std::cout << "sending hello world!" << std::endl;
        socket->sendStr("Hello World");
    }
    else if (commandLine.tfRecv)
    {
        std::string rcvMsg = "";
        while (true)
        {
            rcvMsg = socket->recvStr();
            if (rcvMsg.size() > 1)
                std::cout << "Receive message:\n" << rcvMsg << std::endl;
        }
    }
    else if (commandLine.tfTcpServer)
    {
        std::cout << "Starting tcp server" << std::endl;
        TcpSocketServer* server = dynamic_cast<TcpSocketServer*>(socket);
        server->start();
    }

    delete socket;

    return 0;
}