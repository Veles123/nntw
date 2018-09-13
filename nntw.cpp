#include "includs.h"
#include "nntw.h"

ns::_nn::_nn(std::string str)
{
	try {
		if (str == "for load") {
			this->nl = new int;




		}
			
		else throw ns::ex_(1, "a");
	}
	catch (ns::ex_ e) {
		1;
	}
}

ns::_nn::_nn(int l_,int* nl_,  double*** w_, vector<std::string> act_, double* corrW)   {
    this->l = l_;
    this->w = w_;
    this->nl= nl_;
	if (corrW == NULL) {
		this->correctW = new double[l];
		for (int i = 0; i < l; i++)
			this->correctW[i] = rand() + 0 % 1;
	}
	else
		this->correctW = corrW;
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
        else throw(ex_(2,"Incorrect funcion name"));

        }
    }
    catch(ex_ er)   {
    std::cerr<<er.r;
	_getch();
    }


}

ns::_nn::_nn(int l_, int* nl_, char tgw, int lim, int rlim, int s_in_, vector<std::string> act_) {
	
	//int limit = (lim == 0) ? 1 : lim;
	
	try {
		/*инициализация кол-ва слоев*/
		if (l_ > 0)
			this->l = l_;
		else
			throw ex_(5, "Количество сллоев должно быть > 0");
		/*проверка на ненулевое положительное кол-во нейронов*/

		if (s_in_ > 0)
			this->s_in = s_in_;
		else
			throw ex_(4, "Не может быть < 1 входа");

		for (int i = 0; i < l_; i++)
			if (nl_[i] > 0)
				continue;
			else
				throw ex_(3, "В слое " + std::to_string(i) + " не может быть 0 или меньше нейронов");
		/*инициализация количества нейронов*/
		this->nl = nl_;
		/*ин. акт. функ.*/
		this->cact = new char[this->l];
		double(_nn::*f)(double);
		using f_type = decltype(f);
		this->act = new f_type[l_];
		for (int i = 0; i < l_; i++) {
			if (act_[i] == "relu") {
				this->act[i] = (&ns::_nn::relu);
				this->cact[i] = 'r';
			}
			else if (act_[i] == "tanh") {
				this->act[i] = (&ns::_nn::tanh);
				this->cact[i] = 't';
			}
			else if (act_[i] == "sigm") {
				this->act[i] = (&ns::_nn::sigmoid);
				this->cact[i] = 's';
			}
			else
				throw(ex_(2 ,"Incorrect funcion name"));

		}
		this->q_w = 0;
		for (int i = 0; i < this->l; i++)
			q_w += this->nl[i];
		q_w += this->s_in;
		/*Заполнение массива весов случайными значениями*/
		
			/*Инициализация массива*/
			
			/*дебаг*/ /*Кажется отдебажено*/
			this->w = new double**[this->l];	//дебаг
			for (int i = 0; i < this->l; i++) {	//дебаг	
				this->w[i] = new double*[this->nl[i]];	//дебаг
				for (int j = 0; j < this->nl[i]; j++) {	//дебаг
					this->w[i][j] = new double[(i==0) ? this->s_in : 
														(this->nl[j])];	//дебаг
				}	//дебаг
			}	//дебаг

			/*иниц корректирующего слоя*/
			this->correctW = new double[l_];
			if (tgw == 'r') {
			/*Заполнение массива*/ /*дебаг*/
			for (int i = 0; i < this->l; i++) {
				for (int j = 0; j < this->nl[i]; j++)
					for (int k = 0; k < ((i == 0) ? this->s_in : this->nl[i - 1]); k++)
						w[i][j][k] = double(rand() % ((rlim*1000) - (lim*1000) + 1) + (lim*1000)) *0.001;
				this->correctW[i] = double(rand() % ((rlim * 1000) - (lim * 1000) + 1) + (lim * 1000)) *0.001;
			}
		}	//rand() % (b - a + 1) + a;
		else {
			throw ex_(1 ,"Неизвестный тип заполнения массива вессов \"" + std::to_string(tgw) + "\"\n");
			
		}
	}

	catch (ex_ e) {
		this->ex = e.ir;
		std::cerr << e.r;
		_getch();
		this->~_nn();
		//дописать вызовы деструкторов и т.д.
		
	}
}


double* ns::_nn::think(double* in) {
    //double a = **_nn::act(1);
	
	if (this->ex == 0) {
		double* out = new double[this->nl[1]];
		//    for(int j = 0; j< this->nl[0];j++)
		for (int i = 0; i < this->nl[0]; i++)
			out[i] = (this->*act[0])(
				this->ws(0, i, in));
		return think(out, 1);
	} 
	else { 
		std::cerr << "Error " << this->ex ;
		_getch();
		return 0; 
	}
}

ns::_nn::~_nn() {
	if (this->ex == 0) {
		for (int i = 0; i < this->l; i++) {
			delete[]this->act;
			for (int j = 0; j < this->nl[i]; i++)
				delete[]this->w[i][j];
		}
		for (int i = 0; i < this->l; i++)
			delete[]this->w[i];
		delete[]this->w;
		delete[]this->nl;
	}
	else if (this->ex == 1) {
		delete[]this->act;
		delete[]this->nl;
	}
	else if (this->ex = 2) {
		/*дописать*///////////////////////////////////////////////////
	}
	
}

double *ns::_nn::think(double* in, int l) {
    double* out = new double[ this->nl[l]];
    for(int i = 0; i < this->nl[l];i++)
          out[i] =  (this->*act[l])( this->ws(l,i,in));
    if(l<l)
        return think(out, l+1);
    else return out;
}

double ns::_nn::sum(int l, double* in)    {
    double sum = 0.0;
    for(int i = 0; i<this->nl[l-1];i++)
        sum=sum+in[i];
    return sum;
}
/*Принимает
l - номер слоя
n - номер нейрона в слое для которого нужгно подсчитать веса
in - входящие даные размером nl[l-1]*/
double ns::_nn::ws(int l, int n, double* in)    {
	double out = 0;// new double[this->nl[l]];
    //for(int i = 0; i < nl[l]; i++)
    for(int j = 0; j< ((l==0) ? this->s_in : nl[l-1]);j++)
    out+=in[j]*this->w[l][n][j];
return out + this->correctW[l];
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
/*********************************************************************************************************/
//class loader

ns::loader::loader()
{
}

ns::loader::~loader()
{
}

int ns::loader::save(/*void* file_,*/ _nn* n, std::wstring path, std::wstring name, int v)
{
	DWORD fl = 0;
	std::wstring fpath = path + name + L".ntw";
	try {
	HANDLE file_ = ::CreateFile(fpath.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (GetLastError() == ERROR_NOT_SUPPORTED)
		throw ns::ex_(6, "File not open");
	


	::SetFilePointer(file_, fl, 0, FILE_BEGIN);
	//write version
	::WriteFile(file_, &v, sizeof v, &fl, NULL);
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);
	
	//write quant layers
	::WriteFile(file_, &n->l, sizeof n->l, &fl, NULL);
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);

	//write quqnt inner
	::WriteFile(file_, &n->s_in, sizeof n->s_in, &fl, NULL);

	
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);
	
	//write quant neuron in layers
	::WriteFile(file_, &n->nl, (sizeof n->l)* n->l, &fl, NULL);
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);

	//write actfunc
	::WriteFile(file_, &n->cact, sizeof(n->cact[0])*n->l, &fl, NULL);
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);

	//write correc weight
	::WriteFile(file_, &n->correctW, (sizeof n->correctW[0])*n->l, &fl, NULL);
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);

	//write weights
	::WriteFile(file_, &n->w, (sizeof n->w[0][0][0])*n->q_w, &fl, NULL);
	::SetFilePointer(file_, fl, 0, FILE_CURRENT);

	//write ends
	byte ends = 16;
	::WriteFile(file_, &ends, sizeof ends, &fl, NULL);

	CloseHandle(file_);

	}
	catch (const ns::ex_ e) {
		std::cerr << e.r << " " << e.ir;
		_getch();
	}

	return 0;
}

int ns::loader::load( _nn *n, std::wstring path, std::wstring name, int v)
{
	try {
		std::wstring fpath = path + name + L".ntw";
		HANDLE file_ = CreateFile(fpath.c_str(),
			GENERIC_READ,
			0,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (GetLastError() == ERROR_NOT_SUPPORTED)
			throw ns::ex_(6, "File not open");
		DWORD fl = 0;
		int v = 0;
		::SetFilePointer(file_, 0, 0, FILE_BEGIN);
		::ReadFile(file_, &v, sizeof v, &fl, NULL);
		if (v != GV_LI)
			throw ns::ex_(7, "no my version");
		::SetFilePointer(file_, fl, 0, FILE_BEGIN);
		int l_ = 0;
		::ReadFile(file_, &l_, sizeof l_, &fl, NULL);
		::SetFilePointer(file_, fl, 0, FILE_CURRENT);

		int s_in_ = 0;
		::ReadFile(file_, &s_in_, sizeof s_in_, &fl, NULL);
		::SetFilePointer(file_, fl, 0, FILE_CURRENT);

		int * nl_ = new int[l_];
		::ReadFile(file_, &nl_, (sizeof nl_[0])*l_, &fl, NULL);
		::SetFilePointer(file_, fl, 0, FILE_CURRENT);

		char *cact_ = new char[l_];
		::ReadFile(file_, &cact_, sizeof(cact_[0])*l_, &fl, NULL);
		::SetFilePointer(file_, fl, 0, FILE_CURRENT);



		double *corrW_ = new double[l_];
		::ReadFile(file_, &corrW_, (sizeof corrW_[0])*l_, &fl, NULL);
		::SetFilePointer(file_, fl, 0, FILE_CURRENT);
		int qw_ = 0;
		qw_ += s_in_;
		for (int i = 0; i < l_; i++)
			qw_ += nl_[i];

		double ***w_ = new double**[l_];	//дебаг
		for (int i = 0; i < l_; i++) {	//дебаг	
			w_[i] = new double*[nl_[i]];	//дебаг
			for (int j = 0; j < nl_[i]; j++) {	//дебаг
				w_[i][j] = new double[(i == 0) ? s_in_ :
					(nl_[j])];	//дебаг
			}	//дебаг
		}

		::ReadFile(file_, &w_, sizeof(w_[0][0][0])*qw_, &fl, NULL);
		::SetFilePointer(file_, fl, 0, FILE_CURRENT);
		byte ends;
		::ReadFile(file_, &ends, sizeof ends, &fl, NULL);
		if (ends == 16) {
			n->l = l_;
			n->s_in = s_in_;
			n->q_w = qw_;
			n->nl = nl_;
			n->correctW = corrW_;
			n->w = w_;
			n->cact = cact_;
		}
		else
			throw ns::ex_(7, "Can't read network");


	}
	catch (ns::ex_ e)
	{
		std::cerr << "Error: " << e.ir << " " << e.r;
		_getch();
	}

	return 0;
}
