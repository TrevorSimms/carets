// types
#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "include.h"

typedef struct MapPosition MapPosition;
typedef enum Boolean Boolean;
typedef enum Color Color;
typedef enum Control Control;
typedef struct RuntimeFlags RuntimeFlags;
typedef struct LevelMap LevelMap;
typedef struct LevelProperties LevelProperties;
typedef struct Entity Entity;
typedef struct LevelEntities LevelEntities;
typedef struct Level Level;


struct MapPosition {
    int x;
    int y;
};

enum Boolean {
    False,
    True
};

enum Control {
    Up = KEY_UP,
    Down = KEY_DOWN,
    Left = KEY_LEFT,
    Right = KEY_RIGHT,
    Restart = 'r',
    Quit = 'q'
};

enum Color {
    Floor,
    Wall,
    Exit,
    Carrot,
    Player,
    Gate,
    Hazard,
    Enemy
};

struct RuntimeFlags {
    Boolean bRun;
    Boolean bReset;
    Boolean bQuit;
};

struct LevelMap {
    int rows;
    int cols;
    char* map; // access with map[i * cols + j]
};

struct LevelProperties {
    int currLvl;
    int nCarrot;
    int factor; // TODO: make more dynamic to fit needs of a given map
    MapPosition plrInitPos;
    MapPosition exitPos;
};


struct Entity {
    int id;
    char sprite;
    Color color;
    MapPosition position;
    int bPlayable;
};

struct LevelEntities {
    Entity *Player;
    Entity *Carrots;
    Entity *LevelGate;
    Entity *LevelExit;
};

struct Level {
    LevelMap mapData;
    LevelProperties prop;
    LevelEntities entities;
};

#endif
