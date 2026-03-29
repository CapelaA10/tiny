CXX = clang++
CXXFLAGS = -std=c++17 -Wall -g

TARGET = tiny

SRCS = main.cpp lexer/lexer.cpp token/token.cpp parser/parser.cpp interpreter/interpreter.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET) *.dSYM

.PHONY: all clean
