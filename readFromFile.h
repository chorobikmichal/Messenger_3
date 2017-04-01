#ifndef __MCHOROBI_READANDPARSE__
#define __MCHOROBI_READANDPARSE__

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment1
*mchorobi@uofguelph.mail.ca
*January 29, 2017
*/

typedef struct node{
  char key[200];
  struct node * next;
  struct node * prev;
}node;

/*typedef struct node node;*/

void readAndParse(char fileName[100]);
#endif
