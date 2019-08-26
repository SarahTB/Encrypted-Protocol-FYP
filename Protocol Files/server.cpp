#include<iostream>
#include <string>
#include"sock.cpp"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

using namespace std;

int main()
{
	char *server_name_str = "127.0.0.2";
	unsigned short int tcp_server_port = 3999;
        char temp[256];
        int random=0;

	int port = 2999;
	int ip_address = 1; 

	char nodeID[100];
	int node;
        int r;
	int units = 0;

        //clear buffer
	memset(temp,'\0',sizeof(temp));
	memset(nodeID,'\0',sizeof(nodeID));

        //Begin listening
	CSocket * TCPServer = new CSocket();
	TCPServer->StartTCPServer(port, ip_address);

        //Accept connection
	message incoming_message;


	
	random = 0;
	r = 0; 
	//node = 0;

		CSocket* pc_connection = TCPServer->AcceptTCPConnection();


	while(1)
	{
	        // recieve nodeID 
	        pc_connection->ReceiveNodeObj(&incoming_message);
	       
		//node=incoming_message.get_node();				
		cout<< "Encrypted node received: "<<incoming_message.get_Enode()<<endl;		
		cout<<"node ID(After decryption): "<<incoming_message.get_node()<<endl;
	
		
		cout<< "Calculations after decrypting rest of the packet: "<<endl;

		cout << "Units Assigned = 1000" << endl;
		
		random=incoming_message.get_message_type();	        

		//Send connect_ok message
		if(random == 0)
		{
			strcpy(temp,"Successfully Transmitted");
	                incoming_message.set_transmitted(true);
	                pc_connection->SendTCPMessage(temp,sizeof(temp));
	        	memset(temp,'\0',sizeof(temp));
	 		  
			units = incoming_message.get_tempcon();		
			cout << "Units consumed in this session: " << units << endl;


			units = incoming_message.consumed_units();		
			cout << "Total units consumed: " << units << endl;


			r = incoming_message.remaining_units();		
			cout << "Remaining units: " << r << endl;


			cout << endl << endl << endl;
		}
		else 
	        {
	                incoming_message.set_transmitted(false);
			
			random = incoming_message.get_error();
			
			if (random==0)
			{ 
				strcpy(temp,"faulty meter");
				cout << "Error type: " << temp << endl;
			}
			else if (random==1)
			{
				strcpy(temp,"retrieved units are more than recorded");
				cout << "Error type: " << temp << endl;
			}
			else if (random==2)
			{
				strcpy(temp,"connectivity issue");
				cout << "Error type: " << temp << endl;
			}

			memset(temp,'\0',sizeof(temp));

			cout<< endl << endl << endl;
		}
	}

}
