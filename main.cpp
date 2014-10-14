#include <stdio.h>
#include <iostream>

#include "requesthandler.h"
#include "common.h"
#include "templateengine.h"


int main()
{
    printf("Status: 200\nContent-type: text/html\n\n");
    cgi::RequestHandler request;
    cgi::RequestArgs args = request.getArgs();
    if(args.count("resource")){//process rest
        std::cout << "{" + args["resource"] + "}";
    }else{
        std::cout << readFile("../templates/index.html") ;
    }
    return 1;
}
