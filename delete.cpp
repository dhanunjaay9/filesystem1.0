#include<stdio.h>
#include<string.h>
#include"fils_system.h"
#include"format.h"
#include"diskio.h"
#include<stdlib.h>



struct Metametadata* Getmetadata()
{
	FILE *inputfile;
	struct Metametadata *fileproperties = (struct Metametadata *)malloc(sizeof(struct Metametadata));
	char *buffer = (char *)malloc(sizeofblock*sizeof(char));
	readblock(0, buffer);
	memcpy(fileproperties, buffer, sizeofblock);
	return fileproperties;
}

void setfreeblocks(struct Metametadata *fileproperties, int indexoffile)
{
	int offset = fileproperties->files[indexoffile].start_offset, numberofblocks = fileproperties->files[indexoffile].number_of_blocks;
	for (int i = 0; i < numberofblocks; i++)
	{
		fileproperties->free_blocks[i + offset] = '1';
	}
}
void deletefile(char *filename)
{
	struct Metametadata *fileproperties;
	fileproperties = Getmetadata();
	int numberoffiles = fileproperties->number_of_files;
	int i = 0;
	for (; i < numberoffiles; i++)
	{
		if (strcmp(fileproperties->files[i].file_name, filename) == 0)
		{
			setfreeblocks(fileproperties, i);
			break;
		}
	}
	if (i == numberoffiles)
	{
		printf("File not found");
		return;
	}
	char *buffer = (char *)malloc(sizeofblock*sizeof(char));
	char *filedatabuffer = (char *)malloc(sizeof(struct Filedata));
	memcpy(filedatabuffer, &fileproperties->files[numberoffiles - 1], sizeof(struct Filedata));
	memcpy(&fileproperties->files[i], filedatabuffer, sizeof(struct Filedata));
	fileproperties->number_of_files -= 1;
	memcpy(buffer, fileproperties, sizeofblock);
	writeblock(0, buffer);
	free(buffer);
	free(filedatabuffer);
	buffer = NULL;
	filedatabuffer = NULL;
}