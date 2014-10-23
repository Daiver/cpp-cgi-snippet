#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

#include "minitest.h"
#include "commoncgi.h"
#include "templateengine.h"
#include "mysqlworker.h"

using namespace cgi;

void testTemplateEngine01()
{
    RequestArgs args;
    args["x"] = "10";
    std::string testTemplate = "123 {{x}} 321";
    TemplateRenderEither e = TemplateEngine::renderTemplate(testTemplate, args);
    ASSERT(!e.isLeft);
    ASSERT_EQ(e.getValue(), std::string("123 10 321"));
}

void testTemplateEngine02()
{    
    RequestArgs args;
    args["x"] = "1";
    std::string testTemplate = "123 {{x}}";
    TemplateRenderEither e = TemplateEngine::renderTemplate(testTemplate, args);
    ASSERT(!e.isLeft);
    ASSERT_EQ(e.getValue(), std::string("123 1"));
}

void testTemplateEngine03()
{    
    RequestArgs args;
    args["x"] = "15";
    std::string testTemplate = "{{x}}";
    TemplateRenderEither e = TemplateEngine::renderTemplate(testTemplate, args);
    ASSERT(!e.isLeft);
    ASSERT_EQ(e.getValue(), std::string("15"));
}

void testTemplateEngine04()
{    
    RequestArgs args;
    args["y"] = "15";
    std::string testTemplate = "{{x}}";
    TemplateRenderEither e = TemplateEngine::renderTemplate(testTemplate, args);
    ASSERT(e.isLeft);
    ASSERT_EQ(e.getLeft(), std::string("Bad var name: x"));
}

void testDB01()
{
    MySQLWorker mysql;
    mysql.connect("192.168.10.101", "root", "123", "pract");
    ASSERT(mysql.isConnected());
    mysql.query("DROP DATABASE testDB;");
    MySQLWorker::SQLQueryResult res1 = mysql.query("CREATE DATABASE testDB;");
    ASSERT(!res1.isLeft);
}

void testDB02()
{
    MySQLWorker mysql;
    mysql.connect("192.168.10.101", "root", "123", "testDB");
    ASSERT(mysql.isConnected());
    //MySQLWorker::SQLQueryResult res1 = mysql.query("CREATE DATABASE testDB");
    MySQLWorker::SQLQueryResult res1 = mysql.query("CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20), age INT);");
    MySQLWorker::SQLQueryResult res2 = mysql.query("insert into pet values('Bobby', 'Vasya', 13) ");
    MySQLWorker::SQLQueryResult res4 = mysql.query("insert into pet values('Boo', 'Vasya', 103) ");
    MySQLWorker::SQLQueryResult res3 = mysql.query("select * from pet ");
    //MySQLWorker::SQLQueryResult res2 = mysql.query("DROP DATABASE testDB");
    ASSERT(!res1.isLeft);
    ASSERT(!res2.isLeft);
    ASSERT(!res3.isLeft);
    ASSERT(!res4.isLeft);
    for(int i = 0; i < res3.getValue().size(); ++i){
        for(int j = 0; j < res3.getValue()[i].size(); ++j){
            printf("%s ", res3.getValue()[i][j].c_str());
        }
        printf("\n");
    }//*/
}

void dataBaseTests()
{
    bool isPossibleToRunDBTests = false;
    {
        MySQLWorker mysql;
        mysql.connect("192.168.10.101", "root", "123", "pract");
        isPossibleToRunDBTests = mysql.isConnected();
    }
    if(isPossibleToRunDBTests){
        printf("Yeah, running db tests\n");
        RUN_TEST(testDB01);
        RUN_TEST(testDB02);
        MySQLWorker mysql;
        mysql.connect("192.168.10.101", "root", "123", "pract");
        mysql.query("DROP DATABASE testDB");
    }else{
        printf("Cannot runn db tests\n");
    }
}

int main()
{
    RUN_TEST(testTemplateEngine01);
    RUN_TEST(testTemplateEngine02);
    RUN_TEST(testTemplateEngine03);
    RUN_TEST(testTemplateEngine04);
    dataBaseTests();
    return 0;
}
