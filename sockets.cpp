#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>          
#include "utils.h"
#include "sockets.h"
#include <cstring>
#include <sstream>
#include <ctype.h>

#define MAXRCVLEN 1000
#define PORTNUM 9000
using namespace std;

int do_client(char * addr, int bcast){ 
    char buffer[MAXRCVLEN + 1]; /* +1 so we can add null terminator */
    int len, mysocket;
    vector <string> AllIp2;
    struct sockaddr_in dest;

    struct hostent *hostinfo;

    hostinfo = gethostbyname (addr);

    if (hostinfo == 0)
    {
        perror("Couldn't find destination address\n");
        exit (1);
    }else{
       // printf("Found destination address\n");
    }

    mysocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (mysocket < 0){
       perror("Socket creation failed");
       exit(3);
    }

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (setsockopt (mysocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
               sizeof(timeout)) < 0){
       perror("setsockopt failed\n");
       exit(2);
    }

    if(bcast){
        int optval = 1;
        int response = setsockopt(mysocket, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
        if (response < 0){
           perror("setsockopt failed (for broadcast)\n");
           exit(2);
        }
    }

    memset(&dest, 0, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_addr = *(struct in_addr *) hostinfo->h_addr;
    dest.sin_port = htons(PORTNUM);

    string message;
    AllIp2.clear(); //czyszczenie listy ip przed wpisaniem aktualnej
    message = 'I'; //zapytanie o ip
    sendto(mysocket, message.c_str(), message.size(), 0, (const sockaddr*) &dest, sizeof(dest));
      int pid=fork();
      while(1)
      {
      memset(buffer,0,sizeof buffer);
      len = recv(mysocket, buffer, MAXRCVLEN, 0);
      buffer[len] = '\0';
      if(len > 0){
	AllIp2 = LoadList(".iplist");
	AllIp2.push_back(buffer);//dodawanie ip z buffora do wektora
	CreateList(AllIp2, ".iplist");
        memset(buffer,0,sizeof buffer);
      }
      else
      {
	if(pid==0)
	close(mysocket);
	memset(buffer,0,sizeof buffer);

	break;   
      }
     }
     AllIp2 = LoadList(".iplist");
     AllIp2 = EraseDuplicates(AllIp2);
     CreateList(AllIp2,".iplist");
     memset(buffer,0,sizeof buffer);
     if(pid==0)
       exit(0);
     
     sleep(2); //oczekiwanie na odebranie wszystkich adresów ip przez przez procesy działające w tle, czas w sekundach
      
    close(mysocket);
    return 0;
}
//funkcja zwracająca komentarz błędu
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int serverUDP(string localIp, string localBcastIp)
{
    //definicje zmiennych
    int BUFSIZE = 2048;
    int PORT = 9000;
    vector <string> MyFileList; 
    string myIp=localIp;
    string myBcastIp=localBcastIp;
    struct sockaddr_in myaddr;
    struct sockaddr_in remoteaddr;
    socklen_t addr_len;
    int recvlen;
    int fd;
    unsigned char buf[BUFSIZE+1];

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("cannot create socket\n");
        return 1;
    }

    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
        perror("bind failed");
        return 2;
    }
    string message;
    //komunikacja z klientem
    while(true){
        //printf("waiting on port %d\n", PORT);
        memset((char *)&remoteaddr, 0, sizeof(remoteaddr));
        addr_len = sizeof(remoteaddr);
  recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remoteaddr, &addr_len);
  buf[recvlen] = '\0';
  
  
  message = myIp;//wysłanie lokalnego ip
        sendto(fd, message.c_str(), message.size(), 0, (struct sockaddr *)&remoteaddr, addr_len);
  
  if(buf[0]=='I') //Zapytanie o ip
  {
        message = myIp;//wysłanie lokalnego ip
        sendto(fd, message.c_str(), message.size(), 0, (struct sockaddr *)&remoteaddr, addr_len);
  }
  
  }
  
  }

  int serverTCP(int portNumber)
{
  int PORT = portNumber;
  int LENGTH = 512;
  int BACKLOG = 5;
  /* Defining Variables */
  int sockfd; 
  int nsockfd; 
  int num;
  int sin_size; 
  struct sockaddr_in addr_local; /* client addr */
  struct sockaddr_in addr_remote; /* server addr */
  char revbuf[LENGTH]; // Receiver buffer

  /* Get the Socket file descriptor */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
  {
    fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor. (errno = %d)\n", errno);
    exit(1);
  }
  //else 
    //printf("[Server] Obtaining socket descriptor successfully.\n");

  /* Fill the client socket address struct */
  addr_local.sin_family = AF_INET; // Protocol Family
  addr_local.sin_port = htons(PORT); // Port number
  addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
  bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct

  /* Bind a special Port */
  if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
  {
    fprintf(stderr, "ERROR: Failed to bind Port. (errno = %d)\n", errno);
    exit(1);
  }
  //else 
    //printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",PORT);

  /* Listen remote connect/calling */
  if(listen(sockfd,BACKLOG) == -1)
  {
    fprintf(stderr, "ERROR: Failed to listen Port. (errno = %d)\n", errno);
    exit(1);
  }
  //else
    //printf ("[Server] Listening the port %d successfully.\n", PORT);

  int success = 0;
  while(success == 0)
  {
    sin_size = sizeof(struct sockaddr_in);

    /* Wait a connection, and obtain a new socket file despriptor for single connection */
    if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, (socklen_t*)&sin_size)) == -1) 
    {
        fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
      exit(1);
    }
    //else 
      //printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));
  
    char buffer[MAXRCVLEN + 1];
    int len = recv(nsockfd, buffer, MAXRCVLEN, 0);
    /* We have to null terminate the received data ourselves */
    buffer[len] = '\0';
    //printf("\n***    %s  ****  \n",buffer);
    
    /* Send File to Client */
        char* fs_name = buffer;
        char sdbuf[LENGTH]; // Send buffer
        //printf("[Server] Sending %s to the Client...", fs_name);
        FILE *fs = fopen(fs_name, "r");
        if(fs == NULL)
        {
            //fprintf(stderr, "ERROR: File %s not found on server. (errno = %d)\n", fs_name, errno);
        exit(1);
        }

        bzero(sdbuf, LENGTH); 
        int fs_block_sz; 
        while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0)
        {
            if(send(nsockfd, sdbuf, fs_block_sz, 0) < 0)
            {
                //fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
                exit(1);
            }
            bzero(sdbuf, LENGTH);
        }
        //printf("Ok sent to client!\n");
        //success = 1;
        close(nsockfd);
        //printf("[Server] Connection with Client closed. Server will wait now...\n");
        while(waitpid(-1, NULL, WNOHANG) > 0);
    
    
  }
      
}

void clientTCP(string FileNameToDownload,string ServerIp,string FileNameToSave, int PORTtcp,bool info) 
{ 
  if(info)
  printf("Trwa pobieranie %s",FileNameToDownload.c_str()); 
  int PORT=PORTtcp;
  int LENGTH=512;
  /* Variable Definition */
  int sockfd;
  char revbuf[LENGTH]; 
  struct sockaddr_in remote_addr;

  /* Get the Socket file descriptor */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
    exit(1);
  }
  /* Fill the socket address struct */
  remote_addr.sin_family = AF_INET; 
  remote_addr.sin_port = htons(PORT); 

  string str=ServerIp;
  char * ipTmp = new char[str.size() + 1];
  copy(str.begin(), str.end(), ipTmp);
  ipTmp[str.size()] = '\0'; // don't forget the terminating 0
  inet_pton(AF_INET, ipTmp, &remote_addr.sin_addr); 
  delete[] ipTmp;
  
  bzero(&(remote_addr.sin_zero), 8);

  /* Try to connect the remote */
  if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
  {
    fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
    exit(1);
  }
  //else 
    //printf("[Client] Connected to server at port %d...ok!\n", PORT);

  /* Send FileName to Server */
  
    string fs_name = FileNameToDownload;
    send(sockfd, fs_name.c_str(), fs_name.size(), 0);   
    
  /* Receive chosen File from Server */
  //printf("[Client] Receiveing file from Server and saving on disk...");
  
  string fr_name = FileNameToSave; //nazwa pod jaka zapisuje plik
  char * nameTmp = new char[fr_name.size() + 1];
  copy(fr_name.begin(), fr_name.end(), nameTmp);
  nameTmp[fr_name.size()] = '\0';
  FILE *fr = fopen(nameTmp, "a"); 
  delete[] nameTmp;
  if(fr == NULL)
    printf("File %s Cannot be opened.\n", fr_name.c_str());
  else
  {
    bzero(revbuf, LENGTH); 
    int fr_block_sz = 0;
        while((fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)) > 0)
        {
      int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
            if(write_sz < fr_block_sz)
      {
                  error("File write failed.\n");
            }
      bzero(revbuf, LENGTH);
    }
    if(fr_block_sz < 0)
          {
      if (errno == EAGAIN)
      {
        printf("recv() timed out.\n");
      }
      else
      {
        //fprintf(stderr, "recv() failed due to errno = %d\n", errno);
      }
    }
  //printf("Ok received from server!\n");
  fclose(fr);
  }
  
  close (sockfd);
  if(info)
  printf("\nPobieranie zakończone\n");
  //printf("[Client] Connection lost.\n");
}