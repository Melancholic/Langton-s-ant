compile: 
	g++ -lX11 -lXi -lglut -lGL -lGLU -lboost_thread-mt  *.cpp   -o LangtonAnt

run: 
	echo "1024 700 250 10" |./LangtonAnt


