
# Show the tests summary
V=-v

TARGET=tester

OBJS = factorial.o sum.o
TESTS = factorial_test.o sum_test.o
TESTER = tester.o
ALL = $(TESTER) $(OBJS) $(TESTS)

all: $(TARGET)

$(TARGET): $(ALL)

$(TESTER): $(OBJS) $(TESTS)
	../mkmutest $(TESTS) | gcc -xc -o $(TESTER) -c -

test: $(TARGET)
	./$(TARGET) $(V)

clean:
	$(RM) $(TARGET) $(ALL)

.PHONY: all test clean

