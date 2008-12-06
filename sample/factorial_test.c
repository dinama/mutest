
#include "../mutest.h"
#include "factorial.h"

void mu_test_factorial_zero() {
	unsigned x = factorial(0);
	mu_check(x == 1);
}

void mu_test_factorial_one() {
	unsigned x = factorial(1);
	/* this test is wrong on purpose, to see how it fails */
	mu_check(x == 2);
}

void mu_test_factorial_positive() {
	unsigned x = factorial(2);
	/* this test is wrong on purpose, to see how it fails */
	mu_check(x == 3);

	x = factorial(3);
	/* we don't want to continue if this fails, because the next result
	 * depends on this one. This one will succeed. */
	mu_ensure(x == 6);

	x = factorial(x);
	mu_check(x == 720);

	x = factorial(4);
	mu_ensure(x == 6); /* same as before, but this one will fail. */

	x = factorial(x-15); /* and this will never be executed */
	mu_check(x == 362881); /* but if excecuted, will fail */
}

