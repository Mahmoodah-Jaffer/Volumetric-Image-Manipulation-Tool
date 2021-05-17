CC = g++
CCFLAGS=-std=c++11

volimage: driver.o volimage.o #making an executable file that can be run
	$(CC) $(CCFLAGS) -o volimage driver.o volimage.o 

driver.o: driver.cpp volimage.o
	$(CC) $(CCFLAGS) -c -o driver.o driver.cpp 

volimage.o: volimage.cpp volimage.h
	$(CC) $(CCFLAGS) -c -o volimage.o volimage.cpp 

run: #change command line parameters here
	./volimage MRI -d 0 10 new
clean:
	@rm -f *.o #removing object files
	@rm volimage #removing the executable produced 