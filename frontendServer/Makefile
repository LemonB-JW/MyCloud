TARGETS = httpServer loadbalancer smtp pop3

all: $(TARGETS)

%.o: %.cc utils/%.cc
	g++ $^ -c -o $@

httpServer: httpServer.o request.o response.o utils/utils.o
	g++ $^ -o $@ -lpthread

loadbalancer: loadbalancer.o
	g++ $^ -o $@

smtp: smtp.cc
	g++ $< -lpthread -g -o $@

pop3: pop3.cc
	g++ $^ -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lc

pack:
	rm -f submit-hw3.zip
	zip -r submit-hw3.zip README Makefile *.c* *.h*

clean::
	rm -fv $(TARGETS) *~ *.o submit-hw3.zip


