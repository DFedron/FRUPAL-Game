CXX = g++
CXXFLAGS = -g -Wall -Werror
TARGET = frupal
OBJS = main.o grovnick.o item_tiles.o map.o
LIBS = -lncurses
$(TARGET): $(OBJS)
		$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(LIBS)

main.o: main.cpp

grovnick.o: grovnick.cpp

item_tiles.o: item_tiles.cpp

map.o: map.cpp

clean:
		rm *.o $(TARGET)
