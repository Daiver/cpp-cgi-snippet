#include "../minitest.h"
#include "orm.h"

class TestCl
{
public:
    TestCl()
    {
        this->i = 10;
        this->s = "zero";
    }

    int i;
    std::string s;
    //void initOrm(std::vector<functional::Tripple<std::string, std::string, std::string> > *fields)
    void initOrm(orm::OrmFieldHandler handler)
    {
        handler << (ORM_MODEL_FIELD(i));
        handler << (ORM_MODEL_FIELD(s));
    }
};
ORM_EXPORT_CLASS(TestCl);

void testExport01()
{
    orm::Database db;
    ASSERT(db.getClassName<TestCl>() == "TestCl");
}

void testField01()
{
    int i = 10;
    //orm::OrmField<int> f = ORM_MODEL_FIELD(i);
    //ASSERT(f.fieldValue == 10);
    //ASSERT(f.fieldName == "i");
}

void testField02()
{
    orm::Database db;
    db.registerModel<TestCl>();
    std::string q = db.models[0].getCreationTableQuery();
    ASSERT(q == "CREATE TABLE `orm_model_TestCl` (`orm_id_TestCl` INT NOT NULL AUTO_INCREMENT, `i` INT, `s` VARCHAR(256), PRIMARY KEY(`orm_id_TestCl`));");
}

void testField03()
{
    orm::Database db;
    db.registerModel<TestCl>();
    std::string q = db.models[0].getInsertQuery();
    ASSERT_EQ(q, "INSERT INTO `orm_model_TestCl` (i, s) VALUES(10, 'zero');");
}

void testField04()
{
    orm::Database db;
    db.registerModel<TestCl>();
    std::string q = db.models[0].getUpdateQuery(1);
    ASSERT_EQ(q, "UPDATE `orm_model_TestCl` SET i=10, s='zero' WHERE orm_id_TestCl=1");
}

void testField05()
{
    orm::Database db;
    db.registerModel<TestCl>();
    std::string q = db.models[0].getSelectByIdQuery(1);
    ASSERT_EQ(q, "SELECT * FROM `orm_model_TestCl`");
}

void testStream01()
{
    int i = orm::sqlTypeFromString<int>("12");
    ASSERT_EQ(i, 12);
}

int main()
{
    RUN_TEST(testExport01);
    RUN_TEST(testField01);
    RUN_TEST(testField02);
    RUN_TEST(testField03);
    RUN_TEST(testField04);
    RUN_TEST(testField05);
    RUN_TEST(testStream01);
    return 0;
}
