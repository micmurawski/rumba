#include <vector>
#include <string>
#include <stdio.h>

#ifndef RUMBA_H
#define RUMBA_H

//#define MY_FILE_LIST ".myfilelist"
//#define IP_LIST ".iplist"

int main(int argc, char **argv);
void AddFile(const char *str);
void ListUsers(char **argv);
void ListMyfiles(void);
void DeleteFile(void);
void ListUserFiles(void);
void DownloadFile(void);
void EndProgram(void);
void init(int argc, char **argv);
int do_client(char * addr,int bcast);
int serverUDP(std::string localIp,std::string localBcastIp);
int serverTCP(int portNumber);
void clientTCP(std::string FileNameToDownload,std::string ServerIp,std::string FileNameToSave,int PORTtcp,bool info);
//extern char *addr;// = argv[1]; // adres ip urządzenia
//extern char *bcast_addr;// =argv[2]; //adres ip bcast
//extern std::vector <std::string> MyFileList;  //przechowuje listę udostępnianych plików przez użytkownika lokalnego
//extern std::vector <std::string> ForeinFileList;  //przechowuje cudzą listę udostępnianych plików 
//extern std::vector <std::string> AllIp; //przechowuje adresy ip użytkowników spierających program RUMBA
//extern bool check;// = true;  //zmiana jej wartości logicznej kończy działanie programu
//extern int choice;// = 0;

 

#endif