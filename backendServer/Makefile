
TARGETS = StorageServer

all: $(TARGETS)

StorageServer: StorageServer.cc BigTable.cc FileMetaData.cc Utility.cc
	g++ $^ -L/home/cis505/git/T08/kvstore -I/home/cis505/git/T08/lib -lpthread -g -o $@

clean:
	rm -fv $(TARGETS) *~ *.o 
