#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"fils_system.h"
#include"format.h"
#include"diskio.h"


int getsizeofinputfile(char *inputfile)
{
	FILE *fp;
	int isopen;
	isopen = fopen_s(&fp, inputfile, "rb");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fcloseall();
	return size;
}



unsigned int getoffset(struct Metametadata *filedata, int numberofblocks)
{
	int indexoffree = 1;
	while (indexoffree<=6398)
	{
		while (indexoffree <= 6398 && filedata->free_blocks[indexoffree] == '0')indexoffree++;
		int hasfreeblocks=0;
		while (indexoffree <= 6398 && filedata->free_blocks[indexoffree] == '1'&&hasfreeblocks < numberofblocks)
		{
			hasfreeblocks++;
			indexoffree++;
		}
		if (hasfreeblocks == numberofblocks)
		{
			indexoffree--;
			break;
		}
	}
	int offset = indexoffree - numberofblocks+1;
	int setindex = indexoffree - numberofblocks+1;
	for (int i = 0; i < numberofblocks; i++)
		filedata->free_blocks[setindex++] = '0';
	return offset;
	return 0;
}



int setfilestructure(struct Metametadata *fileproperties, char *destfile)
{
	FILE *inputfile;
	int isopen=fopen_s(&inputfile, destfile, "rb");
	fseek(inputfile, 0, SEEK_END);
	int lenghtoffile = ftell(inputfile), numberoffiles = fileproperties->number_of_files;
	//if (numberoffiles)
	fileproperties->files[numberoffiles].file_length = lenghtoffile;
	strcpy(fileproperties->files[numberoffiles].file_name, destfile);
	int numberofblocks = lenghtoffile%sizeofblock ? lenghtoffile / sizeofblock + 1 : lenghtoffile / sizeofblock;
	fileproperties->files[numberoffiles].number_of_blocks = numberofblocks;
	int offset = getoffset(fileproperties, numberofblocks);
	fileproperties->files[numberoffiles].start_offset = offset;
	fileproperties->number_of_files += 1;
	fclose(inputfile);
	return offset;
}


void copytodisk(char *disk, char *destfile)
{
	FILE *inputfile;
	int isopen, iswrite, isread;
	struct Metametadata *fileproperties=(struct Metametadata *)malloc(sizeof(struct Metametadata));
	char *buffer = (char *)malloc(sizeofblock*sizeof(char));
	readblock(0, buffer);
	memcpy(fileproperties, buffer, sizeofblock);
	int offset=setfilestructure(fileproperties, destfile);
	memcpy(buffer, fileproperties, sizeofblock);
	writeblock(0, buffer);
	int numberoffiles = fileproperties->number_of_files,lengthoffile=fileproperties->files[numberoffiles].file_length;
	int numberofblocks = fileproperties->files[numberoffiles-1].number_of_blocks;
	isopen = fopen_s(&inputfile, destfile, "rb");
	for (int i = 0; i < numberofblocks-1; i++)
	{
		fread(buffer, sizeofblock, 1, inputfile);
		writeblock(offset + i, buffer);
	}
	int lastbuffersize;
	if ((lastbuffersize = lengthoffile%sizeofblock))
	{
		fread(buffer, lastbuffersize, 1, inputfile);
		writeblock(offset + numberofblocks-1, buffer);
	}
	else
	{
		fread(buffer, sizeofblock, 1, inputfile);
		writeblock(offset + numberofblocks-1, buffer);
	}
	free(buffer);
	buffer = NULL;
	fcloseall();
}