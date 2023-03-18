.PHONY: all clean

CC = g++
CFLAGS = -g -Wall -O3 -Wall -shared -std=c++11 -fPIC

SRC = HistogramEqualization.cpp
TARGET = $(patsubst %.cpp, %.so, $(SRC))

all: $(TARGET)

clean:
	rm -r *.so __pycache__/ .pytest_cache/

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) `python3 -m pybind11 --includes` $(SRC) -o $(TARGET) `python3-config --includes --ldflags`