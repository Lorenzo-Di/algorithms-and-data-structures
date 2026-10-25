SUBDIRS = ex1 ex2 ex3 ex4

.PHONY: all test clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ all

test: all
	@echo "\n\n=== Running Module 1 Tests ===" && ./ex1/bin/test_ex1
	@echo "\n=== Running Module 2 Tests ===" && ./ex2/bin/test_ex2
	@echo "\n=== Running Module 3 Tests ===" && ./ex3/bin/test_ex3
	@echo "\n=== Running Module 4 Tests ===" && ./ex4/bin/test_ex4

clean:
	@for dir in $(SUBDIRS); do $(MAKE) --no-print-directory -C $$dir clean; done