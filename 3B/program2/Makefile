# Compiler and flags
CXX = g++
CXXFLAGS = -Wall
DEBUG_FLAGS = -g
OPTIMIZE_FLAGS = -O3

# SQLite paths and libraries
SQLITE_INCLUDE = -I"C:/sqlite3"
SQLITE_LIB = -L"C:/sqlite3" -lsqlite3

# Target to compile program2.o from program2.cpp
program2.o: program2.cpp
	$(CXX) -c program2.cpp $(CXXFLAGS) $(SQLITE_INCLUDE)

# Target to create program2.exe in release mode
program2_release: program2.o
	$(CXX) $(OPTIMIZE_FLAGS) -o program2.exe program2.o $(SQLITE_LIB)

# Target to create program2.exe in debug mode
program2_debug: program2.o
	$(CXX) $(DEBUG_FLAGS) -o program2.exe program2.o $(SQLITE_LIB)

# Default target (will compile program2 in release mode)
all: program2_release

# Clean target
clean:
	del *.o program2.exe
