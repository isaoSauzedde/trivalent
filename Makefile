.PHONY: dots all clean
.SUFFIXES: .dot .jpg .cpp

all: gauss dots

run:
	./gauss

gauss: $(wildcard *.cpp)
	g++ -std=c++11 -I/Users/admin/Desktop/singularCS/gauss_copie/eigen3 trivalent.cpp vertex.cpp main.cpp -o gauss -Wall

dots: test.jpg

clean:
	rm -f gauss

%.jpg: %.dot
	neato -Tjpg $< -o $@
