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

int f(int i)
{
    return i * 10;
}

int main()
{
    if(!test01()) std::cout << "fail test01" << std::endl;
    if(!test02()) std::cout << "fail test02" << std::endl;
    std::cout << "End\n";
    functional::Either<char, int> e = functional::Either<char, int>::Right(100);
    std::cout<< e.map(f).getValue();
    return 0;
}
