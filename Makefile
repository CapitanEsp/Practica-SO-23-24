CC = gcc -Wall
CFLAGS = -Wall -g
SOURCES = p3.c  listP.c listF.c listM.c TADLista.c  funcionesP0.c funcionesP1.c funcionesP2.c funcionesP3.c
HEADERS = listP.h listF.h listM.h TADLista.h funcionesP0.h  includes.h funcionesP1.h funcionesP1.h funcionesP2.h funcionesP3.h
OBJECTS = $(SOURCES:.c=.o)
TARGET = p3

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
