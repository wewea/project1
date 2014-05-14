/*************************************************************************
	> File Name: Socket.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月04日 星期日 13时39分21秒
 ************************************************************************/


#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


class Socket
{
	public:
		Socket(std::string ip, std::string port);
		~Socket();
		int recv_msg(char *buf, int len);
		struct sockaddr_in get_client() const;
	private:
		Socket(const Socket &);
		Socket &operator= (const Socket&);
		int _server_fd;
		struct sockaddr_in _server, _client;
		socklen_t _len;
};





#endif

