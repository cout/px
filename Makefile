all: main

OBJS = \
	main.o \
	p.o \
	scanner.o

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

CFLAGS += -MMD
DEP_FILES = $(patsubst $(OBJS),%.o,%.d)
-include $(DEP_FILES)

