#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>

#ifndef UTILS_H
#define UTILS_H

void CreateList(std::vector <std::string> List, std::string fileName);
std::vector <std::string> LoadList(std::string fileName);
void WriteVector(std::vector <std::string> Vector);
std::vector <std::string> EraseDuplicates(std::vector <std::string> Vector);
std::vector <std::string> EraseElement(std::vector <std::string> Vector, std::string Element);
bool exists_test1 (const std::string& name);

#endif
