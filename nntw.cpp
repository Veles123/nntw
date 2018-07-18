#include "nntw.h"

ns::_nn::_nn(int l_,int* nl_,  double*** w_, vector<std::string> act_)   {
    this->l = l_;
    this->w = w_;
    this->nl= nl_;
   // this->act = new (double[this->l](double));
    double(_nn::*f)(double);
    using f_type = decltype(f);
    this->act = new f_type[l_];
    try {
    for(int i =0 ;i < l_;i++)   {
        if (act_[i]=="relu")
        this->act[i] = (&ns::_nn::relu);
        else if(act_[i]=="tanh")
        this->act[i] = (&ns::_nn::tanh);
        else if(act_[i]=="sigm")
        this->act[i] = (&ns::_nn::sigmoid);
        else throw(ex_("Incorrect funcion name"));

        }
    }
    catch(ex_ er)   {
    std::cout<<er.r;
    }


}


double* ns::_nn::think(double* in) {
    //double a = **_nn::act(1);
    double* out = new double[this->nl[1]];
    for(int i = 0; i < this->nl[1];i++)
        out[i] =  (this->*act[i])(
                            this->sum(1,
                            this->weighing(1,i,in)));
    return think(out, 1);
}

double *ns::_nn::think(double* in, int l) {
    double* out = new double[ this->nl[l]];
    for(int i = 0; i < this->nl[l];i++)
        out[i] =  (this->*act[i])(this->sum(l, this->weighing(l,i,in)));
    return think(out, l+1);
}

double ns::_nn::sum(int l, double* in)    {
    double sum = 0.0;
    for(int i = 0; i<this->nl[l-1];i++)
        sum=sum+in[i];
    return sum;
}

double* ns::_nn::weighing(int l, int n, double* in)    {
    double *out = new double[this->nl[l]];
    for(int i = 0; i < nl[l]; i++)
    for(int j = 0; j< nl[l-1];j++)
    out[i]*=this->w[l][i][j];
return out;
}


double ns::_nn::sigmoid(double in)   {
    return 1/(1+exp(in));
}

double ns::_nn::tanh(double in)   {
return (exp(in*2)-1) / (exp(in*2)+1);
}

double ns::_nn::relu(double in)   {
    return (in<=0) ? 0 : in;
}



