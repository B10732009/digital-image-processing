.PHONY: all clean

CC = g++
CFLAGS = -g -Wall -O3 -Wall -shared -std=c++11 -fPIC

SRC = dct.cpp fdct.cpp
TARGET = $(patsubst %.cpp, %.so, $(SRC))

all: $(TARGET)

clean:
	rm -r *.so __pycache__/ .pytest_cache/

%.so: %.cpp
	$(CC) $(CFLAGS) `python3 -m pybind11 --includes` $< -o $@ `python3-config --includes --ldflags`