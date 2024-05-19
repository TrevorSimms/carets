// config for application runtime environment
#include "include.h"
#include "structs.h"
#include "gameconf.h"

// Initialize the ncurses environment.
void cursesInit(void) 
{
    // ncurses init
    initscr();
    noecho();
    raw();
    keypad(stdscr, TRUE);
    curs_set(0);
    setlocale(LC_ALL, "");
}

// Initialize game colors.
void colorInit(void)
{
    start_color();
    init_pair(Floor, COLOR_WHITE, COLOR_BLACK); // floor
    init_pair(Wall, COLOR_GREEN, COLOR_GREEN); // walls
    init_pair(Exit, COLOR_YELLOW, COLOR_BLUE); // Exit
    init_pair(Carrot, COLOR_YELLOW, COLOR_BLACK); // Carrots
    init_pair(Player, COLOR_CYAN, COLOR_BLACK); // Player
    init_pair(Gate, COLOR_BLACK, COLOR_CYAN); // Gate
    init_pair(Hazard, COLOR_YELLOW, COLOR_RED); // Hazard
    init_pair(Enemy, COLOR_RED, COLOR_BLACK); // Enemy
}

void destructLevel(Level* lvl)
{
    free(lvl->mapData.map);
    free(lvl->entities.Player);
    free(lvl->entities.Carrots);
    free(lvl->entities.LevelGate);
    free(lvl->entities.LevelExit);
}
