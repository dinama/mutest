
/* see factorial_test.c for more complete examples, this file is mostly to show
 * how to have multiple test suites, test suite initialization and
 * termination, and a test suite that succeed. */

#include "sum.h"
#include <stdlib.h> /* malloc(), free() */

#ifdef MUTEST_PY
#include "../py/mutest.h"
#else
#include "../mutest.h"
#endif

/* unused, just for ilustrate the test suite initialization/termination */
static char* global;

int mu_init_sum() {
	global = (char*) malloc(1024);

	return 0; /* initialization OK */
}

void mu_test_sum() {
	mu_check(sum(4, 5) == 9);
	mu_check(sum(-4, -5) == -9);
	mu_check(sum(0, 0) == 0);
	mu_check(sum(1, -1) == 0);
}

void mu_term_sum() {
	free(global);
}

