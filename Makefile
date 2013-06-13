compile: 
	g++ -lX11 -lXi -lglut -lGL -lGLU -lboost_thread-mt  *.cpp   -o LangtonAnt

all:ant.o main.o parser.o window.o
	g++ -lX11 -lXi -lglut -lGL -lGLU -lboost_thread-mt ant.o main.o parser.o window.o -o new
ant.o:
	g++ -c ant.cpp
main.o:
	g++ -c main.cpp  
window.o:
	g++ -c window.cpp
parser.o:
	g++ -c parser.cpp
run: 
	echo "1024 700 250 10" |./LangtonAnt
run-wp:
	echo "1024 700 250 10" |./LangtonAnt data.cfg

clean:
	rm -f ./*.o
