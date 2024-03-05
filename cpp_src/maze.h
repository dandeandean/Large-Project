#ifndef MAZE_H
#define MAZE_H

#define COLS 50
#define ROWS 20
#define BUFSIZE ROWS *COLS + 20 // plus 20

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>

typedef enum Symbol { PATH, WALL, WALK, START, GOAL, UNK } Symbol;

typedef struct Point{
  int row;
  int col;
} Point;

typedef struct Node {
  Symbol symbol;
  int row;
  int col;
} Node;

typedef struct Path {
  Node last_node;
} Path;

typedef struct Maze {
  Symbol imap[ROWS][COLS];
  Node *start;
  Node *end;
  std::vector<Point> get_walkable_neighbors(Point p);
} Maze;

Symbol char_to_sym(char c) {
  switch (c) {
  case ' ':
    return PATH;
  case '#':
    return WALL;
  case 'S':
    return START;
  case 'F':
    return GOAL;
  case '.':
    return WALK;
  default:
    return UNK;
  }
}

char sym_to_char(Symbol s) {
  switch (s) {
  case PATH:
    return ' ';
  case WALL:
    return '#';
  case START:
    return 'S';
  case GOAL:
    return 'F';
  case WALK:
    return '.';
  default:
    return '?';
  }
}

int load_maze(std::string file_name, Maze *maze) ;
void print_map(Maze *m) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%c", sym_to_char(m->imap[i][j]));
    }
    std::cout << std::endl;
  }
}
/*From Lab1 code*/
int fileSize(char *filename) {
  struct stat file_status;
  if (stat(filename, &file_status) < 0)
    return -1;
  else
    return file_status.st_size;
}

#endif // MACRO
