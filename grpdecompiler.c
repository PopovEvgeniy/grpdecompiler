#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "format.h"

void show_intro();
void show_message(const char *message);
void show_progress(const unsigned long int start,const unsigned long int stop);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
void check_memory(const void *memory);
char *get_string_memory(const size_t length);
unsigned char check_character(const char target);
char *correct_name(const char *name);
char *get_name(const char *path,const char *name);
size_t check_format(FILE *input);
grp_block *read_blocks(FILE *input,const size_t amount);
void extract(FILE *input,const grp_block *record,const size_t amount,const char *path);
void work(const char *file,const char *path);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<3)
 {
  show_message("You must give a target file name and output path as command line arguments!");
 }
 else
 {
  show_message("Extracting a files... Please wait");
  work(argv[1],argv[2]);
  show_message("Work finish");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("GRP DECOMPILER");
 puts("Version 2.1.3");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
 puts("File extraction tools for GRP pseudo-archives by Popov Evgeniy Alekseyevich, 2010-2024 years");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

void show_progress(const unsigned long int start,const unsigned long int stop)
{
 unsigned long int progress;
 progress=(start+1)*100;
 progress/=stop;
 putchar('\r');
 printf("Amount of extracted files: %ld from %ld.Progress:%ld%%",start+1,stop,progress);
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_message("Can't create ouput file");
  exit(2);
 }
 return target;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char data;
 size_t index;
 data=0;
 for (index=0;index<length;++index)
 {
  fread(&data,sizeof(unsigned char),1,input);
  fwrite(&data,sizeof(unsigned char),1,output);
 }

}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(unsigned char),length,input);
  fwrite(buffer,sizeof(unsigned char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
  exit(3);
 }

}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 check_memory(memory);
 return memory;
}

unsigned char check_character(const char target)
{
 unsigned char result;
 result=1;
 if(isalnum(target)!=0)
 {
  result=0;
 }
 else
 {
  if(target=='.') result=0;
  if((target=='-')||(target=='_')) result=0;
 }
 return result;
}

char *correct_name(const char *name)
{
 char *result=NULL;
 char *target=NULL;
 size_t index,position;
 position=0;
 target=get_string_memory(12);
 for(index=0;index<12;++index)
 {
  if(check_character(name[index])==1) continue;
  target[position]=name[index];
  ++position;
 }
 result=get_string_memory(position);
 strncpy(result,target,position);
 free(target);
 return result;
}

char *get_name(const char *path,const char *name)
{
 char *output=NULL;
 char *result=NULL;
 size_t length;
 output=correct_name(name);
 length=strlen(output)+strlen(path);
 result=get_string_memory(length);
 strcpy(result,path);
 strcat(result,output);
 free(output);
 return result;
}

size_t check_format(FILE *input)
{
 grp_block target;
 fread(&target,sizeof(grp_block),1,input);
 if(strncmp(target.information,"KenSilverman",12)!=0)
 {
  puts("Bad signature of GRP pseudo-archive!");
  exit(4);
 }
 return (size_t)target.length;
}

grp_block *read_blocks(FILE *input,const size_t amount)
{
 grp_block *result=NULL;
 result=(grp_block*)malloc(amount*sizeof(grp_block));
 check_memory(result);
 fread(result,sizeof(grp_block),amount,input);
 return result;
}

void extract(FILE *input,const grp_block *record,const size_t amount,const char *path)
{
 size_t index;
 char *output=NULL;
 for (index=0;index<amount;++index)
 {
  show_progress((unsigned long int)index,(unsigned long int)amount);
  output=get_name(path,record[index].information);
  write_output_file(input,output,(size_t)record[index].length);
  free(output);
 }

}

void work(const char *file,const char *path)
{
 FILE *input;
 grp_block *record=NULL;
 size_t amount;
 input=open_input_file(file);
 amount=check_format(input);
 record=read_blocks(input,amount);
 extract(input,record,amount,path);
 fclose(input);
 free(record);
}