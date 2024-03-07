#include "maze.h"
#include <algorithm>

Node *init_node(Symbol s, int row, int col) {
  Node *out_node = (Node *)malloc(sizeof(Node));
  out_node->symbol = s;
  out_node->row = row;
  out_node->col = col;
  return out_node;
}

Maze *init_maze(char *file_name) {
  Maze *out_maze = (Maze *)malloc(sizeof(Maze));
  memset(out_maze->imap, 33, sizeof(int) * (COLS * ROWS ));
  // out_maze->nodes = (Node *) malloc(sizeof(Node*) * (COLS * ROWS));
  load_maze(file_name, out_maze);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      out_maze->nodes[i][j] = NULL; // Initialize to NULL or some other default value
    }
  }
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      /*This is a lot of pointers pointing */
      // Node *new = init_node(out_maze->imap[i][j], i, j);
      out_maze->nodes[i][j] = init_node(out_maze->imap[i][j], i, j);
      // std::cout << out_maze->nodes[i][j]->symbol << '\n';
      if (out_maze->nodes[i][j]->symbol == START) {
        out_maze->start = out_maze->nodes[i][j];
      }
      if (out_maze->nodes[i][j]->symbol == GOAL) {
        out_maze->end = out_maze->nodes[i][j];
      }
    }
  }
  return out_maze;
}

/*
  Loads the text file into the Maze object
*/
int load_maze(std::string file_name, Maze *maze) {
  std::ifstream file;
  file.open(file_name);
  std::string line;
  Symbol line_buf[COLS];
  int row_counter = 0;
  while (std::getline(file, line)) {
    for (int i = 0; i < line.length(); i++) {
      // std::cout << char_to_sym(line[i]);
      line_buf[i] = char_to_sym(line[i]);
    }
    /*Actual copyinging into the buf*/
    std::copy(std::begin(line_buf), std::end(line_buf),
              std::begin(maze->imap[row_counter]));
    row_counter++;
  }
  file.close();
  return 0;
}

std::vector<Node*> Maze::get_walkable_neighbors(int row, int col) {
  Point p = {row,col};
  int xs[4] = {-1, 1, 0, 0};
  int ys[4] = {0, 0, 1, -1};
  std::vector<Node*> out;
  for (int i = 0; i < 4; i++) {
    Point n = {p.row + xs[i], p.col + ys[i]};
    if ((n.col < 0 || n.col >= COLS) || (n.row < 0 || n.row >= ROWS)) {
      continue;
    }
    if (this->imap[n.row][n.col] != WALL) {
      out.push_back(this->nodes[n.row][n.col]);
    }
  }
  return out;
}

Path *Maze::bfs(void) {
  std::deque<Node*> queue;
  std::vector<Node*> been_to;
  queue.push_back(this->start);
  Path *agent;
  agent->last_point = this->start;
  while(!queue.empty()){
    Node * parent = queue.front();
    queue.pop_front();
    for (Node *child : this->get_walkable_neighbors(parent->row,parent->col)) {
      bool unvisited = (std::find(been_to.begin(), been_to.end(), child ) == been_to.end());
      if (unvisited){
        been_to.push_back(child);
        queue.push_back(child);
        // if (child->symbol == PATH) {
        //   child->symbol=WALK;
        // }
      }
    }
  }
  return agent;
}
