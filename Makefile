VERSION := 0.2.0

CC				:= g++
C_FLAGS 	:= -std=c++17 \
					 	 -g		     	\
					 	 -Wall     	\
					 	 -Wextra

TEST_BIN	:= test/bin/test
TEST_SRC	:= test/src/*.cc                  \
						 test/src/ccutl_tests/maps/*.cc
LIB_INC		:= -Isrc
TEST_INC  := -Itest/src

all:

clean:
	$(RM) $(TEST_BIN)

test: $(TEST_SRC)
	make clean
	$(CC) $(C_FLAGS) $(LIB_INC) $(TEST_INC) $^ -o $(TEST_BIN)
	./$(TEST_BIN)