# Quick Makefile

PKG=tern-cpu-emu
SRCEXT=.c
SRCS=$(wildcard *$(SRCEXT))
STRIP=strip
CC=gcc
CFLAGS=-Wall -Ofast
LIBS=
#PREFIX=/usr/local
#CONFIGDIR=/etc
DEPDIR=deps
DEPS=$(SRCS:%$(SRCEXT)=$(DEPDIR)/%.d)
OBJDIR=obj
OBJS=$(SRCS:%$(SRCEXT)=$(OBJDIR)/%.o)
ASMDIR=asm
ASMS=$(SRCS:%$(SRCEXT)=$(ASMDIR)/%.s)
DOCDIR=doc
DOCCMD=doxygen
DOCCFG=Doxyfile
SED=sed
MKDIR=@mkdir

$(PKG): $(OBJS)
	@echo "Generating $@"
	$(CC) $(LIBS) $(CFLAGS) $(OBJS) -o $(PKG)
	$(STRIP) $(PKG)

pkg: $(PKG)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(OBJDIR)/%.o: %$(SRCEXT) | $(OBJDIR)
	@echo "CC $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(ASMDIR):
	$(MKDIR) $(ASMDIR)

$(ASMDIR)/%.s: %$(SRCEXT) | $(ASMDIR)
	$(CC) $(CFLAGS) -S -fverbose-asm -c $< -o $@

$(DEPDIR):
	$(MKDIR) $(DEPDIR)

$(DEPDIR)/%.d: %$(SRCEXT) | $(DEPDIR)
	$(CC) $(CFLAGS) -c $< -MM -o $@
	$(SED) -i 's+\($*\)\.o[ :]*+$(OBJDIR)/\1.o $@ : +g' $@

asms: $(ASMS)


test: $(PKG)
	./$(PKG)

#install: $(PKG)
#	cp $(PKG) $(PREFIX)/bin/
#	cp $(PKG)rc $(CONFIGDIR)/

clean-asm:
	rm -rf $(ASMDIR)

clean-obj:
	rm -rf $(OBJDIR)

clean-dep:
	rm -rf $(DEPDIR)

clean: clean-obj clean-asm
	rm -rf *~

clean-pkg: clean clean-dep
	rm -rf $(PKG)

rebuild: clean-pkg pkg

$(DOCCFG):
	$(DOCCMD) -g $(DOCCFG)
	$(SED) -i 's+^OUTPUT_DIRECTORY *=.*$$+OUTPUT_DIRECTORY       = $(DOCDIR)+g' $(DOCCFG)
	$(SED) -i 's+^PROJECT_NAME *=.*$$+PROJECT_NAME           = "$(PKG)"+g' $(DOCCFG)
	$(SED) -i 's+^GENERATE_LATEX *=.*$$+GENERATE_LATEX         = NO+g' $(DOCCFG)
	$(SED) -i 's+^SOURCE_BROWSER *=.*$$+SOURCE_BROWSER         = YES+g' $(DOCCFG)
	$(SED) -i 's+^GENERATE_TREEVIEW *=.*$$+GENERATE_TREEVIEW      = YES+g' $(DOCCFG)
#	$(SED) -i 's+^PLANTUML_JAR_PATH *=.*$$+PLANTUML_JAR_PATH      = /usr/share/plantuml/plantuml.jar+g' $(DOCCFG)

docs: $(DOCCFG)
	$(DOCCMD) $(DOCCFG)

clean-docs:
	rm -rf $(DOCDIR)

rebuild-docs: clean-docs docs

all: $(PKG) docs

clean-all: clean-pkg clean-docs

rebuild-all: clean-all all

include $(DEPS)

#gcc -Wall -Os -fgcse-after-reload -fipa-cp-clone -floop-interchange -floop-unroll-and-jam -fpeel-loops -fpredictive-commoning -fsplit-loops -fsplit-paths -ftree-loop-distribution -ftree-loop-vectorize -ftree-partial-pre -ftree-slp-vectorize -funswitch-loops -fvect-cost-model -fvect-cost-model=dynamic -fversion-loops-for-strides main.c

#gcc -Wall -Os -fassociative-math -fcx-limited-range -ffinite-math-only -fgcse-after-reload -fipa-cp-clone -floop-interchange -floop-unroll-and-jam -foptimize-strlen -fpeel-loops -fpredictive-commoning -freciprocal-math -fsplit-loops -fsplit-paths -ftree-loop-distribute-patterns -ftree-loop-distribution -ftree-loop-vectorize -ftree-partial-pre -ftree-slp-vectorize -funsafe-math-optimizations -funswitch-loops -fno-math-errno -fno-signed-zeros -fno-trapping-math -fvect-cost-model=dynamic main.c

$(V).SILENT:
