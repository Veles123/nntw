#include "includs.h"
#include "nntw.h"

int main(){

    vector<std::string> ac;
    ac.push_back("sigm");
    ac.push_back("relu");
    ac.push_back("tanh");
    int *k = new int[3];
    k[0] = 2;
    k[1] = 2;
    k[2] = 1;
    double ***_w = new double**[3];
    *_w[0] = new double[2];
    //first layer first neur
    _w[0][0][0] = 1.0;
    _w[0][0][1] = 0.23;
    //first layer second neur
    _w[0][1][0] = 0.78;
    _w[0][1][1] = 2.5;
    //second layer first neur
    *_w[1] = new double[2];
    _w[1][0][0] = 0.45;
    _w[1][0][1] = 0.64;
    //second layer second neur
    _w[1][1][0] = 1.0;
    _w[1][1][1] = 0.3;

    *_w[2] = new double[1];
    _w[2][0][0] = 0.7;
    _w[2][0][1] = 0.2;

    ns::_nn * N = new ns::_nn(3, k, _w, ac );
    double* i = new double[2];
    i[0] = 1;
    i[1] = 3;
    std::cout << N->think(i);


return 0;
}
