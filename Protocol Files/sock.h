#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> //inet_addr
#define LISTEN_QUEUE_NUMBER 255
/*****************************************************************
*Name: CSocket
*Description: Makes using Berkeley sockets easy.
*****************************************************************/


using namespace std;


//Encryption

class encryption
{
private:
int x, y, n, t, i, flag;
long int e[50], d[50], temp[50], j;
char en[50], m[50];
char msg[100];
char emsg[100];
char dmsg[100];

//function to check for prime number
int prime(long int pr)
{
   int i;
   j = sqrt(pr);
   for(i = 2; i <= j; i++)
   {
      if(pr % i == 0)
         return 0;
   }
   return 1;
 }



//function to generate encryption key
void encryption_key()
{
   int k;
   k = 0;
   for(i = 2; i < t; i++)
   {
      if(t % i == 0)
         continue;
      flag = prime(i);
      if(flag == 1 && i != x && i != y)
      {
         e[k] = i;
         flag = cd(e[k]);
         if(flag > 0)
         {
            d[k] = flag;
            k++;
         }
         if(k == 99)
         break;
      }
   }
}


long int cd(long int a)
{
   long int k = 1;
   while(1)
   {
      k = k + t;
      if(k % a == 0)
         return(k/a);
   }
}

//function to encrypt the message
void encrypt()
{
   long int pt, ct, key = e[0], k, len;
   i = 0;
   len = strlen(msg);

   while(i != len)
   {
      pt = m[i];
      pt = pt - 96;
      k = 1;
      for(j = 0; j < key; j++)
      {
         k = k * pt;
         k = k % n;
      }
      temp[i] = k;
      ct= k + 96;
      en[i] = ct;
      i++;
   }
   en[i] = -1;
   //cout << "\n\nTHE ENCRYPTED MESSAGE IS\n";

	int counter = 0;

   for(i=0; en[i] != -1; i++)
   {
	emsg[i] = en[i];
	counter++;
	//cout << en[i];
   }

	emsg[counter] = '\0';

}


//function to decrypt the message
void decrypt()
{
   long int pt, ct, key = d[0], k;
   i = 0;
   while(en[i] != -1)
   {
      ct = temp[i];
      k = 1;
      for(j = 0; j < key; j++)
      {
         k = k * ct;
         k = k % n;
      }
      pt = k + 96;
      m[i] = pt;
      i++;
   }
   m[i] = -1;

   //cout << "\n\nTHE DECRYPTED MESSAGE IS\n";


	int counter = 0;

   for(i=0; m[i] != -1; i++)
   {
	dmsg[i] = m[i];
	counter++;
	//cout << en[i];
   }

	dmsg[counter] = '\0';
   
  //cout << endl;
}



public:


void msg_encrypt(char * Omsg)
{
	for(i = 0; Omsg[i] != NULL; i++)
      		msg[i] = Omsg[i];

   //cout << "\nENTER FIRST PRIME NUMBER\n";
   //cin >> x;
	x = 7;
   
   //checking whether input is prime or not
   flag = prime(x);
   if(flag == 0)
   {
      cout << "\nINVALID INPUT\n";
      exit(0);
   }

   //cout << "\nENTER SECOND PRIME NUMBER\n";
   //cin >> y;
	y = 13;
   
   flag = prime(y);
   if(flag == 0 || x == y)
   {
      cout << "\nINVALID INPUT\n";
      exit(0);
   }

   //cout << "\nENTER MESSAGE OR STRING TO ENCRYPT\n";
   //cin >> msg;

   for(i = 0; msg[i] != NULL; i++)
      m[i] = msg[i];
   n = x * y;
   t = (x - 1) * (y - 1);

   encryption_key();
   //cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";

   //for(i = 0; i < j - 1; i++)
      //cout << "\n" << e[i] << "\t" << d[i];

   encrypt();
   decrypt();
   
} //end of the main program



char * getEmsg()
{
	return emsg;
}

char * getDmsg()
{
	return dmsg;
}





};













//Message
class message
{
private:
	bool message_type;
	int err_type;
	int ID;
	int remaining;
	int consumed;
	bool transmitted;
	int assigned;
	int tempconsumed;
	encryption node;
	encryption mtype;
	encryption etype;
	encryption units;
	
public:
	message();
	message(int node);
	int get_remaining();
	int get_node();
	int get_error();
	bool get_message_type();
	int get_consumed();
	int get_tempcon();
	char * get_Dnode();
	char * get_Dmtype();
	char * get_Detype();
	char * get_Dunits();
	char * get_Enode();
	char * get_Emtype();
	char * get_Eetype();
	char * get_Eunits();

	void set_node(int id);  // set node id
	void set_error_type(int error);
	void set_transmitted(bool t);
	void set_message_type(bool set);
	void set_consumed(int con);
	void set_EDnode(char * e);
	void set_EDmtype(char * e);
	void set_EDetype(char * e);
	void set_EDunits(char * e);
	
	int consumed_units();
	int remaining_units();
};



class CSocket
{
private:
int socket_fd;
sockaddr_in remote;
sockaddr_in local;
char buf[10000];
char retbuf[10000];
socklen_t len;
socklen_t rlen;
hostent *hp;

public:

CSocket();
CSocket(int fd);
//˜CSocket();
int SendTCPMessage(char* msg, int msg_size);
int StartTCPServer(int port, int address);
CSocket* AcceptTCPConnection();
int ConnectToTCPServer(int port, char* name);
int ReceiveTCPMessage(char *buffer, int buffer_size);
int CloseSocket();
int SendNodeObj(message *msg);
int ReceiveNodeObj(message *msg);
};



enum message_type {CONNECT_OK = 1, TRACK = 10, TRACK_CONFIRM =
15, STOP = 20, STOP_CONFIRM = 25, SUCCESS = 30, FAILURE =
40, QUIT = 50};



void toString(char*str,int n);


