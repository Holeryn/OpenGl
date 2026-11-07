#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include "obj.h"

#define ERROR(m) printf(#m); \
  exit(-1);

int cursors = 0;

static char *read_next_line(char file[BUF_SIZE], int *flag){
  char *word = malloc(sizeof(char)*BUF_SIZE);

  int i;
  for(i = 0; file[cursors] != '\n' && file[cursors] != '\0'; i++){
    word[i] = file[cursors];
    cursors++;
  }
  cursors++; // Scarto l'ultimo termine

  file[cursors] == '\0' ? (*flag = 1) : (*flag = 0);
  
  word[i] = '\n';
  word[i+1] = '\0';
  return word;
}

#define FILE_SIZE BUF_SIZE*100

int read_obj(char *path, char long_buffer[BUF_SIZE][STRING_SIZE]){
  char buffer[FILE_SIZE];
  int fd;

  fd = open(path,O_RDONLY);
  if(fd == -1){
    ERROR("File non esistente");
  }

  int r = read(fd,buffer,FILE_SIZE);
  if(r == -1){
    ERROR("Non sono riuscito a leggere il file");
  }else{
    buffer[r]='\0';
  }

  int i;
  int flag = 0;
  char *word;
  word = read_next_line(buffer,&flag);
  for(i = 0;
      flag == 0;
      word = read_next_line(buffer,&flag), i++){
    printf("%d , %s",i,word);
    strcpy(long_buffer[i],word);
  }
  strcpy(long_buffer[i],word);
  printf("%d , %s",i,word);
  
  return i;
}

int word_cursor = 0;
static char *read_next_word(char line[BUF_SIZE], int *flag){
  char *word = malloc(sizeof(char)*BUF_SIZE);

  for( int i = 0;
       line[word_cursor] != ' ' && line[word_cursor] != '\0';
       word_cursor++, i++){
    word[i] = line[word_cursor];
  }
  word_cursor++;

  if(line[word_cursor] == '\0'){
    *flag = 1;
    word_cursor = 0;
  }else{
    *flag = 0;
  }

  return word;
}

void build_obj(char long_buffer[BUF_SIZE][STRING_SIZE],
	       int lines,
	       Vertex Vertexes[BUF_SIZE],
	       int *num_vertexes,
	       Face Faces[BUF_SIZE],
	       int *num_faces){
  int v = 1; // Gli obj iniziano da 1 non mi chiedete perchè
  int f = 0;
  
  
  for(int i = 0; i < lines; i++){
    if(long_buffer[i][0] == 'v'){
      int flag;
      char *word = read_next_word(long_buffer[i],&flag); // Scarto 'v'

      int state = 0;
      
      do{
	word = read_next_word(long_buffer[i],&flag);
        if(word[0] == ' ' || word[0] == '\n' || word[0] == '\0')
	  continue;

	printf("%s\n",word);

	switch(state){
	case 0: Vertexes[v].x = atof(word); state = 1; break;// x
	case 1: Vertexes[v].y = atof(word); state = 2; break;// y
	case 2: Vertexes[v].z = atof(word); state = 0; break;// z
	}
      }while(flag == 0);
      v++;
    }else if(long_buffer[i][0] == 'f'){
      int flag;
      char *word = read_next_word(long_buffer[i],&flag);

      int state = 0;

      do{
	word = read_next_word(long_buffer[i],&flag);
	if(word[0] == 0x0)
	  continue;

	printf("%s\n",word);

	switch(state){
	case 0: Faces[f].v1 = atoi(word); state = 1; break; //v1
	case 1: Faces[f].v2 = atoi(word); state = 2; break; //v2
	case 2: Faces[f].v3 = atoi(word); state = 3; break; //v3
	case 3: Faces[f].v4 = atoi(word); state = 0; break; //v4
	}
      }while(flag == 0);
      f++;
    }
  }

  *num_vertexes = v;
  *num_faces = f;
}
