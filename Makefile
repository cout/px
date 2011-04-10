all: main

OBJS = \
	main.o \
	p.o \
	scanner.o

CFLAGS += -ggdb

p.cpp p.hpp: p.y
	lemon p.y
	mv p.c p.cpp
	mv p.h p.hpp

scanner.cpp: scanner.rl
	ragel scanner.rl -o scanner.cpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CCFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) p.c p.cpp p.h p.hpp scanner.cpp

CFLAGS += -MMD
DEP_FILES = $(patsubst %.o,%.d,$(OBJS))
-include $(DEP_FILES)

