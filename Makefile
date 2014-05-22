 # Declaration of variables
CC = g++
CC_FLAGS = -w
CC_LIBS = -lGL -lglut -lGLEW -lGLU

# File names
EXEC = main
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(CC_LIBS)

# To obtain object files
%.o: %.cpp %.h
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)