#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "extra.h"

void mainMenu(){
  printf("\nEnter 1 to out matrix.");
  printf("\nEnter 2 to add node.");
  printf("\nEnter 3 to add edge.");
  printf("\nEnter 4 to delete node");
  printf("\nEnter 5 to delete edge");
  printf("\nEnter 6 to find way by DFS");
  printf("\nEnter 7 to find the shortest way between nodes");
  printf("\nEnter 0 to finish.");
}
void outMatrix(Graph* graph){
  printf("\n\n");
  Node* elem = graph->nodes;
  printf(" ");
  for(int i = 0; i < graph->count; ++i){
    printf("  %s", elem->name);
    elem = elem->next;
  }
  printf("\n ");
  for(int i = 0; i < graph->count; ++i)
    printf("---");
  elem = graph->nodes;
  for(int i = 0; i < graph->count; ++i){
    printf("\n%s| ", elem->name);
    for(int k = 0; k < graph->count; ++k)
      printf("%d  ", graph->matrix[i][k]);
    elem = elem->next;
  }
  printf("\n\n");
  return;
}
void freeMatrix(int** matrix, int size){
  for(int i = 0; i < size; ++i){
    free(matrix[i]);
  }
  free(matrix);
  matrix = NULL;
}
void freeGraph(Graph* graph){
  freeMatrix(graph->matrix, graph->count);
  Node* tmp = graph->nodes;
  Node* pass = NULL;
  while(tmp != NULL){
    pass = tmp;
    tmp = tmp->next;
    free(pass->near);
    free(pass->name);
    free(pass);
  }
  free(graph);
}
