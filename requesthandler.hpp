#include <string>
#include <vector>
#include <map>

#include "commoncgi.hpp"
#include "getpost.hpp"

namespace cgi {

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
