#ifndef NNTW_H_INCLUDED
#define NNTW_H_INCLUDED

#include "includs.h"

namespace ns {

class ex_   {
   public: string r;
    ex_(std::string i)
    { this->r = i;};
};

class _nn   {
    public:
    int s_in;
    int l;
    int* nl;
    double ***w;
    double (_nn::**act)(double);

    _nn(int l_, int* nl_, double***w_, vector<std::string> act_);
    double *think(double* in);


 private:

    double sum(int, double*);
    double* weighing(int, int, double*);
    double *think(double* in, int);
    //vector<double> think(vector<double> in, int n);
    double sigmoid(double in);
    double tanh(double in);
    double relu(double in);

};

}

#endif // NNTW_H_INCLUDED

