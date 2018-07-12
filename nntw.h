#ifndef NNTW_H_INCLUDED
#define NNTW_H_INCLUDED

#include "includs.h"

namespace ns {

class ex_   {
    string r;
    ex_(std::string i)
    { this->r = i;};
};

class _nn   {
    public:
    int l;
    int* nl;
    double ***w;
    double (*act)(double x);

    _nn(int l_, int* nl_, double***w_, vector<std::string> act_);
    double *think(double* in);
    double *think(double* in, int);

 private:

    double sum(int, double*);
    double* weighing(int, int, double*);
    vector<double> think(vector<double> in, int n);
    double sigmoid(double in);
    double tanh(double in);
    double relu(double in);

};

}

#endif // NNTW_H_INCLUDED

