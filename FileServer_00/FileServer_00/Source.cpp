#include"function.h"



void main()
{
	/*char buf[BUFLEN] = { 0 };
	cin >> buf;
	TCP_Send(buf);*/

	/*char in[300] = "../clgt.jpg";
	UpLoad(in);*/

	/*vector<string> c;
	c = ListDir(PATHFILESTORE);
	for (auto i : c)
	{
		cout << i << endl;
	}*/


	//UpLoad("../BTTH02.docx");

	/*vector<string> a;
	char* b;

	a = vtorListDir(PATHFILESTORE);
	b = chrListDir(a);

	TCP_Send("127.0.0.1", 1111, b, strlen(b));


	delete[] b;*/

	// Driver code 

	/*vector<string> L;
	L = Fun_ListIP();
	for (int i = 0; i < L.size(); i++)
	{
		cout << L[i] << endl;
	}*/


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

	//---------------------
	// 

	thread thr1(Thr_ConnectToServer, Ip);
	thr1.detach();

	//Thr_UpLoad();

	
	UDP_RecvSocket(4444);

	WSACleanup();
	system("pause");
	return;
}

//void main()
//{
//	string a;
//	cout << Fun_IntToStr(1111) << endl;
//	system("pause");
//}