driver: driver.o Image.o
	g++ -o imageops driver.o Image.o -std=c++11 

driver.o: driver.cpp 
	g++ -c -o driver.o driver.cpp -std=c++11 

image.o: image.cpp Image.h
	g++ -c -o Image.o Image.cpp -std=c++11

clean:
	rm -Rf *.o imageops
