#include "requesthandler.h"

using namespace cgi;

RequestMethod RequestHandler::requestType() const
{
    char *methType = getenv("REQUEST_METHOD");
    if(methType == NULL)
        return REQUEST_UNKNOWN;
    if(strcmp(methType, "GET") == 0)
        return REQUEST_GET;
    if(strcmp(methType, "POST") == 0)
        return REQUEST_POST;
    if(strcmp(methType, "PUT") == 0)
        return REQUEST_PUT;
    if(strcmp(methType, "DELETE") == 0)
        return REQUEST_DELETE;
    return REQUEST_UNKNOWN;
}

RequestArgs RequestHandler::getArgs() const
{
    RequestArgs args;
    if(this->requestType() == REQUEST_UNKNOWN)
        return args;
    if(this->requestType() == REQUEST_GET)
        initializeGet(args);
    else
        initializePost(args);
    return args;
}
