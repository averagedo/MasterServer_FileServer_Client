#include"Header.h"

int main()
{
	/*string a;

	TCP_Recv(a);

	cout << a << endl;*/


	WSADATA wsaData;
	int iResult;
	string a;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	//-------------------------
	// Write here
	//-------------------------
	

	thread thr1(TCP_Recv_FileSer);
	thread thr2(TCP_Recv_Client);

	thr1.join();
	thr2.join();

	system("pause");
	WSACleanup();
	return 0;
}

