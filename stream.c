#include <stdio.h>
#include <string.h>

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment2
*mchorobi@uofguelph.mail.ca
*February 19, 2017
*/

struct userPost {
  char *username;
  char *streamname;
  char *date;
  char *text[50];
};

void updateStream(struct userPost *st);
void addUser(char *username, char *list);
void removeUser(char *username, char *list);

void updateStream(struct userPost *st){
  int pos=0;
  FILE *fp;
  /*adds a new posting to the stream specified in streamname
  *If the stream does not exist then it creates the files necessary for the stream
  *determine the time and date of the post, format it as a string, and store it in the date string.
  */

  /*first i check if the user is allowed o post in this stream*/
  char streamName[99];

  strcpy(streamName,(*st).streamname);
  strcat(streamName,"StreamUsers");
  strcat(streamName,".txt");

  char line[256];
  int pass=0;

  char temp[99];
  strcpy(temp,"./messages/");
  strcat(temp,streamName);

  if ((fp = fopen(temp, "r"))){
    while (fgets(line, sizeof(line), fp)) {
      if(strstr(line,(*st).username)!=NULL){
        pass=1;
      }
    }
    fclose(fp);
  }
  if(pass==0){
    printf("This user doesn't have access to this stream");
    return;
  }else{
    printf("The message was posted successfully");
  }

  strcpy(streamName,(*st).streamname);
  strcat(streamName,"Stream");
  strcat(streamName,".txt");

  strcpy(temp,"./messages/");
  strcat(temp,streamName);

  char textmessgae[999];
  strcpy(textmessgae,(*st).text[0]);
  textmessgae[strlen(textmessgae)-1]='\0';

  if ((fp = fopen(temp, "a"))){
    fprintf(fp,"Sender: %s",(*st).username);
    fprintf(fp,"%s","\r\n");
    fprintf(fp,"Date: %s",(*st).date);
    fprintf(fp,"%s",textmessgae);
    fprintf(fp,"%s","\r\n");
    fclose(fp);
  }

  /*open the file here to count the positions!!!*/
  fp = fopen(temp, "r");
  char c=getc(fp);
  while (c!=EOF) {
    if((c=='\n'))
      pos++;
    c=getc(fp);
  }
  fclose(fp);

  strcpy(streamName,(*st).streamname);
  strcat(streamName,"StreamData");
  strcat(streamName,".txt");
  strcpy(temp,"./messages/");
  strcat(temp,streamName);

  if ((fp = fopen(temp, "a"))){
    fprintf(fp,"%d",pos);
    fprintf(fp,"%s","\r\n");
    fclose(fp);
  }

  return;

}

void addUser(char *username, char *list){
  /*adds a user with username to all of the streams listed in the list string
  *If a stream name in the list does not exist then a new stream with that name should be created
  */

  /*1 username list*/

  char c;
  int posCount=0,varCount=0,count=0;
  char tempStr[99];
  char streamListSeperated[99][99];

  char author[99];
  strcpy(author,username);

  c = list[count];
  count++;
  while (c!='\0') {
    if(c==','){
      tempStr[posCount]='\0';
      strcpy(streamListSeperated[varCount],tempStr);
      varCount++;
      posCount=0;
    }else{
      tempStr[posCount]=c;
      posCount++;
    }
    c = list[count];
    count++;
  }
  tempStr[posCount]='\0';
  strcpy(streamListSeperated[varCount],tempStr);
  varCount++;
  posCount=0;


  int i;
  for (i = 0; i < varCount; i++) {

/***********************to be replaced************************************/
    char streamName[99];
    strcpy(streamName,streamListSeperated[i]);
    strcat(streamName,"StreamUsers");
    strcat(streamName,".txt");
    char temp[99];
    strcpy(temp,"./messages/");
    strcat(temp,streamName);

    FILE *fp;
    char x[99];

    if ((fp = fopen(temp, "r+"))){
      while (fscanf(fp,"%s", x) == 1) {
        /*printf("%s\n",x );*/
      }
      fprintf(fp,"%s","\r");
      fprintf(fp,"%s",author);
      fprintf(fp," 0");
      fclose(fp);
    }else{
      fp = fopen(temp, "w");
      fprintf(fp,"%s",author);
      fprintf(fp," 0");
      fclose(fp);
    }
/***********************to be replaced************************************/
  }

  printf("successfully added!\n");

}
void removeUser(char *username, char *list){
  /*removes the username from the stream(s) in the list*/
  int pass=0;

  char c;
  int posCount=0,varCount=0,count=0;
  char tempStr[99];
  char streamListSeperated[99][99];

  char author[99];
  strcpy(author,username);

  c = list[count];
  count++;
  while (c!='\0') {
    if(c==','){
      tempStr[posCount]='\0';
      strcpy(streamListSeperated[varCount],tempStr);
      varCount++;
      posCount=0;
    }else{
      tempStr[posCount]=c;
      posCount++;
    }
    c = list[count];
    count++;
  }
  tempStr[posCount]='\0';
  strcpy(streamListSeperated[varCount],tempStr);
  varCount++;
  posCount=0;


  int i;
  for (i = 0; i < varCount; i++) {

    char streamName[99];
    strcpy(streamName,streamListSeperated[i]);
    strcat(streamName,"StreamUsers");
    strcat(streamName,".txt");
    char temp[99];
    strcpy(temp,"./messages/");
    strcat(temp,streamName);

    FILE *fp;
    char x[99];
    char fileCopy[999][999];
    int cpyCount=0;
    int nn=0;

    if ((fp = fopen(temp, "r+"))){
      while (fscanf(fp,"%s", x) == 1) {
        strcpy(fileCopy[cpyCount],x);
        if(nn!=1){
          cpyCount++;
        }else{
          nn=0;
        }
        if(strcmp(author,x)==0){
          cpyCount--;
          nn=1;
          printf("successfully removed the user!\n");
          pass=1;
        }
      }
      fclose(fp);
    }
    if ((fp = fopen(temp, "w"))){
      int q;
      for ( q = 0; q < cpyCount; q++) {
        strcat(fileCopy[q]," ");
        fprintf(fp,"%s",fileCopy[q]);
        if(q%2==1)
        fprintf(fp,"%s","\r\n");
      }
      fclose(fp);
    }
  }

  if(pass==0)
  printf("failed to remove the user!\n");

}
