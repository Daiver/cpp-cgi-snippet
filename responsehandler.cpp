#include "responsehandler.h"

using namespace cgi;

ResponseHandler::ResponseHandler()
{
    this->body = "";
    this->code = 200;
}

void ResponseHandler::send()
{
    printf("Status: %d\nContent-type: text/html\n\n", code);
    printf("%s", this->body.c_str());
}

void ResponseHandler::operator << (std::string s)
{
    this->body += s;
}

void ResponseHandler::operator << (const char *s)
{
    this->body += s;
}
