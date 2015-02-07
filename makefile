CC = gcc
XX = g++
CFLAGS = -g -std=c++0x -lpthread -lprotobuf

#INC += -I /usr/include/mysql
#INC += -I /usr/local/include/mysql++/

#LIBS += -L -lmysqlclient_r -lmysqlpp

TARGET = hello
SOURCES += $(wildcard *.c *.cc *.cpp *.cxx)
SOURCES += $(wildcard proto/*.c proto/*.cc proto/*.cpp proto/*.cxx)
SOURCES += $(wildcard common/*.c common/*.cc common/*.cpp common/*.cxx)

OBJECTS = $(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(patsubst %.cpp,%.o,$(SOURCES))))

%.o:%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.cc
	$(XX) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.cpp
	$(XX) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.cxx
	$(XX) $(CFLAGS) $(INC) -c $< -o $@

$(TARGET) : $(OBJECTS)
	@echo $(SOURCES)
	@echo $(OBJECTS)
	$(XX) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	rm -rf $(OBJECTS) $(TARGET)