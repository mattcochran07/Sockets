#include <sockets/TcpSocketServer.h>
#include <iostream>

TcpSocketServer::TcpSocketServer(int sendPort, int recvPort, std::string ip) : Socket(sendPort, recvPort, ip)
{

}

TcpSocketServer::~TcpSocketServer()
{
    close();
}

void TcpSocketServer::start()
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET SendSocket = INVALID_SOCKET;
    SOCKET ClientSocket1, ClientSocket2 = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[MAX_BUFFER_SIZE];
    int recvbuflen = MAX_BUFFER_SIZE;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, std::to_string(_recvPort).c_str(), &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }

    // Accept a client socket
    ClientSocket1 = accept(ListenSocket, NULL, NULL);
    if (ClientSocket1 == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, std::to_string(_sendPort).c_str(), &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
    }

    // Create a SOCKET for the server to listen for client connections.
    SendSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
    }

    // Setup the TCP listening socket
    iResult = bind( SendSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
    }

    freeaddrinfo(result);

    iResult = listen(SendSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }

    // Accept a client socket
    ClientSocket2 = accept(SendSocket, NULL, NULL);
    if (ClientSocket2 == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }

    // No longer need server socket
    closesocket(ListenSocket);
    closesocket(SendSocket);

    // Receive until the peer shuts down the connection
    do {

        iResult = recv(ClientSocket1, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

        // Echo the buffer back to the sender
            iSendResult = send( SendSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket1); closesocket(ClientSocket2);
                WSACleanup();
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket1); closesocket(ClientSocket2);            
            WSACleanup();
            return;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket2, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket1); closesocket(ClientSocket2);
        WSACleanup();
    }

    // cleanup
    closesocket(ClientSocket1); closesocket(ClientSocket2);
    WSACleanup();
}

void TcpSocketServer::close()
{

}