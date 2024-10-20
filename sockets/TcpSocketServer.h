#ifndef TCP_SOCKET_SERVER_H__
#define TCP_SOCKET_SERVER_H__

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include <sockets/Socket.h>

class TcpSocketServer : public Socket
{
public:
    TcpSocketServer(int sendPort, int recvPort, std::string ip);
    ~TcpSocketServer();

    virtual void start();
    virtual void close();

protected:
    SOCKET _listenSocket;
    SOCKET _clientSocket;
    struct addrinfo *result, hints;
};

#endif // TCP_SOCKET_SERVER_H__