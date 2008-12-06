
#include <stdio.h> // fprintf

#ifdef __cplusplus
extern "C" {
#endif

extern int mutest_failed_checks;
extern int mutest_passed_checks;
extern int mutest_case_failed;

#define mu_check(exp) \
	do { \
		if (exp) ++mutest_passed_checks; \
		else { \
			++mutest_failed_checks; \
			mutest_case_failed = 1; \
			fprintf(stderr, "%s:%d: mu_check(%s) failed, " \
					"resuming test case\n", __FILE__, \
					__LINE__, #exp); \
		} \
	} while (0)

#define mu_ensure(exp) \
	do { \
		if (exp) ++mutest_passed_checks; \
		else { \
			++mutest_failed_checks; \
			mutest_case_failed = 1; \
			fprintf(stderr, "%s:%d: mu_ensure(%s) failed, " \
					"aborting test case\n", __FILE__, \
					__LINE__, #exp); \
			return; \
		} \
	} while (0)

#ifdef __cplusplus
}
#endif

