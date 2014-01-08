test.out: test.o make_xml.o
	g++ -o test.out test.o make_xml.o

test.o: test.cpp
	g++ -c test.cpp

make_xml.o: make_xml.cpp
	g++ -c make_xml.cpp

clean:
	rm test.out test.o make_xml.o
