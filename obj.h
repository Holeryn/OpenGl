#ifndef OBJ
#define OBJ

#define STRING_SIZE 100
#define BUF_SIZE 4096

typedef struct {
  double x;
  double y;
  double z;
}Vertex;

typedef struct{
  int v1;
  int v2;
  int v3;
  int v4;
}Face;

int read_obj(char *path, char long_buffer[BUF_SIZE][STRING_SIZE]);

void build_obj(char long_buffer[BUF_SIZE][STRING_SIZE],
	       int lines,
	       Vertex Vertexes[BUF_SIZE],
	       int *num_vertexes,
	       Face Faces[BUF_SIZE],
	       int *num_faces);
#endif
