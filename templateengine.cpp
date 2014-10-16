#include "templateengine.h"

#include <iostream>

using namespace cgi;
TemplateRenderEither TemplateEngine::renderTemplate(const std::string &temp, 
        const RequestArgs &args)
{
    std::string res;
    res.reserve(temp.size() * 1.3);
    const char PARSE_TEXT = 1;
    const char PARSE_IDENT = 2;
    char curState = PARSE_TEXT;
    std::string accum = "";
    for(int i = 0; i < temp.size() - 1; ++i){
        int a = temp[i];
        int b = temp[i + 1];
        if(a == '{' && b == a && curState == PARSE_TEXT){
            res += accum;
            accum = "";
            curState = PARSE_IDENT;
            ++i;
        }else if(a == '}' && b == a && curState == PARSE_IDENT){
            res += args.at(accum);
            accum = "";
            curState = PARSE_TEXT;
            ++i;
        }else{
            accum += temp[i];
        }
    }
    res += accum;

    return TemplateRenderEither::Right(res);
}
