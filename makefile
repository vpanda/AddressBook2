objects = main.o address.o

main : $(objects)
	g++ -o main $(objects) ./lib/libjson.a ./lib/libjson.so

main.o : main.cpp json/json.h
	g++ -c main.cpp

address.o : address.cpp address.h json/json.h
	g++ -c address.cpp

clean:
	rm -f main $(objects) main.cpp~ makefile~ sample1.txt~ \
	sample2.txt~ sample3.txt~ sample4.txt~ sample5.txt~ \
	sample6.txt~ address.cpp~ address.h~ log~ data.txt~
