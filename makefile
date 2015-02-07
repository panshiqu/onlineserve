CC = gcc
XX = g++
CFLAGS = -g -std=c++0x -lpthread

#INC += -I /usr/include/mysql
#INC += -I /usr/local/include/mysql++/

#LIBS += -L -lmysqlclient_r -lmysqlpp

TARGET = hello
SOURCES = $(wildcard *.c *.cpp ./common/*.c ./common/*.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

%.o:%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.cpp
	$(XX) $(CFLAGS) $(INC) -c $< -o $@

%.o:%.cxx
	$(XX) $(CFLAGS) $(INC) -c $< -o $@

$(TARGET) : $(OBJS)
	$(XX) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) $(TARGET)