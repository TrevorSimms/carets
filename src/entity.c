// Entity functionality and state management.
#include "include.h"
#include "entity.h"
#include "structs.h"
#include "lvlconf.h"

// Initializes an Entity that has been allocated
void initEntity(Entity *ent, int inst, char sprite, Color clr, MapPosition map, Boolean bp)
{
    ent->id = inst;
    ent->sprite = sprite;
    ent->color = clr;
    ent->position = map;
    ent->bPlayable = bp;
}

// Allocates and initializes an item that appears exactly once.
// Returns an Entity pointer to malloc() allocated heap memory.
Entity *initSingleEntity(LevelMap map, char item, Color clr, Boolean bp) 
{
    Entity *ent;
    ent = malloc(sizeof(Entity));
    initEntity(ent, 0, item, clr, getItemPos(item, 1, map), bp);
    return ent;

}

// Allocates and initializes all items of the same kind in a map.
// Returns an Entity pointer to calloc() allocated heap memory.
Entity* initSerialEntities(LevelMap map, char item, Color clr) 
{
    Entity *ents;
    int itemct = getItemCount(item, map);
    ents = calloc(itemct, sizeof(Entity));
    for(int m = 0; m < itemct; m++)
        initEntity(&ents[m], m, item, clr, getItemPos(item, m+1, map), False);
    
    return ents;
}

void initLevelEntities(LevelEntities *entities, LevelMap map) 
{
    entities->Player = initSingleEntity(map, '@', Player, True);
    entities->Carrots = initSerialEntities(map, '^', Carrot);
    entities->Carrots = initSerialEntities(map, '!', Hazard);
    entities->LevelGate = initSingleEntity(map, '+', Gate, False);
    entities->LevelExit = initSingleEntity(map, '$', Exit, False);
}

// getters, for what shall fate say otherwise?
int getEntID(Entity *ent) { return ent->id; }
char getEntSprite(Entity *ent) { return ent->sprite; }
Color getEntColor(Entity *ent) { return ent->color; }
MapPosition getEntPosition(Entity *ent) { return ent->position; }
Boolean isPlayable(Entity *ent) { return ent->bPlayable; }
