#include "nntw.h"

ns::_nn::_nn(int l_,  vector<double*> w_, vector<std::string> act_)   {
    this->l = l_;
    this->w = w_;
    try {
    for(int i =0 ;i < l_;i++)   {
        if (act_[i]=="relu")
        this->(act).push_back(&ns::_nn::relu);
        else if(act_[i]=="tanh")
        this->(act).push_back(&ns::_nn::tanh);
        else if(act_[i]=="sigm")
        this->(act).push_back(&ns::_nn::sigmoid);
        else throw(ex_(""));

        }
    }
    catch(ex_ er)   {
    if}


}

double ns::_nn::sigmoid(double in)   {
    return 1/(1+exp(in));
}

double ns::_nn::tanh(double in)   {
return (exp(in<<1)-1) / (exp(in<<1)+1)
}

double ns::_nn::relu(double in)   {
    return (in<=0) ? 0 : x;
}
