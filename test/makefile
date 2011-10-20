C_COMPILER=gcc
OPTIONS=-Wall

MEM_BASE=test_mem

ifeq ($(OS),Windows_NT)
	TARGET_EXTENSION=.exe
else
	TARGET_EXTENSION=.out
endif

MEM_TARGET = $(MEM_BASE)$(TARGET_EXTENSION)

MEM_SRC_FILES=../unity/src/unity.c ../src/mem.c TestMem.c TestMem_Runner.c

INC_DIRS=-I../src -I../unity/src
SYMBOLS=-DTEST

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

clean:
	$(CLEANUP)
	
