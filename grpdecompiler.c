#include "grpdecompiler.h"
#include "format.h"
#include "exitcode.h"

void show_intro();
void show_message(const char *message);
void show_error(const char *message);
void show_progress(const unsigned long int start,const unsigned long int stop);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void read_data(void *data,const size_t length,const size_t blocks,FILE *input);
void write_data(const void *data,const size_t length,const size_t blocks,FILE *output);
void check_memory(const void *memory);
size_t check_format(FILE *input);
char *get_memory(const size_t length);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
char *correct_name(const char *name);
char *get_name(const char *path,const char *name);
grp_block *read_blocks(FILE *input,const size_t amount);
void extract(FILE *input,const grp_block *record,const size_t amount,const char *path);
void work(const char *file,const char *path);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<3)
 {
  show_message("You must give a target file name and an output path as the command-line arguments!");
 }
 else
 {
  show_message("Extracting the files... Please wait");
  work(argv[1],argv[2]);
  show_message("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("GRP DECOMPILER 2.4.7");
 puts("The file extraction tool for GRP pseudo-archives by Popov Evgeniy Alekseyevich, 2010-2026 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

void show_progress(const unsigned long int start,const unsigned long int stop)
{
 putchar('\r');
 printf("Amount of the extracted files: %lu from %lu",start,stop);
}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"rb");
 }
 if (target==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name!=NULL)
 {
  target=fopen(name,"wb");
 }
 if (target==NULL)
 {
  show_error("Can't create the output file");
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

void read_data(void *data,const size_t length,const size_t blocks,FILE *input)
{
 if (fread(data,length,blocks,input)<blocks)
 {
  show_error("Can't read data!");
  exit(READ_DATA_ERROR);
 }

}

void write_data(const void *data,const size_t length,const size_t blocks,FILE *output)
{
 if (fwrite(data,length,blocks,output)<blocks)
 {
  show_error("Can't write data!");
  exit(WRITE_DATA_ERROR);
 }

}

void check_memory(const void *memory)
{
 if (memory==NULL)
 {
  show_error("Can't allocate memory");
  exit(MEMORY_ALLOCATION_ERROR);
 }

}

size_t check_format(FILE *input)
{
 grp_block target;
 read_data(&target,sizeof(grp_block),1,input);
 if (strncmp(target.information,"KenSilverman",12)!=0)
 {
  show_error("The invalid format!");
  exit(INVALID_FORMAT_ERROR);
 }
 return target.length;
}

char *get_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length,sizeof(char));
 check_memory(memory);
 return memory;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 size_t current=0;
 size_t elapsed=0;
 size_t block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,sizeof(char),block,input);
  write_data(buffer,sizeof(char),block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,sizeof(char),length,input);
  write_data(buffer,sizeof(char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output=NULL;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

char *correct_name(const char *name)
{
 char *result=NULL;
 size_t index=0;
 for (index=0;index<12;++index)
 {
  if (name[index]==0)
  {
   break;
  }

 }
 result=get_memory(index+1);
 return strncpy(result,name,index);
}

char *get_name(const char *path,const char *name)
{
 char *corrected_name=NULL;
 char *result=NULL;
 size_t name_length=0;
 size_t path_length=0;
 corrected_name=correct_name(name);
 if (corrected_name!=NULL)
 {
  name_length=strlen(corrected_name);
 }
 if (path!=NULL)
 {
  path_length=strlen(path);
 }
 if (path_length>0)
 {
  if (name_length>0)
  {
   result=get_memory(path_length+name_length+1);
   strncpy(result,path,path_length);
   strncat(result,corrected_name,name_length);
  }

 }
 free(corrected_name);
 return result;
}

grp_block *read_blocks(FILE *input,const size_t amount)
{
 grp_block *result=NULL;
 result=(grp_block*)calloc(amount,sizeof(grp_block));
 check_memory(result);
 read_data(result,sizeof(grp_block),amount,input);
 return result;
}

void extract(FILE *input,const grp_block *record,const size_t amount,const char *path)
{
 size_t index=0;
 char *output=NULL;
 for (index=0;index<amount;++index)
 {
  show_progress((unsigned long int)index+1,(unsigned long int)amount);
  output=get_name(path,record[index].information);
  write_output_file(input,output,(size_t)record[index].length);
  free(output);
 }

}

void work(const char *file,const char *path)
{
 FILE *input=NULL;
 grp_block *record=NULL;
 size_t amount=0;
 input=open_input_file(file);
 amount=check_format(input);
 record=read_blocks(input,amount);
 extract(input,record,amount,path);
 fclose(input);
 free(record);
}