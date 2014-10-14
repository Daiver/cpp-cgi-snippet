#include "templateengine.h"

using namespace cgi;
std::string TemplateEngine::renderTemplate(const std::string &temp, 
        const RequestArgs &args)
{
    std::string res;
    res.reserve(temp.size() * 1.3);
    const char PARSE_TEXT = 1;
    const char PARSE_IDENT = 2;
    char curState = PARSE_TEXT;
    for(int i = 0; i < temp.size(); ++i){
    }

    return temp;
}
