PROTOC = protoc
PFLAGS = --cpp_out=.
SOURCES = $(wildcard *.proto)
OBJECTS = $(patsubst %.proto,%.cc,$(SOURCES))

all:$(OBJECTS)

$(OBJECTS):
	$(PROTOC) $(PFLAGS) $*.proto

clean:
	rm -rf *.pb.h *.pb.cc