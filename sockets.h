#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include <sys/socket.h>


#ifndef SOCKETS_H
#define SOCKETS_H

int do_client(char * addr,int bcast);
int serverUDP(std::string localIp,std::string localBcastIp);
int serverTCP(int portNumber);
void clientTCP(std::string FileNameToDownload,std::string ServerIp,std::string FileNameToSave,int PORTtcp,bool info);
//std::vector <std::string> MyFileList;
//extern struct sockaddr_in myaddr;
//extern struct sockaddr_in remoteaddr;
//socklen_t addr_len;
//int recvlen;
//int fd;
//extern unsigned char buf[BUFSIZE+1];



#endif 
