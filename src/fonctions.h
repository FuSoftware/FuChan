#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <iostream>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstring>
#include <ctime>
#include <cstdint>
#include <string.h>
#include <fstream>
#include <sstream>

void copyFile(std::string source, std::string dest);

bool isPair(int number);
void checkFolder(std::string path);

std::string int64ToString(int64_t i);
std::string ULintToString(unsigned long int i);
std::string intToString(int i);
char* stringToCString(std::string input);

const std::string currentDateTime();
void outputInfo(std::string type, std::string data, int level);

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
int cachingFile(const char *url, char outfilename[4096], bool output, bool check_file_presence);

#endif // FONCTIONS_H
