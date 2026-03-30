CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lraylib -lm -lpthread -ldl

TARGET = simulation
SRCS = particles.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
