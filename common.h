#include <string>
#include <fstream>

std::string readFile(const std::string &fileName);
void writeFile(const std::string &fileName, const std::string &s);

std::string replaceString(std::string subject, const std::string& search,
                                  const std::string& replace);
