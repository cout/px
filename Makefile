all: main

OBJS = \
	main.o \
	parser/parser.o \
	parser/scanner.o \
	object/Object.o \
	object/Integer.o \
	object/Nil.o \
	object/String.o \
	function/Function.o

CFLAGS += -ggdb
CXXFLAGS = -fno-inline

parser/parser.cpp: parser/parser.hpp

parser/parser.hpp: parser/parser.y
	lemon parser/parser.y
	mv parser/parser.c parser/parser.cpp
	mv parser/parser.h parser/parser.hpp

GENERATED_FILES += parser/parser.hpp

parser/scanner.cpp: parser/scanner.rl
	ragel parser/scanner.rl -o parser/scanner.cpp

GENERATED_FILES += parser/scanner.cpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	$(RM) $(OBJS) $(GENERATED_FILES)

CFLAGS += -MMD -MP
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

