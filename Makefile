CC = g++
CFLAGS = -Wall
LDFLAGS = 

# define the C source files
SRCS = readUtils.cpp solve.cpp Molecule.cpp Equation.cpp main.cpp

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = balancer



all: $(MAIN)

.PHONY: depend clean

.cpp.o:
	$(CC) $(CFLAGS) -c $<  -o $@

$(MAIN): $(OBJS)
	${CC} ${CFLAGS} $(OBJS) ${LDFLAGS} -o $(MAIN)

clean:
	rm -rf *o $(MAIN)
	
depend: $(SRCS)
	makedepend $^


# DO NOT DELETE
