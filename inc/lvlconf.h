// level functionality
#ifndef __LVLCONF_H__
#define __LVLCONF_H__

#include "structs.h"

int importLevelCore(char*, LevelMap*);
int importLevel(char*, LevelMap*, int, Boolean);
int getItemCount(char, LevelMap);
MapPosition getItemPos(char, int, LevelMap);
void initMap(char*, LevelMap*, LevelProperties*, Boolean);
Boolean isValidPos(int, int, LevelMap);
MapPosition createMapPos(int, int, LevelMap);
Boolean mapPosCmp(MapPosition, MapPosition);
char getItemAt(MapPosition, LevelMap);
void setItemAt(char, MapPosition, LevelMap*);
void genMap(Level);
void parseTile(Level, int, int, int);
void mvaddch_colorized(Color, int, int, char);

#endif
