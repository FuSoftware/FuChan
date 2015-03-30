#ifndef FONCTIONS_JSON_H
#define FONCTIONS_JSON_H

#include <iostream>

#include "json/json.h"

Json::Value saveAndLoad(Json::Value root, const char *file);
Json::Value loadJSONFile(const char *filePath);
void saveJSONFile(const char *filePath, std::string data);

#endif // FONCTIONS_JSON_H
