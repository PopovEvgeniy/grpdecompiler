#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "format.h"

void show_intro();
void command_line_help();
void show_start_message();
void show_end_message();
void show_progress(unsigned long int start, unsigned long int stop);
FILE *open_input_file(char *name);
FILE *create_output_file(char *name);
void data_dump(FILE *input, FILE *output, unsigned long int length);
void write_output_file(FILE *input, char *name, unsigned long int length);
void check_memory(void *memory);
char *get_string_memory(unsigned long int length);
unsigned char check_character(char character);
char *correct_name(char *name);
char *get_name(char *path, char *name, unsigned long int path_length);
unsigned long int check_format(FILE *input);
grp_block *read_blocks(FILE *input,unsigned long int amount);
void extract(FILE *input,grp_block *record,unsigned long int amount,char *path);
void work(char *file, char *path);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<3)
 {
  command_line_help();
 }
 else
 {
  work(argv[1],argv[2]);
 }
 return 0;
}

void show_intro()
{
 puts(" ");
 puts("GRP DECOMPILER");
 puts("Version 1.9");
 puts("This program distributed under GNU GENERAL PUBLIC LICENSE");
 puts("File extraction tools for GRP pseudo-archives by Popov Evgeniy Alekseyevich, 2010-2016 years");
 puts(" ");
}

void command_line_help()
{
 puts("You must give a target file name and output path as command line arguments!");
}

void show_start_message()
{
 puts("Extracting a files... Please wait");
}

void show_end_message()
{
 puts(" ");
 puts("Work finish");
}

void show_progress(unsigned long int start, unsigned long int stop)
{
 unsigned long int progress;
 progress=start+1;
 progress*=100;
 progress/=stop;
 printf("\r");
 printf("Amount of extracted files: %ld from %ld.Progress:%ld%%",start+1,stop,progress);
}

FILE *open_input_file(char *name)
{
 FILE *file;
 file=fopen(name,"rb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(2);
 }
 return file;
}

FILE *create_output_file(char *name)
{
 FILE *file;
 file=fopen(name,"wb");
 if (file==NULL)
 {
  puts(" ");
  puts("File operation error");
  exit(2);
 }
 return file;
}

void data_dump(FILE *input, FILE *output, unsigned long int length)
{
 unsigned char single_byte;
 unsigned long int index;
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,1);
 if (buffer==NULL)
 {
  for(index=0;index<length;index++)
  {
   fread(&single_byte,1,1,input);
   fwrite(&single_byte,1,1,output);
  }

 }
 else
 {
  fread(buffer,length,1,input);
  fwrite(buffer,length,1,output);
  free(buffer);
 }

}

void write_output_file(FILE *input, char *name, unsigned long int length)
{
 FILE *output;
 output=create_output_file(name);
 data_dump(input,output,length);
 fclose(output);
}

void check_memory(void *memory)
{
 if(memory==NULL)
 {
  puts(" ");
  puts("Can't allocate memory");
  exit(1);
 }

}

char *get_string_memory(unsigned long int length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,1);
 check_memory(memory);
 return memory;
}

unsigned char check_character(char character)
{
 unsigned char result;
 result=0;
 if(isalnum(character)!=0) result=1;
 if((character=='.')||(character=='_')) result=1;
 if((character=='-')||(character=='~')) result=1;
 if((character=='(')||(character==')')) result=1;
 if((character=='{')||(character=='}')) result=1;
 if((character=='@')||(character=='$')) result=1;
 if((character=='!')||(character=='#')) result=1;
 if((character=='%')||(character=='&')) result=1;
 if((character=='^')||(character=='\'')) result=1;
 return result;
}

char *correct_name(char *name)
{
 char *result=NULL;
 char *output=NULL;
 unsigned char index,position,length;
 output=get_string_memory(12);
 position=0;
 for (index=0;index<12;index++)
 {
  if (check_character(name[index])==1)
  {
   output[position]=name[index];
   position++;
  }

 }
 length=strlen(output);
 result=get_string_memory(length);
 strncpy(result,output,length);
 free(output);
 return result;
}

char *get_name(char *path, char *name, unsigned long int path_length)
{
 char *output=NULL;
 char *result=NULL;
 unsigned long int length;
 output=correct_name(name);
 length=strlen(output)+path_length;
 result=get_string_memory(length);
 strcpy(result,path);
 strcat(result,output);
 free(output);
 return result;
}

unsigned long int check_format(FILE *input)
{
 grp_block target;
 fread(&target,sizeof(grp_block),1,input);
 if(strncmp(target.information,"KenSilverman",12)!=0)
 {
  puts("Bad signature of GRP pseudo-archive!");
  exit(3);
 }
 return target.length;
}

grp_block *read_blocks(FILE *input,unsigned long int amount)
{
 grp_block *result=NULL;
 result=(grp_block*)calloc(amount,sizeof(grp_block));
 check_memory(result);
 fread(result,sizeof(grp_block),amount,input);
 return result;
}

void extract(FILE *input,grp_block *record,unsigned long int amount,char *path)
{
 unsigned long int index,path_length;
 char *output=NULL;
 path_length=strlen(path);
 for (index=0;index<amount;index++)
 {
  show_progress(index,amount);
  output=get_name(path,record[index].information,path_length);
  write_output_file(input,output,record[index].length);
  free(output);
 }

}

void work(char *file, char *path)
{
 FILE *input;
 grp_block *record=NULL;
 unsigned long int amount;
 input=open_input_file(file);
 amount=check_format(input);
 record=read_blocks(input,amount);
 show_start_message();
 extract(input,record,amount,path);
 show_end_message();
 fclose(input);
 free(record);
}