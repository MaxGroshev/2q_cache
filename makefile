TARGET     = lru
T_2Q       = 2q
T_PERF_LRU = perf_lru
T_TESTS    = my_tests
CC         = g++
CFLAGS     = -Wshadow -std=c++17

OPTIMIZATION_FLAGS = -O2 -DNDEBUG

OBJ_DIR   = ./cache/obj/
CACHE_DIR = ./cache/
2Q_DIR    = ./cache/2q_cache/
PERF_LRU_DIR = ./cache/perf_cache/
DEBUG_DIR = ./debug_utils/error_control/
TESTS_DIR = ./tests/

###################################################################################################

#SRC
SRC = $(wildcard *.cpp)
OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(SRC))
#2q_Cache
2Q_SRC = $(wildcard $(2Q_DIR)*.cpp)
2Q_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(2Q_SRC))
#Perf_lru
PERF_LRU_SRC = $(wildcard $(PERF_LRU_DIR)*.cpp)
PERF_LRU_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(PERF_LRU_SRC))
#DEBUG
DEBUG_SRC = $(wildcard $(DEBUG_DIR)*.cpp)
DEBUG_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(DEBUG_SRC))
#Tests
TESTS_SRC = $(wildcard $(TESTS_DIR)*.cpp)
TESTS_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(TESTS_SRC))
#Cache
CACHE_SRC = $(wildcard $(CACHE_DIR)*.cpp)
CACHE_OBJ = $(patsubst $(OBJ_DIR)%.cpp, %.o, $(CACHE_SRC))


###################################################################################################

all: perf_lru 2q tests

perf_lru: $(PERF_LRU_OBJ) $(DEBUG_OBJ) $(CACHE_OBJ)
	$(CC) $(OPTIMIZATION_FLAGS) $(CFLAGS) -o $(T_PERF_LRU) $(PERF_LRU_OBJ) $(DEBUG_OBJ) $(CACHE_OBJ)

2q: $(2Q_OBJ) $(DEBUG_OBJ) $(CACHE_OBJ) $(TESTS_OBJ)
	$(CC) $(OPTIMIZATION_FLAGS) $(CFLAGS) -o $(T_2Q) $(2Q_OBJ) $(DEBUG_OBJ) $(CACHE_OBJ)

tests: $(TESTS_OBJ) $(DEBUG_OBJ) $(CACHE_OBJ) 2q perf_lru
	$(CC) $(OPTIMIZATION_FLAGS) $(CFLAGS) -o $(T_TESTS) $(TESTS_OBJ) $(DEBUG_OBJ) $(CACHE_OBJ)

################################PHONIES############################################################

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)*.o  $(TARGET) $(T_2Q) $(T_PERF_LRU) $(T_TESTS) *.aux *.log vgcore.*
