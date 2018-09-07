# Makfile for 2048 console game written in C++ v11
MYPROG=2048
OBJS=transition.o twozerofoureight.o main.o	
HDRS=transition.h twozerofoureight.h

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
$(MYPROG): $(OBJS)
	$(LINKER) $(OBJS) -o $(MYPROG)

# compile programs
%.o: %.cpp $(HDRS)
	$(COMP) $(COMPFLAGS) $< -o $@

# clean object files
clean:
	$(RM) $(OBJS)

# clean all built files
cleanall: clean
	$(RM) $(MYPROG)

