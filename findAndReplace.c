#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "findAndReplace.h"
#include "listOfKeys.h"

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment2
*mchorobi@uofguelph.mail.ca
*February 19, 2017
*/

void classReplace(node*n){
  char structName[100];
  int pass=0;

  if((strcmp(n->key,"class")==0)){
    node*temp2=n;
    node*temp=n->next;

    int nodeCount=0;
    pass=0;
    while(nodeCount!=2){
      temp2=temp2->next;
      if((strcmp(temp2->key," ")!=0)&&(strcmp(temp2->key,"\t")!=0)&&(strcmp(temp2->key,"newline")!=0)){
        nodeCount++;
          if(strcmp(temp2->key,"{")==0){
            pass=1;
        }
      }
    }
    if(pass==1){
        strcpy(n->key, "struct");
        n=n->next;

        while((strcmp(temp->key," ")==0)||(strcmp(temp->key,"\t")==0)||(strcmp(temp->key,"newline")==0)){
            temp=temp->next;
        }
        strcpy(structName, temp->key);

        classReplace(n);
        /*call function detection*/

          while((strcmp(n->key,"{")!=0)){
              n=n->next;
          }

          node*temp2=n;

          nodeCount=0;
          while(nodeCount!=2){
            n=n->prev;
            if((strcmp(n->key," ")!=0)&&(strcmp(n->key,"\t")!=0)&&(strcmp(n->key,"newline")!=0)){
              nodeCount++;
            }
          }
          n=n->prev;

          /*1 is '{' -1 is '}'*/
          findFuncInClass(temp2,1,structName);
        }
  }else if (n->next==NULL){
  }else{
    n=n->next;
    classReplace(n);
  }

}
void constCall(node * n,node* start){
  int nodeCount=0;

  while(nodeCount!=2){
    n=n->next;
    if((strcmp(n->key," ")!=0)&&(strcmp(n->key,"\t")!=0)&&(strcmp(n->key,"newline")!=0)){
      nodeCount++;
    }
  }

  char constName[100];
  strcpy(constName,n->key);

  nodeCount=0;
  while(nodeCount!=1){
    n=n->prev;
    if((strcmp(n->key," ")!=0)&&(strcmp(n->key,"\t")!=0)&&(strcmp(n->key,"newline")!=0)){
      nodeCount++;
    }
  }

  char constCall[100];
  strcpy(constCall,"constructor");
  strcat(constCall,n->key);

  while(strcmp(n->key,";")!=0){
    n=n->next;
  }

  char constCallLine [100];
  strcpy(constCallLine,"\n");
  strcat(constCallLine,constCall);
  strcat(constCallLine,"(&");
  strcat(constCallLine,constName);
  strcat(constCallLine,");");
  strcat(n->key,constCallLine);


  while (start->next!=NULL) {
    if(strcmp(start->key,constName)==0){
      if(strcmp(start->next->key,".")==0){
        if(strcmp(start->next->next->next->key,"(")==0){
          strcat(start->next->next->next->key,"&");
          strcat(start->next->next->next->key,constName);
          if(strcmp(start->next->next->next->next->key,")")!=0){
            strcat(start->next->next->next->key,", ");
          }
        }
      }
    }
    start=start->next;
  }

}
void findFuncInClass(node*n,int bracCount,char structName[100]){

  while(bracCount!=0){
      n=n->next;
      if(strcmp(n->key,"{")==0){
              bracCount++;
              if(bracCount<3){
                copyAndRenameFunc(n,structName);
              }
      } else if (strcmp(n->key,"}")==0){
              bracCount--;
      }
  }

/*
if it exits this loop that means it finished converting the class
now I move the constructor to the botom so that the functions
are delared before the constructor is defined
*/

moveConstructor(n,structName);

}
void copyAndRenameFunc(node* n,char structName[999]){
    int nodeCount=0,varCount=-1;
    char funcName[999];
    char funcVars[999];
    strcpy(funcVars,"");
    char funcNewName[999];
    char funcPointer[999];

    char variablesStr[999];
    strcpy(variablesStr," ");

    while(strcmp(n->key,"(")!=0){
      n=n->prev;
    }

    int pass=0;
    node*temp=n;
    while(strcmp(temp->key,")")!=0){
      temp=temp->next;
      if((strcmp(temp->key," ")!=0)&&(strcmp(temp->key,"\t")!=0)&&(strcmp(temp->key,"newline")!=0)&&(strcmp(temp->key,",")!=0)&&(strcmp(temp->key,")")!=0)){
        if(strcmp(temp->next->key,"[")==0){
          pass=1;
          strcat(variablesStr,temp->key);
          temp=temp->next;
          strcat(variablesStr,temp->key);
          temp=temp->next;
          strcat(variablesStr,temp->key);
          if(strcmp(temp->next->key,")")!=0)
          strcat(variablesStr,",");
          continue;
        }
        nodeCount++;
        if((nodeCount % 2)&&(pass!=1)){
            if((temp->key[0]=='*')){
              strcat(variablesStr,temp->key);
              continue;
            }
            varCount++;
            funcVars[varCount]=temp->key[0];
            funcVars[varCount+1]='\0';
            strcat(variablesStr,",");
        }
        strcat(variablesStr,temp->key);
        strcat(variablesStr," ");
      }
    }
    if(nodeCount==0){
      funcVars[0]='\0';
    }
    nodeCount=0;

    temp=n;
    while(nodeCount!=2){
      temp=temp->prev;
      if((strcmp(temp->key," ")!=0)&&(strcmp(temp->key,"\t")!=0)&&(strcmp(temp->key,"newline")!=0)){
        nodeCount++;
        if(nodeCount==1){
          strcpy(funcName, temp->key);
        }else if(nodeCount==2){
          strcpy(funcPointer, temp->key);
        }
      }
    }

    /*strcpy(funcNewName,structName);
    strcat(funcNewName,funcName);
    strcat(funcNewName,funcVars);
    */

    strcpy(funcNewName,funcName);

    strcat(funcPointer," (*");
    strcat(funcPointer,funcNewName);
    strcat(funcPointer,")(");
    strcat(funcPointer,"struct ");
    strcat(funcPointer,structName);
    strcat(funcPointer,"* this");
    strcat(funcPointer,variablesStr);
    strcat(funcPointer,");");

    /*here add a node declaring the struct pointer*/

    char funcVar[999];
    strcpy(funcVar,"struct ");
    strcat(funcVar,structName);
    strcat(funcVar,"* this ");
    if(strcmp(n->next->key,")")!=0){
      strcat(funcVar,", ");
    }
    node*new=newNode(funcVar);
    node*closingBrac=n->next;

    n->next=new;
    new->prev=n;
    new->next=closingBrac;
    closingBrac->prev=new;

    searchMain(n,structName, funcName,funcNewName);
    addConstructor(n,structName,funcNewName);
    addFunction(n,funcNewName,funcPointer,structName);

}
void addFunction(node* n,char funcNewName[100],char funcPointer[999],char structName[100]){
  int bracCount,nodeCount=0;
  node*temp=n;

  while (strcmp(temp->key,"{")!=0) {
    temp=temp->next;
    bracCount=2;
  }

    while(bracCount!=0){
        temp=temp->next;
        if(strcmp(temp->key,"{")==0){
                bracCount++;
        } else if (strcmp(temp->key,"}")==0){
                bracCount--;
        }
    }

  while(nodeCount!=2){
    n=n->prev;
    if((strcmp(n->key," ")!=0)&&(strcmp(n->key,"\t")!=0)&&(strcmp(n->key,"newline")!=0)){
      nodeCount++;
      if(nodeCount==1){
        strcpy(n->key, funcNewName);
      }
    }
  }

  node* endOfFunc=n;
  while(strcmp(endOfFunc->key,"}")!=0){
      endOfFunc=endOfFunc->next;

      if((strcmp(endOfFunc->key,"for")==0)||(strcmp(endOfFunc->key,"while")==0)||(strcmp(endOfFunc->key,"if")==0)){
        while(strcmp(endOfFunc->key,"}")!=0){
            endOfFunc=endOfFunc->next;
        }
        endOfFunc=endOfFunc->next;
      }

  }

  node*start=n;
  node*end=endOfFunc;

  /*
  n - is the first node in the function (int) and the function is renamed
  endOfFunc - is the node were the function ends (})
  temp - is the node were class ends (})
  */

  node* beforeFunc=n->prev;
  beforeFunc->next=endOfFunc->next;
  endOfFunc->next->prev=beforeFunc;

  node * funcPtr=newNode(funcPointer);
  beforeFunc->next=funcPtr;
  funcPtr->next=endOfFunc->next;
  endOfFunc->next->prev=funcPtr;
  funcPtr->prev=beforeFunc;

  /*
  temp2 - is the position after the last node of the class
  The node before the first node of the function is pointed the the first node after the function ends
  by Here I erase the function so it can be added at the end
  */

  funcVars(n,NULL,structName);

  while (strcmp(n->key,"}")!=0){

    if((strcmp(n->key,"for")==0)||(strcmp(n->key,"while")==0)||(strcmp(n->key,"if")==0)){
      while(strcmp(n->key,"}")!=0){
          if((strcmp(n->key,"newline")==0)){
            insert(n,"\n");
            temp=n;
            n=n->next;
          }else{
            insert(n,n->key);
            n=n->next;
          }
      }
      if((strcmp(n->key,"newline")==0)){
        insert(n,"\n");
        temp=n;
        n=n->next;
      }else{
        insert(n,n->key);
        n=n->next;
      }
    }

    if((strcmp(n->key,"newline")==0)){
      insert(n,"\n");
      temp=n;
      n=n->next;
    }else{
      insert(n,n->key);
      n=n->next;
    }
  }
  insert(n,n->key);
  insert(n,"\n");

  while(start!=end){
      start=start->next;
      free(start->prev);
    }
    free(end);

}
void addConstructor(node*n, char className[100],char funcNewName[100]){
  int bracCount=0;

  while (strcmp(n->key,"{")!=0) {
    n=n->next;
    bracCount=2;
  }
  while(bracCount!=0){
    n=n->next;
    if(strcmp(n->key,"{")==0){
            bracCount++;
    } else if (strcmp(n->key,"}")==0){
            bracCount--;
    }
  }
  n=n->next;

  char constName1 [100];
  char constName2 [100];

  strcpy(constName1,"\n\nvoid constructor");
  strcat(constName1,className);
  strcat(constName1," (struct ");
  strcat(constName1,className);
  strcat(constName1,"* this) {\n");
  strcpy(constName2,"\t}\n\n");

  node*new1;
  node*new2;

  node*temp=n;

  if((strcmp(temp->next->key,constName1)==0)||(strcmp(temp->next->next->key,constName1)==0)||(strcmp(temp->next->next->next->key,constName1)==0)){
    while(strcmp(temp->next->key,"\t}\n\n")!=0){
      temp=temp->next;
    }
    strcpy(constName1,"\tthis->");
    strcat(constName1,funcNewName);
    strcat(constName1," = &");
    strcat(constName1,funcNewName);
    strcat(constName1,";\n");
    node*newFuncPtr=newNode(constName1);
    new1=temp;
    new2=temp->next;
    new1->next=newFuncPtr;
    newFuncPtr->prev=new1;
    newFuncPtr->next=new2;
    new2->prev=newFuncPtr;
    return;
  }

  new1=newNode(constName1);
  new2=newNode(constName2);

  node*n_next=n->next;

  new1->next=new2;
  new2->prev=new1;

  new1->prev=n;
  new2->next=n_next;
  n->next=new1;
  n_next->prev=new2;

  strcpy(constName1,"\tthis->");
  strcat(constName1,funcNewName);
  strcat(constName1," = &");
  strcat(constName1,funcNewName);
  strcat(constName1,";\n");

  node*newFuncPtr=newNode(constName1);
  new1->next=newFuncPtr;
  newFuncPtr->prev=new1;
  newFuncPtr->next=new2;
  new2->prev=newFuncPtr;

}
void searchMain(node* n,char structName[100],char funcName[100],char funcNewName[100]){

  while(strcmp(n->key,"main")!=0){
    n=n->next;
  }
  while(strcmp(n->key,"}")!=0){
    if(strstr(n->key, structName) != NULL){
      n=n->next;
      if(strcmp(n->key,".")==0){
        n=n->next;
        if(strcmp(n->key,funcName)==0){
          strcpy(n->key,funcNewName);
        }
      }
    }
    n=n->next;
  }

}
