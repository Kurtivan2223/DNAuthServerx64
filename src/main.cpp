#include <iostream>
#include "Includes/Logs/Logs.h"
#include "Includes/Configuration/Configuration.h"
#include <vector>
#include <cstring>
#include <winsock2.h>
#include <sql.h>
#include <sqlext.h>
#include "Includes/MD5/md5.h"

int main(int argc, char* argv[])
{
	SLog->Initialize();
	SConfig->Initialize();

	MD5 md5;

	WSADATA _wsData;
	if (WSAStartup(MAKEWORD(2, 2), &_wsData) != 0)
	{
		WRITE_LOG(SEVERITY_LEVEL::LOG_FATAL, "Failed to initialize Winsock");
		exit(EXIT_FAILURE);
	}

	std::string temp = "Map Server start from " 
		+ std::string(SConfig->Auth.EmulatedIPAddress) 
		+ ":" + std::to_string(SConfig->Auth.EmulatedPort) 
		+ " to " + std::string(SConfig->Auth.VirtualIPAddress)
		+ ":" + std::to_string(SConfig->Auth.VirtualPort);
	WRITE_LOG(SEVERITY_LEVEL::LOG_INFO, temp);

	SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(SConfig->Auth.EmulatedPort);
	serverAddress.sin_addr.s_addr = inet_addr(SConfig->Auth.EmulatedIPAddress);

	bind(server, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	temp = std::string(SConfig->Auth.EmulatedIPAddress) + " Server start at " + std::to_string(SConfig->Auth.EmulatedPort);
	WRITE_LOG(SEVERITY_LEVEL::LOG_INFO, temp);
	listen(server, 5);

	SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in clientAddress;
	clientAddress.sin_family = AF_INET;
	clientAddress.sin_port = htons(SConfig->Auth.VirtualPort);
	clientAddress.sin_addr.s_addr = inet_addr(SConfig->Auth.VirtualIPAddress);

	connect(client, (struct sockaddr*)&clientAddress, sizeof(clientAddress));
	temp = std::string(SConfig->Auth.EmulatedIPAddress)
		+ " Client connect to " + std::string(SConfig->Auth.VirtualIPAddress)
		+ ":" + std::to_string(SConfig->Auth.VirtualPort);
	WRITE_LOG(SEVERITY_LEVEL::LOG_INFO, temp);

	std::vector<SOCKET> inputs = { server };

	//ToDO: Database Operation and so on....
}