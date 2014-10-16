#include <stdio.h>
#include <string>
#include <map>

#include "minitest.h"
#include "commoncgi.h"
#include "templateengine.h"

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

int main()
{
    RUN_TEST(testTemplateEngine01);
    return 0;
}
