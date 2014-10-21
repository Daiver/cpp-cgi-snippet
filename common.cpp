#include "common.h"

std::string replaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::string readFile(const std::string &fileName)
{
    std::string line ;
    std::string res = "";
    std::ifstream infile(fileName.c_str()) ;
    if ( infile ) 
        while ( getline( infile , line ) ) 
            res += line + '\n';
    infile.close( ) ;
    return res;
}

void writeFile(const std::string &fileName, const std::string &s)
{
    std::ofstream out(fileName.c_str());
    out << s;
    out.close();
}
