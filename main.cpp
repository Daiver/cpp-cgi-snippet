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
        if(args["resource"] == "notes" && args.count("id")){
            if(request.requestType() == cgi::REQUEST_GET){
                std::string filePath = pathToExe + "../data/" + args["id"] + ".txt";
                std::string data = replaceString(readFile(filePath), "\n", "\\n");
                std::cout << "{\"text\": \"" + data + "\"}";
            }else if(request.requestType() == cgi::REQUEST_POST){
                writeFile("2.txt", args["data"]);
                std::cout << "ok " << args["data"]
            }
        }
    }else{
        std::cout << 
            cgi::TemplateEngine::renderTemplate(readFile(pathToExe + "../templates/index.html"), cont).getValue();
    }
    return 1;
}
