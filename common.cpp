#include "common.h"


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
