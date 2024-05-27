#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "structs.h"

void parseKeyInput(int, Entity*, Level*, RuntimeFlags*);
void teleEntity(Entity*, MapPosition, LevelMap*);

#endif