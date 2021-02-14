# Makefile to help with assembly

OUTDIR=out
SRCDIR=examples
#PP=yamp.py
PP=gcc -E -xc
MKDIR=@mkdir

default: test

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(OUTDIR)/%.trt: $(SRCDIR)/%.tas assembler.inc | $(OUTDIR)
	$(PP) --include assembler.inc $< -o $@

%: $(OUTDIR)/%.trt
	../emu/tern-cpu-emu $<
