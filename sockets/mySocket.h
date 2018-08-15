#include<winsock2.h>
#include<windows.h>
#include<iostream>
using namespace std;


struct MyServer{
	WSADATA wsadata;
	SOCKET serverSocket,clientSocket;
	SOCKADDR_IN serverAddr,clientAddr;
	
	bool connectTo(int portNo){
		int error=WSAStartup(0x0202,&wsadata);
		if(error){
			return false;
		}if(wsadata.wVersion != 0x0202){
			WSACleanup();
			return false;
		}
		
		serverSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
		serverAddr.sin_family=AF_INET;
		serverAddr.sin_port=htons(portNo);
		if(serverSocket==INVALID_SOCKET){
			return false;
		}
		
		if(bind(serverSocket,(SOCKADDR*)&serverAddr,sizeof(serverAddr)) == SOCKET_ERROR){
			return false;
		}
		
		listen(serverSocket,SOMAXCONN);
		
		return true;
	}
	
	string Listen(int portNo){
		//cout<<"Listening for Incoming Connections...\n";
		
		char buffer[2048];
		memset(buffer,'\0',sizeof(buffer));
		int clientAddrLen=sizeof(clientAddr);
		
		if((clientSocket=accept(serverSocket,(SOCKADDR*)&clientAddr,&clientAddrLen))!=INVALID_SOCKET){
		
			//cout<<"Client Connected...\n";
			int sz=recv(clientSocket,buffer,2048,0);
//			cout<<"Client Says : "<<buffer<<"\n";
			
			return string(buffer);
		}
	
		return "-1";
		
	}
	
	void close(){
		closesocket(clientSocket);
	}
};

struct MyClient{
	WSADATA wsadata;
	SOCKET serverSocket;
	SOCKADDR_IN serverAddr;
	
	bool connectTo(string ipAddress,int portNo){
		
		int error=WSAStartup(0x0202,&wsadata);
		if(error){
			return false;
		}if(wsadata.wVersion!=0x0202){
			WSACleanup();
			return false;
		}
		
		serverSocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		serverAddr.sin_addr.s_addr=inet_addr(ipAddress.c_str());
		serverAddr.sin_family=AF_INET;
		serverAddr.sin_port=htons(portNo);
		
		if(serverSocket==INVALID_SOCKET){
			return false;
		}
		if(connect(serverSocket,(SOCKADDR*)&serverAddr,sizeof(serverAddr))==SOCKET_ERROR){
			return false;
		}
		return true;
	}
	
	bool sendMessage(string msg){
		return send(serverSocket,msg.c_str(),msg.size(),0);
	}
	
	void close(){
		closesocket(serverSocket);
		WSACleanup();
		//cout<<"Socket Closed\n";
	}
		
};


