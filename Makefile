CC      	:= 	g++
C_FLAGS   	:= 	-std=c++17	\
			 		-g		\
			-Wall     	\
			-Wextra

LIB_INC		:=	-Isrc
TEST_BIN	:=	test/bin/test
TEST_SRC	:=	test/src/*.cc			\
			test/src/ccutl_tests/types/*.cc	\
			test/src/ccutl_tests/maps/*.cc	
TEST_INC	:=	-Itest/src

all:

clean:
	$(RM) $(TEST_BIN)

test: clean
	make $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC)
	$(CC) $(C_FLAGS) $(LIB_INC) $(TEST_INC) $^ -o $@