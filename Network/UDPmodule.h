#ifndef UDPMODULE_H
#define UDPMODULE_H

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
//класс для удобного обмена по UDP
//Параметры для конструктора - порт, неблокирующий режим(по умолчанию не блокирующий), считывание до последней дейтаграммы(по умолчанию да)
class UDPmodule
{
private:
    int _sock = -1;
    struct sockaddr_in sockaddr_module;
    unsigned _maxsize = 4096;//максимальный размер дейтаграммы для приема
    bool _nonblocked;
    bool _readAll;
    unsigned short _port;
    char * recieveBuffer = nullptr;
    char * readAllBuffer = nullptr;
    struct sockaddr_in sockaddr_to;
    const char * _ipto;
    unsigned short _portto;

    bool _valid = true;
public:
    UDPmodule(unsigned short port,bool nonblocked = true,bool readAll = true);
    ~UDPmodule();
    bool formTo(const char * ip,unsigned short port);
    static struct sockaddr_in formAddresFromIpAndPort(const char * ip,unsigned short port);
    ssize_t sendTo(const char * data, size_t length, const char * ip , unsigned int port );
    ssize_t sendTo(const char * data, size_t length, struct sockaddr_in addr);
    ssize_t send(const char * data, size_t length);
     ssize_t send(const string & s);
    ssize_t recieve(char *data, size_t length);
    string recieveAsString();
    bool isValid();


    void setMaxSize(const unsigned &maxsize);
};

#endif // UDPMODULE_H
