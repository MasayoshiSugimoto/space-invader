CC := clang
CFLAGS := -Wall -g -fsanitize=address -fno-omit-frame-pointer
DEP_OPT := -MM -MP
SRC_DIR := src
BUILD_DIR := .build
SCRIPT_DIR := scripts
SOURCES := $(shell find $(SRC_DIR) -name "*.c" -type f)
DEPS := $(subst $(SRC_DIR),$(BUILD_DIR),$(SOURCES:.c=.d))
OBJS := $(subst $(SRC_DIR),$(BUILD_DIR),$(SOURCES:.c=.o))
PROGRAM := space-invaders
LIBS := -lcurses -lncurses -lm

$(shell [ ! -d .build ] && mkdir -p .build && mkdir -p .build/generated)
$(shell [ ! -d $(SRC_DIR)/generated ] && mkdir -p $(SRC_DIR)/generated)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Generate dependence files
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEP_OPT) $< | sed -E 's;^(.*)\.o:;$(BUILD_DIR)/\1.o:;' > $@

# Generate objects files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo ./$(SCRIPT_DIR)/generate_array.sh > $@
	$(CC) $(CFLAGS) -c $< -o $@

# $(SRC_DIR)/main.c: $(SRC_DIR)/array.h $(SRC_DIR)/array.c $(SRC_DIR)/slice.h $(SRC_DIR)/slice.c

$(SRC_DIR)/array.h: $(SCRIPT_DIR)/generate_array.sh
	./$(SCRIPT_DIR)/generate_array.sh h> $@

$(SRC_DIR)/array.c: $(SCRIPT_DIR)/generate_array.sh
	./$(SCRIPT_DIR)/generate_array.sh c> $@


.PHONY: clean build try run tags

clean:
	rm -rf .build
	rm -f $(PROGRAM)
	rm -f tags
	rm -rf $(SRC_DIR)/generated

build: $(PROGRAM)

run: build
	./$(PROGRAM)

debug: build
	gdb $(PROGRAM)

try:
	$(info SRC_DIR=$(SRC_DIR))
	$(info SOURCES=$(SOURCES))
	$(info DEPS=$(DEPS))

tags:
	ctags -R .

gen:
	./generators/generate_slice.sh

-include $(DEPS)
