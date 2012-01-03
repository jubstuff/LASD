C_COMPILER=gcc
OPTIONS=-Wall

MEM_BASE=test_mem
LIST_BASE=test_list
VERTEX_BASE=test_vertex
EDGE_BASE=test_edge

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.exe
else
	TARGET_EXTENSION=.out
endif

MEM_TARGET = $(MEM_BASE)$(TARGET_EXTENSION)
LIST_TARGET = $(LIST_BASE)$(TARGET_EXTENSION)
VERTEX_TARGET = $(VERTEX_BASE)$(TARGET_EXTENSION)
EDGE_TARGET = $(EDGE_BASE)$(TARGET_EXTENSION)

MEM_SRC_FILES=../unity/src/unity.c ../src/mem.c TestMem.c TestMem_Runner.c
LIST_SRC_FILES=../unity/src/unity.c ../src/mem.c ../src/lista.c TestList.c TestList_Runner.c
VERTEX_SRC_FILES=../unity/src/unity.c ../src/mem.c ../src/lista.c ../jgraph/jvset_array.c TestVertex.c TestVertex_Runner.c
EDGE_SRC_FILES=../unity/src/unity.c ../src/mem.c ../src/lista.c ../jgraph/jedge.c ../jgraph/jvertex.c TestEdge.c TestEdge_Runner.c

INC_DIRS=-I../src -I../unity/src -I../jgraph
SYMBOLS=-DTEST -DDEBUG

ifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q build\* &&  del /F /Q $(TARGET3) 
else
	CLEANUP = rm -f build/*.o ; rm -f $(TARGET3) 
endif

all: clean default

default: mem

mem:
	ruby ../unity/auto/generate_test_runner.rb TestMem.c TestMem_Runner.c
	$(C_COMPILER) $(OPTIONS) $(INC_DIRS) $(SYMBOLS) $(MEM_SRC_FILES) -o $(MEM_TARGET)
	./$(MEM_TARGET)
list:
	ruby ../unity/auto/generate_test_runner.rb TestList.c TestList_Runner.c
	$(C_COMPILER) $(OPTIONS) $(INC_DIRS) $(SYMBOLS) $(LIST_SRC_FILES) -o $(LIST_TARGET)
	./$(LIST_TARGET)
vertex:
	ruby ../unity/auto/generate_test_runner.rb TestVertex.c TestVertex_Runner.c
	$(C_COMPILER) $(OPTIONS) $(INC_DIRS) $(SYMBOLS) $(VERTEX_SRC_FILES) -o $(VERTEX_TARGET)
	./$(VERTEX_TARGET)
edge:
	ruby ../unity/auto/generate_test_runner.rb TestEdge.c TestEdge_Runner.c
	$(C_COMPILER) $(OPTIONS) $(INC_DIRS) $(SYMBOLS) $(EDGE_SRC_FILES) -o $(EDGE_TARGET)
	./$(EDGE_TARGET)

clean:
	$(CLEANUP)
	
