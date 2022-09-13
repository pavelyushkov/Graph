#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "processing.h"

Graph* addNode(Graph* graph, Node* node){
  if(graph->nodes == NULL){
    graph->nodes = node;
    graph->matrix = (int**) calloc(1, sizeof(int*));
    graph->matrix[0] = (int*) calloc(1, sizeof(int));
    graph->matrix[0][0] = 0;
    ++graph->count;
    return graph;
  }
  else{
    Node* elem = graph->nodes;
    while(elem->next != NULL)
      elem = elem->next;
    elem->next = node;
    ++graph->count;
    graph->matrix = (int**) realloc(graph->matrix, (graph->count * sizeof(int*)));
    for(int i = 0; i < graph->count; ++i){
      if(i == graph->count - 1)
        graph->matrix[i] = (int*) calloc(graph->count, sizeof(int));
      else
        graph->matrix[i] = (int*) realloc(graph->matrix[i], (graph->count * sizeof(int)));
      graph->matrix[i][graph->count - 1] = 0;
    }
    for(int i = 0; i < graph->count; ++i){
        graph->matrix[graph->count - 1][i] = 0;
    }
    return graph;
  }
}
void edgeArray(Node* elem, Node* pass){
  elem->near = (Node**) realloc(elem->near, (elem->edges * sizeof(Node*)));
  elem->near[elem->edges - 1] = pass;
  pass->near = (Node**) realloc(pass->near, (pass->edges * sizeof(Node*)));
  pass->near[pass->edges - 1] = elem;
  return;
}
int addEdge(Graph* graph, char* n1, char* n2){
  if(graph == NULL)
    return 1;
  if(graph->count < 2)
    return 2;
  int pos1 = 0, pos2 = 0;
  Node* elem = graph->nodes;
  while(elem != NULL){
    if(!strcmp(n1, elem->name))
      break;
    ++pos1;
    elem = elem->next;
  }
  if(pos1 == graph->count)
    return 3;
  Node* pass = graph->nodes;
  while(pass != NULL){
    if(!strcmp(n2, pass->name))
      break;
    ++pos2;
    pass = pass->next;
  }
  if(pos2 == graph->count)
    return 3;
  if(graph->matrix[pos1][pos2] == 1 || graph->matrix[pos2][pos1] == 1)
    return 4;
  graph->matrix[pos1][pos2] = 1;
  graph->matrix[pos2][pos1] = 1;
  ++elem->edges;
  ++pass->edges;
  edgeArray(elem, pass);
  return 0;
}
Graph* createGraph(){
  Graph* graph = (Graph*) malloc(sizeof(Graph));
  graph->nodes = NULL;
  graph->matrix = NULL;
  graph->count = 0;
  return graph;
}
void reorgNear(Node* pass, Node* elem){
  if(pass->edges > 1){
    Node** new_near = (Node**) calloc(pass->edges - 1, sizeof(Node*));
    int k = 0;
    for(int i = 0; i < pass->edges; ++i){
      if(pass->near[i] != elem){
        new_near[k] = pass->near[i];
        ++k;
      }
    }
    free(pass->near);
    pass->near = new_near;
    --pass->edges;
  }
  else if(pass->edges == 1){
    pass->edges = 0;
    free(pass->near);
    pass->near = (Node**) calloc(1, sizeof(Node*));
  }
  return;
}
int** reorgMatrix(Graph* graph, int pos){
  int k, d;
  int** new_matrix = (int**) calloc(graph->count - 1, sizeof(int*));
  for(int i = 0; i < graph->count - 1; ++i){
    new_matrix[i] = (int*) calloc(graph->count - 1, sizeof(int));
  }
  k = 0;
  for(int i = 0; i < graph->count; ++i){
    d = 0;
    if(i != pos){
      for(int j = 0; j < graph->count; ++j){
        if(j != pos){
          new_matrix[k][d] = graph->matrix[i][j];
          ++d;
        }
      }
      ++k;
    }
  }
  for(int i = 0; i < graph->count; ++i){
    free(graph->matrix[i]);
  }
  free(graph->matrix);
  return new_matrix;
}
int deleteNode(Graph* graph, char* name){
  if(graph->count == 1 && strcmp(name, graph->nodes->name) == 0){
    free(graph->nodes->name);
    free(graph->nodes->near);
    free(graph->nodes);
    graph->nodes = NULL;
    --graph->count;
    freeMatrix(graph->matrix, 1);
    graph->matrix = NULL;
    return 0;
  }
  int pos = 0;
  Node* elem = graph->nodes;
  while(strcmp(name, elem->name)){
      elem = elem->next;
      ++pos;
      if(elem == NULL)
        return 1;
  }
  for(int i = 0; i < elem->edges; ++i){
    reorgNear(elem->near[i], elem);
    --elem->near[i]->edges;
  }
  free(elem->near);
  if(graph->count == 1){
    for(int i = 0; i < graph->count; ++i){
      free(graph->matrix[i]);
    }
    free(graph->matrix);
    graph->matrix = NULL;
  }
  graph->matrix = reorgMatrix(graph, pos);
  --graph->count;
  if(graph->nodes == elem)
    graph->nodes = elem->next;
  else{
    Node* tmp = graph->nodes;
    while(tmp->next != elem)
      tmp = tmp->next;
    tmp->next = elem->next;
  }
  free(elem->name);
  free(elem);
  return 0;
}
int deleteEdge(Graph* graph, char* n1, char* n2){
  if(graph == NULL)
    return 1;
  if(graph->count < 2)
    return 2;
  int pos1 = 0, pos2 = 0;
  Node* elem = graph->nodes;
  while(elem != NULL){
    if(!strcmp(n1, elem->name))
      break;
    ++pos1;
    elem = elem->next;
  }
  if(pos1 == graph->count)
    return 3;
  Node* pass = graph->nodes;
  while(pass != NULL){
    if(!strcmp(n2, pass->name))
      break;
    ++pos2;
    pass = pass->next;
  }
  if(pos2 == graph->count)
    return 3;
  if(graph->matrix[pos1][pos2] == 0 || graph->matrix[pos2][pos1] == 0)
    return 4;
  else{
    graph->matrix[pos1][pos2] = 0;
    graph->matrix[pos2][pos1] = 0;
    reorgNear(elem, pass);
    reorgNear(pass, elem);
    return 0;
  }
}
Node* DFS_Visit(Node* elem, Node* pass){
  Node* tmp = NULL;
  if(elem == pass)
    return elem;
  else{
    elem->colour = 1;
    for(int i = 0; i < elem->edges; ++i){
      if(elem->near[i]->colour == 0){
        elem->near[i]->pred = elem;
        tmp = DFS_Visit(elem->near[i], pass);
        if(tmp)
          return tmp;
      }
    }
    return NULL;
  }
}
Node* DFS(Graph* graph, char* n1, char* n2){
  int pos1 = 0, pos2 = 0;
  Node* elem = graph->nodes;
  while(elem != NULL){
    if(!strcmp(n1, elem->name))
      break;
    ++pos1;
    elem = elem->next;
  }
  if(pos1 == graph->count)
    return NULL;
  Node* pass = graph->nodes;
  while(pass != NULL){
    if(!strcmp(n2, pass->name))
      break;
    ++pos2;
    pass = pass->next;
  }
  if(pos2 == graph->count)
    return NULL;

  Node* tmp = graph->nodes;
  while(tmp != NULL){
    tmp->colour = 0;
    tmp->pred = NULL;
    tmp = tmp->next;
  }
  Node* ptr = DFS_Visit(elem, pass);
  return ptr;
}
Node* BFV(Graph* graph, char* n1, char* n2){
  //проверка корректности

  int pos1 = 0, pos2 = 0;
  Node* elem = graph->nodes;
  while(elem != NULL){
    if(!strcmp(n1, elem->name))
      break;
    ++pos1;
    elem = elem->next;
  }
  if(pos1 == graph->count)
    return NULL;
  Node* pass = graph->nodes;
  while(pass != NULL){
    if(!strcmp(n2, pass->name))
      break;
    ++pos2;
    pass = pass->next;
  }
  if(pos2 == graph->count)
    return NULL;
  if(pass->near == NULL || elem->near == NULL)
    return NULL;

  //подготовка к алгоритму

  Node* v1 = graph->nodes;
  while(v1 != NULL){// все на бесконечность
    if(v1 == elem)
      v1->range = 0;
    else
      v1->range = 32000;//маx
    v1->pred = NULL;
    v1 = v1->next;
  }

  //поиск пути

  Node* tmp = elem;
  for(int k = 0; k < graph->count; ++k){
    for(int i = 0; i < tmp->edges; ++i){
      if(tmp->near[i]->range > (tmp->range + getWeight(tmp, tmp->near[i]))){
        tmp->near[i]->range = tmp->range + getWeight(tmp, tmp->near[i]);
        tmp->near[i]->pred = tmp;
      }
    }
    tmp = tmp->next;
    if(tmp == NULL)
      tmp = graph->nodes;
  }
  return pass;
}


Tree* del(Tree* root, unsigned int key){
  if(tmp->left != NULL && tmp->right != NULL){
    Tree* max = tmp->left;
    while(max->right != NULL)
      max = max->right;
    unsigned int a = max->key;
    char* b = (char*) calloc (strlen(max->info) + 1, sizeof(char));
    strcpy(b, max->info);
    root = del(root, max->key);
    tmp->key = a;
    free(tmp->info);
    tmp->info = b;
    return root;
  }
}
