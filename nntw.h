#ifndef NNTW_H_INCLUDED
#define NNTW_H_INCLUDED

namespace ns {

class ex_   {
    std::string r;
    ex_(std::string i) : er = i;
}

class _nn   {
    public:
    int l;
    vector<int> nl;
    vector<double*> w;
    vector<double&> (act)(vector<double> x);

    _nn(int l_, vector<int> nl_, vector<double*> w_, vector<std::string> act_);
    vector<double> think(vector<double> in);

    private:

    vector<double> think(vector<double> in, int n);
    double sigmoid(doble in);
    double tanh(double in);
    double relu(double in);

}





}



#endif // NNTW_H_INCLUDED

