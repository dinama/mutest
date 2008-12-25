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
INSTALL = install
# Directories
prefix = /usr/local
BIN_DIR = bin
INC_DIR = include
DOC_DIR = shared/doc/mutest

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

install-readme:
	$(INSTALL) -m 755 -d $(prefix)/$(DOC_DIR)
	$(INSTALL) -m 644 $(MANUAL_SRC) $(prefix)/$(DOC_DIR)/$(MANUAL_SRC)

install-html: $(MANUAL_HTML)
	$(INSTALL) -m 755 -d $(prefix)/$(DOC_DIR)
	$(INSTALL) -m 644 $(MANUAL_HTML) $(prefix)/$(DOC_DIR)/$(MANUAL_HTML)

install-pdf: $(MANUAL_PDF)
	$(INSTALL) -m 755 -d $(prefix)/$(DOC_DIR)
	$(INSTALL) -m 644 $(MANUAL_PDF) $(prefix)/$(DOC_DIR)/$(MANUAL_PDF)

install-c:
	$(INSTALL) -m 755 -d $(prefix)/$(BIN_DIR)
	$(INSTALL) -m 755 -d $(prefix)/$(INC_DIR)
	$(INSTALL) -m 644 mutest.c $(prefix)/$(INC_DIR)/mutest.c
	$(INSTALL) -m 644 mutest.h $(prefix)/$(INC_DIR)/mutest.h
	$(INSTALL) -m 755 mkmutest $(prefix)/$(BIN_DIR)/mkmutest

install-py:
	$(INSTALL) -m 755 -d $(prefix)/$(BIN_DIR)
	$(INSTALL) -m 755 -d $(prefix)/$(INC_DIR)
	$(INSTALL) -m 644 mutest.h $(prefix)/$(INC_DIR)/mutest.h
	$(INSTALL) -m 755 mutest $(prefix)/$(BIN_DIR)/mutest

install-doc: install-readme install-html install-pdf

install: install-c install-py install-doc

test:
	$(MAKE) -k -C sample test test-py

clean:
	$(RM) $(MANUAL_HTML) $(MANUAL_LATEX) $(MANUAL_PDF) $(MANUAL_GARBAGE)

.PHONY: all doc doc-html doc-latex doc-pdf \
		install-readme install-html install-pdf install-doc \
		install-c install-py install \
		test clean

