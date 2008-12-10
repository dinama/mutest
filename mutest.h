
#include <stdio.h> /* fprintf() */

#ifdef __cplusplus
extern "C" {
#endif

/* check that an expression evaluates to true, continue if the check fails */
#define mu_check(exp) \
	do { \
		mu_print(MU_CHECK, "\t\t* Checking mu_check(%s)...\n", #exp); \
		if (exp) ++mutest_passed_checks; \
		else { \
			++mutest_failed_checks; \
			mutest_case_failed = 1; \
			mu_print(MU_ERROR, "%s:%d: mu_check(%s) failed, " \
					"resuming test case\n", __FILE__, \
					__LINE__, #exp); \
		} \
	} while (0)

/*
 * ensure that an expression evaluates to true, abort the current test
 * case if the check fails
 */
#define mu_ensure(exp) \
	do { \
		mu_print(MU_CHECK, "\t\t* Checking mu_ensure(%s)...\n", #exp);\
		if (exp) ++mutest_passed_checks; \
		else { \
			++mutest_failed_checks; \
			mutest_case_failed = 1; \
			mu_print(MU_ERROR, "%s:%d: mu_ensure(%s) failed, " \
					"aborting test case\n", __FILE__, \
					__LINE__, #exp); \
			return; \
		} \
	} while (0)

/*
 * you don't need to pay any attention to what's next, unless you want to do
 * some customization, of course, in which case, you're encouraged to take
 * a look an play =)
 */

/* verbosity level (each level shows all the previous levels too) */
enum {
	MU_QUIET = 0, /* be completely quiet */
	MU_ERROR,     /* shows errors only */
	MU_SUMMARY,   /* shows a summary */
	MU_SUITE,     /* shows test suites progress */
	MU_CASE,      /* shows test cases progress */
	MU_CHECK      /* shows the current running check */
};

/* print a message according to the verbosity level */
#define mu_print(level, ...) \
	do { \
		if (mutest_verbose_level >= level) { \
			if (mutest_verbose_level == MU_ERROR) \
				fprintf(stderr, __VA_ARGS__); \
			else \
				fprintf(stdout, __VA_ARGS__); \
		} \
	} while (0)

/*
 * this function implements the test suites execution, you should generate
 * a module with this function using mkmutest, or take a look to that script
 * if you want to implement your own customized version */
void mu_run_suites();

/* macro for running a single test case */
#ifndef mu_run_case
#define mu_run_case(name) \
	do { \
		mu_print(MU_CASE, "\t- executing test case \"" #name "\"\n"); \
		void name(); \
		mutest_case_name = #name; \
		name(); \
		if (mutest_case_failed) { \
			++mutest_failed_cases; \
			mutest_suite_failed = 1; \
		} else ++mutest_passed_cases; \
		mutest_case_failed = 0; \
	} while (0)
#endif /* mu_run_case */

/*
 * mutest exported variables for internal use, do not use directly unless you
 *  know what you're doing.
 */
extern const char* mutest_suite_name;
extern int mutest_failed_suites;
extern int mutest_passed_suites;
extern int mutest_suite_failed;
/* test cases */
extern const char* mutest_case_name;
extern int mutest_failed_cases;
extern int mutest_passed_cases;
extern int mutest_case_failed;
/* checks */
extern int mutest_failed_checks;
extern int mutest_passed_checks;
/* verbosity */
extern int mutest_verbose_level;

#ifdef __cplusplus
}
#endif

