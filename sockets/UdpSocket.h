#ifndef UDP_SOCKET_H__
#define UDP_SOCKET_H__

#include <string>

#include <WinSock2.h>
#include <Ws2tcpip.h>

#include <sockets/Socket.h>

class UdpSocket : public Socket
{
public:
    UdpSocket(int sendPort, int recvPort, std::string ip);
    ~UdpSocket();

    virtual void sendStr(std::string str);
    virtual std::string recvStr();

protected:

    sockaddr_in dest;
    sockaddr_in local;
};

#endif // UDP_SOCKET_H__