
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <algorithm>
#include "utils.h"

//przekazywanie danych wektora do pliku (jesli plik istnieje, to zostanie on nadpisany)
void CreateList(std::vector <std::string> List, std::string fileName) {
	std::ofstream file;
	file.open(fileName.c_str());

	for (unsigned int i = 0; i < List.size(); i++)
	{
		file << List[i] << std::endl;
	}
	file.close();
}

//wczytywanie danych z pliku o danej nazwie do wektora, uwaga, funkcja tworzy wektor
std::vector <std::string> LoadList(std::string fileName) {
	std::vector <std::string> Vector;
	std::string line;
	std::ifstream file;
	file.open(fileName.c_str());

	if (file.is_open())
	{
		while (getline(file, line))
		{
			Vector.push_back(line);
		}
		file.close();
	}

	//else std::cout << "Unable to open file"; 

	return Vector;
}

//wypisywanie elementow wektora na ekran, uzywamy do tego iteratora
void WriteVector(std::vector <std::string> Vector) {
	
	//for(int i=0;i<50;i++) 
	for (std::vector<std::string>::const_iterator i = Vector.begin(); i != Vector.end(); ++i)
		std::cout << *i << std::endl;
	//for (int i=0;i<Vector.size();i++){
	//	mvprintw(23,23+i,(char*)Vector[i].c_str());
	//}
	
	}


//usuwanie powtarzajacych sie elementow w wketorze
std::vector <std::string> EraseDuplicates(std::vector <std::string> Vector) {
	sort(Vector.begin(), Vector.end());
	Vector.erase(unique(Vector.begin(), Vector.end()), Vector.end());
	return Vector;
}

//usuwanie wybranego elementu wektora po jego wartosci, jesli element sie powtarza usuwa tylko pierwszy w kolejnosci
std::vector <std::string> EraseElement(std::vector <std::string> Vector, std::string Element) {
	std::vector<std::string>::iterator position = std::find(Vector.begin(), Vector.end(), Element);
	if (position != Vector.end())
		Vector.erase(position);
	return Vector;
}

bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}