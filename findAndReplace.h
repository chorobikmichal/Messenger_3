#ifndef __MCHOROBI_FINDANDREPLACE__
#define __MCHOROBI_FINDANDREPLACE__
#include "readFromFile.h"

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment1
*mchorobi@uofguelph.mail.ca
*January 29, 2017
*/

void classReplace(node*n);
void constCall(node * n,node* start);
void findFuncInClass(node*n,int bracCount,char structName[100]);
void copyAndRenameFunc(node* n,char structName[200]);
void addFunction(node* n,char funcNewName[100],char funcPointer[999],char structName[100]);
void addConstructor(node*n, char className[100],char funcNewName[100]);
void searchMain(node* n,char structName[100],char funcName[100],char funcNewName[100]);
#endif
