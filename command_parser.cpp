#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"command_parser.h"
#include"copytodisk.h"
#include"format.h"
#include"debug.h"
#include"delete.h"
#include"copyfromdisk.h"
void cli_parser()
{
	char s[100];
	gets(s);
	char format[] = "FORMAT",copytodisc[]="COPYTODISK",copyfromdisk[]="COPYFROMDISK",debugger[]="DEBUG",exitt[]="EXIT";
	char delet[] = "DELETE";
	while (strcmp(s, EXIT) != 0)
	{
		if (strnicmp(s, copytodisc,10) == 0)
		{
			char *filename=strchr(s,' ')+1;
			copytodisk("hardDisk.hdd", filename);
		}
		else if (strnicmp(s,copyfromdisk,12) == 0)
		{
			char *sourcename, *destname;
			sourcename = strchr(s, ' ')+1;
			destname = strchr(sourcename, ' ') + 1;
			int indexofsource = 0;
			while (sourcename[indexofsource] != ' ')indexofsource++;
			sourcename[indexofsource] = '\0';
			CopyFromDisk(sourcename, destname);
		}
		else if (strnicmp(s, exitt,4) == 0)
		{
			break;
		}
		else if (strnicmp(s, format,6) == 0)
		{
			formatdisk();
		}
		//if ()
		else if (strnicmp(s, debugger,5) == 0)
		{
			debug();
		}
		else if (strnicmp(s, delet, 6) == 0)
		{
			char *sourcefile = strchr(s, ' ') + 1;
			deletefile(sourcefile);
		}
		else
		{
			printf("Please Enter a valid choice\n");
		}
		printf("\nEnter next command");
		gets(s);
	}

}