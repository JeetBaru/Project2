#architecture specific condtional loop
ifeq ($(ARCH), BBB)
#CC flags for BBB
		CC = arm-linux-gnueabihf-gcc          
#CFLAGS flags for BBB
		CFLAGS= -Wall -Werror -std=c99 
else
#flags for host
		CC = gcc
		CFLAGS = -g -Werror -std=c99 
endif
#conditional loop to select FRDM architecture
ifeq ($(ARCH), FRDM)
	CC = arm-none-eabi-gcc
	CFLAGS = -Werror -g -std=c99 -specs=nosys.specs
endif
#conditional loop to select particular test results
ifeq ($(TEST), data)
#source file for test_data.c
	LIB_SRCS = data.c
	EXE = data.out
	TEST_QUADRATIC_SRCS =test_data.c 
	TEST_QUADRATIC_EXE = test_data.out
	

else 
#source files when nothing is specified 
	LIB_SRCS = data.c memory.c cirbuff.c
	EXE = Test.out
	TEST_QUADRATIC_EXE = Test.out
	TEST_QUADRATIC_SRCS = Test.c
endif
#memory unittests
ifeq ($(TEST), memory)
	LIB_SRCS = memory.c
	EXE = memory.out
	TEST_QUADRATIC_SRCS = test_memory.c
endif
#cirbuff unittests
ifeq ($(TEST), cirbuff)
	LIB_SRCS = cirbuff.c
	EXE = cirbuff.out
	TEST_QUADRATIC_SRCS = test_cirbuff.c
	TEST_QUADRATIC_EXE = test_cirbuff.out
endif 


	
#CC = cc
#CFLAGS = -std=c99 -Wall -Werror -g -O0

#
# build third-party libraries
#
#SUBDIRS is changed to libraries from THIRD_PARTY...
SUBDIRS = libraries

ifdef SUBDIRS
.PHONY : $(SUBDIRS)
$(SUBDIRS) : 
	@if [ -d $@ ]; then \
		$(MAKE) --no-print-directory --directory=$@ \
			CC=$(CC) CFLAGS="$(CFLAGS)" $(MAKECMDGOALS); \
	fi	
endif


THIRD_PARTY_DIR =libraries
CMOCKA_INCLUDE_DIR = $(THIRD_PARTY_DIR)/build-Debug/include
CMOCKA_LIBRARY = $(THIRD_PARTY_DIR)/build-Debug/lib/libcmocka.a

cmocka : $(SUBDIRS)

CFLAGS += -I $(CMOCKA_INCLUDE_DIR)

#
# quick and dirty build rules to demonstrate testing, not good build
# system practices.
#

#
# library
#
#LIB_SRCS = \
#	cirbuff.c 

LIB_OBJS = $(LIB_SRCS:%.c=%.o)

LIB_HEADERS = $(LIB_SRCS:%.c=%.h)

LIB = libutils.a

#
# main executable
#
#EXE_SRCS = main.c
#EXE_OBJS = $(EXE_SRCS:%.c=%.o)

#EXE = circbuf.out

#
# tests
#
#TEST_QUADRATIC_SRCS = \
#	test_cirbuff.c

TEST_QUADRATIC_OBJS = $(TEST_QUADRATIC_SRCS:%.c=%.o)

#TEST_QUADRATIC_EXE = test_cirbuf.out


#
# Generic rule to generate objects
#
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIB) : $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

all : $(LIB) $(EXE)

$(EXE) : $(EXE_OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test : $(TEST_QUADRATIC_EXE)
	./$(TEST_QUADRATIC_EXE)

$(TEST_QUADRATIC_EXE) : $(TEST_QUADRATIC_SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(CMOCKA_LIBRARY) 

test-bbb : main.c logger.c analysedata.c cirbuff.c
	arm-linux-gnueabihf-gcc -DVERBOSE -w $^ -o log.out

test-host : main.c logger.c analysedata.c cirbuff.c
	gcc -DVERBOSE -w $^ -o log.out
	
.PHONY : clean
clean : FORCE
	-rm -rf *~ *.o *.out $(LIB) $(EXE) $(TEST_QUADRATIC_EXE) *.dSYM/

.PHONY : clobber
clobber : $(SUBDIRS) clean


FORCE :
