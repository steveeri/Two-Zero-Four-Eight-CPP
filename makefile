# Makfile for 2048 console game written in C++ v11
MYPROG=2048
OBJS=transition.o userinput.o twozerofoureight.o main.o 	
HDRS=transition.hpp userinput.hpp twozerofoureight.hpp 

COMP=gcc
COMPFLAGS=-c -std=c++11 -Wall -Werror
LINKER=g++
LINKERFLAGS=
RM=rm -f

# clean all built files
game: all
	./$(MYPROG)

# make everything
all: $(MYPROG)

# link and build executable binary
link: $(MYPROG)

$(MYPROG): compile
	$(LINKER) $(OBJS) -o $(MYPROG)

# make everything
compile: $(OBJS)

# compile programs
%.o: %.cpp $(HDRS)
	$(COMP) $(COMPFLAGS) $< -o $@

# clean object files
clean:
	$(RM) $(OBJS)

# clean all backup src code files
cleansrc:
	$(RM) *~
	
# clean all built files
cleanall: clean cleansrc
	$(RM) $(MYPROG)

