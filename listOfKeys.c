#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfKeys.h"

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment1
*mchorobi@uofguelph.mail.ca
*January 29, 2017
*/

node* readIntoList(){
  FILE*parsedOutput = fopen("parsedOutput.c","r");
  node*root=NULL;
  char currentCh;
  char key[100];
  int i=0;
  currentCh = getc(parsedOutput);

  while(currentCh!= EOF){
    if(currentCh!='\n'){
      key[i]=currentCh;
      i++;
      currentCh = getc(parsedOutput);
    }else{
      key[i]='\0';
      i=0;
      if(root==NULL){
        root=newNode(key);
      }else{
        insert(root,key);
      }
      key[0]='\0';
      currentCh = getc(parsedOutput);
    }
  }

  fclose(parsedOutput);
  return(root);
}
node* insert(node* n,char token[100]){

  node*root=n;
  node*previous;

  while(n->next!=NULL){
      previous=n;
      n=n->next;
  }
  n->next=newNode(token);
  if(root!=n){
    n->prev=previous;
  }

  return root;
}
node * newNode(char * token){

	node * n = malloc(sizeof(*n));
  n->next=NULL;
  n->prev=NULL;
  strcpy(n->key,token);

	return n;
}
void pritnList(node* n,char out[100]){

  node*temp;
  temp=n;
  while(n->next!=NULL){
      /*printf("%s\n",n->key);*/
      n=n->next;
  }
  n=temp;

  int i=strlen(out);
  out[i-1]='\0';
  FILE*parsedOutput = fopen(out, "w");
  do{
    if((n->key[0]=='/')&&(n->key[1]=='*')){
      fprintf(parsedOutput,"%s",n->key);
      fprintf(parsedOutput,"\n");
    }else if((strcmp(n->key,"newline")==0)){
      fprintf(parsedOutput,"\n");
    }else{
      fprintf(parsedOutput,"%s",n->key);
    }
    n=n->next;
  }while ( n->next != NULL );
    if((n->key[0]=='/')&&(n->key[1]=='*')){
      fprintf(parsedOutput,"%s",n->key);
      fprintf(parsedOutput,"\n");
    }else if((strcmp(n->key,"newline")==0)){
      fprintf(parsedOutput,"\n");
    }else{
      fprintf(parsedOutput,"%s",n->key);
    }
  fclose(parsedOutput);

}
void placeMainAtEnd(node* n){
  node*check=n;

  while((strcmp(n->key,"main")!=0)||(n->next==NULL)){
    n=n->next;
  }

  int nodeCount=0;

  while(nodeCount!=1){
    n=n->prev;
    if((strcmp(n->key," ")!=0)&&(strcmp(n->key,"\t")!=0)&&(strcmp(n->key,"newline")!=0)){
      nodeCount++;
    }
  }
  node* mainStart=n;
  node* beforeMainStart=n->prev;

  /*funcVars(mainStart,firstNode);*/

  node* newLineStart=n;
  mainStart=newNode("\n\n");
  mainStart->next=newLineStart;
  newLineStart->prev=mainStart;

  while(strcmp(n->key,"}")!=0){
    n=n->next;
  }

  node* mainEnd=n;
  node* afterMainEnd=n->next;

  while(n->next!=NULL){
    n=n->next;
  }

  /*i remove main here*/
  beforeMainStart->next=afterMainEnd;
  afterMainEnd->prev=beforeMainStart;

  node* lastNode =n;
  node* newLastNode = newNode("\n");

  /*i add main to the end of the program main here*/

  lastNode->next=mainStart;
  mainStart->prev=lastNode;

  mainEnd->next=newLastNode;
  newLastNode->prev=mainEnd;

  while(check->next!=NULL){
    if((strcmp(check->key,"class")==0)){
      strcpy(check->key, "struct");
      constCall(check,mainStart);
    }
    check=check->next;
  }

}
void moveConstructor(node*n,char structName[100]){
  node*start;
  node*end;
  node*beforestart;
  node*afterEnd;
  char consName[100];

  strcpy(consName,"\n\nvoid constructor");
  strcat(consName,structName);
  strcat(consName," (struct ");
  strcat(consName,structName);
  strcat(consName,"* this) {\n");

  while((strcmp(n->key,consName)!=0)&&(n->next!=NULL)){
    n=n->next;
  }

  if(n->next!=NULL){

    start=n;
    beforestart=n->prev;

    while(strcmp(n->key,"\t}\n\n")!=0){
      n=n->next;
    }

    end=n;
    afterEnd=n->next;

    /*
    here start is at the first node of the constructor
    end is at the last node of the constructor
    */

    beforestart->next=afterEnd;
    afterEnd->prev=beforestart;

    while(n->next!=NULL){
      n=n->next;
    }
    n->next=start;
    start->prev=n;
    end->next=NULL;
  }

}
void funcVars(node* n,node* firstNode, char structName[100]){
  int pass=0;
  char vars[100][100];
  int i=0;
  char globalVars[100][100];
  int y=0;
  int ready=0;

/*here i scan the area between the brackets ( and ) to see is any variables are defined there. if so i add them to an array of variables defiend in this function*/

  while (strcmp(n->key,"(")!=0) {
    n=n->next;
  }

  node*temp=n;
  while (strcmp(temp->key,")")!=0) {
    temp=temp->next;
  }

  while((strcmp(n->key,"}")!=0)&&(n->key!=NULL)){
    n=n->next;
    if(strcmp(n->key,")")==0){
      ready=1;
    }
    if((strcmp(n->key,"char")==0)||(strcmp(n->key,"float")==0)||(strcmp(n->key,"int")==0)||(strcmp(n->key,"long")==0)||(strcmp(n->key,"short")==0)){
      n=n->next;
      while((strcmp(n->key," ")==0)||(strcmp(n->key,"\t")==0)||(strcmp(n->key,"newline")==0)||(strcmp(n->key,"*")==0)){
        n=n->next;
      }
      strcpy(vars[i++],n->key);
      if(ready==1){
        while((strcmp(n->key,"newline")!=0)){
          if(strcmp(n->key,",")==0){
              n=n->next;
              while((strcmp(n->key," ")==0)||(strcmp(n->key,"\t")==0)||(strcmp(n->key,"newline")==0)||(strcmp(n->key,"*")==0)){
                n=n->next;
              }
              strcpy(vars[i++],n->key);
              }
              n=n->next;
          }
      }
    }
  }

/*here i go to the begining of the program to add any global variables*/

  if(firstNode==NULL){
    while (n->prev!=NULL) {
      n=n->prev;
    }
  }else{
    n=firstNode;
  }

  /*here i search for a the struct and add any variables that are defined in the class*/

      node* s=n;
      pass=0;

      while(pass==0){
        while((strcmp(s->key,"struct")!=0)&&(s->next!=NULL)){
          s=s->next;
        }

        s=s->next;
        while((strcmp(s->key," ")==0)||(strcmp(s->key,"\t")==0)){
          s=s->next;
        }

        if(strcmp(s->key,structName)==0){
          pass=1;
          s=s->next;
          while(((strcmp(s->key," ")==0)||(strcmp(s->key,"\t")==0))&&(s->next!=NULL)){
            s=s->next;
          }
          if(strcmp(s->key,"{")==0){
            /*means we found the right struct and now we check for any defined variables*/
            while((strcmp(s->key,"}")!=0)&&(s->key!=NULL)){
              s=s->next;
              if((strcmp(s->key,"char")==0)||(strcmp(s->key,"float")==0)||(strcmp(s->key,"int")==0)||(strcmp(s->key,"long")==0)||(strcmp(s->key,"short")==0)){
                s=s->next;
                while((strcmp(s->key," ")==0)||(strcmp(s->key,"\t")==0)||(strcmp(s->key,"newline")==0)||(strcmp(s->key,"*")==0)){
                  s=s->next;
                }
                strcpy(globalVars[y++],s->key);
                  while((strcmp(s->key,"newline")!=0)){
                    if(strcmp(s->key,",")==0){
                        s=s->next;
                        while((strcmp(s->key," ")==0)||(strcmp(s->key,"\t")==0)||(strcmp(s->key,"newline")==0)||(strcmp(s->key,"*")==0)){
                          s=s->next;
                        }
                        strcpy(globalVars[y++],s->key);
                        }
                        s=s->next;
                    }
                }
              }
          }
        }
        if(s->next==NULL){
          pass=1;
        }
      }

/******************************************************************************************************************/
  while(strcmp(n->key,"(")!=0){
    n=n->next;
  }

  while (strcmp(n->key,"{")!=0){
    n=n->next;
    if((strcmp(n->key,"char")==0)||(strcmp(n->key,"float")==0)||(strcmp(n->key,"int")==0)||(strcmp(n->key,"long")==0)||(strcmp(n->key,"short")==0)){
      n=n->next;
      while((strcmp(n->key," ")==0)||(strcmp(n->key,"\t")==0)||(strcmp(n->key,"newline")==0)||(strcmp(n->key,"*")==0)){
        n=n->next;
      }
      /*strcpy(globalVars[y++],n->key);*/
      while((strcmp(n->key," ")==0)||(strcmp(n->key,"\t")==0)||(strcmp(n->key,"newline")==0)||(strcmp(n->key,"*")==0)){
        n=n->next;
      }
    }
  }

  varUsed(temp,globalVars,y,vars,i);

}
void varUsed(node* n,char globalVars[100][100],int globalVarCount,char vars[100][100],int varCount){
  int i=0;
  int x=0;
  int q=0;
  int w=0;
  int fail=0;
  node*temp=n;
  int pass=0;
  char replace[100];

  for(x=0;x<globalVarCount;x++){
    n=temp;
    while (strcmp(n->key,"}")!=0) {
      if(strcmp(n->key,globalVars[x])==0){
        for(i=0;i<varCount;i++){
          if(strcmp(vars[i],globalVars[x])==0){
            pass=1;
          }
        }
      }
        if((pass==0)&&(strcmp(n->key,globalVars[x])==0)){
          for(q=0;q<globalVarCount;q++){
            for(w=0;w<globalVarCount;w++){
              if((strcmp(globalVars[q],globalVars[w])==0)){
                if((strcmp(n->key,globalVars[q])==0)&&(q!=w)){
                  fail=1;
                }
              }
            }
          }

          if(fail==0){
            strcpy(replace,n->key);
            strcpy(n->key,"this->");
            strcat(n->key,replace);
          }

        }
      n=n->next;
    }
  }

}
void freeMEM(node* n){
  node* temp;
  while(n->next!=NULL){
      temp=n->next;
      free(n);
      n=temp;
  }
  free(n);
}
