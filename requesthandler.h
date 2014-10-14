#include "getpost.h"

namespace cgi {

enum RequestMethod { REQUEST_GET, REQUEST_POST, REQUEST_PUT, REQUEST_DELETE };

class RequestHandler
{
    public:
        RequestHandler (){}

        RequestMethod requestType() const;
};

}
