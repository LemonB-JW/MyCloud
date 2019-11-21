TARGETS = StorageServer

<<<<<<< HEAD
TARGETS = serverInfo

=======
>>>>>>> ab97f8ff5952f4715ebd9f3f0db5e0655fc0e9e6
all: $(TARGETS)

%.o: %.cc
	g++ $^ -c -o $@
	
CPPFLAGS = -lpthread -I../../lib -c

<<<<<<< HEAD
serverInfo.o:
		g++ $(CPPFLAGS) serverInfo.cc
=======
StorageServer: StorageServer.cc BigTable.cc FileMetaData.cc Utility.cc
	g++ $^ -L/home/cis505/git/T08/kvstore -I/home/cis505/git/T08/lib -lpthread -g -o $@
>>>>>>> ab97f8ff5952f4715ebd9f3f0db5e0655fc0e9e6

clean:
	rm -fv $(TARGETS) *~ *.o 
