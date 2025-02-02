CC = clang
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer -O1
DEP_OPT = -MM -MP
SRC_DIR = src
BUILD_DIR = .build
SOURCES = $(foreach d, $(SRC_DIR), $(wildcard $(addprefix $(d)/*, .c)))
DEPS = $(subst $(SRC_DIR), $(BUILD_DIR), $(SOURCES:.c=.d))
OBJS = $(subst $(SRC_DIR), $(BUILD_DIR), $(SOURCES:.c=.o))
PROGRAM = space-invaders
LIBS = -lcurses -lncurses -lm

ignore := $(shell [ ! -d .build ] && mkdir -p .build)

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Generate dependence files
$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(DEP_OPT) $< | sed -E 's;^(.*)\.o:;$(BUILD_DIR)/\1.o:;' > $@

# Generate objects files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean build try run tags


clean:
	rm -rf .build
	rm -f $(PROGRAM)
	rm -f tags

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

-include $(DEPS)
