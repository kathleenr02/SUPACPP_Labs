# Compiler and flags
CC = g++
CFLAGS = -Wall

# Default program to compile
TARGET = AnalyseData

# Object files
OBJECTS = $(TARGET).o CustomFunctions.o

# Default input file (can be overridden)
FILE ?= input2D_float.txt

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Compile AnalyseData.cxx
$(TARGET).o: $(TARGET).cxx CustomFunctions.h
	$(CC) $(CFLAGS) -c $(TARGET).cxx

# Compile CustomFunctions.cxx
CustomFunctions.o: CustomFunctions.cxx CustomFunctions.h
	$(CC) $(CFLAGS) -c CustomFunctions.cxx

# Run the program with the FILE argument
run: $(TARGET)
	./$(TARGET) $(FILE)

# Remove object files
clean:
	rm -f *.o

cleantarget:
	rm -f *.o $(TARGET)
