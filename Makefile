all: main

OBJS = \
	main.o \
	parser/p.o \
	parser/scanner.o \
	object/Nil.o

CFLAGS += -ggdb

parser/p.cpp parser/p.hpp: parser/p.y
	lemon parser/p.y
	mv parser/p.c parser/p.cpp
	mv parser/p.h parser/p.hpp

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

