#ifndef NNTW_H_INCLUDED
#define NNTW_H_INCLUDED

#include "includs.h"

namespace ns {

class ex_   {
   public: string r;
		   int ir;
    ex_(int ir_, std::string it)
    { this->r = it;
	this->ir = ir_;
	};
};
/*����� �����*/
class _nn   {
    public:
    int s_in;
    int l;
    int* nl;
    double ***w;
	double *correctW;
    double (_nn::**act)(double);
	int q_w;
	char *cact;

	_nn(std::string);
    _nn(int l_, int* nl_, double***w_, vector<std::string> act_, double* d= NULL);
	_nn(int l_, int* nl_, char tgw, int llim, int rlim, int s_in_, vector<std::string> act_);
    double *think(double* in);
	~_nn();

 private:
	 int ex = 0;
    double sum(int, double*);
    double ws(int, int, double*);
    double *think(double* in, int);
    //vector<double> think(vector<double> in, int n);
    double sigmoid(double in);
    double tanh(double in);
    double relu(double in);

};

class loader
{
public:
	loader();
	~loader();
	static int save(/*void*,*/ _nn*, std::wstring, std::wstring, int v);
	static int load( _nn* n, std::wstring, std::wstring, int v);

private:

};

}

#endif // NNTW_H_INCLUDED

