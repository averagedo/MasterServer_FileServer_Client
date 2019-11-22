#include"function.h"



void main()
{
	//----------------------
	// Declare and initialize variables.
	int iResult;
	WSADATA wsaData;

	//----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return ;
	}
	
	//----------------------
	// Write here
	//----------------------

	//----------------------
	//Chon IP
	int choose;
	string Ip;
	vector<string> lsIpLocal;

	cout << "Card mang: " << endl;
	lsIpLocal = Fun_ListIP();
	lsIpLocal.push_back("127.0.0.1");
	for (int i = 0; i < lsIpLocal.size(); i++)
	{
		cout << i + 1 << ". " << lsIpLocal[i] << endl;
	}
	cout << "Chon card mang: ";
	cin >> choose;

	Ip = lsIpLocal[choose - 1];

	cout << Ip << endl;
	system("pause");
	system("cls");

	//----------------------------
	// 

	thread thr1(Thr_ConnectToServer, Ip);

	thread thr2(UDP_RecvSocket, 4444);
	
	while (1)
	{
		int chon;
		cout << "Nhap lua chon: " << endl;
		cout << "1. Tai file len." << endl;
		cout << "2. Ngat ket noi." << endl;
		cout << "-->";
		cin >> chon;
		if (chon == 1)
		{
			Thr_UpLoad();
			Thr_ConnectToServer(Ip);
		}
		if (chon == 2)
		{
			InTheEnd(Ip);
			exit(0);
		}
		system("cls");
	}
	thr1.join();
	thr2.join();

	WSACleanup();
	system("pause");
	return;
}

