# Author: Jiaying Guo

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
IFLAG = -lpthread -I../lib
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = protos

vpath %.proto $(PROTOS_PATH)

TARGETS = bigtable_server bigtable_client bigtable_client_2
all: $(TARGETS)

bigtable_client: bigtable.pb.o bigtable.grpc.pb.o bigtable_client.o
	$(CXX) $^ $(LDFLAGS) -o $@

bigtable_client_2: bigtable.pb.o bigtable.grpc.pb.o bigtable_client_2.o
	$(CXX) $^ $(LDFLAGS) -o $@

bigtable_server: bigtable.pb.o bigtable.grpc.pb.o bigtable_server.o TableCell.cc BigTable.cc FileMetaData.cc Utility.cc MetaTree.cc DistributedStorage.cc masterBackend.pb.o masterBackend.grpc.pb.o 
	$(CXX) $^ $(LDFLAGS) $(IFLAG) -g -o $@

tester: table_tester.cc TableCell.cc BigTable.cc FileMetaData.cc Utility.cc MetaTree.cc
	$(CXX) $^ $(IFLAG) -g -o $@

# master_server: masterBackend.pb.o masterBackend.grpc.pb.o masterKVServer.o masterInfo.cc
# 	$(CXX) $^ $(IFLAGS) $(LDFLAGS) -g -o $@

# storageserver: StorageServer.cc TableCell.cc BigTable.cc FileMetaData.cc Utility.cc MetaTree.cc
# 	$(CXX) $^ $(IFLAG) -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean:
	rm -fv $(TARGETS) *~ *.o *.pb.cc *.pb.h
	


# The following is to test your system and ensure a smoother experience.
# They are by no means necessary to actually compile a grpc-enabled software.

# PROTOC_CMD = which $(PROTOC)
# PROTOC_CHECK_CMD = $(PROTOC) --version | grep -q libprotoc.3
# PLUGIN_CHECK_CMD = which $(GRPC_CPP_PLUGIN)
# HAS_PROTOC = $(shell $(PROTOC_CMD) > /dev/null && echo true || echo false)
# ifeq ($(HAS_PROTOC),true)
# HAS_VALID_PROTOC = $(shell $(PROTOC_CHECK_CMD) 2> /dev/null && echo true || echo false)
# endif
# HAS_PLUGIN = $(shell $(PLUGIN_CHECK_CMD) > /dev/null && echo true || echo false)

# SYSTEM_OK = false
# ifeq ($(HAS_VALID_PROTOC),true)
# ifeq ($(HAS_PLUGIN),true)
# SYSTEM_OK = true
# endif
# endif

# system-check:
# ifneq ($(HAS_VALID_PROTOC),true)
# 	@echo " DEPENDENCY ERROR"
# 	@echo
# 	@echo "You don't have protoc 3.0.0 installed in your path."
# 	@echo "Please install Google protocol buffers 3.0.0 and its compiler."
# 	@echo "You can find it here:"
# 	@echo
# 	@echo "   https://github.com/google/protobuf/releases/tag/v3.0.0"
# 	@echo
# 	@echo "Here is what I get when trying to evaluate your version of protoc:"
# 	@echo
# 	-$(PROTOC) --version
# 	@echo
# 	@echo
# endif
# ifneq ($(HAS_PLUGIN),true)
# 	@echo " DEPENDENCY ERROR"
# 	@echo
# 	@echo "You don't have the grpc c++ protobuf plugin installed in your path."
# 	@echo "Please install grpc. You can find it here:"
# 	@echo
# 	@echo "   https://github.com/grpc/grpc"
# 	@echo
# 	@echo "Here is what I get when trying to detect if you have the plugin:"
# 	@echo
# 	-which $(GRPC_CPP_PLUGIN)
# 	@echo
# 	@echo
# endif
# ifneq ($(SYSTEM_OK),true)
# 	@false
# endif
