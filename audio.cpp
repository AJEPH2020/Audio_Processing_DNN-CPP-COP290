#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <mkl/mkl.h>
#include "weight_bias.h"


using namespace std;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;


typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);


float *fcMkl(int column1, int row2, int r1c2, float *inputmat, float *weightmat, float *biasmat)
{

    float *inputmatrix, *weightmatrix, *biasmatrix;
    int i;

    inputmatrix = (float *)mkl_malloc(column1 * r1c2 * sizeof(float), 64);
    weightmatrix = (float *)mkl_malloc(r1c2 * row2 * sizeof(float), 64);
    biasmatrix = (float *)mkl_malloc(column1 * row2 * sizeof(float), 64);
    if (inputmatrix == NULL || weightmatrix == NULL || biasmatrix == NULL)
    {
        mkl_free(inputmatrix);
        mkl_free(weightmatrix);
        mkl_free(biasmatrix);

        return NULL;
    }

    for (i = 0; i < (column1 * r1c2); i++)
    {
        inputmatrix[i] = inputmat[i];
    }

    for (i = 0; i < (r1c2 * row2); i++)
    {
        weightmatrix[i] = weightmat[i];
    }

    for (i = 0; i < (column1 * row2); i++)
    {
        biasmatrix[i] = biasmat[i];
    }

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, column1, row2, r1c2, 1.0, inputmatrix, r1c2, weightmatrix, row2, 1.0, biasmatrix, row2);

    float *out = new float[column1 * row2];

    for (i = 0; i < (column1 * row2); i++)
    {
        out[i] = biasmatrix[i];
    }

    mkl_free(inputmatrix);
    mkl_free(weightmatrix);
    mkl_free(biasmatrix);

    return out;
}

float *relu(int length, float *inputmat)
{
    float *inputmatrix = new float[length];

    int i;

    for (i = 0; i < length; ++i)
    {
        inputmatrix[i] = inputmat[i];
    }

    for (i = 0; i < length; ++i)
    {
        if (inputmatrix[i] < 0)
        {
            inputmatrix[i] = 0;
        }
    }

    return inputmatrix;
}

float *softmax(int length, float *inputvec)
{

    float inputvector[length];
    float *out = new float[length];

    int i, j;

    for (i = 0; i < length; ++i)
    {
        inputvector[i] = inputvec[i];
    }

    float b = 0;
    for (i = 0; i < length; ++i)
    {
        b += exp(inputvector[i]);
    }

    for (i = 0; i < length; ++i)
    {
        float a = exp(inputvector[i]);
        out[i] = a / b;
    }

    return out;
}

pred_t* libaudioAPI(const char* inputmatrix, pred_t* pred)
{
    ifstream inMat(inputmatrix);
    float inputmtrx1[250];

    for (int i = 0; i < 250; i++)
    {
        inMat >> inputmtrx1[i];
    }

    float weightmat1[] = IP1_WT;
    float biasmat1[] = IP1_BIAS;

    float *inputmtrx2;

    inputmtrx2 = fcMkl(1, 144, 250, inputmtrx1, weightmat1, biasmat1); ///////////////////////////////////////////////////////////

    


    inputmtrx2 = relu(144, inputmtrx2); ///////////////////////////////////////////////////////////

    float weightmat2[] = IP2_WT;
    float biasmat2[] = IP2_BIAS;

    float *inputmtrx3;

    inputmtrx3 = fcMkl(1, 144, 144, inputmtrx2, weightmat2, biasmat2); ///////////////////////////////////////////////////////////

    inputmtrx3 = relu(144, inputmtrx3); ///////////////////////////////////////////////////////////

    float weightmat3[] = IP3_WT;
    float biasmat3[] = IP3_BIAS;

    float *inputmtrx4;

    inputmtrx4 = fcMkl(1, 144, 144, inputmtrx3, weightmat3, biasmat3); ///////////////////////////////////////////////////////////

    inputmtrx4 = relu(144, inputmtrx4); ///////////////////////////////////////////////////////////

    float weightmat4[] = IP4_WT;
    float biasmat4[] = IP4_BIAS;

    float *outMat;

    outMat = fcMkl(1, 12, 144, inputmtrx4, weightmat4, biasmat4); ///////////////////////////////////////////////////////////

    outMat = softmax(12, outMat); ///////////////////////////////////////////////////////////


    int first;int second;int third;
    float temp1,temp2,temp3=-1;
    for(int i=0;i<12;i++){
        if(temp1<outMat[i]){
            temp1=outMat[i];
            first=i;
        }
    }
    for(int i=0;i<12;i++){
        if(temp2<outMat[i] && i!=first){
            temp2=outMat[i];
            second=i;
        }
    }
    for(int i=0;i<12;i++){
        if(temp3<outMat[i] && i!=first && i!=second){
            temp3=outMat[i];
            third=i;
        }
    }

    (pred+0)->prob=temp1;
    (pred+0)->label=first;

    (pred+1)->prob=temp2;
    (pred+1)->label=second;

    (pred+2)->prob=temp3;
    (pred+2)->label=third;


    return pred;
}
