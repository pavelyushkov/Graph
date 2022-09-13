#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node {
  int x;
  int y;
  char* name;
  int edges;
  int colour; // 0 - белый, 1 - серый
  double range;
  struct Node* pred;
  struct Node** near;
  struct Node* next;
} Node;

typedef struct Graph {
  int count;
  Node* nodes;
  int** matrix;
} Graph;

#endif // STRUCT_H
