CXX = g++
CXXFLAGS = -std=c++17 -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
DEBUG_FLAGS = -g
TARGET = testa_velha

YOUR_SOURCES = velha.cpp velha.hpp testa_velha.cpp
TEST_BUILD_SOURCES = testa_velha.cpp catch_amalgamated.cpp

all: test

$(TARGET): $(TEST_BUILD_SOURCES) velha.o
	$(CXX) $(CXXFLAGS) velha.o $(TEST_BUILD_SOURCES) -o $(TARGET)

velha.o: velha.cpp velha.hpp
	$(CXX) $(CXXFLAGS) -c velha.cpp

test: $(TARGET)
	./$(TARGET)

cpplint:
	cpplint $(YOUR_SOURCES)

cppcheck:
	cppcheck --quiet --enable=warning $(YOUR_SOURCES)

gcov:
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c velha.cpp
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) velha.o $(TEST_BUILD_SOURCES) -o $(TARGET)
	./$(TARGET)
	gcov velha.cpp

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c velha.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -g velha.o $(TEST_BUILD_SOURCES) -o $(TARGET)
	gdb $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=yes --log-file=valgrind.rpt ./$(TARGET)

clean:
	rm -f *.o *.gc* *.gcov *.gcda *.gcno $(TARGET) valgrind.rpt