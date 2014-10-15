#include "either.h"
#include <iostream>
#include <string>

functional::Either<std::string, int> f1(int i)
{
    if(i % 2 == 0)
        return functional::Either<std::string, int>::Right(i / 2);
    return functional::Either<std::string, int>::Left(std::string("bad num"));
}

bool test01()
{
    functional::Either<std::string, int> e = functional::Either<std::string, int>::Right(20).bind(f1).bind(f1);
    return (!e.isLeft) && (e.getValue() == 5);
}

bool test02()
{
    functional::Either<std::string, int> e = functional::Either<std::string, int>::Right(20).bind(f1).bind(f1).bind(f1);
    return (e.isLeft) ;
}


int main()
{
    if(!test01()) std::cout << "fail test01";
    if(!test02()) std::cout << "fail test02";
    std::cout << "End";
    return 0;
}
