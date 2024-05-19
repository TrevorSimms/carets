#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "structs.h"

void initEntity(Entity*, int, char, Color, MapPosition, Boolean);
Entity* initSingleEntity(LevelMap, char, Color, Boolean);
Entity* initSerialEntities(LevelMap, char, Color);
void initLevelEntities(LevelEntities *entities, LevelMap map);
// getters
int getEntID(Entity*);
char getEntSprite(Entity*);
Color getEntColor(Entity*);
MapPosition getEntPosition(Entity*);
Boolean isPlayable(Entity*);

#endif
