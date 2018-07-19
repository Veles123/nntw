#include "includs.h"
#include "nntw.h"

int main(){

    vector<std::string> ac;
    ac.push_back("sigm");
    ac.push_back("relu");
    ac.push_back("tanh");
    int *k = new int[2];
    k[0] = 3;
    k[1] = 1;

    double ***_w = new double**[2];
    _w[0] = new double*[3];
    _w[0][0] = new double[2];
    //first layer first neur
    _w[0][0][0] = 0.5;
    _w[0][0][1] = 1.3;
    //first layer second neur
    _w[0][1] = new double[2];
    _w[0][1][0] = 0.2;
    _w[0][1][1] = 0.8;

    _w[0][2] = new double[2];
    _w[0][2][0] = 1.0;
    _w[0][2][1] = 0.1;
    //second layer first neur
    _w[1] = new double*[1];
    _w[1][0] = new double[3];
    _w[1][0][0] = 0.2;
    _w[1][0][1] = 0.2;
    _w[1][0][2] = 0.3;

    ns::_nn * N = new ns::_nn(3, k, _w, ac );
    N->s_in = 2;
    double* i = new double[2];
    i[0] = 1;
    i[1] = 1;
    cout << N->think(i);



return 0;
}
