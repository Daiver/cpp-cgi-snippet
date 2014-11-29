#include "either.hpp"
#include <iostream>
#include <string>

#include "../minitest.h"

functional::Either<std::string, int> f1(int i)
{
    if(i % 2 == 0)
        return functional::Either<std::string, int>::Right(i / 2);
    return functional::Either<std::string, int>::Left(std::string("bad num"));
}

void test01()
{
    functional::Either<std::string, int> e = functional::Either<std::string, int>::Right(20).bind(f1).bind(f1);
    ASSERT( (!e.isLeft) && (e.getValue() == 5));
}

void test02()
{
    functional::Either<std::string, int> e = functional::Either<std::string, int>::Right(20).bind(f1).bind(f1).bind(f1);
    ASSERT( (e.isLeft) );
}

int f(int i)
{
    return i * 10;
}

void test03()
{
    functional::Either<char, int> e = functional::Either<char, int>::Right(100);
    ASSERT( (!e.map(f).isLeft) && (e.map(f).getValue() == 1000));
}

void test04()
{
    functional::Either<char, int> e = functional::Either<char, int>::Left('1');
    ASSERT( (e.map(f).isLeft) && (e.map(f).getLeft() == '1'));
}

void test05()
{
    typedef functional::Either<std::string, int> E;
    E e = E::Right(40) >> f1 >> f1 >> f1;
    ASSERT((!e.isLeft) && e.getValue() == 5);
}


int main()
{
    RUN_TEST(test01);
    RUN_TEST(test02);
    RUN_TEST(test03);
    RUN_TEST(test04);
    RUN_TEST(test05);
    return 0;
}
