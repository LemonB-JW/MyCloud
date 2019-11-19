
# TARGETS = BigTable.o FileMetaData.o

# all: $(TARGETS)

CPPFLAGS = -lpthread -I../lib -c

TableCell.o:
		g++ $(CPPFLAGS) TableCell.cc

BigTable.o: 
		g++ $(CPPFLAGS) BigTable.cc

FileMetaData.o:
		g++ $(CPPFLAGS) FileMetaData.cc

clean:
	rm -fv $(TARGETS) *~ *.o 
