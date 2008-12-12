/*
 * This file is part of mutest, a simple micro unit testing framework for C.
 *
 * mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
 * under the BOLA license, please see the LICENSE file or visit:
 * http://blitiri.com.ar/p/bola/
 *
 * This is a dummy test suite that illustrates how a test suite initialization
 * can fail. Each (public) function starting with mu_init will be picked up
 * by mkmutest as an initialization function and executed unless one fails
 * (returns != 0). Functions starting with mu_test will be used as test cases,
 * but since an initialization function fails, none will be executed.
 *
 * Please, read the README file for more details.
 */

#include "../mutest.h"

static int ret = 0;

int mu_init_success() {
	return ret++;
}

int mu_init_fail() {
	return ret;
}

/* this test will never be executed because the initialization failed */
void mu_test_dummy() {
}

/* this test will never be executed either */
void mu_term_success() {
}

