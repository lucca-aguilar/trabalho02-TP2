CXX = g++
CXXFLAGS = -std=c++17 -Wall
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
DEBUG_FLAGS = -g
TARGET = testa_backup

YOUR_SOURCES = backup.cpp backup.hpp testa_backup.cpp
TEST_BUILD_SOURCES = testa_backup.cpp catch_amalgamated.cpp

all: test

$(TARGET): $(TEST_BUILD_SOURCES) backup.o
	$(CXX) $(CXXFLAGS) backup.o $(TEST_BUILD_SOURCES) -o $(TARGET)

velha.o: backup.cpp backup.hpp
	$(CXX) $(CXXFLAGS) -c backup.cpp

test: $(TARGET)
	./$(TARGET)

cpplint:
	cpplint $(YOUR_SOURCES)

cppcheck:
	cppcheck --quiet --enable=warning $(YOUR_SOURCES)

gcov:
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c backup.cpp
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) backup.o $(TEST_BUILD_SOURCES) -o $(TARGET)
	./$(TARGET)
	gcov backup.cpp

debug:
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -c backup.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAGS) -g backup.o $(TEST_BUILD_SOURCES) -o $(TARGET)
	gdb $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=yes --log-file=valgrind.rpt ./$(TARGET)

clean:
	rm -f *.o *.gc* *.gcov *.gcda *.gcno $(TARGET) valgrind.rpt