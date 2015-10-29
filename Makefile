compile: 
	g++ -std=c++11 *.cpp   -lX11 -lXi -lglut -lGL -lGLU -lpthread -o LangtonAnt
all:ant.o main.o parser.o window.o
	g++ -std=c++11 *.o -lX11 -lXi -lglut -lGL -lGLU -lpthread   -o LangtonAnt
ant.o:
	g++ -std=c++11 -c ant.cpp
main.o:
	g++ -std=c++11 -c main.cpp  
window.o:
	g++ -std=c++11 -c window.cpp
parser.o:
	g++ -std=c++11 -c parser.cpp
run: 
	echo "1024 700 250 10" |./LangtonAnt
run-wp:
	echo "1024 700 250 10" |./LangtonAnt data.cfg

clean:
	rm -f ./*.o
