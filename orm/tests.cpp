#include "../minitest.h"
#include "orm.h"

class TestCl
{
public:
    int i;
    std::string s;
    void initOrm(std::vector<std::pair<std::string, std::string> > *fields)
    {
        fields->push_back(ORM_MODEL_FIELD(i).getSQLNameAndType());
        fields->push_back(ORM_MODEL_FIELD(s).getSQLNameAndType());
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
    orm::OrmField<int> f = ORM_MODEL_FIELD(i);
    ASSERT(f.fieldValue == 10);
    ASSERT(f.fieldName == "i");
}

void testField02()
{
    orm::Database db;
    db.registerModel<TestCl>();
    std::string q = db.models[0].getCreationTableQuery();
    ASSERT(q == "CREATE TABLE `orm_model_TestCl` (`orm_id_TestCl` INT NOT NULL AUTO_INCREMENT, `i` INT, `s` VARCHAR(256), PRIMARY KEY(`orm_id_TestCl`));");
}

int main()
{
    RUN_TEST(testExport01);
    RUN_TEST(testField01);
    RUN_TEST(testField02);
    return 0;
}
