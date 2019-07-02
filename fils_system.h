#ifndef file_system_h
#define file_system_h
struct Filedata
{
	char file_name[20];
	unsigned int start_offset;
	unsigned int number_of_blocks;
	unsigned int file_length;
};
struct Metametadata
{
	unsigned int Magicnumber;
	struct Filedata files[32];
	int number_of_files;
	char free_blocks[6398];
	int offset;
};

#define sizeofblock (16*1024)
#define magicnumber 0x444E524D

#endif