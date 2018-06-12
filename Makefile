COMP = g++-5.3.0
OBJS = main.o
EXEC = ex4
CPP_COMP_FLAG = -std=gnu++14 -g -Wall -Wextra \
-Werror -pedantic-errors -DNDEBUG -g
DEPS = *.h

rps_tournament: $(OBJS)
	$(COMP) -o $(EXEC) $(OBJS)
    
%.o: %.cpp $(DEPS)
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)