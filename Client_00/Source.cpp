#include"Header.h"

void main()
{
	int iResult;
	WSADATA wsaData;

	//----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return;
	}

	//---------------------------
	// Write here
	//---------------------------

	string recv;
	string ip, port, name;
	char send[300] = { 0 };
	cout << "NHAP yes." << endl;
	cin >> send;
	system("cls");
	TCP_Send_Master("127.0.0.1", 2222, send, sizeof(send), recv);

	//cout << recv << endl;
	//TCP_Recv_Master(recv, MAST);
	//cout << recv << endl;

	int ke = 0, ka = 0;
	vector<vector<string>> lis;
	vector<string> chua;
	for (int i = 0; i < recv.length(); i++)
	{
		if (recv[i] == '\n')
		{
			chua.push_back(name);
			name.clear();
			continue;
		}
		if (recv[i] == '\t')
		{
			lis.push_back(chua);
			chua.clear();
			continue;
		}
		name.push_back(recv[i]);
	}

	int x = 0;
	
	while (1)
	{
		string choose;
		int z = x % lis.size();
		cout << "Trang " << z + 1 << "/" << lis.size() << endl;
		cout << lis[z][0] << endl;
		for (int i = 1; i < lis.size(); i++)
		{
			cout << i << ". " << lis[z][i] << endl;
		}

		cout << "Lua chon( 0 de huy): ";

		cin >> choose;
		
		if (choose.compare(">>") == 0)
		{
			x++;
			system("cls");
			continue;
		}
		if (Fun_StrToInt(choose) == 0)
			break;

		int nhay = 0;
		for (int i = 0; i < lis[z][0].length(); i++)
		{
			if (lis[z][0][i] == '_')
			{
				nhay = 1;
				continue;
			}
			if (nhay == 1)
			{
				port.push_back(lis[z][0][i]);
			}
			else
				ip.push_back(lis[z][0][i]);
		}
		name = lis[x][Fun_StrToInt(choose)];

		//UDP_SendSocket(ip.c_str(), Fun_StrToInt(port), (char*)name.c_str(), name.length());
		thread a(UDP_SendSocket, ip.c_str(), Fun_StrToInt(port), (char*)name.c_str(), name.length());
		a.detach();
		system("cls");
	}

	//UDP_RecvSocket(5555);

	/*Test("../store/test.docx");*/



	//WSACleanup();


}