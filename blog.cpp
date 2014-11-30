#include <stdio.h>
#include <iostream>

#include "requesthandler.hpp"
#include "responsehandler.hpp"
#include "common.hpp"
#include "functional/either.hpp"
#include "templateengine.hpp"
#include "sqlworker.hpp"
#include "mysqlworker.hpp"

#include "orm/orm.hpp"

class BlogPost
{
public:
    BlogPost()
    {
    }

    void initOrm(orm::OrmFieldHandler handler)
    {
        handler << ORM_MODEL_FIELD(postCaption);
        handler << ORM_MODEL_FIELD(postText);
    }

    std::string postCaption;
    std::string postText;
};
ORM_EXPORT_CLASS(BlogPost);

int main(int argc, char **argv)
{
    std::string pathToExe = pathToFile(argv[0]);
    std::string exeName   = last(split(argv[0], '/'));

    MySQLWorker mysql;
    mysql.connect("192.168.10.101", "root", "123", "blogDB");
    orm::Database db(&mysql);
    db.registerModel<BlogPost>();
    if(argc > 1){
        std::cout << "Migrate" << std::endl;
            db.createScheme();
        return 0;
    }


    cgi::RequestHandler request;
    cgi::ResponseHandler response;
    cgi::RequestArgs args = request.getArgs();
    cgi::RequestArgs cont;
    cont["STATIC_PATH"] = exeName + "?staticfile=";

    if (args.count("staticfile")){
        std::string reqFile = args["staticfile"];
        std::string res = readFile(std::string("../static/") + reqFile);
        if(getExtensionOfFileByPath(reqFile) == "js")
            response.mimeType = "text/javascript";
        response << res;
    }else{
        response << cgi::TemplateEngine::renderTemplate(readFile(pathToExe + "../templates/blogindex.html"), cont).getValue();

    }
    response.send();
    return 1;
}

