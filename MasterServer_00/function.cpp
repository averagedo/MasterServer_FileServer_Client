#include"Header.h"

#define BUFLEN 512
#define DEFAULT_PORT_File "1111"
#define DEFAULT_PORT_Client "2222"
#define PATH_ "../alotoffiles/"

void ffile(string& str)
{
	vector<string> c;

	char path[] = PATH_;
	char a[300];

	strcpy(a, path);
	strcat_s(a, 300, "*");
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile(a, &data);      // DIRECTORY

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			c.push_back(data.cFileName);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}

	c.erase(c.begin());
	c.erase(c.begin());

	for (int i = 0; i < c.size(); i++)
	{
		string name = path;
		name.append(c[i]);

		ifstream iif(name);
		if (!iif.is_open())
		{
			cout << "Loi!" << endl;
			return;
		}

		char chr;
		while (1)
		{
			iif.get(chr);
			if (iif.eof())
				break;
			str.push_back(chr);
		}
		str.push_back('\t');
	}
}

vector<string> separate_str(string str)
{
	vector<string> vec;
	string temp;

	int flag = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '\r' && str[i + 1] == '\n')
		{
			i = i + 1;
			vec.push_back(temp);
			temp.clear();
			continue;
		}
		temp.push_back(str[i]);
	}
	return vec;
}

void file_save(string str)
{
	vector<string> fil;
	fil = separate_str(str);

	string path = "../alotoffiles/";

	////sua /t thanh _ giua ip va port
	//fil[fil[0].find_first_of("\t")]='_';

	path.append(fil[0]);
	ofstream oof(path, ios::trunc);
	if (!oof.is_open())
	{
		cout << "Mo file loi" << endl;
		return;
	}

	for (int i = 0; i < fil.size(); i++)
	{

		oof << fil[i];
		oof << '\n';
	}

	oof.close();
}

int TCP_Recv_FileSer()
{
	/*WSADATA wsaData;*/
	int iResult;
	string str;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	char recvbuf[BUFLEN];

	//// Initialize Winsock
	//iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//if (iResult != 0) {
	//	printf("WSAStartup failed with error: %d\n", iResult);
	//	return 1;
	//}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT_File, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		/*WSACleanup();*/
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		/*WSACleanup();*/
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		/*	WSACleanup();*/
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		/*WSACleanup();*/
		return 1;
	}

	while (1)
	{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			/*WSACleanup();*/
			return 1;
		}

		// No longer need server socket
		//closesocket(ListenSocket);


		do {
			iResult = recv(ClientSocket, recvbuf, (int)BUFLEN, 0);
			if (iResult == SOCKET_ERROR) {
				printf("recv failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				/*WSACleanup();*/
				return 1;
			}

			for (int i = 0; i < iResult; i++)
			{
				str.push_back(recvbuf[i]);
			}


		} while (iResult > 0);

		if (str[0] == '\r' && str[1] == '\n')
		{
			file_remove(str);
		}
		else
			file_save(str);

		cout << str << endl;
		str.clear();
		closesocket(ClientSocket);
	}

	//cout << iResult << endl;

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		/*WSACleanup();*/
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	/*WSACleanup();*/

	return 0;
}

int TCP_Send(const char IP[], unsigned short port, char sendbuf[], int buflen)
{

	//----------------------
	// Declare and initialize variables.
	int iResult;
	/*WSADATA wsaData;*/

	SOCKET ConnectSocket = INVALID_SOCKET;
	struct sockaddr_in clientService;

	//----------------------
	// Initialize Winsock
	/*iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %d\n", iResult);
		return 1;
	}*/

	//----------------------
	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
		/*WSACleanup();*/
		return 1;
	}

	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(IP);
	clientService.sin_port = htons(port);

	//----------------------
	// Connect to server.
	iResult = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		/*WSACleanup();*/
		return 1;
	}

	//----------------------
	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, buflen, 0);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		/*WSACleanup();*/
		return 1;
	}

	printf("Bytes Sent: %d\n", iResult);

	//// shutdown the connection since no more data will be sent
	//iResult = shutdown(ConnectSocket, SD_SEND);
	//if (iResult == SOCKET_ERROR) {
	//	wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
	//	closesocket(ConnectSocket);
	//	WSACleanup();
	//	return 1;
	//}

	// close the socket
	iResult = closesocket(ConnectSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"close failed with error: %d\n", WSAGetLastError());
		/*WSACleanup();*/
		return 1;
	}

	//WSACleanup();
	return 0;
}

int TCP_Recv_Client()
{
	/*WSADATA wsaData;*/
	int iResult;
	string str;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	char recvbuf[BUFLEN];

	//// Initialize Winsock
	//iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	//if (iResult != 0) {
	//	printf("WSAStartup failed with error: %d\n", iResult);
	//	return 1;
	//}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT_Client, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		/*WSACleanup();*/
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		/*WSACleanup();*/
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		/*	WSACleanup();*/
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		/*WSACleanup();*/
		return 1;
	}

	while (1)
	{
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			/*WSACleanup();*/
			return 1;
		}

		// No longer need server socket
		//closesocket(ListenSocket)
		do {
			iResult = recv(ClientSocket, recvbuf, (int)BUFLEN, 0);
			if (iResult == SOCKET_ERROR) {
				printf("recv failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				/*WSACleanup();*/
				return 1;
			}

			for (int i = 0; i < iResult; i++)
			{
				str.push_back(recvbuf[i]);
			}


		} while (iResult > 0);

		cout << str << endl;

		string gg;
		ffile(gg);
		if (str.compare("yes"))
		{
			//TCP_Send("127.0.0.1", 3333, trc, sizeof(trc));
			iResult = send(ClientSocket, gg.c_str(), gg.length(), 0);
			if (iResult == SOCKET_ERROR) {
				printf("recv failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				/*WSACleanup();*/
				return 1;
			}
		}
		str.clear();

		closesocket(ClientSocket);
	}

	//cout << iResult << endl;

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		/*WSACleanup();*/
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	/*WSACleanup();*/

	return 0;
}

void file_remove(string str)
{
	string path = PATH_;
	for (int i = 2; i < str.length() - 2; i++)
	{
		path.push_back(str[i]);
	}
	remove(path.c_str());
}
