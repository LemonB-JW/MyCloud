
TARGETS = serverInfo

all: $(TARGETS)

%.o: %.cc
	g++ $^ -c -o $@
	
CPPFLAGS = -lpthread -I../../lib -c

serverInfo.o:
		g++ $(CPPFLAGS) serverInfo.cc

clean:
	rm -fv $(TARGETS) *~ *.o 
