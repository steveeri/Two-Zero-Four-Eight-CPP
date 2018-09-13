# Makfile for 2048 console game written in C++ v11
MYPROG=2048
OBJS=transition.o terminalutility.o twozerofoureight.o main.o 	
HDRS=transition.hpp terminalutility.hpp twozerofoureight.hpp 

COMP=gcc
CFLAGS=-c -std=c++11  -Wall -Werror
LINKER=g++
LFLAGS=-lcurses -lncurses
RM=rm -f

# clean all built files
game: all
	./$(MYPROG)

# make everything
all: $(MYPROG)

# link and build executable binary
link: $(MYPROG)

$(MYPROG): compile
	$(LINKER) $(LFLAGS) $(OBJS) -o $(MYPROG)

# make everything
compile: $(OBJS)

# compile programs
%.o: %.cpp $(HDRS)
	$(COMP) $(CFLAGS) $< -o $@

# clean object files
clean:
	$(RM) $(OBJS)

# clean all backup src code files
cleansrc:
	$(RM) *~
	
# clean all built files
cleanall: clean cleansrc
	$(RM) $(MYPROG)

