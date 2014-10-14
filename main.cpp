#include <stdio.h>
#include <iostream>

#include "requesthandler.h"
#include "common.h"

int main()
{
    printf("Status: 200\nContent-type: text/html\n\n");
    cgi::RequestHandler request;
    cgi::RequestArgs args = request.getArgs();
    std::cout << readFile("../templates/index.html") << "\n" << args.size();
    return 1;
}
