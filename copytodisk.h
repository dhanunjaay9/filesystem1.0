#include"fils_system.h"
#ifndef copytodisk_h
#define copytodisk_h
int getsizeofinputfile(char *inputfile);
unsigned int getoffset(struct Metametadata, int);
void writestructure(struct Metametadata , char, char, int);
void startnew(char *, char *);
void copytodisk(char *, char *);
#endif