#include "includs.h"
#include "nntw.h"

int main(){

	int *l = new int(3);
    char* ac = new char[*l];
    ac[0] = 'r';
    ac[1] = 't';
	ac[2] = 'r';
	
    //ac.push_back("tanh");
    int *k = new int[*l];
    k[0] = 3;
    k[1] = 2;
	k[2] = 2;

    double *_w = new double[19];
    //первый слой с тремя нейронами
	//_w[0] = new double*[3];

   // _w[0][0] = new double[2];
    //first layer first neur
    
	_w[0] = 0.1;
    _w[1] = 1.3;  
    _w[2] = 0.2;

    _w[3] = 0.2;
    _w[4] = 0.8;
    _w[5] = 0.1;

    _w[6] = 0.3;
    _w[7] = 0.2;
    _w[8] = 0.3;

	//
	_w[9] = 1.0;
	_w[10] = 0.5;
	_w[11] = 0.7;

	_w[12] = 1.1;
	_w[13] = 0.5;
	_w[14] = 0.7;

	//
	_w[15] = 2.0;
	_w[16] = 2.1;

	
	_w[17] = 2.1;
	_w[18] = 0.25;
	double *cor = new double[*l];
	cor[0] = 0.1;
	cor[1] = 0.2;
	cor[2] = 0.3;
	

    //ns::_nn * N = new ns::_nn(l, k, _w, ac, cor, 3 );
	

	//подборка
/*	int* t = new int[3];
	using type_a = decltype(t);
	type_a* collect = new type_a[10];
	for (int i = 0; i < 10; i++) {
		collect[i][0] = rand() % 1;
		collect[i][1] = rand() % 1;
		collect[i][2] = collect[i][0] ^ collect[i][1];
	}
	
	*/
	//ns::loader::save(N, L"", L"Dina2", GV_LI);
	//ns::_nn* P;// = new ns::_nn("for load");
	ns::_nn * P = new ns::_nn( ns::loader::load( L"", L"Dina2", GV_LI));
    double* i = new double[2];
	i[0] = 0;
    i[1] = 0;
	std::cout << *P->think(i) << "\n"<< P->think(i)[1];
	//std::cout << sizeof i[0];
	_getch();


	//delete[]i;
//	delete N;
	//P->~_nn();

return 0;
}
