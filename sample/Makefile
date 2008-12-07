
# Show the tests summary
V=-v

TARGET=tester

OBJS = factorial.o sum.o
TESTS = factorial_test.o sum_test.o
TESTER = tester.o
SO = factorial.so sum.so
ALL = $(TESTER) $(OBJS) $(TESTS)

all: $(TARGET)

py: $(SO)

$(TARGET): $(ALL)

$(TESTER): $(OBJS) $(TESTS)
	../mkmutest $(TESTS) | gcc -xc -o $(TESTER) -c -

factorial.so: factorial_test.c

sum.so: sum_test.c

test: $(TARGET)
	./$(TARGET) $(V)

test-py: $(SO)
	../py/mutest $(V) -a

clean:
	$(RM) $(TARGET) $(SO) $(ALL)

.c.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -DMUTEST_PY -fPIC -shared -o $@ $^

.SUFFIXES: .so

.PHONY: all test clean

