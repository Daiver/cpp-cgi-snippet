#include "either.h"
#include <iostream>
#include <string>

int main()
{
    functional::Either<std::string, int> eith = functional::Either<std::string, int>::Right(15);
    return 0;
}
