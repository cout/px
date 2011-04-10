all: main

OBJS = \
	main.o \
	p.o

p.cpp p.hpp: p.y
	lemon p.y
	mv p.c p.cpp
	mv p.h p.hpp

%.o: %.cpp
	$(CXX) $(CCFLAGS) -c $< -o $@

main: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

