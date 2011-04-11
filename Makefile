all: main

OBJS = \
	main.o \
	parser/parser.o \
	parser/scanner.o \
	object/Nil.o

CFLAGS += -ggdb

parser/parser.cpp: parser/parser.hpp

parser/parser.hpp: parser/parser.y
	lemon parser/parser.y
	mv parser/parser.c parser/parser.cpp
	mv parser/parser.h parser/parser.hpp

parser/scanner.cpp: parser/scanner.rl
	ragel parser/scanner.rl -o parser/scanner.cpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CCFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) parser/p.c parser/p.cpp parser/p.h parser/p.hpp parser/scanner.cpp

CFLAGS += -MMD
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

