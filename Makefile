all: asst1

asst1 : scannerCSVsorter.c scannerCSVsorter.h mergesort.c simpleCSVsorter.c simpleCSVsorter.h 
	gcc scannerCSVsorter.c -o output

clean:
	rm -rf output
