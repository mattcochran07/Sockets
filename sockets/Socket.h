#ifndef SOCKET_H__
#define SOCKET_H__

#include <WinSock2.h>
#include <Ws2tcpip.h>

#include <string>

class Socket
{
public:
    Socket(int sendPort, int recvPort, std::string ip);
    ~Socket();

    virtual void sendStr(std::string str);
    virtual std::string recvStr();

    const int MAX_BUFFER_SIZE = 1024;

protected:
    int _sendPort;
    int _recvPort;
    std::string _ip;
    SOCKET _socketConn;
};

#endif // SOCKET_H__