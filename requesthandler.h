#include <string>
#include <vector>
#include <map>

#include "getpost.h"

namespace cgi {

typedef std::map<std::string, std::string> RequestArgs;

enum RequestMethod { 
    REQUEST_GET, REQUEST_POST, REQUEST_PUT, REQUEST_DELETE, REQUEST_UNKNOWN
};

class RequestHandler
{
    public:
        RequestHandler (){}

        RequestMethod requestType() const;
        RequestArgs getArgs() const;
};

}
