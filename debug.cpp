#include<stdio.h>
#include<string.h>
#include"fils_system.h"
#include"format.h"
#include"diskio.h"
#include<stdlib.h>
struct Metametadata* GetMetadata()
{
	FILE *inputfile;
	struct Metametadata *fileproperties = (struct Metametadata *)malloc(sizeof(struct Metametadata));
	char *buffer = (char *)malloc(sizeofblock*sizeof(char));
	readblock(0, buffer);
	memcpy(fileproperties, buffer, sizeofblock);
	return fileproperties;
}
void debug()
{
	struct Metametadata *fileproperties;
	fileproperties = GetMetadata();
	printf("Number of files:%d\n", fileproperties->number_of_files);
	int count = 0;
	for (int i = 0; i < 6398; i++)
	{
		if (fileproperties->free_blocks[i] == '1')
			count++;
	}
	printf("\nNumber of free blocks:%d\n", count);
	printf("\nNumber of files:%d\n", fileproperties->number_of_files);
	for (int i = 0; i < fileproperties->number_of_files; i++)
	{
		printf("Filename:%s\tNumberofblocks:%d\tOffset:%d\tFilelength:%d\n", fileproperties->files[i].file_name, fileproperties->files[i].number_of_blocks, fileproperties->files[i].start_offset, fileproperties->files[i].file_length);
	}
	free(fileproperties);
	fileproperties = NULL;
}