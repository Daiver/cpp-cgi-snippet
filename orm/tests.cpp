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
    void initOrm(std::vector<functional::Tripple<std::string, std::string, std::string> > *fields)
    {
        fields->push_back(ORM_MODEL_FIELD(i));
        fields->push_back(ORM_MODEL_FIELD(s));
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
    ASSERT(q == "INSERT INTO `TestCl` VALUES(10, 'zero');");
}


int main()
{
    RUN_TEST(testExport01);
    RUN_TEST(testField01);
    RUN_TEST(testField02);
    RUN_TEST(testField03);
    return 0;
}
