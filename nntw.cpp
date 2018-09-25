#include "includs.h"
#include "nntw.h"


/*конструкторы*/
///////////////////////////////////////////////////////////////////////////////
ns::_nn::_nn(const ns::_nn &n)
{
	try {
		this->l = n.l;
		this->nl = new int[l];
		this->s_in = n.s_in;

		this->q_w = n.q_w;
		this->w = new double[this->q_w];//((new double*((mw_))));//
		for (int i = 0; i < this->q_w; i++)
			this->w[i] = n.w[i];
		double *tpw = this->w;
		this->mw = new double**[this->l];	//дебаг
		for (int i = 0; i < this->l; i++) {	//дебаг	 бек по слоям
			this->nl[i] = n.nl[i]; //
			this->mw[i] = new double*[this->nl[i]];	//дебаг
			int s_t = ((sizeof(double))*(i == 0) ? this->s_in :
				(this->nl[i - 1]));
			for (int j = 0; j < this->nl[i]; j++) {	//дебаг бег по нецронам

				this->mw[i][j] = new double[s_t];
				this->mw[i][j] = (double*)tpw;
				tpw += s_t;
			}
		}

		this->correctW = new double[this->l];

		this->cact = new char[this->l];
		double(_nn::*f)(double);
		using f_type = decltype(f);
		this->act = new f_type[(int)this->l];
		for (int i = 0; i < this->l; i++) {
			this->correctW[i] = n.correctW[i];
			this->cact[i] = n.cact[i];
			if (n.cact[i] == 'r')
				this->act[i] = (&ns::_nn::relu);
			else if (this->cact[i] == 't')
				this->act[i] = (&ns::_nn::tanh);
			else if (this->cact[i] == 's')
				this->act[i] = (&ns::_nn::sigmoid);
			else throw(ex_(2, "Incorrect funcion name"));
		}
	}
	catch (ns::ex_ e) {
		std::cerr << e.ext;
		_getch();
	}

}
/*
///////////////////////////////////////////////////////////////////////////////
ns::_nn::_nn(ns::_nn& n) {
	try {
		this->l = n.l;
		this->nl = new int[l];
		this->s_in = n.s_in;
		for (int i = 0; i < this->l; i++)
			this->nl[i] = n.nl[i];
		this->q_w += this->s_in * this->nl[0];
		for (int i = 0; i < (this->l - 1); i++)
			this->q_w += this->nl[i] * (this->nl[i + 1]);
		this->w = new double[this->q_w];//((new double*((mw_))));//
		for (int i = 0; i < this->q_w; i++)
			this->w[i] = n.w[i];
		double *tpw = this->w;
		this->mw = new double**[this->l];	//дебаг
		for (int i = 0; i < this->l; i++) {	//дебаг	 бек по слоям
			this->mw[i] = new double*[this->nl[i]];	//дебаг
			int s_t = (i == 0) ? this->s_in :
				(this->nl[i - 1]);
			for (int j = 0; j < this->nl[i]; j++) {	//дебаг бег по нецронам

				this->mw[i][j] = new double[s_t];
				this->mw[i][j] = (double*)tpw;
				tpw += s_t;
			}
		}

		this->correctW = new double[this->l];

		this->cact = new char[this->l];
		double(_nn::*f)(double);
		using f_type = decltype(f);
		this->act = new f_type[(int)this->l];
		for (int i = 0; i < this->l; i++) {
			this->correctW[i] = n.correctW[i];
			this->cact[i] = n.cact[i];
			if (n.cact[i] == 'r')
				this->act[i] = (&ns::_nn::relu);
			else if (this->cact[i] == 't')
				this->act[i] = (&ns::_nn::tanh);
			else if (this->cact[i] == 's')
				this->act[i] = (&ns::_nn::sigmoid);
			else throw(ex_(2, "Incorrect funcion name"));
		}
	}
	catch (ns::ex_ e) {
		std::cerr << e.r;
		_getch();
	}

}

*/
///////////////////////////////////////////////////////////////////////////////
/*
ns::_nn::_nn(ns::_nn* n) {
	try {
		this->l = (n->l);
		this->nl = new int[l];
		this->s_in = n->s_in;
		for (int i = 0; i < this->l; i++)
			this->nl[i] = n->nl[i];
		this->q_w += this->s_in * this->nl[0];
		for (int i = 0; i < (this->l - 1); i++)
			this->q_w += this->nl[i] * (this->nl[i + 1]);
		this->w = new double[this->q_w];//((new double*((mw_))));//
		for (int i = 0; i < this->q_w; i++)
			this->w[i] = n->w[i];
		double *tpw = this->w;
		this->mw = new double**[this->l];	//дебаг
		for (int i = 0; i < this->l; i++) {	//дебаг	 бек по слоям
			this->mw[i] = new double*[this->nl[i]];	//дебаг
			int s_t = (i == 0) ? this->s_in :
				(this->nl[i - 1]);
			for (int j = 0; j < this->nl[i]; j++) {	//дебаг бег по нецронам

				this->mw[i][j] = new double[s_t];
				this->mw[i][j] = (double*)tpw;
				tpw += s_t;
			}
		}

		this->correctW = new double[this->l];

		this->cact = new char[this->l];
		double(_nn::*f)(double);
		using f_type = decltype(f);
		this->act = new f_type[(int)this->l];
		for (int i = 0; i < this->l; i++) {
			this->correctW[i] = n->correctW[i];
			this->cact[i] = n->cact[i];
			if (n->cact[i] == 'r')
				this->act[i] = (&ns::_nn::relu);
			else if (this->cact[i] == 't')
				this->act[i] = (&ns::_nn::tanh);
			else if (this->cact[i] == 's')
				this->act[i] = (&ns::_nn::sigmoid);
			else throw(ex_(2, "Incorrect funcion name"));
		}
	}
	catch (ns::ex_ e) {
		std::cerr << e.r;
		_getch();
	}

}

*/
///////////////////////////////////////////////////////////////////////////////
ns::_nn::_nn(int *l_/*количество слоев*/,
	int* nl_/*количество нейронов в лое n где n < l*/,
	PREF<double> w_/*линейный массив весов*/, 
	char* act_/*активационные функции*/, 
	double* corrW/*корректирующи веса*/,
	int s_in_ /*количество входов*/)   {
	this->s_in = s_in_;
	this->l = (*l_);
	this->nl = *(new int*(nl_));//менял
	
	this->cact = new char[this->l];
	this->cact = *(new char*(act_));
	this->q_w += s_in_ * nl_[0];
	for (int i = 0; i < *l_ - 1; i++)
		this->q_w += nl_[i] * nl_[i + 1];
	this->w = new double[this->q_w];//((new double*((mw_))));//
	this->w = (double*)w_;
	double *tpw = this->w;
	this->mw = new double**[this->l];	//дебаг
	for (int i = 0; i < this->l; i++) {	//дебаг	 бек по слоям
		this->mw[i] = new double*[this->nl[i]];	//дебаг
		int s_t = (sizeof (double) * (i == 0) ? this->s_in :
			(this->nl[i - 1]));
		for (int j = 0; j < this->nl[i]; j++) {	//дебаг бег по нецронам
			
			(this->mw[i][j] = new double[s_t]) = (double*)tpw;
			//this->mw[i][j] = (double*)tpw;
			tpw += s_t;//+= sizeof(*tpw)*s_t);	//дебаг
			//for (int k = 0; k < (this->nl[((i == 0) ? this->s_in : i - 1)]); k++)  //бег по весам
				//this->mw[i][j][k] = tpw++;
		}	//дебаг
	}



	if (corrW == NULL) {
		this->correctW = new double[l];
		for (int i = 0; i < l; i++)
			this->correctW[i] = rand() + 0 % 1;
	}
	else
		this->correctW = *(new double*(corrW));
   // this->act = new (double[this->l](double));
    double(_nn::*f)(double);
    using f_type = decltype(f);
    this->act = new f_type[*l_];
    try {
    for(int i =0 ;i < *l_;i++)   {
		if (act_[i] == 'r') 
			this->act[i] = (&ns::_nn::relu);
        else if(act_[i]=='t')
        this->act[i] = (&ns::_nn::tanh);
        else if(act_[i]=='s')
        this->act[i] = (&ns::_nn::sigmoid);
        else throw(ex_(2,"Incorrect funcion name"));

        }
    }
    catch(ex_ er)   {
    std::cerr<<er.ext;
	_getch();
    }


}
///////////////////////////////////////////////////////////////////////////////
ns::_nn::_nn(int l_, int* nl_, char tgw, int lim, int rlim, int s_in_, std::string* act_) {
	
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
			if (act_[i] == "r") {
				this->act[i] = (&ns::_nn::relu);
				this->cact[i] = 'r';
			}
			else if (act_[i] == "t") {
				this->act[i] = (&ns::_nn::tanh);
				this->cact[i] = 't';
			}
			else if (act_[i] == "s") {
				this->act[i] = (&ns::_nn::sigmoid);
				this->cact[i] = 's';
			}
			else
				throw(ex_(2 ,"Incorrect funcion name"));

		}
		this->q_w = 0;
		this->q_w += this->s_in*nl[0];
		for (int i = 0; i < (this->l-1); i++)
			this->q_w += (this->nl[i])*(this->nl[i+1]);
		
		/*Заполнение массива весов случайными значениями*/
		
			/*Инициализация массива*/
			
			/*дебаг*/ /*Кажется отдебажено*/
			this->mw = new double**[this->l];	//дебаг
			for (int i = 0; i < this->l; i++) {	//дебаг	
				this->mw[i] = new double*[this->nl[i]];	//дебаг
				for (int j = 0; j < this->nl[i]; j++) {	//дебаг
					this->mw[i][j] = new double[(i==0) ? this->s_in : 
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
						mw[i][j][k] = double(rand() % ((rlim*1000) - (lim*1000) + 1) + (lim*1000)) *0.001;
				this->correctW[i] = double(rand() % ((rlim * 1000) - (lim * 1000) + 1) + (lim * 1000)) *0.001;
			}
		}	//rand() % (b - a + 1) + a;
		else {
			throw ex_(1 ,"Неизвестный тип заполнения массива вессов \"" + std::to_string(tgw) + "\"\n");
			
		}
	}

	catch (ex_ e) {
		//this->ex;// = e.ir;
		std::cerr << e.ext;
		_getch();
		this->~_nn();
		//дописать вызовы деструкторов и т.д.
		
	}
}

double* ns::_nn::think(double* in) {
    //double a = **_nn::act(1);
	try {
		/*if ((sizeof T )> sizeof double) {
			this->ex = 10;
			this->ext = "very Bigg data";
			throw ns::ex_(this->ex, this->ext);
		}*/
		if (this->ex == 0) {
			double* out = new double[this->nl[1]];
			//    for(int j = 0; j< this->nl[0];j++)
			for (int i = 0; i < this->nl[0]; i++)
				out[i] = (this->*act[0])(
					this->ws(0, i, (double*)in));
			return think(out, 1);
		}
		else
			throw ns::ex_(this->ex, this->ext);
	}
		catch (ns::ex_ e) {
			std::cerr << "Error " << this->ex;
			_getch();
			//return e.ex;
		}
	
		return 0;
}

ns::_nn::~_nn() {
	if ((this)->ex == 0) {
		for (int i = 0; i < this->l; i++) {
			delete[]this->act;
			for (int j = 0; j < this->nl[i]; i++)
				delete[]this->mw[i][j];
		}
		for (int i = 0; i < this->l; i++) {
			int s_t = (i == 0) ? this->s_in :
				(this->nl[i - 1]);
			for (int j = 0; j < s_t;j++)
				delete[]this->mw[i][j];
		}
		delete[]this->mw;
		delete[]this->nl;
		delete[]this->w;
	}
	else if (this->ex == 1) {
		delete[]this->act;
		delete[]this->nl;
	}
	else if (this->ex = 2) {
		/*дописать*///////////////////////////////////////////////////
	}
	
}

double *ns::_nn::think(double* in, int l_) {
    double* out = new double[ this->nl[l_]];
    for(int i = 0; i < this->nl[l_];i++)
          out[i] =  (this->*act[l_])( this->ws(l_,i,in));
    if(l_<this->l-1)
        return think(out, l_+1);
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
	int s_t = ((l == 0) ? this->s_in : nl[l - 1]);
    for(int j = 0; j< s_t;j++)
    out+=in[j]*(this->mw[l][n][j]);
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

void * ns::loader::ps_str(/*PTOD in,*/ ns::_nn * n)
{
	PTOD in;
	size_t so = 0;
	so += sizeof(int) * 3 + sizeof(int)*n->l + sizeof(double)*n->l + sizeof(char)*n->l + sizeof(double)*n->q_w;
	in = (PTOD) malloc(sizeof(size_t)+so);
	if (in == NULL)
		return nullptr;
	PTOD vtd = in;
	*(size_t*)vtd = so;
	((size_t&)vtd) += sizeof(size_t);

	*(int*)vtd = GV_LI;
	((int&)vtd)+= sizeof(int);

	*(int*)vtd = n->l;
	((int&)vtd) += sizeof(int);

	*(int*)vtd = n->s_in;
	((int&)vtd) += sizeof(int);
	for(int i = 0; i < n->l; i++) {
		*(int*)vtd = n->nl[i];
		((int&)vtd) += sizeof(int);
	}
	for (int i = 0; i < n->l; i++) {
		*(char*)vtd = n->cact[i];
		((char&)vtd) += sizeof(char);
	}
	for (int i = 0; i < n->l; i++) {
		*(double*)vtd = n->correctW[i];
		((char&)vtd) += sizeof(double);
	}
	for (int i = 0; i < n->q_w; i++) {
		*(double*)vtd = n->w[i];
		((char&)vtd) += sizeof(double);
	}
	*(byte*)vtd = 16;

	return in;
}

ns::loader::loader()
{
}

ns::loader::~loader()
{
}

int ns::loader::save(PTOD s_f, std::wstring path, std::wstring name)
{
	DWORD mfl = 0;
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
		if ((GetLastError() == ERROR_NOT_SUPPORTED) || file_ == INVALID_HANDLE_VALUE)
			throw ns::ex_(6, "File not open");

		::SetFilePointer(file_, fl, 0, FILE_BEGIN);

		size_t ts = 0;
		ts = *(size_t*)s_f;
		PTOD tps_f = s_f;
		((size_t&)tps_f) -= sizeof(size_t);
		::WriteFile(file_, tps_f, ts, &fl, NULL);
		CloseHandle(file_);
	}
	
	catch (const ns::ex_ e) {
		std::cerr << e.ex << " " << e.ext;
		_getch();
	}

	return 0;
}

int ns::loader::save(/*void* file_,*/ _nn* n, std::wstring path, std::wstring name, int v)
{
	DWORD mfl = 0;
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
	if ((GetLastError() == ERROR_NOT_SUPPORTED)||file_ == INVALID_HANDLE_VALUE)
		throw ns::ex_(6, "File not open");
	
	::SetFilePointer(file_, fl, 0, FILE_BEGIN);
	//write version
	::WriteFile(file_, &v, sizeof v, &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);
	
	//write quant layers
	::WriteFile(file_, &n->l, sizeof n->l, &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);
	
	//write quqnt inner
	::WriteFile(file_, &n->s_in, sizeof n->s_in, &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);
	
	//write quant neuron in layers
	::WriteFile(file_, n->nl, ((sizeof n->l)* n->l), &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

	//write actfunc
	::WriteFile(file_, n->cact, (sizeof(n->cact[0])*(n->l)), &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

	//write correc weight
	::WriteFile(file_, n->correctW, (sizeof n->correctW[0])*(n->l), &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

	//write weights
	::WriteFile(file_, n->w, sizeof(*n->w)*n->q_w, &fl, NULL);
	::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

	//write ends
	byte ends = 16;
	::WriteFile(file_, &ends, sizeof ends, &fl, NULL);	
	CloseHandle(file_);
	}
	catch (const ns::ex_ e) {
		std::cerr << e.ex << " " << e.ext;
		_getch();
	}
	return 0;
}

ns::_nn& ns::loader::load(/* _nn *n,*/ std::wstring path, std::wstring name, int v)
{
	try {
		int *nl_;
		double *corrW_;
		double *w_;
		int *l_ = new int(0);
		int s_in_;
		char *cact_;
		char* ac_;
		std::wstring fpath = path + name + L".ntw";
		HANDLE file_ = CreateFile(fpath.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if ((GetLastError() == ERROR_NOT_SUPPORTED) || (file_ == INVALID_HANDLE_VALUE))
			throw ns::ex_(6, "File not open");
		DWORD mfl = 0;
		DWORD fl = 0;
		int v = 5;
		::SetFilePointer(file_, 0, 0, FILE_BEGIN);
		::ReadFile(file_, &v, sizeof v, &fl, NULL);
		if (v != GV_LI)
			throw ns::ex_(7, "no my version");
		::SetFilePointer(file_, fl, 0, FILE_BEGIN);

		::ReadFile(file_, l_, sizeof(*l_), &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

		s_in_ = 0;
		::ReadFile(file_, &s_in_, sizeof s_in_, &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

		nl_ = new int[(*l_)];
		::ReadFile(file_, *(&nl_), (sizeof nl_[0])*(*l_), &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

		cact_ = new char[*l_];
		for (int i = 0; i < *l_; i++)
			cact_[i] = 0;
		::ReadFile(file_, *&cact_, sizeof(cact_[0])*(*l_), &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);

		corrW_ = new double[*l_];
		//std::cout << sizeof(corrW_[0])*l_;
		::ReadFile(file_, *&corrW_, ((sizeof(corrW_[0]))*(*l_)), &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);
		int qw_ = 0;
		qw_ += s_in_ * nl_[0];
		for (int i = 0; i < *l_ - 1; i++)
			qw_ += nl_[i] * nl_[i + 1];

		w_ = new double[qw_];
		::ReadFile(file_, (w_), sizeof(*w_)*qw_, &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);
		byte ends = 0;
		::ReadFile(file_, &ends, sizeof ends, &fl, NULL);
		if (ends == 16) {
			ac_ = new char[*l_];
			for (int i = 0; i < *l_; i++)
				ac_[i] = cact_[i];
		}
		else
			throw ns::ex_(7, "Can't read network");
		ns::_nn* O = (new  ns::_nn(l_, nl_,/* (double*&)*/w_, ac_, corrW_, s_in_));
		return *O;
	}
	catch (ns::ex_ &e)
	{
		std::cerr << "Error: " << e.ex << " " << e.ext;
		_getch();
		//return ns::ex_(e);
	}

}

template<typename T, typename D>
inline void * ns::Teacher::teach(ns::_nn *, std::pair<T, D>*)
	{
		return NULL;
	}

	//return 0;

