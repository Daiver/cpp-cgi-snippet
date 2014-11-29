#include "common.hpp"

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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string getExtensionOfFileByPath(std::string s)
{
    std::vector<std::string> splited = split(s, '.');
    return splited[splited.size() - 1];
}

std::string pathToFile(const std::string &s)
{
    std::vector<std::string> vec = split(s, '/');
    std::string res;
    for(int i = 0; i < vec.size() - 1; ++i)
        res += vec[i] + '/';
    return res;
}
