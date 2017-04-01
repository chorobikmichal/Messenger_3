#include <stdio.h>
#include <stdlib.h>
#include "readFromFile.h"
#include "findAndReplace.h"
#include "listOfKeys.h"

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment1
*mchorobi@uofguelph.mail.ca
*January 29, 2017
*/

int main(int argc, char *argv[]) {
  readAndParse(argv[1]);
  node*head=readIntoList();
  classReplace(head);
  placeMainAtEnd(head);
  pritnList(head,argv[1]);
  freeMEM(head);
  return 0;
}
