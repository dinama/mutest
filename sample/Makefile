#
# This file is part of mutest, a simple micro unit testing framework for C.
#
# mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
# under the BOLA license, please see the LICENSE file or visit:
# http://blitiri.com.ar/p/bola/
#
# This is the samples Makefile.
#
# Please, read the README file for more details.
#

# Show the tests summary
V = -v

# Set to 0 if you don't want to compile the C++ test suite
CPP_SUITE = 1

CFLAGS = -Wall -std=c89
CXXFLAGS = -Wall -std=c++98
LD = $(CC)

TARGET = tester
RUNNER_SRC = test_suite_runner.c
MKMUTEST = ../mkmutest
MUTEST = ../mutest
MUTEST_H = ../mutest.h
MUTEST_C = ../mutest.c

OBJS = factorial.o sum.o
TEST_OBJS = factorial_test.o sum_test.o init_fail_test.o
MUTEST_OBJ = mutest.o
RUNNER_OBJ = $(RUNNER_SRC:.c=.o)
ALL_OBJS = $(RUNNER_OBJ) $(OBJS) $(TEST_OBJS) $(MUTEST_OBJ)
TEST_SOS = $(TEST_OBJS:.o=.so)

ifeq ($(CPP_SUITE), 1)
TEST_OBJS += exception_test.o
LD = $(CXX)
endif

all: $(TARGET)

py: $(TEST_SOS)

$(TARGET): $(ALL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(RUNNER_SRC): $(MKMUTEST_OBJ) $(MUTEST_H) $(TEST_OBJS)
	$(MKMUTEST) $(MUTEST_H) $(TEST_OBJS) > $@

factorial_test.so: factorial.c

sum_test.so: sum.c

$(MUTEST_OBJ): $(MUTEST_C)
	$(CC) $(CFLAGS) -c -o $@ $^

test: $(TARGET)
	./$(TARGET) $(V)

test-py: $(TEST_SOS)
	$(MUTEST) $(V) -a

clean:
	$(RM) $(TARGET) $(TEST_SOS) $(ALL_OBJS) $(RUNNER_SRC)

.c.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -DMUTEST_PY -fPIC -shared -o $@ $^

.cpp.so:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -DMUTEST_PY -fPIC -shared -o $@ $^

.SUFFIXES: .so

.PHONY: all test clean

