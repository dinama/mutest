/*
 * This file is part of mutest, a simple micro unit testing framework for C.
 *
 * mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
 * under the BOLA license, please see the LICENSE file or visit:
 * http://blitiri.com.ar/p/bola/
 *
 * This is an example module that calculates a factorial.
 *
 * Please, read the README file for more details.
 */

unsigned factorial(unsigned x) {
	if (x <= 1)
		return 1;
	return x * factorial(x-1);
}

