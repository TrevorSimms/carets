#include "include.h"
#include "structs.h"
#include "entity.h"
#include "lvlconf.h"
#include "logic.h"

// Central Game Logic
void parseKeyInput(int input, Entity *ent, Level *lvl, RuntimeFlags *flags)
{
    // Error preparedness! :D
    FILE *log;
    // Easy peasy lembu squeasy -- OR NOT :/
    MapPosition mapCursor = lvl->entities.Player->position;
    switch(input) {
        case Up: case 'k':
            mapCursor.y = mapCursor.y - 1;
            break;
        case Down: case 'j':
            mapCursor.y = mapCursor.y + 1;
            break;
        case Left: case 'h':
            mapCursor.x = mapCursor.x - 1;
            break;
        case Right: case 'l':
            mapCursor.x = mapCursor.x + 1;
            break;
        case Restart:
            flags->bReset = True;
            return;
        case Quit:
            flags->bRun = False;
            flags->bQuit = True;
            return;
        /** Debug control, delete when exporting **
        case 'n':
            flags->bRun = False;
            return;
        ** End Debug */
        default:
            return;
    }
    // Stay inside your slave quarters, peon!! :D
    if (!(isValidPos(mapCursor.x, mapCursor.y, lvl->mapData))) {
        fprintf(stderr, "Unable to control Entity. Added incident to Logs.\n");
        log = fopen("./nrucres.log","a");
        fprintf(log, "\n\n-- New Log --\n\n");
        fprintf(log, "Attempted to travel to location: (%d,%d)\n", mapCursor.x, mapCursor.y);
        exit(1);
        return;
    }
    char cursItem = getItemAt(mapCursor, lvl->mapData);
    switch (cursItem) {
        case '#':
            // do nothing
            return;
        case ' ':
            teleEntity(lvl->entities.Player, mapCursor, &(lvl->mapData));
            break;
        case '^':
            lvl->prop.nCarrot--;
            teleEntity(lvl->entities.Player, mapCursor, &(lvl->mapData));
            break;
        case '+':
            if(lvl->prop.nCarrot == 0) 
                teleEntity(lvl->entities.Player, mapCursor, &(lvl->mapData));
            break;
        case '$':
            teleEntity(lvl->entities.Player, mapCursor, &(lvl->mapData));
            lvl->entities.Player->color = Exit;
            flags->bRun = False;
            break;
        case '!':
            teleEntity(lvl->entities.Player, mapCursor, &(lvl->mapData));
            lvl->entities.Player->color = Hazard;
            genMap(*lvl);
            refresh();
            mvprintw(lvl->mapData.rows + lvl->prop.factor + 1, 2 * lvl->prop.factor,
                "Oh h*ck, I can't believe you've done this.");
            getch();
            flags->bReset = True;
            break;
        default:
            return;
    }
}



// Notice: User must validate that `pos` is an empty space in map. 
//    Failing to validate thusly may break the level acted upon.
// Teleports entity to `pos` position in map.
void teleEntity(Entity *ent, MapPosition pos, LevelMap *map)
{
    setItemAt(ent->sprite, pos, map);
    setItemAt(' ', ent->position, map);
    ent->position = pos;
    refresh();
}
