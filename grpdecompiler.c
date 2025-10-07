#include "grpdecompiler.h"
#include "format.h"

void show_intro();
void show_message(const char *message);
void show_progress(const unsigned long int start,const unsigned long int stop);
void check_memory(const void *memory);
char *get_memory(const size_t length);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
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
  show_message("You must give a target file name and an output path as the command-line arguments!");
 }
 else
 {
  show_message("Extracting a files... Please wait");
  work(argv[1],argv[2]);
  show_message("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("GRP DECOMPILER");
 puts("Version 2.3");
 puts("The file extraction tool for GRP pseudo-archives by Popov Evgeniy Alekseyevich, 2010-2025 years");
 puts("This program is distributed under the GNU GENERAL PUBLIC LICENSE");
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
 printf("Amount of the extracted files: %lu from %lu. The progress:%lu%%",start+1,stop,progress);
}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
  exit(3);
 }

}

char *get_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length,sizeof(char));
 check_memory(memory);
 return memory;
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open the input file");
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
  show_message("Can't create the ouput file");
  exit(2);
 }
 return target;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer;
 size_t current,elapsed,block;
 elapsed=0;
 block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  fread(buffer,sizeof(char),block,input);
  fwrite(buffer,sizeof(char),block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(char),length,input);
  fwrite(buffer,sizeof(char),length,output);
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

char *correct_name(const char *name)
{
 char *result;
 size_t index;
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
 char *output=NULL;
 char *result=NULL;
 size_t length;
 output=correct_name(name);
 length=strlen(output)+strlen(path);
 result=get_memory(length+1);
 sprintf(result,"%s%s",path,output);
 free(output);
 return result;
}

size_t check_format(FILE *input)
{
 grp_block target;
 fread(&target,sizeof(grp_block),1,input);
 if(strncmp(target.information,"KenSilverman",12)!=0)
 {
  puts("The invalid format!");
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