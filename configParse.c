#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void send(char website[100], char line[300]) {
  FILE*fp;

  if ((fp = fopen(website, "a"))){
    fprintf(fp,"%s",line);
    fprintf(fp,"%s","\r\n");
    fclose(fp);
  }

}
void parseTag(char website[100], char tag[300]){
  FILE*fp2;
  char c;
  char type=tag[0];
  char sendLine[300];


  /*tag b*/
  char* buttonName;
  char newButtonName[300];
  char* buttonLink;
  char newButtonLink[300];

  /*tag p*/
  char* width;
  char newWidth[300];
  char* height;
  char newHeight[300];
  char* img;
  char newImg[300];

  /*tag e*/
  char* exeName;
  char newExeName[300];

  /*tag i*/
  char*action;
  char newAction[300];
  char* textName;
  char newTextName[300];
  char* value;
  char newValue[300];
  /*still tag i vars for if there is more than 1 input box*/
  char boxStr[30][300];
  int pos=-1;
  int inputBoxCount=0;

  /*tag E*/
  char argList[999][999];

  /*tag l*/
  char* link;
  char newLink[300];
  char* linkName;
  char newLinkName[300];

  /*tag t and h and i*/
  char*size;
  char newsize[300];
  char* text;
  char newtext[300];
  char* fileName;
  char newFileName[300];
  char line[300];

/***********************Finds the size variable**************************************/
  size="3";
  strcpy(newsize,"3");
  int count=0,i,q;
  if((size=strstr(tag,"size"))){
    for(i=0;i<strlen(size);i++){
      if(size[i]=='"'){
        break;
      }
      if(size[i]=='='){
        count=0;
        while(size[i]!=')'){
          i++;
          if(size[i]!=')')
            newsize[count++]=size[i];
        }
      }
    }
    newsize[count]='\0';
    printf("%d\n",atoi(newsize));
  }
/***********************************************************/


  switch(type) {
    case 'b'  :
      /***********************Finds the button name**************************************/
        strcpy(newButtonName,"button");

        if((buttonName=strstr(tag,"name"))){
          for(i=0;i<strlen(buttonName);i++){
            if(buttonName[i]=='"'){
              count=0;
              i++;
              while(buttonName[i]!='"'){
                newButtonName[count++]=buttonName[i];
                i++;
              }
              break;
            }
          }
          newButtonName[count]='\0';
          printf("newButtonName: %s\n",newButtonName);
        }
      /***********************Finds the button's link**************************************/

        if((buttonLink=strstr(tag,"link"))){
          for(i=0;i<strlen(buttonLink);i++){
            if(buttonLink[i]=='"'){
              count=0;
              i++;
              while(buttonLink[i]!='"'){
                newButtonLink[count++]=buttonLink[i];
                i++;
              }
              break;
            }
          }
          newButtonLink[count]='\0';
          printf("newButtonLink: %s\n",newButtonLink);
        }

      /****************************************************************************/
      strcpy(sendLine,"\n<form action=\"");
      strcat(sendLine,newButtonLink);
      strcat(sendLine,"\"><input type=\"submit");
      strcat(sendLine,"\" value=\"");
      strcat(sendLine,newButtonName);
      strcat(sendLine,"\" />");
      if(strstr(tag,"fff")==0)
      strcat(sendLine,"</form>");
      send(website,sendLine);

      printf("b\n");
      break;
    case 'd'  :
      send(website,"<hr>");
      printf("d\n");
      break;
    case 'n'  :
      send(website,"<br>");
      break;
    case '1'  :
      send(website,"\n<?php\n $username = str_replace(' ','~',$username);\n?>");
      break;
    case 'e'  :
      /***********************Finds name of executable**************************************/
      strcpy(newExeName,"");

        if((exeName=strstr(tag,"exe"))){
          for(i=0;i<strlen(exeName);i++){
            if(exeName[i]=='"'){
              count=0;
              i++;
              while(exeName[i]!='"'){
                newExeName[count++]=exeName[i];
                i++;
              }
              break;
            }
          }
          newExeName[count]='\0';
          printf("text: %s\n",newExeName);
        }

        /*************************I search for where the file is located***********************************/

          FILE *myFP=fopen(newExeName,"r");
          if(myFP==NULL){
            strcpy(newButtonLink,"./bin/");
            strcat(newButtonLink,newExeName);
            myFP=fopen(newButtonLink,"r");
            if(myFP==NULL){
              strcpy(newButtonLink,"/bin/");
              strcat(newButtonLink,newExeName);
              strcpy(newExeName,newButtonLink);
            }else{
              strcpy(newExeName,newButtonLink);
            }
          }else{
            strcpy(newButtonLink,"./");
            strcat(newButtonLink,newExeName);
            strcpy(newExeName,newButtonLink);
          }
      /***********************************************************/


      strcpy(sendLine,"\n<?php\nexec(\"");
      strcat(sendLine,newExeName);
      strcat(sendLine,"\");\n");
      strcat(sendLine,"?>\n");

      send(website,sendLine);
      break;

      case 'W'  :

        strcpy(sendLine,"\n<?php\n$username=$_GET[\"username\"];");
        strcat(sendLine,"\n$stream=$_GET[\"stream\"];");
        strcat(sendLine,"\n$next=$_GET[\"next\"];");
        strcat(sendLine,"\n$sort=$_GET[\"sort\"];");
        strcat(sendLine,"\n$status = (exec(\"./view.py $username $stream $next 0 0 $sort\"));");
        strcat(sendLine,"\necho $status;\n\n ");
        strcat(sendLine,"if($status==\"0\"){\n ");
        strcat(sendLine,"        header(\"Location: choose.php? username=$username&stream=$stream&status=<br>This is not a possible option for this user&next=0&sort=0\");");
        strcat(sendLine,"\n}\n?>\n");

        send(website,sendLine);
        break;

      case 'G'  : /*get a variable and assign it */

        /***********************Finds the variable name**************************************/

          if((buttonName=strstr(tag,"var"))){
            for(i=0;i<strlen(buttonName);i++){
              if(buttonName[i]=='"'){
                count=0;
                i++;
                while(buttonName[i]!='"'){
                  newButtonName[count++]=buttonName[i];
                  i++;
                }
                break;
              }
            }
            newButtonName[count]='\0';
            printf("newButtonName: %s\n",newButtonName);
          }
        /***********************Finds if use get or post**************************************/

          if((buttonLink=strstr(tag,"type"))){
            for(i=0;i<strlen(buttonLink);i++){
              if(buttonLink[i]=='"'){
                count=0;
                i++;
                while(buttonLink[i]!='"'){
                  newButtonLink[count++]=buttonLink[i];
                  i++;
                }
                break;
              }
            }
            newButtonLink[count]='\0';
            printf("newButtonLink: %s\n",newButtonLink);
          }

        /****************************************************************************/
        strcpy(sendLine,"\n<?php\n");
        strcat(sendLine,"if(isset(");
        strcat(sendLine,newButtonLink);
        strcat(sendLine,"[\"");
        strcat(sendLine,newButtonName);
        strcat(sendLine,"\"])){\n$");

        if(strstr(tag,"nnn")){
          strcat(sendLine,"next=$_GET[\"next\"]+1;\n");
        } else if(strstr(tag,"ppp")){
          strcat(sendLine,"previous=$_GET[\"next\"]-1;\n");

        }else{
          strcat(sendLine,newButtonName);
          strcat(sendLine," = ");
          strcat(sendLine,newButtonLink);
          strcat(sendLine,"[\"");
          strcat(sendLine,newButtonName);
          strcat(sendLine,"\"];\n");
        }

        if(strstr(tag,"qqq")){
          strcat(sendLine,"$message = str_replace(\"\\n\",'\"<br/>\"',$message);\n");
          strcat(sendLine,"$message = str_replace(\"\\r\",'',$message);");
        }
        strcat(sendLine,"\n}\n?>\n");

        send(website,sendLine);

        break;

    case 'R'  :/*REDIRECT*/
      /***********************Finds variable**************************************/
        if((exeName=strstr(tag,"msg"))){
          for(i=0;i<strlen(exeName);i++){
            if(exeName[i]=='"'){
              count=0;
              i++;
              while(exeName[i]!='"'){
                newExeName[count++]=exeName[i];
                i++;
              }
              break;
            }
          }
          newExeName[count]='\0';
          printf("text: %s\n",newExeName);
        }

        /*********************Finds message*********************************/

        if((buttonLink=strstr(tag,"link"))){
          for(i=0;i<strlen(buttonLink);i++){
            if(buttonLink[i]=='"'){
              count=0;
              i++;
              while(buttonLink[i]!='"'){
                newButtonLink[count++]=buttonLink[i];
                i++;
              }
              break;
            }
          }
          newButtonLink[count]='\0';
          printf("newButtonLink: %s\n",newButtonLink);
        }

      /***********************************************************/

      strcpy(sendLine,"\n<?php\n");
      strcat(sendLine,"$username=$_GET[\"username\"];\n");
      strcat(sendLine,"if($_POST[\"choice\"]==\"");
      strcat(sendLine,newExeName);
      strcat(sendLine,"\"){\n");
      strcat(sendLine,"       header(\"Location: ");
      strcat(sendLine,newButtonLink);
      strcat(sendLine,"\");\n}\n");
      strcat(sendLine,"?>\n");

      send(website,sendLine);
      break;

    case 'S'  : /*Status bar*/

      strcpy(sendLine,"\n<?php\n");
      strcat(sendLine,"    echo ($_GET[\"status\"]);");
      strcat(sendLine,"\n?>\n");

      send(website,sendLine);
      break;

    case 'h'  :
      /***********************Finds the text**************************************/
        if((text=strstr(tag,"text"))){
          for(i=0;i<strlen(text);i++){
            if(text[i]=='"'){
              count=0;
              i++;
              while(text[i]!='"'){
                newtext[count++]=text[i];
                i++;
              }
            }
          }
          newtext[count]='\0';
          printf("text: %s\n",newtext);
        }else{
          strcpy(newtext,"HEADING");
        }
      /***********************************************************/
      printf("h\n");

      strcpy(sendLine,"<h");
      strcat(sendLine,newsize);
      strcat(sendLine,">");
      strcat(sendLine,newtext);
      strcat(sendLine,"</h");
      strcat(sendLine,newsize);
      strcat(sendLine,">");

      send(website,sendLine);
      break;

      case 'f'  :

      for(i=0;i<strlen(tag);i++){
        if(tag[i]=='a'){
          if(tag[i+1]=='r'){
            if(tag[i+2]=='g'){
                  pos=0;
                  inputBoxCount++;
            }
          }
        }
        if(pos!=-1)
        boxStr[inputBoxCount-1][pos++]=tag[i];
      }
      for(i=0;i<inputBoxCount;i++)
      printf("boxStr %s\n",boxStr[i] );

      for(q=0;q<inputBoxCount;q++){
            /***********************Finds the action **************************************/
              if((action=strstr(boxStr[q],"arg"))){
                for(i=0;i<strlen(action);i++){
                  if(action[i]=='"'){
                    count=0;
                    i++;
                    while(action[i]!='"'){
                      newAction[count++]=action[i];
                      i++;
                    }
                    break;
                  }
                }
                newAction[count]='\0';
                strcpy(argList[q],newAction);
                printf("newAction: %s\n",newAction);
              }
            /***********************Finds the value **************************************/
              if((value=strstr(boxStr[q],"from"))){
                for(i=0;i<strlen(value);i++){
                  if(value[i]=='"'){
                    count=0;
                    i++;
                    while(value[i]!='"'){
                      newValue[count++]=value[i];
                      i++;
                    }
                    break;
                  }
                }
                newValue[count]='\0';
              }
              /****************************************************************************/
              if(q==0){
                strcpy(sendLine,"\n\n<?php\n");
                strcat(sendLine,newAction);
                strcat(sendLine,"= $_REQUEST['");
                strcat(sendLine,newValue);
                strcat(sendLine,"'];\n");

                send(website,sendLine);
                continue;
              }
              /****************************************************************************/

              strcpy(sendLine,newAction);
              strcat(sendLine,"= $_REQUEST['");
              strcat(sendLine,newValue);
              strcat(sendLine,"'];\n");

              send(website,sendLine);

        }/* the box count for loop ends here */

        /***********************Finds the text**************************************/
          if((text=strstr(tag,"exe"))){
            for(i=0;i<strlen(text);i++){
              if(text[i]=='"'){
                count=0;
                i++;
                while(text[i]!='"'){
                  newtext[count++]=text[i];
                  i++;
                }
                break;
              }
            }
            newtext[count]='\0';
          }
        /***********************************************************/

        strcpy(sendLine,"exec(\"./");
        strcat(sendLine,newtext);

        for(q=0;q<inputBoxCount;q++){
          strcat(sendLine," ");
          strcat(sendLine,argList[q]);
        }
        send(website,sendLine);

        strcpy(sendLine,"\");");
        strcat(sendLine,"\n?>\n\n");

        send(website,sendLine);

        printf("r\n");
        break;

    case 'E'  :

    /***********************Finds the number associated with the button**************************************/

    strcpy(newLinkName,"");
    strcpy(newLink,"");

      if((linkName=strstr(tag,"num"))){
        for(i=0;i<strlen(linkName);i++){
          if(linkName[i]=='"'){
            count=0;
            i++;
            while(linkName[i]!='"'){
              newLinkName[count++]=linkName[i];
              i++;
            }
            break;
          }
        }
        newLinkName[count]='\0';
        printf("newLinkName: %s\n",newLinkName);
      }
    /***********************Finds the link**************************************/

      if((link=strstr(tag,"value"))){
        for(i=0;i<strlen(link);i++){
          if(link[i]=='"'){
            count=0;
            i++;
            while(link[i]!='"'){
              newLink[count++]=link[i];
              i++;
            }
            break;
          }
        }
        newLink[count]='\0';
        printf("newLink: %s\n",newLink);
      }

    /****************************************************************************/

    strcpy(sendLine,"\n<form action=\"\" method=\"post\" id =\"form");
    strcat(sendLine,newLinkName);
    strcat(sendLine,"\">");
    strcat(sendLine,"\n<input type=\"hidden\" name=\"choice");
    strcat(sendLine,newLinkName);
    strcat(sendLine,"\" value=\"");
    strcat(sendLine,"set");
    strcat(sendLine,newLinkName);
    strcat(sendLine,"\"></form>");
    strcat(sendLine,"\n<button type=\"submit\" form=\"form");
    strcat(sendLine,newLinkName);
    strcat(sendLine,"\" value=\"");
    strcat(sendLine,newLink);
    strcat(sendLine,"\">");
    strcat(sendLine,newLink);
    strcat(sendLine,"</button>\n");

    send(website,sendLine);

    break;

    case 'i'  :

      for(i=0;i<strlen(tag);i++){
        if(tag[i]=='t'){
          if(tag[i+1]=='e'){
            if(tag[i+2]=='x'){
              if(tag[i+3]=='t'){
                if(tag[i+4]=='='){
                  pos=0;
                  inputBoxCount++;
                }
              }
            }
          }
        }
        if(pos!=-1)
        boxStr[inputBoxCount-1][pos++]=tag[i];
      }
      for(i=0;i<inputBoxCount;i++)
      printf("boxStr %s\n",boxStr[i] );

            /***********************Finds the action **************************************/
              if((action=strstr(tag,"action"))){
                for(i=0;i<strlen(action);i++){
                  if(action[i]=='"'){
                    count=0;
                    i++;
                    while(action[i]!='"'){
                      newAction[count++]=action[i];
                      i++;
                    }
                    break;
                  }
                }
                newAction[count]='\0';
                printf("newAction: %s\n",newAction);
              }

                strcpy(sendLine,"<form action=\"");
                strcat(sendLine,newAction);
                strcat(sendLine,"\" method=\"post\" id=\"form");
                strcat(sendLine,"\" >\n");
                send(website,sendLine);


              for(q=0;q<inputBoxCount;q++){
            /***********************Finds the text********************************/
              if((text=strstr(boxStr[q],"text="))){
                for(i=0;i<strlen(text);i++){
                  if(text[i]=='"'){
                    count=0;
                    i++;
                    while(text[i]!='"'){
                      newtext[count++]=text[i];
                      i++;
                    }
                    break;
                  }
                }
                newtext[count]='\0';
                printf("text: %s\n",newtext);
              }
            /**********************Finds the text name****************************/
              if((textName=strstr(boxStr[q],"name="))){
                for(i=0;i<strlen(textName);i++){
                  if(textName[i]=='"'){
                    count=0;
                    i++;
                    while(textName[i]!='"'){
                      newTextName[count++]=textName[i];
                      i++;
                    }
                    break;
                  }
                }
                newTextName[count]='\0';
              }
            /***********************Finds the value**************************/
              if((value=strstr(boxStr[q],"value"))){
                for(i=0;i<strlen(value);i++){
                  if(value[i]=='"'){
                    count=0;
                    i++;
                    while(value[i]!='"'){
                      newValue[count++]=value[i];
                      i++;
                    }
                    break;
                  }
                }
                newValue[count]='\0';

                  strcpy(sendLine,"<?php\n");
                  strcat(sendLine,"    $");
                  strcat(sendLine,newTextName);
                  strcat(sendLine,"=\"");
                  strcat(sendLine,newValue);
                  strcat(sendLine,"\";\n?>\n");

                  send(website,sendLine);
              }
            /****************************************************************************/

            strcpy(sendLine,newtext);
            strcat(sendLine,"<br><input type=\"text");
            strcat(sendLine,"\" name=\"");
            strcat(sendLine,newTextName);
            strcat(sendLine,"\"><br><br> ");

            send(website,sendLine);



      }/* the box count for loop ends here */

      if(strstr(tag,"qqq")){
        strcpy(sendLine,"\nmessage:<br><textarea name=\"");
        strcat(sendLine,newAction);
        strcat(sendLine,"message\" rows=\"7\" cols=\"50\"></textarea><br>");
        send(website,sendLine);
      }

      strcpy(sendLine,"\n<form form=\"form\" action=\"");
      strcat(sendLine,newAction);
      strcat(sendLine,"\" ><input type=\"submit\" value=\"");
      /*strcat(sendLine,"post");*/
      strcat(sendLine,newValue);
      strcat(sendLine,"\" /></form>");

      send(website,sendLine);

      break;
    case 'l'  :
      /***********************Finds the link name**************************************/

        if((linkName=strstr(tag,"text"))){
          for(i=0;i<strlen(linkName);i++){
            if(linkName[i]=='"'){
              count=0;
              i++;
              while(linkName[i]!='"'){
                newLinkName[count++]=linkName[i];
                i++;
              }
              break;
            }
          }
          newLinkName[count]='\0';
          printf("newLinkName: %s\n",newLinkName);
        }else{
          strcpy(newLinkName,"link");
        }
      /***********************Finds the link**************************************/

        if((link=strstr(tag,"link"))){
          for(i=0;i<strlen(link);i++){
            if(link[i]=='"'){
              count=0;
              i++;
              while(link[i]!='"'){
                newLink[count++]=link[i];
                i++;
              }
              break;
            }
          }
          newLink[count]='\0';
          printf("newLink: %s\n",newLink);
        }

      /****************************************************************************/

      strcpy(sendLine,"<br>\n<a href=\"");
      strcat(sendLine,newLink);
      strcat(sendLine,"\">");
      strcat(sendLine,newLinkName);
      strcat(sendLine,"</a>");
      send(website,sendLine);

      break;
    case 'p'  :

    /***********************Finds the width**************************************/
      strcpy(newWidth,"100");

      if((width=strstr(tag,"size"))){
        for(i=0;i<strlen(width);i++){
          if(width[i]=='='){
            count=0;
            i++;
            while(width[i]!='x'){
              newWidth[count++]=width[i];
              i++;
            }
            break;
          }
        }
        newWidth[count]='\0';
        printf("newWidth: %s\n",newWidth);
      }
    /***********************Finds the height**************************************/
    strcpy(newHeight,"100");

    if((height=strstr(tag,"size"))){
      for(i=0;i<strlen(height);i++){
        if(height[i]=='x'){
          count=0;
          i++;
          while(height[i]!=')'){
            newHeight[count++]=height[i];
            i++;
          }
          break;
        }
      }
      newHeight[count]='\0';
      printf("newWidth: %s\n",newHeight);
    }
    /***********************Finds the image name**************************************/
      strcpy(newImg,"100");

      if((img=strstr(tag,"image"))){
        for(i=0;i<strlen(img);i++){
          if(img[i]=='"'){
            count=0;
            i++;
            while(img[i]!='"'){
              newImg[count++]=img[i];
              i++;
            }
          }
        }
        newImg[count]='\0';
        printf("text: %s\n",newImg);
      }
    /***********************************************************/

      strcpy(sendLine,"<img src=\"");
      strcat(sendLine,newImg);
      strcat(sendLine,"\" style=\"width:");
      strcat(sendLine,newWidth);
      strcat(sendLine,"px; height:");
      strcat(sendLine,newHeight);
      strcat(sendLine,"px;\">");
      send(website,sendLine);

      printf("p\n");
      break;

      case 'X'  :

      /***********************Finds the variable type**************************************/
        if((width=strstr(tag,"type"))){
          for(i=0;i<strlen(width);i++){
            if(width[i]=='"'){
              count=0;
              i++;
              while(width[i]!='"'){
                newWidth[count++]=width[i];
                i++;
              }
              break;
            }
          }
          newWidth[count]='\0';
          printf("newWidth: %s\n",newWidth);
        }
      /***********************Finds the variable name**************************************/
      if((height=strstr(tag,"var"))){
        for(i=0;i<strlen(height);i++){
          if(height[i]=='"'){
            count=0;
            i++;
            while(height[i]!='"'){
              newHeight[count++]=height[i];
              i++;
            }
            break;
          }
        }
        newHeight[count]='\0';
        printf("newWidth: %s\n",newHeight);
      }
      /***********************Finds what to put in the exec command**************************************/
        if((img=strstr(tag,"exe"))){
          for(i=0;i<strlen(img);i++){
            if(img[i]=='"'){
              count=0;
              i++;
              while(img[i]!='"'){
                newImg[count++]=img[i];
                i++;
              }
              break;
            }
          }
          newImg[count]='\0';
          printf("text: %s\n",newImg);
        }
    /**************************findsd where to redirect*********************************/
        if((link=strstr(tag,"header"))){
          for(i=0;i<strlen(link);i++){
            if(link[i]=='"'){
              count=0;
              i++;
              while(link[i]!='"'){
                newLink[count++]=link[i];
                i++;
              }
              break;
            }
          }
          newLink[count]='\0';
          printf("newLink: %s\n",newLink);
        }
    /***********************************************************/

        strcpy(sendLine,"<?php\n");

        strcat(sendLine,"if(isset(");
        strcat(sendLine,newWidth);
        strcat(sendLine,"[\"");
        strcat(sendLine,newHeight);
        strcat(sendLine,"\"])){\n");

        if(strstr(tag,"aaa")){
          strcat(sendLine,"\n        $next=$next+1;\n");
        }

        if(strstr(tag,"eee")){
          strcat(sendLine,"if($sort==0){\n$sort=1;\n}else{\n$sort=0;\n}");
        }

        strcat(sendLine,"      $status = (exec(\"");
        strcat(sendLine,newImg);
        strcat(sendLine,"\"));\n");

        strcat(sendLine,"      header(\"");
        strcat(sendLine,newLink);
        strcat(sendLine,"\");\n");
        strcat(sendLine,"}\n?>\n\n");
        send(website,sendLine);

        printf("p\n");
        break;

    case 'r'  :

    for(i=0;i<strlen(tag);i++){
      if(tag[i]=='v'){
        if(tag[i+1]=='a'){
          if(tag[i+2]=='l'){
            if(tag[i+3]=='u'){
              if(tag[i+4]=='e'){
                pos=0;
                inputBoxCount++;
              }
            }
          }
        }
      }
      if(pos!=-1)
      boxStr[inputBoxCount-1][pos++]=tag[i];
    }
    for(i=0;i<inputBoxCount;i++)
    printf("boxStr %s\n",boxStr[i] );

    for(q=0;q<inputBoxCount;q++){
          /***********************Finds the action **************************************/

            if(q==0){

              if((action=strstr(tag,"action="))){
                for(i=0;i<strlen(action);i++){
                  if(action[i]=='"'){
                    count=0;
                    i++;
                    while(action[i]!='"'){
                      newAction[count++]=action[i];
                      i++;
                    }
                    break;
                  }
                }
                newAction[count]='\0';
                printf("newAction: %s\n",newAction);
              }

              strcpy(sendLine,"<form action=\"");
              strcat(sendLine,newAction);
              strcat(sendLine,"\" method=\"post\" id=\"form");
              strcat(sendLine,"\" >\n");
              send(website,sendLine);
            }

            /***********************Finds the name********************************/
              if((buttonName=strstr(tag,"name"))){
                for(i=0;i<strlen(buttonName);i++){
                  if(buttonName[i]=='"'){
                    count=0;
                    i++;
                    while(buttonName[i]!='"'){
                      newButtonName[count++]=buttonName[i];
                      i++;
                    }
                    break;
                  }
                }
                newButtonName[count]='\0';
                printf("text: %s\n",newButtonName);
              }
            /***********************Finds the value**************************/
              if((value=strstr(boxStr[q],"value"))){
                for(i=0;i<strlen(value);i++){
                  if(value[i]=='"'){
                    count=0;
                    i++;
                    while(value[i]!='"'){
                      newValue[count++]=value[i];
                      i++;
                    }
                    break;
                  }
                }
                newValue[count]='\0';
                printf("newTextName: %s\n",newValue);
              }
            /****************************************************************************/

            strcpy(sendLine,"<input type=\"radio\" name=\"");
            strcat(sendLine,newButtonName);
            strcat(sendLine,"\" value=\"");
            strcat(sendLine,newValue);
            strcat(sendLine,"\">");
            strcat(sendLine,newValue);
            strcat(sendLine,"<br> ");

            send(website,sendLine);

      }/* the box count for loop ends here */

      strcpy(sendLine,"\n<br></form>");
      strcat(sendLine,"\n<button type=\"submit\" form=\"form");
      strcat(sendLine,"\" value=\"Submit\">Submit</button>");

      send(website,sendLine);

      printf("r\n");
      break;

    case 't'  :

      strcpy(sendLine,"Default text");

      /***********************Finds the text**************************************/
        if((text=strstr(tag,"text="))){
          for(i=0;i<strlen(text);i++){
            if(text[i]=='"'){
              count=0;
              i++;
              while(text[i]!='"'){
                newtext[count++]=text[i];
                i++;
              }
            }
          }
          newtext[count]='\0';
          printf("text: %s\n",newtext);
          strcpy(sendLine,newtext);
        }
        /***********************Finds the text**************************************/
          if((fileName=strstr(tag,"file="))){
            for(i=0;i<strlen(fileName);i++){
              if(fileName[i]=='"'){
                count=0;
                i++;
                while(fileName[i]!='"'){
                  newFileName[count++]=fileName[i];
                  i++;
                }
              }
            }
            newFileName[count]='\0';

            count=0;

            if ((fp2 = fopen(newFileName, "r"))){
              while ((c=getc(fp2))!=EOF) {
                  if(c=='\n'){
                    line[count++]='<';
                    line[count++]='b';
                    line[count++]='r';
                    line[count++]='>';
                    continue;
                  }
                  line[count++]=c;
                  if(count>200){
                    line[count]='\0';
                    send(website,line);
                    count=0;
                  }
              }
            }
            fclose(fp2);
            if(count<200){
              line[count]='\0';
              send(website,line);
              count=0;
            }
            break;
          }
      /***********************************************************/

      send(website,sendLine);

      printf("t\n");
      break;
  }

}
int main(int argc, char const *argv[]) {

  char website[100];
  strcpy(website,argv[1]);
  strcat(website,".php");
  FILE*fp = fopen(website, "w");
  fclose(fp);

  strcpy(website,argv[1]);
  strcat(website,".wpml");
  fp = fopen(website, "r");
  char line[500];
  int count=0;
  char c;

  strcpy(website,argv[1]);
  strcat(website,".php");

  send(website,"<!DOCTYPE html>");
  send(website,"<html>");
  send(website,"<body>");

  while ((c=getc(fp))!=EOF) {
    count=0;
    if(c=='.'){
      while(c!=')'){
        c=getc(fp);
        line[count++]=c;
      }
      line[count]='\0';
      parseTag(website,line);
    }
  }
  fclose(fp);
  send(website,"</body>");
  send(website,"</html>");

  return 0;
}
