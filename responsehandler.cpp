#include "responsehandler.hpp"

using namespace cgi;

ResponseHandler::ResponseHandler()
{
    this->body = "";
    this->code = 200;
    this->mimeType = "text/html";
}

void ResponseHandler::send()
{
    printf("Status: %d\nContent-type: %s\n\n", code, this->mimeType.c_str());
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
