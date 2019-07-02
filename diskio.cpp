#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"fils_system.h"
#include"format.h"
void readblock(int blocknumber,char *buffer)
{
	FILE *diskfp;
	int isopen, isread;
	isopen = fopen_s(&diskfp, "hardDisk.hdd", "rb");
	if (isopen == -1)
	{
		printf("Invalid disk read");
		fclose(diskfp);
		return;
	}
	fseek(diskfp, blocknumber*sizeofblock, 0);
	//char *temporarybuffer = (char *)malloc(sizeofblock*sizeof(char));
	isread = fread(buffer, sizeofblock, 1, diskfp);
	//memcpy(buffer, temporarybuffer, sizeofblock);
	fclose(diskfp);
}
void writeblock(int blocknumber,char *buffer)
{
	FILE *diskfp;
	int isopen, iswrite;
	isopen = fopen_s(&diskfp, "hardDisk.hdd", "rb+");
	if (isopen == -1)
	{
		printf("Invalid disk opened");
		fclose(diskfp);
		return;
	}
	fseek(diskfp, (blocknumber)*sizeofblock, 0);
	iswrite=fwrite(buffer, sizeofblock, 1, diskfp);
	fflush(diskfp);
	fclose(diskfp);
}