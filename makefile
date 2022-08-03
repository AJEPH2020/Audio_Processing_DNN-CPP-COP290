all:
	g++ -fopenmp libaudio.cpp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -o yourcode.out
	./yourcode.out 3c257192_nohash_3.txt output.txt