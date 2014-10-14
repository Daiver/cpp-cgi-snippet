#include <stdio.h>
#include <iostream>

#include "getpost.h"

int main()
{
    printf("Status: 200\nContent-type: text/html\n\n");
    printf("Every thing is OK");
    char *data = getenv("REQUEST_METHOD");
    printf("METH TYPE %s", data);
    return 1;
}
