#ifndef __TEMPLATE_ENGINE_H__
#define __TEMPLATE_ENGINE_H__

#include <string>
#include <map>

#include "commoncgi.h"

namespace cgi {

class TemplateEngine{
    public:
        static std::string renderTemplate(
                const std::string &temp,
                const RequestArgs &args);
};

}

#endif
