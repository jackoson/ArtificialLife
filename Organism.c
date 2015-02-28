#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define THRESHOLD_PERC 50

int exists(char *fname)
{
    FILE *file;
    if (file = fopen(fname, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}


void findName(char* name){

  int i = 0;
  sprintf(name, "%d.exe", i);

  while(exists(name)){
    i=i+1;
    sprintf(name, "%d.exe", i);
  }
}

int main(int argc, char* args[]){



  printf("Hi");

  char* name = malloc(30*sizeof(char));
  findName(name);
  printf("Getting unique name: '%s'\n", name);

  char* cp = malloc(50*sizeof(char));
  strcpy(cp, "copy ");
  strcat(cp, args[0]);
  strcat(cp, " ");
  strcat(cp, name);
  printf("Copying binary: '%s'\n", cp);
  system(cp);


  time_t t;
  srand((unsigned) time(&t));
  printf("Should I mutate?");
  if(rand()%100>=THRESHOLD_PERC){
    printf("Randomly Editing: '%s'\n", name);
    FILE* f = fopen( name, "ab");
    fseek(f, 0L, SEEK_END);
    int end = ftell(f);

    int EditPos = rand()%end;
    fseek(f, EditPos, SEEK_SET);
    char* in = malloc(50*sizeof(char));
    fread(in, 1, 1, f);
    printf("this is here: '%s'\n",in);
    printf("%c\n", in[0]);
    in[0] = in[0]^1;
    printf("%c\n", in[0]);
    fread(in, 1, 1, f);
    fclose(f);
  }



  char* run = malloc(30*sizeof(char));
  strcpy(run, name);

  printf("Running new binary: '%s'\n", run);
  system(run);

  char* rm = malloc(30*sizeof(char));
  sprintf(rm, "remove %s", args[0]);
  system(rm);

  return 0;
}
