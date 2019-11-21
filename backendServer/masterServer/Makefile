
TARGETS = master
CXX = g++
CXXFLAGS += -std=c++11
IDIR =../../lib
CPPFLAGS = -lpthread -I$(IDIR)
all: $(TARGETS)

#%.o: %.cc
#	$(CXX) $^ $(CPPFLAGS) -o $@ 

#masterInfo.o: masterInfo.cc
#$(CXX) $^ $(CPPFLAGS) -c masterInfo.cc
	
master: master.cc masterInfo.cc
	$(CXX) $^ $(CPPFLAGS) -g -o $@

clean:
	rm -fv $(TARGETS) *~ *.o 
