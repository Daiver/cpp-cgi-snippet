#include <stdio.h>
#include <string>
#include <iostream>
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

int main()
{
    RUN_TEST(testTemplateEngine01);
    RUN_TEST(testTemplateEngine02);
    RUN_TEST(testTemplateEngine03);
    RUN_TEST(testTemplateEngine04);
    return 0;
}
