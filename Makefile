CC = clang
TARGET = maze maze_harness maze_gcov_harness maze.bc maze_assert.bc
LDFLAGS_KLEERUNTEST=-lkleeRuntest -L$(HOME)/klee_build/lib/ -I$(HOME)/klee_build/include/

all: $(TARGET)

maze: maze.c
	$(CC) $^ -o $@

maze_harness: maze.c
	$(CC) $^ -DKLEE_ANALYSIS $(LDFLAGS_KLEERUNTEST) -o $@

maze_gcov_harness: maze.c
	$(CC) $^ -DKLEE_ANALYSIS $(LDFLAGS_KLEERUNTEST) -coverage -o $@

maze.bc: maze.c
	$(CC) $^ -DKLEE_ANALYSIS -c -emit-llvm -o $@

maze_assert.bc: maze.c
	$(CC) $^ -DKLEE_ANALYSIS -DKLEE_ASSERT -c -emit-llvm -o $@

klee-last: maze.bc
	klee $^

clean:
	rm -r -f klee-last  klee-out-*
	rm -f *.gcda *.gcno *.gcov
	rm -f $(TARGET)

