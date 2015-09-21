
DATA_FLAGS += -DDOUBLEPRECISION
#DATA_FLAGS += -DREAL

CXX = CC
CXX_FLAGS = -std=c++11

WOO_DIR = ${HOME}/edison/hipgisaxs.git/include

BOOST_INCL = -I $(BOOST_DIR)/include -I $(NUM_BOOST_DIR)/include
BOOST_LDFLAGS = -L $(BOOST_DIR)/lib
BOOST_LIBS = -lboost_system -lboost_filesystem -lboost_timer -lboost_chrono

ALL_INCL = -I $(WOO_DIR) $(BOOST_INCL) -I $(MKL_INC)
ALL_LDFLAGS = $(BOOST_LDFLAGS)
ALL_LIBS = $(BOOST_LIBS)

OBJECTS1 = cmathtest.o
OBJECTS2 = mkltest.o

BINARY1 = cmathtest
BINARY2 = mkltest

all: $(BINARY1) $(BINARY2)

$(OBJECTS1): cmathtest.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS) $(ALL_INCL) -no-vec -O1 $(DATA_FLAGS)

$(BINARY1): $(OBJECTS1)
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(ALL_LDFLAGS) $(ALL_LIBS) -lm $(DATA_FLAGS)

$(OBJECTS2): mkltest.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS) $(ALL_INCL) -mkl -mavx -O2 -DMKL_DIRECT_CALL $(DATA_FLAGS)

$(BINARY2): $(OBJECTS2)
	$(CXX) $(CXX_FLAGS) -o $@ $^ $(ALL_LDFLAGS) $(ALL_LIBS) -mkl -lmkl_core -DMKL_DIRECT_CALL $(DATA_FLAGS)

clean:
	rm -f *.o $(BINARY1) $(BINARY2)
