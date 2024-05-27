// Objectives:
// -- Provide functionality to Playable Entities
// -- Add functionality to check if carrots have been picked up
//    -- Provide some means to 
#include "include.h"
#include "structs.h"
#include "entity.h"
#include "lvlconf.h"
#include "gameconf.h"
#include "logic.h"



int main(int argc, char **argv) 
{
    // TODO: stop hardcoding the level path eventually, if still possible ;_;
    Level lvl;
    lvl.prop.currLvl = 0;
    // probably should be its own structure?
    char *lvlFolder[] = {
        "./.levels/lvpk1/lv01",
        "./.levels/lvpk1/lv02",
        "./.levels/lvpk1/lv03",
        "./.levels/lvpk1/lv04",
        "./.levels/lvpk1/lv05",
        "./.levels/lvpk1/lv06"
    };
    char lvlQuantity = sizeof(lvlFolder) / sizeof(lvlFolder[0]);

    cursesInit();
    colorInit();

    /** Logging only **
    FILE* log;
    log = fopen("./nrucres.log", "a");
    fprintf(log, "\n\n--New Log--\n\n"); **/

    // Game Loop Environment Setup
    RuntimeFlags flags;
	int input;
    // Game Loop -- Level Iterator
    for(int l = 0; l < lvlQuantity; l++) {
        // Map initialization
        clear();
        flags.bRun = True; flags.bReset = False; 
        flags.bQuit = False;
        initMap(lvlFolder[l], &(lvl.mapData), &(lvl.prop), True);
        initLevelEntities(&lvl.entities,lvl.mapData);
        genMap(lvl);

        refresh();
        /** game loop here **/
        // Game Loop -- Level Logic
        while(flags.bRun) {
            input = getch();
			parseKeyInput(input, lvl.entities.Player, &lvl, &(flags));
            if(flags.bReset) {
                clear();
                initMap(lvlFolder[l], &(lvl.mapData), &(lvl.prop), False);
                initLevelEntities(&lvl.entities,lvl.mapData);
                flags.bReset = False;
            }
            if(flags.bQuit) break;
            genMap(lvl);
            refresh();
        } /**/
        if(flags.bQuit) break;
        mvprintw(lvl.prop.factor+ lvl.mapData.rows +1, lvl.prop.factor * 2, 
            "Passed Level %d!", lvl.prop.currLvl);
        getch();
    }
    if(flags.bQuit == False) {
        mvprintw(lvl.prop.factor+ lvl.mapData.rows + 2, lvl.prop.factor * 2, 
            "Congradulations~!!");
        getch();
    }
    destructLevel(&lvl);
    endwin();

    return 0;
}
