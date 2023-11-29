#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include <map>

void printHeader();
std::map<std::string, double> openFile(std::string);
void printBracket(std::string, std::string);
std::string printFillChar(std::string, const std::string&, const std::string&);

#endif
