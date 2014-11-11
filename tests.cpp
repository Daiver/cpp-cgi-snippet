#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

#include "minitest.h"
#include "common.h"
#include "commoncgi.h"
#include "templateengine.h"
#include "mysqlworker.h"
#include "orm/orm.h"

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
    SQLWorker::VectorOfVectorOfString res = res3.getValue();
}

class TestCLL
{
public:
    void initOrm(orm::OrmFieldHandler handler)
    {
        handler << ORM_MODEL_FIELD(someIndex);
        handler << ORM_MODEL_FIELD(name);
    }

    int someIndex;
    std::string name;
};
ORM_EXPORT_CLASS(TestCLL);

void testOrmCreation01()
{
    MySQLWorker mysql;
    mysql.connect("192.168.10.101", "root", "123", "testDB");
    ASSERT(mysql.isConnected());
    orm::Database db(&mysql);
    db.registerModel<TestCLL>();
    db.createScheme();
    TestCLL tmp;
    tmp.someIndex = 5;
    tmp.name = "Hello";
    int id = db.newInst(tmp);

    TestCLL tmp2;
    functional::Either<std::string, TestCLL> res1 = db.getInstById<TestCLL>(id);
    ASSERT(!res1.isLeft);
    tmp2 = res1.getValue();

    ASSERT_EQ(tmp2.someIndex, 5);
    ASSERT_EQ(tmp2.name, "Hello");

    TestCLL tmp3;
    tmp3.name = "World";
    tmp3.someIndex = 1;
    db.updInst(id, tmp3);

    functional::Either<std::string, TestCLL> res2 = db.getInstById<TestCLL>(id);
    ASSERT(!res2.isLeft);
    TestCLL tmp4 = res2.getValue();

    ASSERT_EQ(tmp4.someIndex, 1);
    ASSERT_EQ(tmp4.name, "World");

}

void testOrm02()
{
    MySQLWorker mysql;
    mysql.connect("192.168.10.101", "root", "123", "testDB");
    ASSERT(mysql.isConnected());
    orm::Database db(&mysql);
    db.registerModel<TestCLL>();
    db.createScheme();
    db.createScheme();
    db.createScheme();
    TestCLL t1, t2, t3, r1, r2 ,r3;
    t1.someIndex = 1;
    t2.someIndex = 2;
    t3.someIndex = 3;
    int id2 = db.newInst(t2);
    int id3 = db.newInst(t3);
    int id1 = db.newInst(t1);

    db.createScheme();

    r1 = db.getInstById<TestCLL>(id1).getValue();
    r3 = db.getInstById<TestCLL>(id3).getValue();
    r2 = db.getInstById<TestCLL>(id2).getValue();
    
    ASSERT_EQ(r1.someIndex, t1.someIndex);
    ASSERT_EQ(r2.someIndex, t2.someIndex);
    ASSERT_EQ(r3.someIndex, t3.someIndex);

    db.deleteInst<TestCLL>(id2);
    ASSERT(db.getInstById<TestCLL>(id2).isLeft);
    ASSERT(!db.getInstById<TestCLL>(id3).isLeft);
    ASSERT(!db.getInstById<TestCLL>(id1).isLeft);
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
        RUN_TEST(testOrmCreation01);
        RUN_TEST(testOrm02);
        MySQLWorker mysql;
        mysql.connect("192.168.10.101", "root", "123", "pract");
        mysql.query("DROP DATABASE testDB");
    }else{
        printf("Cannot runn db tests\n");
    }
}

void testCompareVectors01()
{
    std::vector<int> v1;
    std::vector<int> v2;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    ASSERT(isVectorsAreTheSame(v1, v2));
    v2.push_back(4);
    v1.push_back(6);
    ASSERT(!isVectorsAreTheSame(v1, v2));
}

int main()
{
    RUN_TEST(testTemplateEngine01);
    RUN_TEST(testTemplateEngine02);
    RUN_TEST(testTemplateEngine03);
    RUN_TEST(testTemplateEngine04);
    RUN_TEST(testCompareVectors01);
    dataBaseTests();
    return 0;
}
