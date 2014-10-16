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

bool test03()
{
    functional::Either<char, int> e = functional::Either<char, int>::Right(100);
    return (!e.map(f).isLeft) && (e.map(f).getValue() == 1000);
}

bool test04()
{
    functional::Either<char, int> e = functional::Either<char, int>::Left('1');
    return (e.map(f).isLeft) && (e.getLeft() == '1');
}

int main()
{
    if(!test01()) std::cout << "fail test01" << std::endl;
    if(!test02()) std::cout << "fail test02" << std::endl;
    if(!test03()) std::cout << "fail test03" << std::endl;
    if(!test04()) std::cout << "fail test04" << std::endl;
    std::cout << "End\n";
    return 0;
}
