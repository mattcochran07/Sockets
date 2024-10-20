#ifndef TCP_SOCKET_H__
#define TCP_SOCKET_H__

#include <ws2tcpip.h>

#include <sockets/Socket.h>

class TcpSocketClient : public Socket
{
public:
    TcpSocketClient(int sendPort, int recvPort, std::string ip);
    ~TcpSocketClient();

    virtual void sendStr(std::string str);
    virtual std::string recvStr();

protected:
    // struct addrinfo hints, *result;
    SOCKET ConnectSocket;

};

#endif // TCP_SOCKET_H__