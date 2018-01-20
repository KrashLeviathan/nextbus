CC = gcc
CXX = g++
ECHO = echo
RM = rm -f

CFLAGS = -Wall -ggdb -funroll-loops
CXXFLAGS = -Wall -Wno-sign-compare -ggdb -funroll-loops
LDFLAGS = -lcurl

BIN = nextbus
OBJS = nextbus.o config.o io.o connection.o curlplusplus.o route.o route_parser.o predictions_parser.o xml_parser.o actions.o agency_parser.o route_list_parser.o stop_list_parser.o

all: $(BIN) etags

$(BIN): $(OBJS)
	@$(ECHO) Linking $@
	@$(CXX) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)

%.o: %.c
	@$(ECHO) Compiling $<
	@$(CC) $(CFLAGS) -MMD -MF $*.d -c $<

%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $<

.PHONY: all clean clobber etags

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.*

clobber: clean
	@$(ECHO) Removing backup files
	@$(RM) *~ \#*

etags:
	@$(ECHO) Updating TAGS
	@etags *.cpp *.h
