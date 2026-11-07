#include <stdio.h>
#include <stdlib.h>

#include "obj.h"
#include "graphics/graphics.h"

int main(int argc, char **argv){
  char objF[BUF_SIZE][STRING_SIZE];

  Vertex Vertexes[BUF_SIZE];
  int num_vertexes;
  Face Faces[BUF_SIZE];
  int num_faces;
  
  int lines = read_obj(argv[1],objF);
  build_obj(objF,lines,Vertexes,&num_vertexes,Faces,&num_faces);

  for(int i = 0; i <= num_vertexes; i++){
    printf(" %d x:%f, y: %f, z: %f ",i,Vertexes[i].x,Vertexes[i].y,Vertexes[i].z);
  }

  for(int i = 0; i <= num_faces; i++){
    printf(" %d v1:%d, v2: %d, v3: %d, v4: %d ",i,Faces[i].v1,Faces[i].v2,Faces[i].v3, Faces[i].v4);
  }

  
  loadOBJ(Vertexes,Faces,num_faces,num_vertexes);
  start_opengl(argc,argv);
  
}
