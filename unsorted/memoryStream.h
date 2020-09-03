
#include <list>
#include <mutex>
#include <algorithm>
#include <functional>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define DEFAULTALLOCSIZE 2
using namespace std;
class byteArray
{
private:
    char * _data;
    unsigned _size = 0;
    unsigned _capacity = 0;
public:
    const char * data()
    {

        return static_cast<const char *>(_data);
    }

    const unsigned size(){return _size;}
    const unsigned capacity(){return _capacity;}
    void reallocBuffer(unsigned _size)
    {
        if(void* mem = static_cast< char* >( std::realloc( _data, _size ) ))
        {
            _data = static_cast< char* >(mem);
            _capacity = _size;
        }
        else
        {
            cout << "bad_alloc" << endl;
            //toDo add throw!!!!
        }
    }

    void write(const void * _data,size_t length)
    {
        if( length > _capacity - _size)
        {
            reallocBuffer( (length > _capacity) ? ( length)*2 + _capacity : length *2 );
            memset(this->_data+_size,0,_capacity-_size);

        }
        memcpy(this->_data+_size,_data,length);
        _size = _size + length;
    }

    void free()
    {
        memset(_data,0,_size);
        _size = 0;
    }




    byteArray(){
        reallocBuffer( DEFAULTALLOCSIZE );
    };


}; 
