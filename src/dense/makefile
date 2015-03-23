
# Source, Executable, Includes, Library Defines
INCL   = ../../include/ -I$TACC_PAPI_INC
SRC    = PQ_sssp_ring.c PQ_sssp_half.c
OBJ    = $(SRC:.c=.o)
LIBS   = -lrt -lpapi
OPTION = -DN=4096 -DFLUSH_SIZE=1024*32
EXE    = main

# Compiler, Linker Defines
CC      = gcc
CFLAGS  = -Wall -Werror -O2
LIBPATH = -L$TACC_PAPI_LIB
LDFLAGS = -o $(EXE) $(LIBPATH) $(LIBS) $(OPTION)
CFDEBUG = -ansi -pedantic -Wall -g -DDEBUG $(LDFLAGS)
RM      = /bin/rm -f

# Compile and Assemble C Source Files into Object Files
%.o: %.c
       $(CC) -c $(CFLAGS) $*.c

# Link all Object Files with external Libraries into Binaries
$(EXE): $(OBJ)
       $(CC) $(LDFLAGS) $(OBJ)

# Objects depend on these Libraries
$(OBJ): $(INCL)

# Create a gdb/dbx Capable Executable with DEBUG flags turned on
debug:
	$(CC) $(CFDEBUG) $(SRC)

# Clean Up Objects, Exectuables, Dumps out of source directory
clean:
	$(RM) $(OBJ) $(EXE) core a.out

