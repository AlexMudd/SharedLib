
help:
	@echo "build - builds a main program and dynamic library"
	@echo "run - runs a program"
	@echo "clean - cleans directory"

build: main.o pushkin.o
	gcc -shared -fPIC -o libpushkin.so pushkin.o
	gcc -o main.exe main.o

run:
	@./main.exe



%.o:%.c
	gcc -c -fPIC $< -o $@
	
clean:
	@rm -vf *.o *.so *.a *.exe *~ *.a
