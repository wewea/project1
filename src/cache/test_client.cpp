/*************************************************************************
	> File Name: test_client.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 14时13分45秒
 ************************************************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
	ifstream fin(argv[1]);
	string ip, port;
	fin >> ip >> port;
	fin.close();
	cout << ip << " " << port << endl;

	int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_fd == -1)
	{
		std::runtime_error("socket failed!");
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(port.c_str()));
	server.sin_addr.s_addr = inet_addr(ip.c_str());
	
	
	string line;
	char buf[128]="";
	while(getline(cin, line))
	{
		sendto(client_fd, line.c_str(), strlen(line.c_str()), 0, (struct sockaddr*)&server, sizeof(server));
		line.empty();	
		int ret = recvfrom(client_fd, buf, 2028, 0, NULL, NULL);
		buf[ret] = '\0';
		cout << buf << endl;	
	}
	return 0;
}

