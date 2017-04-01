#include <stdio.h>
#include <stdlib.h>

/*
*Michal Chorobik 0937145
*CIS 2750 Assignment1
*mchorobi@uofguelph.mail.ca
*January 29, 2017
*/

void readAndParse(char fileName[100]) {
   char currentCh,lastChar;
   FILE *fp = fopen(fileName, "r");
   FILE *out = fopen("output.c", "w");

   currentCh = getc(fp);

   while (currentCh != EOF){

     if((currentCh!='\r')&&(currentCh!='\n')&&(currentCh!='\t')&&(currentCh!=' ')&&(currentCh!='"')&&(currentCh!='/')&&(currentCh!='+')&&(currentCh!='-')&&(currentCh!='[')&&(currentCh!='*')&&(currentCh!='=')&&(currentCh!='#')&&(currentCh!='.')){

         if((currentCh == ';')||(currentCh == ',')||(currentCh == '{')||(currentCh == '}')||(currentCh == '(')||(currentCh == ')')){
               fprintf(out,"\n%c\n",currentCh);
         }else{
           if((lastChar == ';')||(lastChar == ',')||(lastChar == '{')||(lastChar == '}')||(lastChar == '(')||(lastChar == ')')){
             fprintf(out,"\n");
            }
            fprintf(out,"%c",currentCh);
         }

       }else if(currentCh=='"'){
            fprintf(out,"\n%c", currentCh);
            currentCh = getc(fp);
            while (1) {
              if(currentCh=='"'){
                if(lastChar!='\\'){
                  break;
                }
              }
              fprintf(out,"%c", currentCh);
              lastChar=currentCh;
              currentCh = getc(fp);
            }
            fprintf(out,"%c", currentCh);
      }else if(currentCh=='#'){
            fprintf(out,"\n%c",currentCh);
            lastChar=currentCh;
            currentCh = getc(fp);
            while((currentCh!='>')&&(currentCh!='"')){
              fprintf(out,"%c",currentCh);
              lastChar=currentCh;
              currentCh = getc(fp);
            }
            /***********************************************************************/
            if(currentCh=='"'){
              fprintf(out,"%c",currentCh);
              currentCh = getc(fp);
              while(currentCh!='"'){
                fprintf(out,"%c",currentCh);
                lastChar=currentCh;
                currentCh = getc(fp);
              }
            }
            /***********************************************************************/

            fprintf(out,"%c\n",currentCh);
      }else if(currentCh=='/'){
            lastChar=currentCh;
            currentCh = getc(fp);
            if(currentCh=='/'){
                fprintf(out,"\n%c*", lastChar);
                while(currentCh!='\n'){
                  lastChar=currentCh;
                  currentCh = getc(fp);
                  if((currentCh!='\r')&&(currentCh!='\n')){
                    fprintf(out,"%c",currentCh);
                  }else{
                   fprintf(out,"*/\n");
                    break;
                  }
                }
            }else if(currentCh=='*'){
              fprintf(out,"\n%c%c", lastChar,currentCh);
              while(currentCh!='/'){
                lastChar=currentCh;
                currentCh = getc(fp);
                fprintf(out,"%c",currentCh);
              }
            }else{
              fprintf(out,"\n%c\n%c",lastChar,currentCh);
            }
            fprintf(out,"\n");
      }else if((currentCh=='+')||(currentCh=='-')||(currentCh=='*')||(currentCh=='=')||(currentCh=='.')||(currentCh=='[')){
        fprintf(out,"\n%c\n",currentCh);
      }else if((currentCh!='\r')||(currentCh=='\n')||(currentCh=='\t')||(currentCh==' ')){

             if (currentCh==' '){
               fprintf(out,"\n \n");
             }else if((lastChar!='\n')||(currentCh!='\r')){
               if((currentCh!='\n')){
                 fprintf(out,"%c", currentCh);
               }else if(currentCh=='\n'){

                 if((lastChar=='\r')||(lastChar=='\r')){
                   fprintf(out,"\n");
                 }
                 fprintf(out,"\nnewline");
               }
                 fprintf(out,"\n");
                 currentCh='\n';
           }
      }
     lastChar=currentCh;
     currentCh=getc(fp);
   }
   fclose(fp);
   fclose(out);

   out = fopen("output.c","r");
   FILE*parsedOutput = fopen("parsedOutput.c", "w");
   currentCh = getc(out);

   while ( currentCh != EOF ){
     if((currentCh=='\n')&&(lastChar=='\n')){
     }else{
       fprintf(parsedOutput,"%c",currentCh);
     }
     lastChar=currentCh;
     currentCh = getc(out);
   }
   fclose(parsedOutput);
   fclose(out);
}
