CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lGL -lGLU -lglut -lm

TARGET = obj

SOURCES = graphics/graphics.c main.c obj.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
