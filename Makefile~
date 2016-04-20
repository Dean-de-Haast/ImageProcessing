driver: driver.o image.o
	g++ -o imageops driver.o image.o -std=c++11 

driver.o: driver.cpp 
	g++ -c -o driver.o driver.cpp -std=c++11 

image.o: image.cpp image.h
	g++ -c -o image.o image.cpp -std=c++11

clean:
	rm -Rf *.o imageops
