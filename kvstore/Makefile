
TARGETS = tester storageserver

all: $(TARGETS)

CPPFLAGS = -lpthread -I../lib -g -o

tester: table_tester.cc TableCell.cc BigTable.cc FileMetaData.cc Utility.cc
		g++ $^ $(CPPFLAGS) $@

storageserver: StorageServer.cc TableCell.cc BigTable.cc FileMetaData.cc Utility.cc
		g++ $^ $(CPPFLAGS) $@

clean:
	rm -fv $(TARGETS) *~ *.o 
