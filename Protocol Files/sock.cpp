#include "sock.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <sstream>
#include <arpa/inet.h> //inet_addr
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <unistd.h>

#include <cstring>
using namespace std;

CSocket::CSocket()
{
	len = sizeof(local);
	rlen = sizeof(remote);
}

CSocket::CSocket(int fd)
{
	socket_fd = fd;
	len = sizeof(local);
	rlen = sizeof(remote);
}


int CSocket::SendTCPMessage(char* msg, int msg_size)
{
	return send(socket_fd, msg, msg_size, 0);
}

int CSocket::SendNodeObj(message *msg)///, int msg_size,int error)
{
	return send(socket_fd, msg, 10000, 0);
}


int CSocket::ReceiveTCPMessage(char *buffer, int buffer_size)
{
	int msglen = recv(socket_fd, buffer, buffer_size, 0);
	return msglen;
}

int CSocket::ReceiveNodeObj(message * msg)
{
	int msglen = recv(socket_fd, msg, 10000, 0);
	return msglen;
}


int CSocket::StartTCPServer(int port, int address)
{
	//create socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	
        //setup socket
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr("127.0.0.1");
	local.sin_port = port;
	
        //bind socket to addr
	bind(socket_fd, (struct sockaddr *)&local, len);
	listen(socket_fd, LISTEN_QUEUE_NUMBER);
	
        //return port number
	getsockname(socket_fd, (struct sockaddr *)&local, &len);
	return local.sin_port;
}

CSocket* CSocket::AcceptTCPConnection()
{
	CSocket * new_socket = NULL;
	int accept_connection_fd = accept(socket_fd, (struct sockaddr *)0, (socklen_t*) 0);

	if(accept_connection_fd != -1)
	{
	   new_socket = new CSocket(accept_connection_fd);
	}
	return new_socket;
}

int CSocket::ConnectToTCPServer(int port, char* name)
{
	//create socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	//setup socket
	remote.sin_family = AF_INET;
	hp = gethostbyname(name);
	memcpy(&remote.sin_addr, hp->h_addr, hp->h_length);
	remote.sin_port = port;

	//connect to server
	  if(connect(socket_fd, (struct sockaddr *)&remote,
		sizeof(remote)) < 0)
		{
	//        close(socket_fd);

		return -1;
		} 
	  return 0;
}

int CSocket::CloseSocket()
{
	 close(socket_fd);
	  return 0;
}

/******************** MESSAGE CLASSS ******************************/

message::message()
{
      	message_type = true; 
        //remaining = 100;
      	transmitted = false;
	assigned = 1000;
	consumed = 0;
}

message:: message(int Nid)
{
	ID = Nid;
	message_type = true;
        remaining = 1000;
      	transmitted = false;	
	assigned = 1000;
	consumed = 0;
}
 
void message::set_node(int Nid)
{
	ID = Nid;
}

int message::get_node()
{
	return ID;
}

void message::set_error_type(int error)
{
	err_type = error;
}

int message::get_error()
{
	return err_type;
}

void message::set_message_type(bool error)
{
	message_type=error;
}

bool message::get_message_type()
{
	return message_type;
}

void message::set_transmitted(bool type)
{
	if (type)
  		transmitted = true;
	else
		transmitted = false;
}

int message::get_remaining()
{
	return remaining;
}

int message::remaining_units()
{
	if (transmitted)
		remaining = remaining - consumed;
	return remaining;
}

int message::consumed_units()
{
	if (transmitted)
	{		
		return consumed;
	}
	return 0;
}

void message::set_consumed(int con)
{
	tempconsumed = con;
	consumed += con;
}

int message::get_consumed()
{
	return consumed;
}

int message::get_tempcon()
{
	return tempconsumed;
}


//ED getter
char * message::get_Dnode()
{
	return node.getDmsg();
}

char * message::get_Dmtype()
{
	return mtype.getDmsg();
}

char * message::get_Detype()
{
	return etype.getDmsg();
}

char * message::get_Dunits()
{
	return units.getDmsg();
}

char * message::get_Enode()
{
	return node.getEmsg();
}

char * message::get_Emtype()
{
	return mtype.getEmsg();
}

char * message::get_Eetype()
{
	return etype.getEmsg();
}

char * message::get_Eunits()
{
	return units.getEmsg();
}


//ED setter
void message::set_EDnode(char * e)
{
	node.msg_encrypt(e);
}

void message::set_EDmtype(char * e)
{
	mtype.msg_encrypt(e);
}

void message::set_EDetype(char * e)
{
	etype.msg_encrypt(e);
}

void message::set_EDunits(char * e)
{
	units.msg_encrypt(e);
}

