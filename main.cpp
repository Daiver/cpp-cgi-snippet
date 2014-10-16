#include <stdio.h>
#include <iostream>

#include "requesthandler.h"
#include "common.h"
#include "functional/either.h"
#include "templateengine.h"

std::string getPathToExe(std::string argv0)
{
    std::string exeName = "main";
    return argv0.substr(0, argv0.size() - exeName.size());
}

int main(int argc, char **argv)
{
    std::string pathToExe = getPathToExe(argv[0]);

    printf("Status: 200\nContent-type: text/html\n\n");
    cgi::RequestHandler request;
    cgi::RequestArgs args = request.getArgs();
    cgi::RequestArgs cont;
    cont["someVar"] = "YEP!";
    if(args.count("resource")){//process rest
        std::cout << "{\"text\": \"" + args["resource"] + "\"}";
    }else{
        std::cout << 
            cgi::TemplateEngine::renderTemplate(readFile(pathToExe + "../templates/index.html"), cont).getValue();
    }
    return 1;
}
