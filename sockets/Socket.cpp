#include <sockets/Socket.h>

Socket::Socket(int sendPort, int recvPort, std::string ip)
{
    _sendPort = sendPort;
    _recvPort = recvPort;
    _ip = ip;
}

Socket::~Socket()
{

}

void Socket::sendStr(std::string msg)
{

}

std::string Socket::recvStr()
{
    return "";
}