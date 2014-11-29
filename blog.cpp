#include <stdio.h>
#include <iostream>

#include "requesthandler.hpp"
#include "responsehandler.hpp"
#include "common.hpp"
#include "functional/either.hpp"
#include "templateengine.hpp"
#include "sqlworker.hpp"
#include "mysqlworker.hpp"


int main(int argc, char **argv)
{
    std::string pathToExe = pathToFile(argv[0]);
    std::string exeName   = last(split(argv[0], '/'));

    cgi::RequestHandler request;
    cgi::ResponseHandler response;
    cgi::RequestArgs args = request.getArgs();
    cgi::RequestArgs cont;
    cont["STATIC_PATH"] = exeName + "?staticfile=";

    if (args.count("staticfile")){
        std::string reqFile = args["staticfile"];
        std::string res = readFile(std::string("../static/") + reqFile);
        if(getExtensionOfFileByPath(reqFile) == "js")
            response.mimeType = "text/javascript";
        response << res;
    }else{
        response << 
            cgi::TemplateEngine::renderTemplate(readFile(pathToExe + "../templates/blogindex.html"), cont).getValue();

    }
    response.send();
    return 1;
}

