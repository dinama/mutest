#
# This file is part of mutest, a simple micro unit testing framework for C.
#
# mutest was written by Leandro Lucarella <llucax@gmail.com> and is released
# under the BOLA license, please see the LICENSE file or visit:
# http://blitiri.com.ar/p/bola/
#
# This is the main Makefile.
#
# Please, read the README file for more details.
#

MANUAL_SRC=README
MANUAL_HTML=manual.html
MANUAL_LATEX=manual.latex
MANUAL_PDF=manual.pdf
SAMPLES = sample/factorial.c sample/factorial_test.c sample/exception_test.cpp
MANUAL_GARBAGE = manual.aux manual.log manual.out
# Programs
RST2HTML = rst2html
RST2LATEX = rst2latex
PDFLATEX = pdflatex

all:

doc: doc-html doc-pdf

doc-html: $(MANUAL_HTML)

$(MANUAL_HTML): $(MANUAL_SRC) $(SAMPLES)
	$(RST2HTML) $< > $@

doc-latex: $(MANUAL_LATEX)

$(MANUAL_LATEX): $(MANUAL_SRC) $(SAMPLES)
	$(RST2LATEX) $< > $@

doc-pdf: $(MANUAL_PDF)

$(MANUAL_PDF): $(MANUAL_LATEX)
	$(PDFLATEX) $<
	$(PDFLATEX) $<

test:
	$(MAKE) -k -C sample test test-py

clean:
	$(RM) $(MANUAL_HTML) $(MANUAL_LATEX) $(MANUAL_PDF) $(MANUAL_GARBAGE)

.PHONY: all doc doc-html doc-latex doc-pdf test clean

