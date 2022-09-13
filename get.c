#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <readline/readline.h>
#include "struct.h"
#include "get.h"

int get_integer(){
  unsigned int res = 0;
  int q, i, flag = 1;
  char* input = NULL;
  while(flag == 1){
   if(input != NULL)
      free(input);
    input = readline("");
    if(input == NULL)
      return 0;
    q = strlen(input);
    for(i = 0; i < q; i++){
      if(!isdigit(input[i])){
        printf("\nWrong input. Try again:   ");
        flag = 1;
        break;
      }
      if(i == (q - 1))
        flag = 0;
    }
    res = atoi(input);
  }
  free(input);
  return res;
}

Node* getNode(){
  Node* node = (Node*) malloc(sizeof(Node));
  printf("\nEnter x:  ");
  node->x = get_integer();
  printf("\nEnter y:  ");
  node->y = get_integer();
  node->name = readline("\nEnter name:  ");
  node->next = NULL;
  node->edges = 0;
  node->near = (Node**) calloc(1, sizeof(Node*));
  return node;
}

double getWeight(Node* elem, Node* pass){
  int y = elem->y - pass->y;
  int x = elem->x - pass->x;
  return pow((x*x + y*y), (1/2));
}
char* getWay(Node* pass){
  char* way = NULL, *point;
  point = (char*) calloc(2, sizeof(char));
  point[0] = '-';
  int way_len = 0;
  Node* tmp = pass;
  while(tmp != NULL){
    way_len = way_len + strlen(tmp->name);
    tmp = tmp->pred;
    if(tmp)
      way_len += 2;
  }
  way = (char*) calloc(way_len + 1, sizeof(char));
  int i = 0;
  tmp = pass;
  while(tmp != NULL){
    strcat(way, tmp->name);
    tmp = tmp->pred;
    if(tmp)
      strcat(way, point);
  }
  free(point);
  return way;
}
