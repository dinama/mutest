/*
 * This file is part of mutest, a simple micro unit testing framework for C.
 *
 * mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
 * under the BOLA license, please see the LICENSE file or visit:
 * http://blitiri.com.ar/p/bola/
 *
 * This is a Python implementation of the mutest main idea. This header file
 * should be included in the source files that will make up a test suite, as
 * a dynamic shared object (.so file).
 *
 * Please, read the README file for more details.
 */

#include <stdio.h> /* printf(), fprintf() */

#ifdef __cplusplus
extern "C" {
#endif

/* this increments when the "API" changes */
int mutest_api_version = 1;

int mutest_passed_count;
int mutest_failed_count;
void mutest_reset_counters() {
	mutest_passed_count = 0;
	mutest_failed_count = 0;
}

/*
 * Verbose level:
 * 0: quiet
 * 1: errors
 * 2: summary
 * 3: suites
 * 4: cases
 * 5: checks
 */
int mutest_verbose_level = 1;
void mutest_set_verbose_level(int val) {
	mutest_verbose_level = val;
}

#define mu_check(exp) \
	do { \
		if (exp) { \
			++mutest_passed_count; \
			if (mutest_verbose_level >= 5) \
				printf("%s:%d: mu_check(%s) passed\n", \
					__FILE__, __LINE__, #exp); \
		} else { \
			++mutest_failed_count; \
			if (mutest_verbose_level) \
				fprintf(stderr, "%s:%d: mu_check(%s) " \
					"failed, resuming test case\n", \
					__FILE__, __LINE__, #exp); \
		} \
	} while (0)

#define mu_ensure(exp) \
	do { \
		if (exp) { \
			++mutest_passed_count; \
			if (mutest_verbose_level >=5) \
				printf("%s:%d: mu_ensure(%s) passed\n", \
					__FILE__, __LINE__, #exp); \
		} else { \
			++mutest_failed_count; \
			if (mutest_verbose_level) \
				fprintf(stderr, "%s:%d: mu_ensure(%s) " \
					"failed, aborting test case\n", \
					__FILE__, __LINE__, #exp); \
			return; \
		} \
	} while (0)

#ifdef __cplusplus
}
#endif

