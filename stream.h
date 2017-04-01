#ifndef __MCHOROBI_STREAM__
#define __MCHOROBI_STREAM__

struct userPost {
  char *username;
  char *streamname;
  char *date;
  char *text[50];
};

void updateStream(struct userPost *st);
void addUser(char *username, char *list);
void removeUser(char *username, char *list);

#endif
