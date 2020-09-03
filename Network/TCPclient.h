#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fcntl.h>
using namespace  std;

class TCPclient
{
private:
    int _sock = -1;
    unsigned _maxsize = 4096;
    bool _valid = true;
    unsigned short _port;
    struct sockaddr_in sockaddr_to;
public:

    TCPclient(const char * ipto, unsigned short portto );
    ~TCPclient();
    bool valid() const;
    void setValid(bool valid);
    ssize_t senddata( char * data, size_t length);
ssize_t recieve(char *data, size_t length);

};

#endif // TCPCLIENT_H
