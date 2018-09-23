#include "includs.h"
#include "nntw.h"

int main(){

    char* ac = new char[2];
    ac[0] = 'r';
    ac[1] = 't';
    //ac.push_back("tanh");
    int *k = new int[2];
    k[0] = 3;
    k[1] = 1;

    double *_w = new double[9];
    //первый слой с тремя нейронами
	//_w[0] = new double*[3];

   // _w[0][0] = new double[2];
    //first layer first neur
    _w[0]/*[0][0]*/ = 0.5;
    _w/*[0][0]*/[1] = 1.3;
    //first layer second neur
  //  _w[0][1] = new double[2];
    _w/*[0][1]*/[2] = 0.2;
    _w/*[0][1]*/[3] = 0.8;

    //_w[0][2] = new double[2];
    _w/*[0][2]*/[4] = 0.8;
    _w/*[0][2]*/[5] = 0.1;
    //second layer first neur
 //   _w[1] = new double*[1];
   // _w[1][0] = new double[3];
    _w/*[1][0]*/[6] = 0.2;
    _w/*[1][0]*/[7] = 0.2;
    _w/*[1][0]*/[8] = 0.3;


	double *cor = new double[2];
	cor[0] = 0.3;
	cor[1] = 0.3;
	int *l = new int(2);

   // ns::_nn * N = new ns::_nn(l, k, _w, ac, cor, 2 );
	
	
	
	//ns::loader::save(/*f,*/ N, L"", L"Dina", GV_LI);
	ns::_nn* P;// = new ns::_nn("for load");
	P = ns::loader::load(/*P,*/ L"", L"Dina", GV_LI);

    double* i = new double[2];
    i[0] = 0;
    i[1] = 0;
	std::cout << P->think(i)[0];
	//std::cout << sizeof i[0];
	_getch();


	delete[]i;
//	delete N;
	//delete[] P;

return 0;
}
