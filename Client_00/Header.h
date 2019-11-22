#include<iostream>
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<string.h>
#include<stdio.h>
#include<fstream>
#include<direct.h>
#include<Windows.h>
#include<vector>
#include<string>
#include<thread>
#include<mutex>
#include<time.h>


#pragma comment(lib, "Ws2_32.lib")

//#define BUFLEN 300
//#define DEFAULT_PORT_Client "3333"

using namespace std;
namespace fs = std::experimental::filesystem;

struct DinhDanh
{
	string Ip;
	unsigned short Port;
	string Name;
	int dem;
};

int TCP_Send_Master(const char IP[], unsigned short port, char sendbuf[], int buflen, string &);

int TCP_Recv_Master(string &,SOCKET);

int UDP_SendSocket(const char Addr[], unsigned short Port, char* SendBuf, int BufLen);

//int UDP_RecvSocket(unsigned short Port);

int UDP_RecvSocket(SOCKET ,sockaddr_in);

void Get_Ip_Port_Name(string a,string &Ip,string &Port,string &Name);

string Fun_IntToStr(unsigned int a);

int Fun_StrToInt(string a);

void Bef_Recvfrom(char* RecvBuf, int iResult, SOCKET, sockaddr_in);

int Random_Port();

