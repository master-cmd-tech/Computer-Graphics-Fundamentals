CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra

LIBS = -lglfw3 -lopengl32 -lgdi32

PROGRAMS = red_triangle blue_square polygons creative

all: $(PROGRAMS)

red_triangle: red_triangle.cpp glad.c
	$(CXX) $(CXXFLAGS) red_triangle.cpp glad.c -o red_triangle $(LIBS)

blue_square: blue_square.cpp glad.c
	$(CXX) $(CXXFLAGS) blue_square.cpp glad.c -o blue_square $(LIBS)

polygons: polygons.cpp glad.c
	$(CXX) $(CXXFLAGS) polygons.cpp glad.c -o polygons $(LIBS)

creative: creative.cpp glad.c
	$(CXX) $(CXXFLAGS) creative.cpp glad.c -o creative $(LIBS)

clean:
	del /Q $(PROGRAMS).exe 2>NUL || exit 0
