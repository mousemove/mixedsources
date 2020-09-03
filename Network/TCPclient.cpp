#include "TCPclient.h"

TCPclient::TCPclient(const char *ipto, unsigned short portto)
{
    int err = 0;
    //make send socket
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if ( _sock < 0 ) {
        cout << "socket create failed" << endl;
        _valid = false;
        return;
    }

    //init sockaddr_to strunct
    memset(&sockaddr_to, 0, sizeof(struct sockaddr_in));
    sockaddr_to.sin_family = AF_INET;
    sockaddr_to.sin_port = htons(portto);
    if(inet_pton(AF_INET,ipto,&sockaddr_to.sin_addr) <= 0)
    {
        cout << "server address failed failed" << endl;
        _valid = false;
        return;
    }

    err = connect( _sock, (sockaddr *) &sockaddr_to, sizeof(sockaddr_to));

    if (err != 0) {
        close(_sock);
        cout << "connect failed " << ipto << " " << portto << endl;
        _valid = false;
    }

    //    int flags = fcntl(_sock,F_GETFL,0);
    //    flags = flags | O_NONBLOCK ;
    //    fcntl(_sock,F_SETFL,flags);


}

TCPclient::~TCPclient()
{
    close(_sock);
}

bool TCPclient::valid() const
{
    return _valid;
}

void TCPclient::setValid(bool valid)
{
    _valid = valid;
}

ssize_t TCPclient::senddata( char *data, size_t length)
{
  // cout << "two address:" << (unsigned int)(*data) << endl;
  // char b[36];
    auto k = send(_sock, data, length, MSG_NOSIGNAL);
 // cout << "two address3:" << (unsigned int)(*data) << endl;
    return k;
}

ssize_t TCPclient::recieve(char *data, size_t length)
{
    ssize_t a = recv(_sock,data,length,0);
    return a;
}

