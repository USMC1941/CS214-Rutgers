all: test.c libstuff.a
	gcc -o awesomesauce test.c libstuff.a

libstuff.a: stuff.o stuff.h
	ar r libstuff.a stuff.o

stuff.o: stuff.c stuff.h
	gcc -c stuff.c

clean:
	rm ./awesomesauce ./*.o
