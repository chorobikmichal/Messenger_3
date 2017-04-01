#include <string.h>
newline
#include <stdio.h>
newline
#include <stdlib.h>
newline
#include "stream.h"
newline
#include <time.h>
newline
newline
/*
*Michal Chorobik 0937145
*CIS 2750 Assignment2
*mchorobi@uofguelph.mail.ca
*February 19, 2017
*/
newline
newline
class
 
PostEntry
 
{
newline
 
 
void
 
formatEntry
(
struct
 
userPost
*
st
,
char
*
arg
[
99]
,
char
*
stream
[
99]
,
char
*
text
[
99]
)
{
newline
 
 
 
 
/*creates the struct used by the updateStream() function*/
newline
newline
 
 
 
 
(
*
st
)
.
username
=
*
arg
;
newline
 
 
 
 
(
*
st
)
.
streamname
=
*
stream
;
newline
 
 
 
 
(
*
st
)
.
text
[
0]
=
*
text
;
newline
newline
 
 
 
 
/*printf("%s\n",(*st).username );*/
newline
 
 
 
 
/*printf("%s\n",(*st).streamname );*/
newline
 
 
 
 
/*printf("%s\n",(*st).text[0] );*/
newline
newline
 
 
}
newline
 
 
void
 
readInput
(
char
*
 
stream
[
99]
,
char
*
 
text
[
99]
)
{
newline
 
 
 
 
/*reads the user's input to the post program*/
newline
newline
 
 
 
 
 
 
char
 
tempText
[
99]
;
newline
newline
 
 
 
 
 
 
printf
(
"stream: "
)
;
newline
 
 
 
 
 
 
fgets
(
*
stream
,
99
,
stdin
)
;
newline
 
 
 
 
 
 
/**stream[strlen(*stream)-1]='\0';*/
newline
newline
 
 
 
 
 
 
printf
(
"enter text: "
)
;
newline
 
 
 
 
 
 
fgets
(
tempText
,
99
,
stdin
)
;
newline
 
 
 
 
 
 
tempText
[
strlen
(
tempText
)
-
1]
=
'\0'
;
newline
newline
 
 
 
 
 
 
if
(
strcmp
(
tempText
,
"ctrl-d"
)
!
=
0
)
{
newline
 
 
 
 
 
 
 
 
strcpy
(
*
text
,
tempText
)
;
newline
 
 
 
 
 
 
 
 
printf
(
"- "
)
;
newline
 
 
 
 
 
 
 
 
fgets
(
tempText
,
99
,
stdin
)
;
newline
 
 
 
 
 
 
 
 
tempText
[
strlen
(
tempText
)
-
1]
=
'\0'
;
newline
 
 
 
 
 
 
}
newline
newline
 
 
 
 
 
 
while
 
(
strcmp
(
tempText
,
"ctrl-d"
)
!
=
0
)
 
{
newline
 
 
 
 
 
 
 
 
strcat
(
*
text
,
"\r\n"
)
;
newline
 
 
 
 
 
 
 
 
strcat
(
*
text
,
tempText
)
;
newline
 
 
 
 
 
 
 
 
printf
(
"- "
)
;
newline
 
 
 
 
 
 
 
 
fgets
(
tempText
,
99
,
stdin
)
;
newline
 
 
 
 
 
 
 
 
tempText
[
strlen
(
tempText
)
-
1]
=
'\0'
;
newline
 
 
 
 
 
 
}
newline
newline
 
 
}
newline
 
 
void
 
getTimeDate
(
struct
 
userPost
*
st
)
{
/*determines the current time and date and formats it as a string*/
newline
newline
 
 
 
 
/*the stuff below gives the time and date example: Tue Feb 14 14:46:56 2017*/
newline
 
 
 
 
time_t
 
rawtime
;
newline
 
 
 
 
struct
 
tm
 
*
 
timeinfo
;
newline
 
 
 
 
time
 
(
 
&rawtime
 
)
;
newline
 
 
 
 
timeinfo
 
=
 
localtime
 
(
 
&rawtime
 
)
;
newline
 
 
 
 
/*printf ( "Current local time and date: %s", asctime(timeinfo));*/
newline
 
 
 
 
(
*
st
)
.
date
=
asctime
(
timeinfo
)
;
newline
newline
 
 
}
newline
 
 
void
 
submitPost
(
struct
 
userPost
*
st
)
{
/*calls the updateStream() function*/
newline
 
 
 
 
updateStream
(
st
)
;
newline
 
 
}
newline
}
;
newline
newline
int
 
main
(
int
 
argc
,
 
char
 
const
 
*
argv
[
]
)
 
{
newline
 
 
/*format of args: id,stream,text*/
newline
newline
 
 
class
 
PostEntry
 
PostEntry
;
newline
newline
 
 
char
 
author
[
99]
;
newline
 
 
strcpy
(
author
,
argv
[
1]
)
;
newline
 
 
char
 
*
ptr1
=
author
;
newline
newline
 
 
char
 
stream
[
99]
;
newline
 
 
strcpy
(
stream
,
argv
[
2]
)
;
newline
 
 
char
 
*
ptr2
=
stream
;
newline
newline
 
 
char
 
text
[
99]
;
newline
 
 
int
 
i
;
newline
newline
 
 
char
 
arguments
[
1000]
[
1000]
;
newline
newline
 
 
for
(
i
=
3
;
i<argc
;
i
+
+
)
newline
 
 
 
 
strcpy
(
arguments
[
i
-
3]
,
argv
[
i]
)
;
newline
newline
 
 
for
(
i
=
3
;
i<argc
;
i
+
+
)
newline
 
 
 
 
strcat
(
arguments
[
i
-
3]
,
" "
)
;
newline
newline
 
 
strcpy
(
text
,
arguments
[
0]
)
;
newline
 
 
for
(
i
=
1
;
i<argc
+
3
;
i
+
+
)
newline
 
 
 
 
strcat
(
text
,
arguments
[
i]
)
;
newline
newline
 
 
char
 
*
ptr3
=
text
;
newline
newline
 
 
struct
 
userPost
 
userPost
;
newline
 
 
struct
 
userPost
*
 
spt
 
=
 
&userPost
;
newline
newline
 
 
PostEntry
.
formatEntry
(
spt
,
&ptr1
,
&ptr2
,
&ptr3
)
;
newline
newline
 
 
/*by here the stream name, author and the text are added into the struct*/
newline
 
 
/*update stream posts the post to the stream*/
newline
 
 
PostEntry
.
getTimeDate
(
&userPost
)
;
newline
 
 
PostEntry
.
submitPost
(
&userPost
)
;
newline
newline
 
 
return
 
0
;
newline
}
newline
