# Makefile to help with assembly

OUTDIR=out
SRCDIR=examples
#PP=yamp.py
PP=gcc -E -xc
MKDIR=@mkdir
EMUDIR=../emu/
EMUEXE=tern-cpu-emu
EMU=$(EMUDIR)$(EMUEXE)
EMUDEPS=$(wildcard $(EMUDIR)*.c) $(wildcard $(EMUDIR)*.h)
TASFILES=$(wildcard $(SRCDIR)/*.tas)
TRTFILES=$(TASFILES:$(SRCDIR)/%.tas=$(OUTDIR)/%.trt)

default: test

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

# Rule to assemble Ternary Assembly into loadable Trit files
$(OUTDIR)/%.trt: $(SRCDIR)/%.tas assembler.inc | $(OUTDIR)
	$(PP) --include assembler.inc $< -o $@

# Rule to run a Trit file in the emulator
%: $(OUTDIR)/%.trt $(EMU)
	$(EMU) $<

all: $(TRTFILES)

clean:
	rm -rf $(OUTDIR)

clean-all: clean

$(EMU): $(EMUDEPS)
	$(MAKE) -C $(EMUDIR) $(EMUEXE)

.PRECIOUS: $(OUTDIR)/%.trt
