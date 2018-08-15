// g++ sockets.cpp -o test "C:\Compilers\c++\MinGW\lib\libws2_32.a"

#include"mySocket.h"
using namespace std;

int main(){	
	int op,portNo;
	string host,message;
	
	cout<<"Act As Server/Client (1/2) ? ..\n";
	cin>>op;
	
	if(op==1){
		cout<<"Enter Port No.\n";
		cin>>portNo;
		
		MyServer server;
		
		cout<<"Server Started : "<<server.connectTo(portNo)<<"\n";
		cout<<"Listening For Incomming Connections : \n";
		while(true){
			string tmp=server.Listen(portNo);
			cout<<"Client Says : "<<tmp<<"\n";
			//cout<<"Size of buffer : "<<tmp.size()<<"\n";
		}
		server.close();
	}
	else if(op==2){
		cout<<"Enter Host and Port\n";
		cin>>host>>portNo;
		
		MyClient client;
		cout<<"Connected : "<<client.connectTo(host,portNo)<<"\n";
		
		cout<<"Enter Message To Send.. : \n";
		while(true){
			// cin>>message;

			getline(cin, message);
			client.sendMessage(message);
			client.close();
			client.connectTo(host,portNo);
		}
		
		client.close();
	}
	
}
