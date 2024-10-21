#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h> // for sockaddr_in, etc.
using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool Initialize(){
    WSADATA data;
    return WSAStartup(MAKEWORD(2,2), &data) == 0;
}

int main(){
    if(!Initialize()){
        cout<<"WinSock initialization failed!!"<<endl;
        return 1;
    }
    cout<<"Server code"<<endl;

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(listenSocket == INVALID_SOCKET){
        cout<<"Socket creation failed!!"<<endl;
        return 1;
    }

    // create address structure:-
    int port=12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port); // host to network

    // Use inet_addr instead of InetPton to convert "0.0.0.0"
    serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    if(serveraddr.sin_addr.s_addr == INADDR_NONE){
        cout<<"Invalid IP address!"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // bind:-
    if(bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR){
        cout<<"bind failed "<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // listen on the port:-
    if(listen(listenSocket, SOMAXCONN)== SOCKET_ERROR){
        cout<<"Cannot listen to port"<<endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    cout<<"Server has started listening on port "<<port<<endl; 

    // start accpeting connection from the client:-
    SOCKET client_Socket=accept(listenSocket, nullptr, nullptr);
    if(client_Socket == INVALID_SOCKET){
        cout<<"invalid client socket"<<endl;
    }

    // receive:-
    char buff[4096];
    int bytes_received=recv(client_Socket, buff, sizeof(buff), 0);
    string message(buff, bytes_received);
    cout<<"Message from client:-"<<message<<endl;

    // close clientsocket;-
    closesocket(client_Socket);
    closesocket(listenSocket);
    // Clean up
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
