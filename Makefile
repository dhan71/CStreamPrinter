
CCC = g++
CXX = g++
LD  = g++
CP  = /bin/cp
MV  = /bin/mv
RM  = /bin/rm -f

CCOPTIONS = -std=c++17 -fPIC -g -Wall -Wextra -Wno-unused-parameter -Wno-ignored-qualifiers
#CCOPTIONS = -std=c++17 -g -Wall #-Wextra -Wno-unused-parameter -Wno-ignored-qualifiers
LDOPTIONS = -g -m64
SLOPTIONS = -shared -g -m64

#SYS_INC = -I. -I/usr/include -I/usr/include/c++/8
SYS_INC = #-I/usr/include -I/usr/include/c++/8
#SYS_LIB = -L/usr/lib64 -L/lib -lstd++ -lm
SYS_LIB = -L/usr/lib64 -lstdc++ -lm

BOOSTUT_LIB = -lboost_unit_test_framework

CXXFLAGS = $(CCOPTIONS) $(SYS_INC)
LDFLAGS  = $(SYS_LIB)
VPATH    = .

.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<


EXEFILES = ut


all: lib exe

clean:
	$(RM) ut.o ut

run: $(EXEFILES)

exe: $(EXEFILES)

lib:

ut: ut.o
	$(CCC) $(LDOPTIONS) -o $@ $? $(LDFLAGS) $(BOOSTUT_LIB)

