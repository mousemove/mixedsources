#include "UDPmodule.h"

void UDPmodule::setMaxSize(const unsigned &maxsize)
{
    _maxsize = maxsize;
    if(recieveBuffer != nullptr)
    {
        delete [] recieveBuffer;
        recieveBuffer = new char[_maxsize];
        delete [] readAllBuffer;
        readAllBuffer = new char[_maxsize];
    }
}

UDPmodule::UDPmodule(unsigned short port, bool nonblocked , bool readAll):_port(port),_readAll(readAll),_nonblocked(nonblocked)
{
    _sock = socket(AF_INET, SOCK_DGRAM, 0);
    if ( _sock < 0 ) {
        cout << "socket create failed" << endl;
        _valid = false;
        return;
    }

    sockaddr_module.sin_family    = AF_INET;
    sockaddr_module.sin_addr.s_addr = INADDR_ANY;
    sockaddr_module.sin_port = htons(_port);

    if ( bind(_sock, (const struct sockaddr *)&sockaddr_module,
              sizeof(sockaddr_module)) < 0 )
    {
        cout << "?????UDP socket bind failed " << port << endl;
        _valid = false;
        return;
    }
    if (_nonblocked == true)
    {
        int flags = fcntl(_sock,F_GETFL,0);
        flags = flags | O_NONBLOCK ;
        fcntl(_sock,F_SETFL,flags);
    }
    else
    {
        int flags = fcntl(_sock,F_GETFL,0);
        flags = flags & ~O_NONBLOCK ;
        fcntl(_sock,F_SETFL,flags);
    }

    recieveBuffer = new char[_maxsize];
    readAllBuffer = new char[_maxsize];
}

UDPmodule::~UDPmodule()
{
    delete [] recieveBuffer;
    delete [] readAllBuffer;
    close(_sock);
}

bool UDPmodule::formTo(const char *ip, unsigned short port)
{

    sockaddr_to.sin_family    = AF_INET;
    sockaddr_to.sin_addr.s_addr = INADDR_ANY;
    sockaddr_to.sin_port = htons(port);
    return  inet_pton(AF_INET,ip,&sockaddr_to.sin_addr) > 0;

}

sockaddr_in UDPmodule::formAddresFromIpAndPort(const char *ip, unsigned short port)
{
    sockaddr_in addr;
    addr.sin_family    = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    inet_pton(AF_INET,ip,&addr.sin_addr);
    return addr;
}

ssize_t UDPmodule::sendTo(const char *data,size_t length, const char *ip, unsigned int port)
{
    sockaddr_in addr = formAddresFromIpAndPort(ip,port);
    return  sendto(_sock, data, length,
                   0, (const struct sockaddr *)&addr,
                   sizeof(addr));

}

ssize_t UDPmodule::sendTo(const char *data, size_t length, sockaddr_in addr)
{
    return  sendto(_sock, data, length,
                   0, (const struct sockaddr *)&addr,
                   sizeof(addr));
}

ssize_t UDPmodule::send(const char *data, size_t length)
{
    return  sendto(_sock, data, length,
                   0, (const struct sockaddr *)&sockaddr_to,
                   sizeof(sockaddr_to));

}

ssize_t UDPmodule::send(const string &s)
{
    return  sendto(_sock, s.c_str(), s.length(),
                   0, (const struct sockaddr *)&sockaddr_to,
                   sizeof(sockaddr_to));
}

ssize_t UDPmodule::recieve(char *data,size_t length)
{
    if(!_readAll || !_nonblocked)
    {
        ssize_t a = recv(_sock,data,length,0);
        return a;
    }
    else
    {


        if(length > _maxsize) cout << "warning! length > maxsize datagram" << endl;
        memset(readAllBuffer,0,_maxsize);
        memset(recieveBuffer,0,_maxsize);
        ssize_t recb,recb_success = -1;
        while((recb =recv(_sock,readAllBuffer,_maxsize,0)) > 0)
        {
            memcpy(recieveBuffer,readAllBuffer,_maxsize);
            recb_success = recb;
        }
        if(recb_success > 0) memcpy(data,recieveBuffer,length);
        return recb_success;
    }
}

string UDPmodule::recieveAsString()
{
    memset(recieveBuffer,0,_maxsize);
    ssize_t recb;
    if(!_readAll || !_nonblocked )
    {
        recb =  recv(_sock,recieveBuffer,_maxsize,0);
    }
    else
    {
        memset(readAllBuffer,0,_maxsize);
        while((recb =recv(_sock,readAllBuffer,_maxsize,0)) > 0)
        {
            memcpy(recieveBuffer,readAllBuffer,_maxsize);
        }
    }
    string s(recieveBuffer);
    return s;

}

bool UDPmodule::isValid()
{
    return _valid;
}
