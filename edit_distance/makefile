#makefile for edit_distance project

SRC1 = edit_distance.c
SRC2 = edit_distance_client.c
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

EXE = $(SRC1:.c=.e)

CFLAGS = -w -std=c99 

HFILES = edit_distance.h

all : $(EXE)
 
$(EXE): $(OBJ1) $(OBJ2)
	gcc $(CFLAGS) $(OBJ1) $(OBJ2) -o $(EXE) 

$(OBJ1) : $(SRC1) $(HFILES)
	gcc -c $(CFLAGS) $(SRC1) -o $(OBJ1) 

$(OBJ2) : $(SRC2) $(HFILES)
	gcc -c $(CFLAGS) $(SRC2) -o $(OBJ2) 
	
clean:
	rm -f $(EXE) $(OBJ1) $(OBJ2)


