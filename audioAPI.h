#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <mkl/mkl.h>
#include "weight_bias.h"

using namespace std;

#ifndef LIBAUDIOAPI_H
#define LIBAUDIOAPI_H

typedef struct{
int label;
float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

#endif
