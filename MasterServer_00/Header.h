#pragma once
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<thread>
#include<fstream>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void ffile(string& str);

vector<string> separate_str(string str);

void file_save(string str);

int TCP_Recv_FileSer();

int TCP_Send(const char IP[], unsigned short port, char sendbuf[], int buflen);

int TCP_Recv_Client();

void file_remove(string str);