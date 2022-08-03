# Audio_Processing_DNN-CPP-COP290
 Implemented a deep neural network in C++ that finds the top 3 most probable words that each of the 1 second audio clips (as [1x250] input matrix) classifies to from the following 12 audio keywords (silence, unknown, yes, no, up, down, left, right, on, off, stop, go)

#### Tar file consists of::
* main.cpp
* libaudio.so
* audio.cpp
* weight_bias.h
* audioAPI.h
* makefile
* readme.md

main() function cpp file:
 ##### main.cpp

Shared library:
 ##### libaudio.so

#### *Instructions to Run::*

##### Command sequence in terminal:
* export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
* make
* ./yourcode.out audiosamplefile outputfile

The audiosamplefile name, followed by the 3 keywords with the highest probabilities, further followed by their respective probabilities would get appended in the outputfile at the end of file, at the beginning of the next line.
