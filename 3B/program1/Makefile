# Set the compiler to Visual Studio's C++ compiler (cl.exe)
CC = cl
CFLAGS = /nologo /std:c++17 /EHsc

# Linker flags (with the proper LIBPATH and quotes)
LDFLAGS = /link /LIBPATH:"C:\Program Files\Boost\boost_1_86_0\stage\lib"

# Boost Libraries to link against (ensure you use the correct file names)
LIBS = libboost_system-vc143-mt-x64-1_86.lib libboost_date_time-vc143-mt-x64-1_86.lib 
# Paths to include Boost headers (ensure this is correct)
BOOST_INC = "C:/Program Files/Boost/boost_1_86_0"

# Source and output files
SRC = program1.cpp
OBJ = program1.obj
EXE = program1.exe

# Targets and rules
all: $(EXE)

# Link object files to create the executable
$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBS) /OUT:$(EXE)

# Compile source file to object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) /I$(BOOST_INC) /c $(SRC)

# Clean up generated files
clean:
	del $(OBJ) $(EXE)
