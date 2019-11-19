
# TARGETS = serverInfo.o

# all: $(TARGETS)

CPPFLAGS = -lpthread -I../lib -c

masterInfo.o:
		g++ $(CPPFLAGS) serverInfo.cc

clean:
	rm -fv $(TARGETS) *~ *.o 
