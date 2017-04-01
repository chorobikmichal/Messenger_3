/*==========================================================================

Example using mySQL

==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <time.h>

#define MAX_QUERY 512
#define HOSTNAME  "dursley.socs.uoguelph.ca"
#define USERNAME  "mchorobi"
#define PASSWORD  "0937145"
#define DATABASE  "mchorobi"

/*standard error clause.*/

void error(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(1);
}

/*clear the contents of an array of char's*/

void clrstr(char *buf){
	buf[0] = '\0';
}

int main(int argc, char *argv[]) {
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	char query[MAX_QUERY];
	int x;
	int i = 0;

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,
		DATABASE, 0, NULL, 0)) {
	   error("Could not connect to host.",&mysql);
	}

	/*Build query*/

/****************************************************************************************************************************************************/
		
	/*clrstr(query);
	strcat(query, "drop table students");
	mysql_query(&mysql, query);

	clrstr(query);
	strcat(query, "drop table users");
	mysql_query(&mysql, query);

	clrstr(query);
	strcat(query, "drop table stream");
	mysql_query(&mysql, query);

	clrstr(query);
	strcat(query, "drop table post");
	mysql_query(&mysql, query);*/


	clrstr(query);

	strcat(query, "create table users (userID int primary key auto_increment,");
	strcat(query, "userName varchar(15) unique,");
	/*strcat(query, "postRead int default 0);");*/
	strcat(query, "postRead text);");/*format is <Stream>_<LineNUM>*/

	if(mysql_query(&mysql, query)){
	  /*error("Could not create table users!",&mysql);*/
	}

	clrstr(query);

	strcat(query, "create table stream (streamID int primary key auto_increment,");
	strcat(query, "streamName varchar(15) unique);");

	if(mysql_query(&mysql, query)){
	  /*error("Could not create table stream!",&mysql);*/
	}

	clrstr(query);

	strcat(query, "create table post (postID int primary key auto_increment,");
	strcat(query, "userID int,");
	strcat(query, "streamID int,");
	strcat(query, "postDate varchar(30),");
	strcat(query, "postMessage text);");

	if(mysql_query(&mysql, query)){
	  /*error("Could not create table post!",&mysql);*/
	}

/**************************************link vars**************************************************/

	clrstr(query);
	strcat(query, "alter table post add foreign key (userID) refernces user(usreID);");
	mysql_query(&mysql, query);

	clrstr(query);
	strcat(query, "alter table post add foreign key (streamID) refernces stream(streamID);");
	mysql_query(&mysql, query);

/*******************************************User Data Base********************************************/
	int posCount=0,varCount=0,count=0;
	char tempStr[99];
	char streamListSeperated[99][99];
	char c = argv[3][count++];
	char streamList[99];


	if(strstr(argv[1],"1")){

		clrstr(query);
		strcat(query, "select * from users where userName = '");
		strcat(query, argv[2]);
		strcat(query, "'");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);

	    if(mysql_num_rows(res)){
	      /*printf("exists\n");*/

			row = mysql_fetch_row(res);
			strcpy(streamList,row[2]);
			strcat(streamList,",");
			strcat(streamList,argv[3]);
			strcat(streamList,"_0");

			/********************Stream********************************/
				clrstr(query);
				strcat(query, "insert into stream (streamName) values ('");
				strcat(query,  argv[3]);
				strcat(query, "')");
				mysql_query(&mysql, query);
			/**********************************************************/	

			clrstr(query);
			strcat(query, "update users set postRead='");
			strcat(query,streamList);
			strcat(query,"' where users.userName='");
			strcat(query,argv[2]);
			strcat(query,"'");
			mysql_query(&mysql, query);

	    } else {
	      /*printf("doesnt exist\n");*/

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
			    c = argv[3][count];
			    count++;
		  	}
			tempStr[posCount]='\0';
			strcpy(streamListSeperated[varCount],tempStr);
			varCount++;
			strcpy(streamList,"");
		  	int w;
		  	for(w=0;w<varCount;w++){
		  		strcat(streamList,streamListSeperated[w]);
				/********************Stream*************************************/
					clrstr(query);
					strcat(query, "insert into stream (streamName) values ('");
					strcat(query,  streamListSeperated[w]);
					strcat(query, "')");
					mysql_query(&mysql, query);
				/**********************************************************/	
		  		strcat(streamList,"_0");
		  		if(w!=varCount-1)
		  			strcat(streamList,",");
		  	}


			if(strstr(argv[1],"1")){
				clrstr(query);
				strcat(query, "insert into users (userName,postRead) values ('");
				strcat(query,argv[2]);
				strcat(query, "','");
				strcat(query,streamList);
				strcat(query,"')");
				mysql_query(&mysql, query);
			}

	    }

		printf("User was successfully added");

	}else if(strstr(argv[1],"2")){

		char streamList[99];

		char removeStream[99];
		strcpy(removeStream,argv[3]);

		clrstr(query);
		strcat(query, "select * from users where userName = '");
		strcat(query, argv[2]);
		strcat(query, "'");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);

	    if(mysql_num_rows(res)){
			/*printf("exists\n");*/

			row = mysql_fetch_row(res);
			strcpy(streamList,row[2]);

			posCount=0,varCount=0,count=0;
			c = streamList[count++];

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
			    c = streamList[count];
			    count++;
		  	}
			tempStr[posCount]='\0';
			strcpy(streamListSeperated[varCount],tempStr);
			varCount++;
			strcpy(streamList,"");
		  	int w;
		  	for(w=0;w<varCount;w++){
		  		if(!strstr(streamListSeperated[w],removeStream)){
		  			strcat(streamList,streamListSeperated[w]);
		  			if(w!=varCount-1)
		  				strcat(streamList,",");
		  		}
		  	}

		  	if(streamList[strlen(streamList)-1]==','){
		  		streamList[strlen(streamList)-1]='\0';
		  	}

			clrstr(query);
			strcat(query, "update users set postRead='");
			strcat(query,streamList);
			strcat(query,"' where users.userName='");
			strcat(query,argv[2]);
			strcat(query,"'");
			mysql_query(&mysql, query);

		}else{
			/*this user isnt in any streams*/
		}

		printf("User was successfully removed");


	}else if(strstr(argv[1],"3")){

		char thisDate[99];
		time_t rawtime;
		struct tm * timeinfo;
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strcpy(thisDate,asctime(timeinfo));
		thisDate[strlen(thisDate)-1]='\0';

		clrstr(query);
		strcat(query,"select users.postRead from users where userName='");
		strcat(query,argv[2]);
		strcat(query,"'");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		if(strstr(row[0],argv[3])){
			clrstr(query);
			strcat(query,"insert into post (userID, streamID, postDate, postMessage) values ((select userID from users where userName='");
			strcat(query,argv[2]);
			strcat(query,"'),(select streamID from stream where streamName='");
			strcat(query,argv[3]);
			strcat(query,"'),('");
			strcat(query,thisDate);
			strcat(query,"'),('");
			strcat(query,argv[4]);
			int t;
			for(t=5;t<argc;t++){
				strcat(query," ");
				strcat(query,argv[t]);
			}
			strcat(query,"'));");
			mysql_query(&mysql, query);

			printf("Message was successfully posted");
		}else{
			printf("This user doesn't have access to this stream");
		}



	}else if(strstr(argv[1],"4")){

	/*this returns a list of users and the messages and streams they posted to*/
	/*here i return the list of all streams the user is in */

		clrstr(query);
		strcat(query,"select users.postRead from users where userName='");
		strcat(query,argv[2]);
		strcat(query,"'");
		mysql_query(&mysql, query);

		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		printf("%s\n",row[0]);

	}else if(strstr(argv[1],"5")){

		clrstr(query);
		strcat(query,"select users.postRead from users where userName='");
		strcat(query,argv[2]);
		strcat(query,"'");
		mysql_query(&mysql, query);

		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		char*findStr=strstr(row[0],argv[3]);
		int i,count=0;
		char readLn[99];
		for(i=0;i<strlen(findStr);i++){
            if(findStr[i]=='_'){
              count=0;
              i++;
              while((findStr[i]!=',')&&(findStr[i]!=' ')&&(findStr[i]!='\0')){
                readLn[count++]=findStr[i];
                i++;
              }
              break;
            }
        }
        readLn[count]='\0';

		printf("%s",readLn);

	}else if(strstr(argv[1],"6")){

		/*prints the stream of messages*/

		char streamX[99];
		strcpy(streamX,"");

		clrstr(query);
		strcat(query,"select users.userName, stream.streamName, post.postMessage, post.postDate from users ");
		strcat(query,"inner join post on users.userID = post.userID ");
		strcat(query,"inner join stream on post.streamID=stream.streamID ");
		mysql_query(&mysql, query);

		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res))) {
				if(strstr(argv[3],row[1])){

					strcat(streamX,"Sender: ");
					strcat(streamX,row[0]);
					strcat(streamX,"\nDate: ");
					strcat(streamX,row[3]);
					strcat(streamX,"\n");
					strcat(streamX,row[2]);
					strcat(streamX,"\n");
				}
		} 

		printf("%s",streamX);

	}else if(strstr(argv[1],"7")){

		/*saves the last read position*/
		/*argv 4 is the last viewed see if its bigger then the one already existing first*/

		char streamsss[99];

		/**************************gets the position number**************************************/
		clrstr(query);
		strcat(query,"select users.postRead from users where userName='");
		strcat(query,argv[2]);
		strcat(query,"'");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		strcpy(streamsss,row[0]);

		char*findStr=strstr(row[0],argv[3]);
		int i,count=0;
		char readLn[99];
		for(i=0;i<strlen(findStr);i++){
            if(findStr[i]=='_'){
              count=0;
              i++;
              while((findStr[i]!=',')&&(findStr[i]!=' ')&&(findStr[i]!='\0')){
                readLn[count++]=findStr[i];
                i++;
              }
              break;
            }
        }
        readLn[count]='\0';
		printf("%s",readLn);
		/****************************************************************/

		if(atoi(readLn)<atoi(argv[4])){
			clrstr(query);
			strcat(query, "update users set postRead='");

			char*temp=strstr(streamsss,argv[3]);
			int i=0;
			while((temp[i]!=',')&&(temp[i]!=' ')&&(temp[i]!='\0')){
				temp[i]=' ';
				i++;
			}
			temp[i]=' ';

			i=0;
			int cc=0;
			char newstr[99];

			while(streamsss[i]!='\0'){
				if(streamsss[i]!=' '){
					newstr[cc++]=streamsss[i];
				}
				i++;
			}
			newstr[cc]='\0';

			strcat(query,newstr);
			strcat(query,",");
			strcat(query,argv[3]);
			strcat(query,"_");
			strcat(query,argv[4]);
			strcat(query,"' where users.userName='");
			strcat(query,argv[2]);
			strcat(query,"'");
			mysql_query(&mysql, query);
		}

	}else if(strstr(argv[1],"8")){

		clrstr(query);
		strcpy(query, "select * from users");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res))) {
			printf("\n__________________________\n");
			printf("%s |", row[0]);
			printf("%s |", row[1]);
			printf("%s |", row[2]);
			printf("\n");
		}
		clrstr(query);
		strcpy(query, "select * from post");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res))) {
			printf("\n__________________________\n");
			printf("%s |", row[0]);
			printf("%s |", row[1]);
			printf("%s |", row[2]);
			printf("%s |", row[3]);
			printf("%s |", row[4]);
			printf("\n");
		}
		clrstr(query);
		strcpy(query, "select * from stream");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res))) {
			printf("\n__________________________\n");
			printf("%s |", row[0]);
			printf("%s |", row[1]);
			printf("%s |", row[2]);
			printf("\n");
		}

	}else if(strstr(argv[1],"-clear")){

		clrstr(query);
		strcat(query, "TRUNCATE  table users");
		mysql_query(&mysql, query);

		clrstr(query);
		strcat(query, "TRUNCATE  table stream");
		mysql_query(&mysql, query);

		clrstr(query);
		strcat(query, "TRUNCATE  table post");
		mysql_query(&mysql, query);

	}else if(strstr(argv[1],"-reset")){

		clrstr(query);
		strcat(query, "drop table users");
		mysql_query(&mysql, query);

		clrstr(query);
		strcat(query, "drop table stream");
		mysql_query(&mysql, query);

		clrstr(query);
		strcat(query, "drop table post");
		mysql_query(&mysql, query);
		
	}else if(strstr(argv[1],"-posts")){

		clrstr(query);
		strcpy(query, "select * from post");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);

		char mess[99];

		while ((row = mysql_fetch_row(res))) {

			strcpy(mess,row[4]);
			int i;
			for(i=0;i<strlen(mess);i++){
				if(mess[i]=='<'){
					mess[i]=' ';
					mess[i+1]=' ';
					mess[i+2]=' ';
					mess[i+3]=' ';
					mess[i+4]='\n';
				}
			}
			printf("************************************\n");
			printf("%s", mess);
			printf("\n");
		}
		printf("************************************\n");

	}else if(strstr(argv[1],"-users")){

		clrstr(query);
		strcpy(query, "select * from users");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);

		printf("************************************\n");
		while ((row = mysql_fetch_row(res))) {
			printf("%s", row[1]);
			printf("\n");
		}
		printf("************************************\n");

	}else if(strstr(argv[1],"-streams")){

		clrstr(query);
		strcpy(query, "select * from stream");
		mysql_query(&mysql, query);
		res = mysql_store_result(&mysql);

		printf("************************************\n");
		while ((row = mysql_fetch_row(res))) {
			printf("%s", row[1]);
			printf("\n");
		}
		printf("************************************\n");
		
	}else if(strstr(argv[1],"-help")){

		printf("Program Usage\n");
		printf("This program takes in minimum of 3 arguments the first is the operation that needs to be performed by the program\n");
		printf("(display the list of stream, add user, post a message ect) second is the username the third is the stream\n");

	}else if(strstr(argv[1],"9")){

		/***********************************************/
		clrstr(query);
		strcat(query,"select users.postRead from users where userName='");
		strcat(query,argv[2]);
		strcat(query,"'");
		mysql_query(&mysql, query);

		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);

		char streamz[99];
		strcpy(streamz,row[0]);
		/***********************************************/


		/*prints the stream of messages*/

		char streamX[99];
		strcpy(streamX,"");

		clrstr(query);
		strcat(query,"select users.userName, stream.streamName, post.postMessage, post.postDate from users ");
		strcat(query,"inner join post on users.userID = post.userID ");
		strcat(query,"inner join stream on post.streamID=stream.streamID ");
		mysql_query(&mysql, query);

		res = mysql_store_result(&mysql);
		while ((row = mysql_fetch_row(res))) {
				if(strstr(streamz,row[1])){

					strcat(streamX,"Sender: ");
					strcat(streamX,row[0]);
					strcat(streamX,"\nDate: ");
					strcat(streamX,row[3]);
					strcat(streamX,"\n");
					strcat(streamX,row[2]);
					strcat(streamX,"\n");
				}
		} 

		printf("%s",streamX);

	}

/****************************************************************************************************************************************************/	

	/*Finally close connection to server*/

	mysql_close(&mysql);

	/*printf("All done\n");*/

	return 0;
}
