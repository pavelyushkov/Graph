#ifndef PROCESSING_H
#define PROCESSING_H

Graph* addNode(Graph* graph, Node* node);
void edgeArray(Node* elem, Node* pass);
int addEdge(Graph* graph, char* n1, char* n2);
Graph* createGraph();
void reorgNear(Node* pass, Node* elem);
int** reorgMatrix(Graph* graph, int pos);
int deleteNode(Graph* graph, char* name);
int deleteEdge(Graph* graph, char* n1, char* n2);
Node* DFS_Visit(Node* elem, Node* pass);
Node* DFS(Graph* graph, char* n1, char* n2);
Node* BFV(Graph* graph, char* n1, char* n2);

#endif //PROCESSING_H
