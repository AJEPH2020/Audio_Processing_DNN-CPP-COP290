#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "audioAPI.h"

using namespace std;


int main(int i, char **c)
{

    string sounds[] = {"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};

    string help = "._HELP_\n"
                  "      Supported command type: \n"
                  "      --> ./yourcode.out audiosamplefile.txt outputfile.txt\n";

    if (i == 3)
    {
        string inputmatrix = c[1];
        string filetype = inputmatrix.substr(inputmatrix.length() - 4, inputmatrix.length() - 1);
        ifstream ifile;
        ifile.open(inputmatrix);
        if (filetype == ".txt" && ifile)
        {

            string outputmatrix = c[2];
            string filetype = outputmatrix.substr(outputmatrix.length() - 4, outputmatrix.length() - 1);
            if (filetype == ".txt")
            {
                pred_t* pred;
	            pred=new pred_t[3];

                libaudioAPI(c[1],pred);

                // audio(inputmatrix, outputmatrix);
                ofstream out;
                out.open(outputmatrix, std::ios_base::app);

                out<<inputmatrix<<" ";

                for(int j=0;j<3;j++){
                    int x = (pred+j)->label;
	                out<<sounds[x]<<" ";
	            }

	            for(int i=0;i<3;i++){
	                out<<(pred+i)->prob<<" ";
	            }

	            out<<endl;

            }
            else
            {
                cout << "ERROR: output file type not supported, .txt required: " << outputmatrix << endl;
                cout << help << endl;
            }
        }
        else if (filetype != ".txt" && ifile)
        {
            cout << "ERROR: input file type not supported, .txt required: " << inputmatrix << endl;
            cout << help << endl;
        }
        else
        {
            cout << "ERROR: file dose not exist: " << inputmatrix << endl;
            cout << help << endl;
        }
    }
    else
    {
        cout << "ERROR: bad input: " << endl;
        cout << help << endl;
    }

    return 0;
}
