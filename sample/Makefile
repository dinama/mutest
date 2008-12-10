
# Show the tests summary
V=-v

CFLAGS = -Wall -std=c89

TARGET = tester
SUITES_RUNNER_SRC = test_suite_runner.c
MKMUTEST = ../mkmutest
MUTEST_H = ../mutest.h
MUTEST_C = ../mutest.c

OBJS = factorial.o sum.o
TESTS = factorial_test.o sum_test.o init_fail_test.o
MUTEST = mutest.o
SUITES_RUNNER = $(SUITES_RUNNER_SRC:.c=.o)
SO = factorial.so sum.so init_fail_test.so
ALL = $(SUITES_RUNNER) $(OBJS) $(TESTS) $(MUTEST)

all: $(TARGET)

py: $(SO)

$(TARGET): $(ALL)
	$(CC) $(LDFLAGS) -o $@ $^

$(SUITES_RUNNER_SRC): $(MKMUTEST) $(MUTEST_H) $(TESTS)
	$(MKMUTEST) $(MUTEST_H) $(TESTS) > $@

factorial.so: factorial_test.c

sum.so: sum_test.c

$(MUTEST): ../mutest.c
	$(CC) $(CFLAGS) -c -o mutest.o $^

test: $(TARGET)
	./$(TARGET) $(V)

test-py: $(SO)
	../py/mutest $(V) -a

clean:
	$(RM) $(TARGET) $(SO) $(ALL) $(SUITES_RUNNER_SRC)

.c.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -DMUTEST_PY -fPIC -shared -o $@ $^

.SUFFIXES: .so

.PHONY: all test clean

