/*
 * This file is part of mutest, a simple micro unit testing framework for C.
 *
 * mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
 * under the BOLA license, please see the LICENSE file or visit:
 * http://blitiri.com.ar/p/bola/
 *
 * This is the sum module test suite. It shows how to have multiple test
 * suites, test suite initialization and termination, and a test suite that
 * succeed. Each (public) function starting with mu_init will be picked up by
 * mkmutest as an initialization function and executed unless one fails
 * (returns != 0) Functions starting with mu_term will be used as termination
 * functions, called after all test cases were executed. Functions starting
 * with mu_test will be used as test cases.
 *
 * Please, read the README file for more details.
 */

#include "sum.h"
#include <stdlib.h> /* malloc(), free() */

#include "../mutest.h"

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

