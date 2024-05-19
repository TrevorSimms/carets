// config for level data
// functions for entities interfacing with level data
#include "include.h"
#include "lvlconf.h"

// Functional core of importLevel().
int importLevelCore(char *filename, LevelMap *map)
{
	FILE *lvptr; 
	lvptr = fopen(filename,"r");

	if(lvptr == NULL) {
        perror("Cannot access level data. \n");
		exit(1);
	}

	// transfer file data to buffer char array
	int col = 0, row = 0;
	int r_i = 0;
	char i_ch = 0, buff[1000]; 
	do {
		i_ch = fgetc(lvptr);
		buff[r_i] = i_ch;
		r_i++;
	} while (i_ch != EOF);
	
	// get cols
	while(buff[col] != 0x0a)
		col++;

	// get rows
	row = r_i / (col + 1);

	// transfer file buffer data into level data
	char *level = malloc((row * col) * sizeof(char));
	int l_i = 0, l_j = 0; 
	r_i = 0;
	while (buff[r_i] != EOF){
		if(buff[r_i] == '\n') {
			r_i++;
			l_i = 0;
			l_j++;
			continue;
		}
		level[l_j * col + l_i] = buff[r_i];
		r_i++;
		l_i++;
	}
	map->rows = row;
	map->cols = col;
	map->map = level;
	return 1;
}

// Get data from file and use it to populate fields in map.
// If successful, increment lvct.
int importLevel(char *filename, LevelMap *map, int lvct, Boolean bNext) 
{
	char bImport = importLevelCore(filename, map);
	if (bImport == 0) {
		printf("it broke, sowwy :<\n");
		return -1;
	}
	return lvct + bNext;
}

// For a given ascii item, get # of instances of it in lv.
int getItemCount(char item, LevelMap map)
{
	int count = 0;
	for(int i = 0; i < map.rows; i++)
		for(int j = 0; j < map.cols; j++) 
			if(map.map[i * map.cols + j] == item)
				count++;

	return count;
}

// Searches along each column in a row before traversing to
// the next row in order to find 'item.' If the nth instance
// of item is found, return its position. 
// Returns coordinates (-1,-1) if item not found.
MapPosition getItemPos(char item, int n, LevelMap map)
{
    MapPosition itemPos;
    int count = n;
    for (int i = 0; i < map.rows; i++)
        for (int j = 0; j < map.cols; j++)
            if(map.map[i * map.cols + j] == item) {
                count--;
                if(count == 0) {
                    itemPos.x = j;
                    itemPos.y = i;
                    return itemPos;
                }
            }
	
    itemPos.x = -1;
    itemPos.y = -1;
    return itemPos;
} // Converted tabs to spaces but just for this one function.

// Initialize level map.
void initMap(char *filename, LevelMap *map, LevelProperties *prop, Boolean bNext)
{
	prop->factor = 5;
	prop->currLvl = importLevel(filename, map, prop->currLvl, bNext);
	prop->nCarrot = getItemCount('^', *(map));
	prop->plrInitPos = getItemPos('@', 1, *(map)); // entity id's should be 1
	prop->exitPos = getItemPos('$', 1, *(map));
}

// Checks if (x,y) is within bounds.
Boolean isValidPos(int x, int y, LevelMap map)
{
    if((x < 0) || (y < 0) || (x >= map.cols) || (y >= map.rows))
        return False;
    return True;
}

// Returns a MapPosition struct if (x,y) are valid. Otherwise,
// returns an invalid MapPosition.
MapPosition createMapPos(int x, int y, LevelMap map) 
{
    MapPosition pos;
    if(isValidPos(x, y, map)) {
        pos.x = x;
        pos.y = y;
        return pos;
    }
    pos.x = -1;
    pos.y = -1;
    return pos;
}

Boolean mapPosCmp(MapPosition map1, MapPosition map2)
{
    return (Boolean)(map1.x == map2.x) && (map1.y == map2.y);
}

// Get Item at MapPosition.
char getItemAt(MapPosition pos, LevelMap map) 
{ 
    return map.map[pos.y * map.cols + pos.x]; 
}

//Set Item at MapPosition.
void setItemAt(char item, MapPosition pos, LevelMap* map) 
{
    map->map[pos.y * map->cols + pos.x] = item;
}

// Prints map and UI, given map and prop structs.
// TODO: will be refactored to generate "windowed maps" idk
// TODO: Color map based on Entity Color
void genMap(Level lvl)
{
	for(int i = 0; i < lvl.mapData.rows; i++)
		for(int j = 0; j < lvl.mapData.cols; j++)
			parseTile(lvl, j, i, lvl.prop.factor);

	mvprintw(lvl.prop.factor, lvl.prop.factor * 2 + lvl.mapData.cols, "\t lv:\t%d", lvl.prop.currLvl);
    mvprintw(lvl.prop.factor + 1, lvl.prop.factor * 2 + lvl.mapData.cols, "\t %c:\t%d", '^', lvl.prop.nCarrot);
}

// Isn't the most elegant way of handling tile color.
// What if we want to change the entity color via
// entity state change? No.
void parseTile(Level lvl, int x, int y, int factor)
{
    char tile = lvl.mapData.map[y * lvl.mapData.cols + x];
    int posX = factor * 2 + x;
    int posY = factor + y;
	switch(tile) {
		case ' ':
            mvaddch_colorized(Floor, posX, posY, '.');
			return;
		case '#':
            mvaddch_colorized(Wall, posX, posY, 'h');
			return; 
		case '@':
            mvaddch_colorized(lvl.entities.Player->color, posX, posY, tile);
			return;
		case '$':
            mvaddch_colorized(lvl.entities.LevelExit->color, posX, posY, tile);
			return;
		case '^':
            mvaddch_colorized(Carrot, posX, posY, tile);
			return;
		case '+':
            mvaddch_colorized(lvl.entities.LevelGate->color, posX, posY, '#');
			return;
		default:
			return;
	}
	return;
}

// helps parseTile do work
void mvaddch_colorized(Color clr, int x, int y, char ch)
{
    attron(COLOR_PAIR(clr));
    mvaddch(y, x, ch);
    attroff(COLOR_PAIR(clr)); 
}
