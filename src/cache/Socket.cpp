/*************************************************************************
	> File Name: Socket.cpp
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 13时50分59秒
 ************************************************************************/


#include "Socket.h"
#include <iostream>

Socket::Socket(std::string ip, std::string port)
{
	_server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(_server_fd == -1)
	{
		std::runtime_error("socket failed!");
	}
	_server.sin_family  = AF_INET;
	_server.sin_port = htons(atoi(port.c_str()));
	_server.sin_addr.s_addr = inet_addr(ip.c_str());
	if(-1 == bind(_server_fd, (struct sockaddr*)&_server, sizeof(_server)))
	{
		close(_server_fd);
		std::runtime_error("bind failed");
	}
	
	_len = sizeof(_client);
}

Socket::~Socket()
{
	close(_server_fd);
}

struct sockaddr_in Socket::get_client()const
{
	return _client;
}

int Socket::recv_msg(char *buf, int len)
{
	int ret = recvfrom(_server_fd, buf, len, 0, (struct sockaddr*)&_client, &_len);
	buf[ret] =  '\0';
	std::cout << buf << std::endl;
	return ret;
}
