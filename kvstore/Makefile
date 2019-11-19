
# TARGETS = BigTable.o FileMetaData.o

# all: $(TARGETS)

CPPFLAGS = -lpthread -I/home/cis505/git/T08/lib -c
#  $(CC) $(LDFLAGS) -o $(PROG) $(OBJS)
TableCell.o:
		g++ $(CPPFLAGS) TableCell.cc

BigTable.o: 
		g++ $(CPPFLAGS) BigTable.cc
#  FileMetaData.h FileMetaData.cc
FileMetaData.o:
		g++ $(CPPFLAGS) FileMetaData.cc

clean:
	rm -fv $(TARGETS) *~ *.o 
