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

int main()
{
    RUN_TEST(testExport01);
    return 0;
}
