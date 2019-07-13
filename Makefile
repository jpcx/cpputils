#                                 ccutl_tests                                  #

CT_BUILDDIR	:=	build/ccutl_tests

CT_CC		:=	clang++
CT_CFLAGS	:=	-std=c++17			\
			-O3				\
			-Wall				\
			-pedantic			\
			-Wextra				\
			-Weverything			\
			-Wno-c++98-compat		\
			-Wno-c++98-compat-pedantic	\
			-Wno-extra-semi-stmt

CT_SRCDIR	:=	test
CT_SRCEXT	:=	cc
CT_INC		:=	-Iinclude	\
			-Itestnew

CT_SOURCES	:=	$(shell				\
				find $(CT_SRCDIR)	\
				-type f			\
				-name *.$(CT_SRCEXT)	\
			)

CT_OBJECTS	:=	$(patsubst				\
				$(CT_SRCDIR)/%,			\
				$(CT_BUILDDIR)/%,		\
				$(CT_SOURCES:.$(CT_SRCEXT)=.o)	\
			)

$(CT_BUILDDIR)/%.o: $(CT_SRCDIR)/%.$(CT_SRCEXT)
	@mkdir -p $(CT_BUILDDIR)
	$(CT_CC) $(CT_CFLAGS) $(CT_INC) -c -o $@ $<

#                                    gtest                                     #

GT_BUILDDIR	:=	build/gtest

GT_CC		:=	clang++
GT_CFLAGS	:=	-std=c++17			\
			-O3				\
			-pthread			\
			-Wall				\
			-Wextra

GT_SRCDIR	:=	external/googletest/googletest/src
GT_SRCEXT	:=	cc
GT_INC		:=	-Iexternal/googletest/googletest/include	\
			-Iexternal/googletest/googletest

GT_SOURCES	:=	$(shell				\
				find $(GT_SRCDIR)	\
				-type f			\
				-name *.$(GT_SRCEXT)	\
				! -name gtest-all.cc	\
			)

GT_OBJECTS	:=	$(patsubst				\
				$(GT_SRCDIR)/%,			\
				$(GT_BUILDDIR)/%,		\
				$(GT_SOURCES:.$(GT_SRCEXT)=.o)	\
			)

$(GT_BUILDDIR)/%.o: $(GT_SRCDIR)/%.$(GT_SRCEXT)
	@mkdir -p $(GT_BUILDDIR)
	$(GT_CC) $(GT_CFLAGS) $(GT_INC) -c -o $@ $<

#                                    target                                    #

TARGET		:=	bin/test

TARGET_CC	:=	clang++
TARGET_CFLAGS	:=	-std=c++17			\
			-O3				\
			-pthread			\
			-Wall				\
			-Wextra

TARGET_OBJECTS	:=	$(CT_OBJECTS)	\
			$(GT_OBJECTS)
TARGET_INC	:=	$(CT_INC)	\
			$(GT_INC)

$(TARGET): $(TARGET_OBJECTS)
	$(TARGET_CC) $(TARGET_CFLAGS) $(TARGET_INC) $^ -o $@


all: $(TARGET)

clean:
	@echo "Cleaning ccutl_test build files..."
	$(RM) -r $(CT_BUILDDIR) $(TARGET)

clean_all:
	@echo "Cleaning all build files..."
	$(RM) -r $(CT_BUILDDIR) $(GT_BUILDDIR) $(TARGET)

test:	clean
	make $(TARGET)
	./$(TARGET)

.PHONY: clean
.PHONY: clean_all
.PHONY: test