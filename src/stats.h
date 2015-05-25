#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <cstdio>
#include "fonctions_json.h"
#include "json/json.h"

#include <sstream>
#include <ostream>
#include <istream>
#include <fstream>

#include "constantes.h"

void checkStatFile();
void increaseSearchCount();
void increaseViewedPicture();
void increaseDownloadedPicture();
void increasePostsLoaded();
void increaseThumbLoaded();
void increaseThreadLoaded();
void increaseBoardView(std::string board);

#endif // STATS_H
