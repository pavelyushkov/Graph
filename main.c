#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "processing.h"

int main(){
  int check = 10, x, y;
  Graph* graph = createGraph();
  while(check != 0){
    mainMenu();
    printf("\n\nYour input:   ");
    check = get_integer();
    if(check == 1){
      if(graph->count == 0)
        printf("\nGraph is empty\n");
      else{
        outMatrix(graph);
      }
    }
    else if(check == 2){
      Node* node = getNode();
      graph = addNode(graph, node);
    }
    else if(check == 3){
      if(graph->count < 2)
        printf("\nNot enough nodes\n");
      else{
        char* n1 = readline("\nEnter first node:  ");
        char* n2 = readline("\nEnter second node:  ");
        if(!strcmp(n1, n2))
          printf("\nNodes can't be same\n");
        else{
          int res = addEdge(graph, n1, n2);
          if(res == 3)
            printf("\nWrong nodes entered\n");
          else if(res == 4)
            printf("\nEdge already exist\n");
        }
        free(n1);
        free(n2);
      }
    }
    else if(check == 4){
      if(graph->count == 0)
        printf("\nGraph is empty\n");
      else{
        char* name = readline("\nEnter node name:  ");
        int res = deleteNode(graph, name);
        if(res == 1)
          printf("\nNo such node\n");
        else
          printf("\nNode deleted\n");
        free(name);
      }
    }
    else if(check == 5){
      if(graph->count == 0)
        printf("\nGraph is empty\n");
      else{
        char* n1 = readline("\nEnter first node:  ");
        char* n2 = readline("\nEnter second node:  ");
        if(!strcmp(n1, n2))
          printf("\nNodes can't be same\n");
        else{
          int res = deleteEdge(graph, n1, n2);
          if(res == 3)
            printf("\nWrong nodes entered\n");
          else if(res == 4)
            printf("\nNo edge between these nodes\n");
        }
        free(n1);
        free(n2);
      }
    }
    else if(check == 6){
      char* n1 = readline("\nEnter first node:  ");
      char* n2 = readline("\nEnter second node:  ");
      if(!strcmp(n1, n2))
        printf("\nNodes can't be same\n");
      else{
        Node* pass = DFS(graph, n1, n2);
        if(!pass)
          printf("\nIncorrect data entered or no way between nodes\n");
        else{
          char* way = getWay(pass);
          printf("\nWay between your nodes:     %s\n", way);
          free(way);
        }
      }
      free(n1);
      free(n2);
    }
    else if(check == 7){
      char* n1 = readline("\nEnter first node:  ");
      char* n2 = readline("\nEnter second node:  ");
      if(!strcmp(n1, n2))
        printf("\nNodes can't be same\n");
      else{
        Node* pass = BFV(graph, n1, n2);
        if(!pass)
          printf("\nIncorrect data entered or no way between nodes\n");
        else{
          char* way = getWay(pass);
          printf("\nShortes way between your nodes:     %s\n", way);
          free(way);
        }
      }
      free(n1);
      free(n2);
    }
  }
  freeGraph(graph);
  printf("\n\nFinished successfully!\n\n");
  return 0;
}
