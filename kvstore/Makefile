
# TARGETS = BigTable.o FileMetaData.o

# all: $(TARGETS)

CPPFLAGS = -g -Wall -I/home/cis505/git/T08/lib
#  $(CC) $(LDFLAGS) -o $(PROG) $(OBJS)
# TableCell.o: TableCell.h TableCell.cc
# 		g++ $(CPPFLAGS) -Wall -lpthread -c TableCell.cc

BigTable.o: BigTable.h BigTable.cc 
		g++ $(CPPFLAGS) -Wall -lpthread -c BigTable.cc

FileMetaData.o: FileMetaData.h FileMetaData.cc
		g++ $(CPPFLAGS) -Wall -c FileMetaData.cc

clean:
	rm -fv $(TARGETS) *~ *.o 
