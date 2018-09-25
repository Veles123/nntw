#ifndef NNTW_H_INCLUDED
#define NNTW_H_INCLUDED

#include "includs.h"


namespace ns {



template<class T> using PREF = T * &;
typedef void* PTOD;





class ex_   {
   public: string ext;
		   int ex;
	ex_() {
		this->ext = "";
		this->ex = 0;
	}
    ex_(int ir_, std::string it)
    { this->ext = it;
	this->ex = ir_;
	};
};
/*класс готов*/
//template<typename T>
class _nn : ex_  {
    public:
    int s_in;
    int l;
    int* nl;
    double ***mw;
	double *w;
	double *correctW;
    double (_nn::**act)(double);
	int q_w;
	char *cact;

	_nn(const ns::_nn &);
	//_nn(ns::_nn&);
	//_nn(ns::_nn*);
    _nn(int *l_, int* /*менял*/nl_, PREF<double> w_, char* act_, double* d, int s_in_);
	_nn(int l_, int* nl_, char tgw, int llim, int rlim, int s_in_, std::string* act_);
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
	static void* ps_str(ns::_nn*);
	loader();
	~loader();
	static int save(PTOD s_f, std::wstring, std::wstring);
	static int save(/*void*,*/ _nn*, std::wstring, std::wstring, int v);
	static ns::_nn& load( /*_nn* n,*/ std::wstring, std::wstring, int v);
private:
	

};

class Teacher {
public:
	template<typename T, typename D>
	static void* teach(ns::_nn*, std::pair<T,D>*);

private:

};



}

#endif // NNTW_H_INCLUDEd
