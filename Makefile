TOPDIR = $(PWD)
OBJDIR = $(TOPDIR)/obj/
INCLUDE = $(TOPDIR)/include/header.h
SOURCE = $(TOPDIR)/src/
LIBDIR = $(TOPDIR)/lib/



all: matrixMul.o timer.o 
	gcc $(OBJDIR)timer.o $(OBJDIR)matrixMul.o $(INCLUDE) -o hello.out
	./hello.out
	gnuplot -p src/fixed.ps
	gnuplot -p src/floating.ps
	gnuplot -p src/both.ps
	
	
	
matrixMul.o: $(SOURCE)matrixMulfixed.c
	gcc -c $(SOURCE)matrixMulfixed.c -o $(OBJDIR)matrixMul.o

timer.o: $(SOURCE)timer.c
	gcc -c $(SOURCE)timer.c -o $(OBJDIR)timer.o
	
clean: 
	rm -rf $(OBJDIR)*.o
	rm -rf *.out
	rm -rf $(SOURCE)*.dat
	
