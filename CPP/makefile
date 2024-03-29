#
# Substitute commands below with gmake -f Makefile.mk
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
#               Use 'gcc' for C and 'g++' for cpp
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES += include/BattleMonitor.h
INCLUDES += include/Card.h
INCLUDES += include/cardTypes.h
INCLUDES += include/cardUtils.h
INCLUDES += include/Deck.h
INCLUDES += include/fileUtils.h
INCLUDES += include/GameMonitor.h
INCLUDES += include/Player.h
INCLUDES += include/Profile.h
INCLUDES += include/versions.h
INCLUDES += include/versionTypes.h

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L/lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -ljsoncpp

# define the C source files
SRCS += json/jsoncpp.cpp
SRCS += src/BattleMonitor.cpp
SRCS += src/Card.cpp
SRCS += src/Deck.cpp
SRCS += src/GameMonitor.cpp
SRCS += src/main.cpp
SRCS += src/Player.cpp
SRCS += src/Profile.cpp

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file
TARGET = cardgame

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(TARGET)
		@echo  Target: '$(TARGET)' has been compiled

$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
		$(RM) *.o *~ $(TARGET)

depend: $(SRCS)
		makedepend $(INCLUDES) $^

# This is needed for make depend