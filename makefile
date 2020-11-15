CXX = g++
CXXFLAGS = -g -Wall -Werror
TARGET = Frupal
OBJS = main.o grovnick.o item_tiles.o

$(TARGET): $(OBJS)
		$(CXX) $(OBJS) -o Frupal $(CXXFLAGS) -lncurses

main.o: main.cpp item_tiles.h

grovnick.o: grovnick.h grovnick.cpp

item_tiles.o: item_tiles.h item_tiles.cpp

clean:
		rm *.o $(TARGET)
