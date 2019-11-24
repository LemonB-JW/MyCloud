# Author: Peng Li

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
IDIR =../../../lib
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
IFLAG = -lpthread -I$(IDIR)
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = protos

vpath %.proto $(PROTOS_PATH)

TARGETS = masterKVGrpc masterKVClientGrpc
all: $(TARGETS)
	
masterKVGrpc: masterBackend.pb.o masterBackend.grpc.pb.o masterKVGrpc.o masterInfo.cc
	$(CXX) $^ $(IFLAGS) $(LDFLAGS) -g -o $@

masterKVClientGrpc: masterBackend.pb.o masterBackend.grpc.pb.o masterKVClientGrpc.o
	$(CXX) $^ $(IFLAGS) $(LDFLAGS) -g -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<
		
clean:
	rm -fv $(TARGETS) *~ *.o *.pb.cc *.pb.h
