
/* see factorial_test.c for more complete examples, this file is mostly to show
 * how to have multiple test suites, and a test suite that succeed. */

#include "../mutest.h"
#include "sum.h"

void mu_test_sum() {
	mu_check(sum(4, 5) == 9);
	mu_check(sum(-4, -5) == -9);
	mu_check(sum(0, 0) == 0);
	mu_check(sum(1, -1) == 0);
}

