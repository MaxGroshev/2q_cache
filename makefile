TARGET  = lru
CC      = g++
CFLAGS  = -Wshadow -std=c++17 -Winit-self -Wredundant-decls -Wcast-align          \
		  -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations\
		  -Wmissing-include-dirs -Wswitch-enum -Wmain -Wextra -Wall -g -pipe      \
		  -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy               \
		  -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers          \
		  -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor			  \
		  -Woverloaded-virtual -Wpointer-arith -Wsign-promo					      \
		  -Wstack-usage=8192  -Wstrict-aliasing -Wstrict-null-sentinel  		  \
		  -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE            \

OPTIMIZATION_FLAF = -o2-DNGEBUG


OBJ_DIR   = ./cache/obj/
CACHE_DIR = ./cache/
DEBUG_DIR = ./debug_utils/
TESTS_DIR = ./tests/

###################################################################################################

#SRC
SRC = $(wildcard *.cpp)
OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(SRC))
#Debug
DEBUG_SRC = $(wildcard $(DEBUG_DIR)*.cpp)
DEBUG_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(DEBUG_SRC))
#Tests
TESTS_SRC = $(wildcard $(TESTS_DIR)*.cpp)
TESTS_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(TESTS_SRC))
#Cache
CACHE_SRC = $(wildcard $(CACHE_DIR)*.cpp)
CACHE_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(CACHE_SRC))

###################################################################################################

all: $(TARGET)
$(TARGET):  $(OBJ) $(DEBUG_OBJ) $(CACHE_OBJ) $(TESTS_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(DEBUG_OBJ) $(CACHE_OBJ) $(TESTS_OBJ)

optimized: $(OBJ) $(DEBUG_OBJ) $(CACHE_OBJ) $(TESTS_OBJ)
	$(CC) $(OPTIMIZATION_FLAF) $(CFLAGS) -o $(TARGET) $(OBJ) $(DEBUG_OBJ) $(CACHE_OBJ) $(TESTS_OBJ)

$(OBJ_DIR)%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

################################PHONIES############################################################

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)*.o  $(TARGET) *.aux *.log vgcore.*
