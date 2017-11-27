#OBJS specifies which files to compile as part of the project
OBJS = main.cpp task.cpp task.h

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -std=c++11
COMPILER_FLAGS = -std=c++11 -O3

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lsqlite3

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = task

#This is the target that compiles our executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
