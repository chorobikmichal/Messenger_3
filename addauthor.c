#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stream.h"

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment2
*mchorobi@uofguelph.mail.ca
*February 19, 2017
*/

int main(int argc, char const *argv[]) {
  int remove=0;
  char author[99];
  int i=0;

  for(i=0;i<argc;i++){
    if(strstr(argv[i],"-r")){
      remove=1;
    }
  }

  char streamList[999];

  /***************************************************************/
  if(remove==0){
    strcpy(author,argv[2]);
    for(i=3;i<argc;i++){
      strcat(author,"~");
      strcat(author,argv[i]);
    }
    strcpy(streamList,argv[1]);
  }else{
    strcpy(author,argv[3]);
    for(i=4;i<argc;i++){
      strcat(author,"~");
      strcat(author,argv[i]);
    }
    strcpy(streamList,argv[2]);
    printf("removing\n");
  }

  /***************************************************************/

  char *ptr1=author;
  char *ptr2=streamList;

  if(remove==1){
    removeUser(ptr1,ptr2);
  }else{
    addUser(ptr1,ptr2);
  }

  return 1;
}
