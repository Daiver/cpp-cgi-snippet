#include <stdio.h>
#include <iostream>

#include "requesthandler.h"
#include "common.h"

int main()
{
    printf("Status: 200\nContent-type: text/html\n\n");
    printf("Every thing is OK");
    char *data = getenv("REQUEST_METHOD");
    std::cout << readFile("templates/index.html");
    return 1;
}
