#include<iostream>
#include<winsock2.h>
#include<ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

bool Initialize(){
    WSADATA data;
    return WSAStartup(MAKEWORD(2,2), &data) == 0;
}

int main(){
    if(!Initialize()){
        cout<<"Initialize Winsock Failed"<<endl;
        return 1;
    }

    // Create a socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == INVALID_SOCKET){
        cout<<"Invalid socket created"<<endl;
        return 1;
    }

    int port = 12345;
    string serveraddress = "127.0.0.1";
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);

    // Use inet_addr instead of inet_pton
    serveraddr.sin_addr.s_addr = inet_addr(serveraddress.c_str());
    if(serveraddr.sin_addr.s_addr == INADDR_NONE){
        cout<<"Invalid IP address"<<endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    // Fix the condition here
    if(connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR){
        cout<<"Server not able to connect"<<endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout<<"Server connected successfully!!"<<endl;

    // Send/receive
    string message = "hello there network lover";
    int bytesSent = send(s, message.c_str(), message.length(), 0);
    if(bytesSent == SOCKET_ERROR){
        cout<<"Sending failed to server"<<endl;
    }

    // Clean up
    closesocket(s);
    WSACleanup();
    return 0;
}


// g++ -o client client.cpp -lws2_32
// .\client.exe

// for server:-
// g++ -o server server.cpp -lws2_32
// ./server.exe