#ifndef __RESPONCE_HANDLER_H__
#define __RESPONCE_HANDLER_H__

#include <string>
#include <iostream>
#include <stdio.h>

namespace cgi {

class ResponseHandler
{
public:
    ResponseHandler();
    void send();

    void operator << (std::string s);
    void operator << (const char *s);

    int code;
    std::string mimeType;
    std::string body;
};

}

#endif
