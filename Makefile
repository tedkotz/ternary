# Makefile to fanout make commands to sub projects

SUBDIRS= emu/% asm/%

default: asm/test
	@echo done

define SUBMAKE

$(1):
	$$(MAKE) -C $$(@D)/ $$(@F)

endef

$(foreach DIR,$(SUBDIRS),$(eval $(call SUBMAKE,$(DIR))))

%: $(SUBDIRS)
	@echo done

.PHONY: default % $(SUBDIRS)
