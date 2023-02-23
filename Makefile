CXX=g++
CXXFLAGS=-O3 -pthread
SRC_DIR=newGASS-base
SRCS=$(SRC_DIR)/Individuo.cpp $(SRC_DIR)/GA.cpp $(SRC_DIR)/newGASS.cpp compatGASS.cpp
OBJS=$(SRCS:.cpp=.o)
TARGET=compatGASS

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)