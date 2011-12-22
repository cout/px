all: main

ifneq (,)
This makefile requires GNU Make.
endif

# --- Global build options ---

CPPFLAGS +=
CFLAGS += -ggdb
CXXFLAGS = -fno-inline

# --- Build objects from C++ source ---

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# --- Build main from objects ---

MAIN_OBJS = \
	main.o \
	parser/parser.o \
	parser/scanner.o \
	object/Object.o \
	object/Integer.o \
	object/Nil.o \
	object/String.o \
	function/Function.o

main: $(MAIN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

OBJS += $(MAIN_OBJS)
GENERATED_FILES += $(MAIN_OBJS)

# --- Build parser using lemon ---

parser/parser.cpp: parser/parser.hpp

parser/parser.hpp: parser/parser.y
	lemon parser/parser.y
	mv parser/parser.c parser/parser.cpp
	mv parser/parser.h parser/parser.hpp

GENERATED_FILES += parser/parser.hpp
GENERATED_FILES += parser/parser.cpp
GENERATED_FILES += parser/parser.h
GENERATED_FILES += parser/parser.c

# --- Build scanner using ragel ---

parser/scanner.cpp: parser/scanner.rl
	ragel parser/scanner.rl -o parser/scanner.cpp

GENERATED_FILES += parser/scanner.cpp

# --- Cleanup rule ---

.PHONY: clean
clean:
	$(RM) $(GENERATED_FILES)

# --- Dependencies ---

CFLAGS += -MMD -MP
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

