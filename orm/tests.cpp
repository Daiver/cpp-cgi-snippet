#include "../minitest.h"
#include "orm.h"

class TestCl
{
public:
    int i;
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
int main()
{
    RUN_TEST(testExport01);
    RUN_TEST(testField01);
    return 0;
}
