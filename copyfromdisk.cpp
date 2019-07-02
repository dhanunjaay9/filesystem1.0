#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"fils_system.h"
#include"format.h"
#include"diskio.h"

void CopyFromDisk(char *sourcefile, char *destfile)
{
	FILE *inputfile;
	int isopen, iswrite, isread;
	isopen = fopen_s(&inputfile, destfile, "wb+");
	struct Metametadata *fileproperties = (struct Metametadata *)malloc(sizeof(struct Metametadata));
	char *buffer = (char *)malloc(sizeofblock*sizeof(char));
	readblock(0, buffer);
	memcpy(fileproperties, buffer, sizeofblock);
	int numberoffiles = fileproperties->number_of_files;
	int i;
	for ( i = 0; i < numberoffiles; i++)
	{
		if (strcmp(fileproperties->files[i].file_name, sourcefile)==0)
		{
			break;
		}
	}
	if (i == numberoffiles)
	{
		printf("File not found in disk");
		return;
	}
	int lengthoffile = fileproperties->files[i].file_length, offset = fileproperties->files[i].start_offset;
	int numberofblocks = fileproperties->files[i].number_of_blocks;
	if (isopen == -1)
	{
		printf("Couldn't open the file");
	}
	for (int j = 0; j < numberofblocks-1; j++)
	{
		readblock(offset + j, buffer);
		fwrite(buffer, sizeofblock, 1, inputfile);
	}
	int lastbuffersize;
	if ((lastbuffersize=lengthoffile%sizeofblock))
	{
		readblock(offset + numberofblocks - 1, buffer);
		fwrite(buffer, lastbuffersize, 1, inputfile);
	}
	else
	{
		readblock(offset + numberofblocks - 1, buffer);
		fwrite(buffer, sizeofblock, 1, inputfile);
	}
	fclose(inputfile);
	free(buffer);
	buffer = NULL;
	printf("File copied successfully");
}