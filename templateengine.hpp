#ifndef __TEMPLATE_ENGINE_H__
#define __TEMPLATE_ENGINE_H__

#include <string>
#include <map>

#include "functional/either.h"
#include "commoncgi.hpp"

namespace cgi {

typedef functional::Either<std::string, std::string> TemplateRenderEither;
class TemplateEngine{
    public:
        static TemplateRenderEither renderTemplate(
                const std::string &temp,
                const RequestArgs &args);
};

}

#endif
