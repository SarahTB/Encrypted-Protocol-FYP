#include<iostream>
#include"sock.cpp"
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>


int main()
{
        //Connect to localhost on port 9999  
	char *server_name_str = "127.0.0.1";
	unsigned short int tcp_server_port = 2999;
        char temp[256];
        int random=0;
       
	//encryption E;

        memset(temp,'\0',sizeof(temp));

	
     	//Connect to the server
	CSocket* TCPClientSocket = new CSocket();
	TCPClientSocket->ConnectToTCPServer(tcp_server_port,server_name_str);

	//Set nodeID
	srand(time(NULL));
        random=rand()%100;


        message msg(random);
        //msg.set_node(random);

	char buffer[100];
	//itoa(random, buffer,10);
	sprintf(buffer, "%d", random);
	msg.set_EDnode(buffer);

        cout<<"node id: "<<msg.get_node() <<endl;
	cout<< "encrypted node id sent: "<<msg.get_Enode()<<endl;

while(1)
{
        random=0;
        srand(time(NULL));
        random=rand()%2;
        
	char buffer1[100];
	//itoa(random, buffer1,10);
	sprintf(buffer1, "%d", random);
	msg.set_EDmtype(buffer1);

        msg.set_message_type(random);
        cout<< "message type: "<<msg.get_message_type()<<endl;
	cout<< "encrypted message type sent: "<<msg.get_Emtype()<<endl;
        
         
        if(random==1)
        {
		srand(time(NULL));
        	random=rand()%3;

		char buffer2[100];
		//itoa(random, buffer2,10);
		sprintf(buffer2, "%d", random);
		msg.set_EDetype(buffer2);

        	msg.set_error_type(random);
		cout<<"error type: "<<msg.get_error()<<endl;
		cout<< "encrypted error type sent: "<<msg.get_Eetype()<<endl;
	}
	else
	{
		random=0;
	        srand(time(NULL));
	        random=rand()%20;
	         
		char buffer3[100];
		//itoa(random, buffer3,10);
		sprintf(buffer3, "%d", random);
		msg.set_EDunits(buffer3);

	        msg.set_consumed(random);
	        cout<< "units consumed: "<<random<<endl;
		cout<< "encrypted units consumed sent: "<<msg.get_Eunits()<<endl;
	}
         
        //Send nodeID   
        TCPClientSocket->SendNodeObj(&msg);
   
	cout << endl << endl;	

	sleep(30);

}
	
	TCPClientSocket->CloseSocket();

}
