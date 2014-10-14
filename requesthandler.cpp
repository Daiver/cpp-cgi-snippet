#include "requesthandler.h"

using namespace cgi;

RequestMethod RequestHandler::requestType() const
{
    char *methType = getenv("REQUEST_METHOD");
}
