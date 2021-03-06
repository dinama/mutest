
======================================================
|mutest| - A simple micro unit testing framework for C
======================================================

forked from:

:Author: Leandro Lucarella
:Contact: llucax@gmail.com
:Version: 1.0
:Copyright: Leandro Lucarella (2008), released under the BOLA_ license
:Abstract: |mutest| is a micro `unit testing`_ framework for C (with some
    `C++ support`_). It's mostly an idea (it even comes with
    2 implementations_ of the idea!) with the goal of being easy to use
    (just write your `test cases`_ grouped in `test suites`_ and you're
    set) and so small and simple that you don't mind to copy the files to
    your project and just use it (i.e., no dependencies).

    The idea is simple: a source file is a `test suite`_, a function is
    a `test case`_ (special functions can be used for `test suite`_
    initialization_ and termination_), which can can have several checks_.
    Checks_ comes in 2 flavors, one that only prints an error, and one that
    terminates the current `test case`_ too. A (normally) automated `test
    program`_ run all the `test suites`_ and print some stats. It fails
    (returns non-zero) if any `test suite`_ fails.


.. contents::
    :backlinks: entry


Installation
============

To actually install |mutest| run::

    $ make install

Default installation path is ``/usr/local`` (because of that, you'll probably
need superuser privileges to install to the default location). You can override
that by passing the ``prefix`` make variable, for example::

    $ make prefix=/opt/mutest install

If you want to install just the docs, you can do::

    $ make install-doc

Or even ``install-readme``, ``install-html`` or ``install-pdf`` if you are too
picky.

If you want to install just one particular implementation_, to can use the
``install-c`` and ``install-py`` targets.


Quick Sample
============

You can find some samples in the sample__ directory.

https://github.com/dinama/mutest/tree/master/sample

This is an example taken from there. A simple *module* called `factorial.c`_
with its corresponding `test suite`_ (`factorial_test.c`_).

You can see some `C++ support`_ in the `exception_test.cpp`_ `test suite`_.

factorial.c
-----------

.. include:: sample/factorial.c
    :code: c

factorial_test.c
----------------

.. include:: sample/factorial_test.c
    :code: c

exception_test.cpp
------------------

.. include:: sample/exception_test.cpp
    :code: c++


Concepts
========

|mutest| is about 4 simple concepts: `test program`_, `test suite`_, `test
case`_ and checks_. Well, to be honest you probably will need `test suite`_
initialization_ and termination_ too =)


Test Program
------------

A **test program** is the higher level unit of |mutest|. The test program is
the one in charge of running all your tests. Probably one of the more important
features of |mutest| is that you are not supposed to bother about the test
program. So, different implementations_ have different ways to tackle this.
Some need more or less interactions from your part, and each have their pros
and cons.

But this is all you need to know for now, for more details see how the test
program is implemented by your implementation_ of choice.


Test Suite
----------

A **test suite** is the higher level unit of |mutest| that you should
care about =). Is not much more than a way to group `test cases`_. Code-wise,
a test suite is a C (or C++) module (or compilation unit). Not clear enough?
A unit test is an object file (could be a shared object depending on the
implementation_). This module should have one or more `test cases`_ and it
could have any number (including zero) of initialization_ and termination_
functions.

A test suite, is inspected by the `test program`_ for `test cases`_ and
initialization_ and termination_ functions, and run them.

A test suite fail if one or more `test cases`_ fail, and it's skipped if one or
more initialization_ functions fail (or, depending on the implementation, if
the test suite can't be loaded at all).


Test Case
---------

A **test case** is just a plain function with a special signature and name.
A test case function name must start with ``mu_test``, and take no arguments
and return nothing. For example::

    void mu_test_something(void);

A test case (probably) only make sense if it has checks_. A test case succeed
only if all its checks succeed too.

Test are executed in an implementation_-dependant order, but usually the
default order is alphabetical.


Checks
------

Checks are assertions that a `test case`_ must pass (a boolean expression that
must evaluate to *true*). There are 2 big flavors of checks: **check** and
**ensure**. **check** just print an error (and *mark* the `test case`_ as
failed) and **ensure** halt the `test case`_ execution, jumping to the next
one.

For better `C++ support`_ there are check macros that assert that a specified
exception is thrown (instead of check for a boolean expression to evaluate to
*true*).

You can take a look at the reference_ to see the different flavors of check
macros in more detail.


Initialization
--------------

Sometimes you need to setup some environment shared between all the `test
cases`_ in a `test suite`_. You can use **initialization functions** for this.

An initialization function, like a `test case`_, is a plain C function with
a special name and signature. The name must start with ``mu_init`` and it must
take no arguments, and return an *error code* (``0`` being success). For
example::

    int mu_init_something(void);

All initialization functions are executed before any `test case`_, in an
implementation_-dependant order, and if one of them fail (returns non-zero),
the whole `test suite`_ is skipped immediately.


Termination
-----------

**Termination functions** are just like initialization_ functions, but they're
executed **after** the `test cases`_, their names start with ``mu_term`` and
they return nothing. For example::

    void mu_term_something(void);


C++ Support
===========

You can use |mutest| with C++, the only care you must take is that, because of
C++ `name mangling`_ (and |mutest| relaying on function names), you must
declare your `test cases`_ and initialization_ and termination_ functions as
``extern "C"`` (see `exception_test.cpp`_ for an example).

Checks_ become *exception-safe* when using |mutest| with a C++ compiler, and
2 extra checks_ designed for C++ get defined (`mu_echeck()`_ and
`mu_eensure()`_). They assert that an expression throws a particular exception.


Implementations
===============

There are 2 big groups of possible implementations that I can think
of: *static* and *dynamic*.

|mutest| comes with one implementation of each group.


Static Implementations
----------------------

Static implementations can be only written in C/C++ (or other language that is
link-compatible with C, like the `D Programming Language`_, but since one of
the main goals of |mutest| is avoid unnecessary dependencies, you probably
don't want to depend on an extra language/compiler to run your tests =).

The main advantage is better debugging support, because you can run the `test
program`_ in a standard debugger and see what happens with `test cases`_ very
naturally.

The main disadvantage is, the `test suites`_ must be figured out in
*compile-time*, usually using some kind of code generation (if you want to
avoid writing repetitive code yourself). There's also a limitation in the `test
case`_, initialization_ and termination_ functions names: they should be unique
for all the `test program`_.


C implementation
~~~~~~~~~~~~~~~~

|mutest| comes with a C static implementation. Only 3 files are needed:
``mutest.c`` (the *user-independent* part of the `test program`_), ``mkmutest``
(a bash script for generating the *user-dependent* part of the `test program`_)
and ``mutest.h`` (the header file that `test suites`_ should include).

You can copy this 3 files to your project or install them at system-level and
use them globally.

The procedure is simple, You should compile you `test suites`_, ``mutest.c``
and the generated output of ``mkmutest`` as object files and link them
together.

For example::

    $ cc -c -o mutest.o mutest.c
    $ cc -c -o test1.o test1.c
    $ cc -c -o test2.o test2.c
    $ mkmutest mutest.h test1.o test2.o | cc -xc -c -o runmutest.o -
    $ cc -o testprg mutest.o test1.o test2.o runmutest.o

Then you can run the `test program`_ invoking it with no arguments::

    $ ./testprg


``mkmutest`` Invocation
"""""""""""""""""""""""

This small script take 1 mandatory positional argument: the path to the
``mutest.h`` file. All remaining positional arguments should be object files
representing `test suites`_.


Test Program Invocation
"""""""""""""""""""""""

The test program can be invoked without arguments, but can take some extra
options:

``-v``
    Be verbose. This is accumulative, when you add extra ``-v`` you will
    get extra verbosity.

    By default, you just get failed checks_ printed. If you use a single
    ``-v``, a summary of failed/passed `test suites`_, `test cases`_ and
    checks_ will be printed. If an extra ``-v`` is used, you'll see the current
    `test suite`_ being executed. Another ``-v`` and you'll get the current
    `test case`_, and another one, and you'll get each check_.


Dependencies
""""""""""""

Even when dependencies are kept minimal, there always be a few ;)

To use this implementation you just need:

* A C compiler (you already needed that, so...)
* The ``nm`` program (from `GNU Binutils`_, included in virtually any \*NIX)
* The `GNU Bash`_ shell interpreter (also included in virtually any \*NIX)


Dynamic Implementations
-----------------------

Dynamic implementations, on the other hand, can be written in any language that
can access to shared objects. The idea is to inspect a shared object for `test
suites`_ and run them, without requiring any information about `test suites`_
at compile time.

There are several advantages in this kind of implementations. The dynamic
nature let you completely separate the `test program`_ from the user-written
`test suites`_ and you can choose at *run-time* what `test suites`_ to execute
by just selecting the correct shared objects. Also, `test case`_,
initialization_ and termination_ functions names only have to be unique in the
scope of the `test suites`_, because `test suites`_ are completely isolated in
separate shared objects.

But everything comes at a price, and the higher price to pay is
*debuggability*. It's a little harder to plug a debugger to a shared object.


Python implementation
~~~~~~~~~~~~~~~~~~~~~

This implementation is much simpler and elegant than the `C implementation`_.
Only 2 files are needed: ``mutest`` (`test program`_ written in Python_ using
ctypes_ module to access the shared object symbols) and ``mutest.h`` (the
header file that `test suites`_ should include).

Since both implementations provided by |mutest| share the same ``mutest.h``,
you should define the ``MUTEST_PY`` macro when compiling the `test suites`_ if
you will run them using this implementation.

As with the `C implementation`_, you can copy this 2 files to your project or
install them at system-level and use them globally.

The procedure is even simpler than the `C implementation`_: compile and link
you `test suites`_ as shared objects and then run the ``mutest`` program
passing the shared objects as arguments. For example::

    $ cc -c -fPIC -DMUTEST_PY -o test1.o test1.c
    $ cc -shared -o test1.so test1.o
    $ cc -c -fPIC -DMUTEST_PY -o test2.o test2.c
    $ cc -shared -o test2.so test2.o
    $ mutest test1.so test2.so

That's it.

``mutest`` Invocation
"""""""""""""""""""""

``mutest`` program takes `test suites`_ shared objects to run as positional
arguments. It accepts the same options as the `C implementation's test
program`__ and some extra options are accepted too:

``--verbose``
    Alias for ``-v``.

``-q``, ``--quiet``
    Be quiet (no output is shown at all).

``-s``, ``--search``
    Search for `test suites`_ (\*.so) in the current directory and add them
    to the list of `test suites`_ to run.

``-h``, ``--help``
    Show a help message and exit.

__ `Test Program Invocation`_


Dependencies
""""""""""""

As with the `C implementation`_, some minor dependencies are needed:

* Python_ (2.5 or later)
* The ``nm`` program (from `GNU Binutils`_, included in virtually any \*NIX)

You will need a C compiler for building the `test suites`_ too, but technically
is not needed by |mutest| itself ;)


Reference
=========

``mu_check()``
--------------

Synopsis
    ``mu_check(expression)``

Description
    Check that the ``expression`` evaluates to *true*. Continue with the
    `test case`_ if fail.

Availability
    Always

Example
    ::

        void mu_test(void)
        {
            mu_check(5 == 4); /* fail */
            mu_check(5 == 5); /* excecuted, pass */
        }


``mu_ensure()``
---------------

Synopsis
    ``mu_ensure(expression)``

Description
    Check that the ``expression`` evaluates to *true*. Interrupt the `test
    case`_ if fail.

Availability
    Always

Example
    ::

        void mu_test(void)
        {
            mu_ensure(5 == 4); /* fail */
            mu_check(5 == 5); /* not excecuted */
        }


``mu_echeck()``
---------------

Synopsis
    ``mu_echeck(class, expression)``

Description
    Check that the ``expression`` throws a specific exception ``class`` (or
    subclass). Continue with the `test case`_ if fail.

Availability
    C++ only

Example
    ::

        #include <stdexcept>

        extern "C"
        {
            void mu_test(void)
            {
                mu_echeck(std::exception, true); /* fail */
                mu_echeck(std::exception,
                        throw std::runtime_error("!")); /* excecuted, pass */
            }
        }

``mu_eensure()``
----------------

Synopsis
    ``mu_eensure(class, expression)``

Description
    Check that the ``expression`` throws a specific exception ``class`` (or
    subclass). Interrupt the `test case`_ if fail.

Availability
    C++ only

Example
    ::

        #include <stdexcept>

        extern "C"
        {
            void mu_test(void)
            {
                mu_eensure(std::exception, true); /* fail */
                mu_echeck(std::exception,
                        throw std::runtime_error("!")); /* not excecuted */
            }
        }


``mu_nothrow_check()``
---------------

Synopsis
    ``mu_nothrow_check(expression)``

Description
    Check that the ``expression`` not throws any exception. Continue with the `test case`_ if fail.

Availability
    C++ only

Example
    ::

        #include <stdexcept>

        extern "C"
        {
            void mu_test(void)
            {
                mu_nothrow_check(throw 1); /* fail */            
                mu_nothrow_check(true); /* excecuted, pass */            
            }
        }

``mu_nothrow_ensure()``
----------------

Synopsis
    ``mu_nothrow_ensure(expression)``

Description
    Check that the ``expression`` not throws any exception. Interrupt the `test case`_ if fail.

Availability
    C++ only

Example
    ::

        #include <stdexcept>

        extern "C"
        {
            void mu_test(void)
            {                
                mu_nothrow_ensure(throw 1); /* fail */
                mu_nothrow_check(throw 1); /* not excecuted */                
            }
        }

About
=====

This manual was written using reStructuredText_.

.. Use section numbers
.. sectnum::
    :suffix: .

.. Internal Links (aliases):
.. _`test suites`: `test suite`_
.. _`test cases`: `test case`_
.. _check: checks_
.. _implementation: implementations_


.. External Links:
.. _BOLA: http://blitiri.com.ar/p/bola/
.. _`unit testing`: http://en.wikipedia.org/wiki/Unit_testing
.. _`name mangling`: http://en.wikipedia.org/wiki/Name_mangling
.. _`D Programming Language`: http://www.digitalmars.com/d/
.. _`GNU Binutils`: http://www.gnu.org/software/binutils/
.. _`GNU Bash`: http://www.gnu.org/software/bash/
.. _Python: http://www.python.org/
.. _ctypes: http://docs.python.org/library/ctypes.html
.. _reStructuredText: http://docutils.sourceforge.net/rst.html
.. _Git: http://git.or.cz/


.. Substitutions:
.. |mutest| replace:: *mutest*
.. |date| date::

.. vim: set filetype=rst expandtab shiftwidth=4 softtabstop=4 :

