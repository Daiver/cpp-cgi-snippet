#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <fstream>
#include <vector>
#include <sstream>

std::string readFile(const std::string &fileName);
void writeFile(const std::string &fileName, const std::string &s);

std::string replaceString(std::string subject, const std::string& search,
                                  const std::string& replace);

template<typename T>
bool compareOperator(const T &a, const T &b)
{
    return a == b;
}

template<typename T, typename Comparator>
bool isVectorsAreTheSame(const std::vector<T> &a, const std::vector<T> &b, Comparator compare)
{
    if(a.size() != b.size())
        return false;
    for(int i = 0; i < a.size(); ++i)
        if(!compare(a[i], b[i]))
            return false;
    return true;
}

template<typename T>
bool isVectorsAreTheSame(const std::vector<T> &a, const std::vector<T> &b)
{
    return isVectorsAreTheSame(a, b, &compareOperator<T>);
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) ;

std::vector<std::string> split(const std::string &s, char delim);


#ifdef __GNUG__
#define TYPEOF(x) __typeof__((x))
#endif

#endif
