/*
 * This file is part of mutest, a simple micro unit testing framework for C.
 *
 * mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
 * under the BOLA license, please see the LICENSE file or visit:
 * http://blitiri.com.ar/p/bola/
 *
 * This is a C++ module test suite. It shows how to use checks involving
 * exceptions.
 *
 * Please, read the README file for more details.
 */

#include <stdexcept> // std::out_of_range
#include <vector> // std::vector

#include "../mutest.h"

extern "C" {

void mu_test_exceptions() {
	std::vector<int> v(1);
	// ok
	mu_check(v.at(0) == 0);
	// throws! This fails
	mu_check(v.at(1) == 0);
	// ok, we expect the exception to be thrown, and it does
	mu_echeck(std::out_of_range, v.at(1));
	// fails! We expect this to throw, but it doesn't
	mu_echeck(std::out_of_range, v.at(0));
	// fails again, but this time the show is over (note the "ensure")
	mu_eensure(std::out_of_range, v.at(0));
	// this will never be executed (it should fail if it is)
	mu_check(v.empty());
}

} // extern "C"

