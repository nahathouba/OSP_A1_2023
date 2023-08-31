
##
 # startup code provided by Paul Miller for COSC1114 - Operating Systems
 # Principles
 ##

# provide make targets here to build the two programs 


# Makefile for copier program

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall

# Paths for copier
SRC_DIR_COPIER = ./copier_files
BUILD_DIR_COPIER = ./copier_files

#Paths for mtcopier
SRC_DIR_MTCOPIER = ./mtcopier_files
BUILD_DIR_MTCOPIER = ./mtcopier_files

# Build the program copier
copier:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR_COPIER)/copier $(SRC_DIR_COPIER)/main.cpp $(SRC_DIR_COPIER)/reader.cpp $(SRC_DIR_COPIER)/writer.cpp

# Build the program mtcopier
mtcopier:
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR_MTCOPIER)/mtcopier $(SRC_DIR_MTCOPIER)/main.cpp $(SRC_DIR_MTCOPIER)/reader.cpp $(SRC_DIR_MTCOPIER)/writer.cpp -lpthread

# Clean the build copier
clean_copier:
	rm -f  $(BUILD_DIR_COPIER)/copier

# Clean the build mtcopier
clean_mtcopier:
	rm -f $(BUILD_DIR_MTCOPIER)/mtcopier