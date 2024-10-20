#include <sockets/UdpSocket.h>

#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

UdpSocket::UdpSocket(int sendPort, int recvPort, std::string ip) : Socket(sendPort, recvPort, ip)
{
    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data);

    local.sin_family = AF_INET;
    inet_pton(AF_INET, _ip.c_str(), &local.sin_addr.s_addr);
    local.sin_port = htons(recvPort);

    dest.sin_family = AF_INET;
    inet_pton(AF_INET, _ip.c_str(), &dest.sin_addr.s_addr);
    dest.sin_port = htons(sendPort);

    _socketConn = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bind(_socketConn, (sockaddr *)&local, sizeof(local));
}

UdpSocket::~UdpSocket()
{
    WSACleanup();
    closesocket(_socketConn);
}

void UdpSocket::sendStr(std::string msg)
{
    sendto(_socketConn, msg.c_str(), msg.size(), 0, (sockaddr *)&dest, sizeof(dest));   
}

std::string UdpSocket::recvStr()
{
    char recvBuffer[MAX_BUFFER_SIZE];
    // memcpy(recvBuffer, 0, MAX_BUFFER_SIZE);
    int sizeofLocal = sizeof(local);
    recvfrom(_socketConn, recvBuffer, MAX_BUFFER_SIZE, 0, (sockaddr*)&local, &sizeofLocal);
    return recvBuffer;
}