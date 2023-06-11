CC = g++
CFLAGS = -std=c++20 $(shell pkg-config gtkmm-3.0 --cflags)
LDFLAGS = $(shell pkg-config gtkmm-3.0 --libs)

TARGET = Labyrinth
SOURCES = main.cpp 

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
