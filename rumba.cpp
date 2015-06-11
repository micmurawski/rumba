#include "sockets.h"
#include "utils.h"
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
#include <cstring>
#include <sstream>
#include <ctype.h>
#include "rumba.h"

using namespace std ;

char *addr;// = argv[1]; // adres ip urządzenia
char *bcast_addr;// =argv[2]; //adres ip bcast
std::vector <std::string> MyFileList;  //przechowuje listę udostępnianych plików przez użytkownika lokalnego
std::vector <std::string> ForeinFileList;  //przechowuje cudzą listę udostępnianych plików 
std::vector <std::string> AllIp; //przechowuje adresy ip użytkowników spierających program RUMBA
bool check;// = true;  //zmiana jej wartości logicznej kończy działanie programu
int choice;// = 0;

void init(int argc, char **argv){
	addr= argv[1]; // adres ip urządzenia
	bcast_addr=argv[2]; //adres ip bcast
	std::vector <std::string> MyFileList;  //przechowuje listę udostępnianych plików przez użytkownika lokalnego
	std::vector <std::string> ForeinFileList;  //przechowuje cudzą listę udostępnianych plików 
	std::vector <std::string> AllIp; //przechowuje adresy ip użytkowników spierających program RUMBA
	check = true;  //zmiana jej wartości logicznej kończy działanie programu
	choice = 0;
	int TCPserverPID=fork();
    if(TCPserverPID==0)
    serverTCP(20000);
    if(TCPserverPID==0)
    exit(0);
    
    //server odpowiedzialny za przesyłanie adresów ip
    int PIDD=fork();
    if(PIDD==0)
    serverUDP(argv[1],argv[2]);
    if(PIDD==0)
      exit(0);

}

void AddFile(const char *str){
				string tmp=str;
				//cout << "Podaj nazwe nowego pliku do udostepniania razem ze ścieżką"<< endl;
				//cout << "Np.: /home/user/folder_do_zapisu_pliku/nazwa_pliku.txt"<<endl;
				//cin >> tmp;
				if(!exists_test1(str))
				{
				   cout<<"Plik nie istnieje!!!"<<endl;
				   //break;
				}
				else cout<<"Plik został dodany"<<endl;
				MyFileList = LoadList(".myflielist");
				MyFileList.push_back(tmp);
				CreateList(MyFileList, ".myflielist");
			}

void DeleteFile(void){
				cout<<endl;
				cout<<"************************"<<endl;
				cout<<"Pliki udostępniane:"<<endl;
				//remove(".myflielist");
				MyFileList = LoadList(".myflielist");
				for(int i=0;i<MyFileList.size();i++)
				{
				  cout<<"nr: "<<i<<"  "<<MyFileList[i]<<endl;
				}
				cout<<"Który plik usunąć z listy?"<<endl;
				int tmp;
				cin>>tmp;
				MyFileList.erase(MyFileList.begin()+tmp);
				WriteVector(MyFileList);
				CreateList(MyFileList, ".myflielist");
			}

void ListMyfiles(void){
				cout<<endl;
				cout<<"************************"<<endl;
				cout<<"Pliki udostępniane:"<<endl;
				cout<<endl;
				MyFileList = LoadList(".myflielist");
				WriteVector(MyFileList);
				cout<<"************************"<<endl;
				cout<<endl;
}

void ListUsers(char **argv){
	remove(".iplist");
				cout<<"************************"<<endl;
				cout<<"Użytkownicy wspierający protokół:"<<endl;
				cout<<"Poczekaj aż zostaną wypisane wszystkie adresy ip"<<endl;
				do_client(bcast_addr, 1);
				AllIp = LoadList(".iplist");
				AllIp=EraseElement(AllIp,(string)argv[1]);
				WriteVector(AllIp);
				cout<<"Lista jest kompletna!"<<endl;
				CreateList(AllIp, ".iplist");
				cout<<"************************"<<endl;
}

void ListUserFiles(void){
	AllIp = LoadList(".iplist");
				if(AllIp.size()<=0)
				{
				  cout<<"Załaduj liste użytkowników!!!"<<endl;
				  //break;
				}
				  
				remove(".foreinfilelist");
				cout<<"************************"<<endl;
				cout<<"Który użytkownik?"<<endl;
				cout<<endl;
				for( size_t i = 0; i < AllIp.size(); i++ )
				{
				  cout<<"nr: "<<i<<"  ip: "<<AllIp[i]<<endl;
				}
				cout<<"************************"<<endl;
				int idServer=0;
				cin>>idServer; //wybieranie użytkownika, którego listę plików chcemy zobaczyć
				cout<<"Wybrano: "<<AllIp[idServer]<<endl;
				string str = AllIp[idServer];
				char *cstr = new char[str.length() + 1];
				strcpy(cstr, str.c_str());
				clientTCP(".myflielist",cstr, ".foreinfilelist",20000,false);
				delete [] cstr;
				ForeinFileList = LoadList(".foreinfilelist");
				ForeinFileList = LoadList(".foreinfilelist");
				for( size_t i = 0; i < ForeinFileList.size(); i++ )
				{
				  cout<<"nr: "<<i<<"  ip: "<<ForeinFileList[i]<<endl;
				}
				cout<<"************************"<<endl;
				remove(".foreinfilelist");
}

void DownloadFile(void){
	AllIp = LoadList(".iplist");
				if(AllIp.size()<=0)
				{
				  cout<<"Załaduj liste użytkowników!!!"<<endl;
				  //break;
				}
				remove(".foreinfilelist");
				cout<<"************************"<<endl;
				cout<<"Który użytkownik?"<<endl;
				cout<<endl;
				AllIp = LoadList(".iplist");
				for( size_t i = 0; i < AllIp.size(); i++ )
				{
				  cout<<"nr: "<<i<<"  ip: "<<AllIp[i]<<endl;
				}
				cout<<"************************"<<endl;
				int idServer=0;
				cin>>idServer; //wybieranie użytkownika, którego listę plików chcemy zobaczyć
				cout<<"Wybrano: "<<AllIp[idServer]<<endl;
				string str = AllIp[idServer];
				char *cstr = new char[str.length() + 1];
				strcpy(cstr, str.c_str());
				clientTCP(".myflielist",cstr, ".foreinfilelist",20000,false);
				ForeinFileList = LoadList(".foreinfilelist");
				cout<<"Który plik?"<<endl;
				for( size_t i = 0; i < ForeinFileList.size(); i++ )
				{
				  cout<<"nr: "<<i<<"  nazwa pliku: "<<ForeinFileList[i]<<endl;
				}
				cout<<"************************"<<endl;
				int tmpNumberOfFile;
				cout<<"Ktory plik chcesz pobrac?"<<endl;
				cin>>tmpNumberOfFile;
				cout<<"Wybrano: "<<ForeinFileList[tmpNumberOfFile]<<endl;
				cout<<"Jak ten plik ma się nazywac na Twoim komputerze??"<<endl;
				cout<<"Podaj nazwę razem ze ścieżką do pliku np.: /home/user/folder_do_zapisu_pliku/nazwa_pliku.txt"<<endl;
				string tmpName;
				cin>>tmpName;
				clientTCP(ForeinFileList[tmpNumberOfFile],cstr, tmpName,20000,true);
				delete [] cstr;
				remove(".foreinfilelist");
}

void EndProgram(void){
	remove(".iplist");
	check = false;
	exit(0);
}


