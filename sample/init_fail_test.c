
/* dummy test to illustrate how a test suite initialization could fail */

#ifdef MUTEST_PY
#include "../py/mutest.h"
#else
#include "../mutest.h"
#endif

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

