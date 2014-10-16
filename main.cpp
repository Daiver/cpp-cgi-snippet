#include <stdio.h>
#include <iostream>

#include "requesthandler.h"
#include "common.h"
#include "functional/either.h"
#include "templateengine.h"


int main()
{
    printf("Status: 200\nContent-type: text/html\n\n");
    cgi::RequestHandler request;
    cgi::RequestArgs args = request.getArgs();
    cgi::RequestArgs cont;
    cont["someVar"] = "YEP!";
    if(args.count("resource")){//process rest
        std::cout << "def";
        std::cout << "{" + args["resource"] + "}";
    }else{
        std::cout << 
            cgi::TemplateEngine::renderTemplate(readFile("../templates/index.html"), cont);
    }
    return 1;
}
