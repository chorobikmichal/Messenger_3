#ifndef __MCHOROBI_LISTOFKEYS__
#define __MCHOROBI_LISTOFKEYS__
#include "readFromFile.h"
#include "findAndReplace.h"

/*
*Michal Chorobik 0937145
*CIS 2500
*mchorobi@uofguelph.mail.ca
*January 29, 2017
*/

node* readIntoList();
node* insert(node* n,char token[100]);
node * newNode(char * token);
void pritnList(node* n,char out[100]);
void placeMainAtEnd(node* n);
void moveConstructor(node*n,char structName[100]);
void funcVars(node* n,node* firstNode, char structName[100]);
void varUsed(node* n,char globalVars[100][100],int globalVarCount,char vars[100][100],int varCount);
void freeMEM(node* n);
#endif
