#include "includs.h"
#include "nntw.h"
/*
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
*/
ns::_nn::_nn(int *l_,int* nl_,  double*& w_, char* act_, double* corrW, int s_in_)   {
	this->s_in = s_in_;
	this->l = (*l_);
	this->nl = *(new int*(nl_));//�����
	
	this->cact = new char[this->l];
	this->cact = *(new char*(act_));
	this->q_w += s_in_ * nl_[0];
	for (int i = 0; i < *l_ - 1; i++)
		this->q_w += nl_[i] * nl_[i + 1];
	this->w = new double[this->q_w];//((new double*((mw_))));//
	this->w = (double*)w_;
	double *tpw = this->w;
	this->mw = new double**[this->l];	//�����
	for (int i = 0; i < this->l; i++) {	//�����	 ��� �� �����
		this->mw[i] = new double*[this->nl[i]];	//�����
		int s_t = (i == 0) ? this->s_in :
			(this->nl[i - 1]);
		for (int j = 0; j < this->nl[i]; j++) {	//����� ��� �� ��������
			
			this->mw[i][j] = new double[s_t];
			this->mw[i][j] = (double*)tpw;
			tpw += s_t;//+= sizeof(*tpw)*s_t);	//�����
			//for (int k = 0; k < (this->nl[((i == 0) ? this->s_in : i - 1)]); k++)  //��� �� �����
				//this->mw[i][j][k] = tpw++;
		}	//�����
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
    std::cerr<<er.r;
	_getch();
    }


}

ns::_nn::_nn(int l_, int* nl_, char tgw, int lim, int rlim, int s_in_, std::string* act_) {
	
	//int limit = (lim == 0) ? 1 : lim;
	
	try {
		/*������������� ���-�� �����*/
		if (l_ > 0)
			this->l = l_;
		else
			throw ex_(5, "���������� ������ ������ ���� > 0");
		/*�������� �� ��������� ������������� ���-�� ��������*/

		if (s_in_ > 0)
			this->s_in = s_in_;
		else
			throw ex_(4, "�� ����� ���� < 1 �����");

		for (int i = 0; i < l_; i++)
			if (nl_[i] > 0)
				continue;
			else
				throw ex_(3, "� ���� " + std::to_string(i) + " �� ����� ���� 0 ��� ������ ��������");
		/*������������� ���������� ��������*/
		this->nl = nl_;
		/*��. ���. ����.*/
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
		
		/*���������� ������� ����� ���������� ����������*/
		
			/*������������� �������*/
			
			/*�����*/ /*������� ����������*/
			this->mw = new double**[this->l];	//�����
			for (int i = 0; i < this->l; i++) {	//�����	
				this->mw[i] = new double*[this->nl[i]];	//�����
				for (int j = 0; j < this->nl[i]; j++) {	//�����
					this->mw[i][j] = new double[(i==0) ? this->s_in : 
														(this->nl[j])];	//�����
				}	//�����
			}	//�����

			/*���� ��������������� ����*/
			this->correctW = new double[l_];
			if (tgw == 'r') {
			/*���������� �������*/ /*�����*/
			for (int i = 0; i < this->l; i++) {
				for (int j = 0; j < this->nl[i]; j++)
					for (int k = 0; k < ((i == 0) ? this->s_in : this->nl[i - 1]); k++)
						mw[i][j][k] = double(rand() % ((rlim*1000) - (lim*1000) + 1) + (lim*1000)) *0.001;
				this->correctW[i] = double(rand() % ((rlim * 1000) - (lim * 1000) + 1) + (lim * 1000)) *0.001;
			}
		}	//rand() % (b - a + 1) + a;
		else {
			throw ex_(1 ,"����������� ��� ���������� ������� ������ \"" + std::to_string(tgw) + "\"\n");
			
		}
	}

	catch (ex_ e) {
		this->ex = e.ir;
		std::cerr << e.r;
		_getch();
		this->~_nn();
		//�������� ������ ������������ � �.�.
		
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
	if ((this)->ex == 0) {
		for (int i = 0; i < this->l; i++) {
			delete[]this->act;
			for (int j = 0; j < this->nl[i]; i++)
				delete[]this->mw[i][j];
		}
		for (int i = 0; i < this->l; i++)
			delete[]this->mw[i];
		delete[]this->mw;
		delete[]this->nl;
		delete[]this->w;
	}
	else if (this->ex == 1) {
		delete[]this->act;
		delete[]this->nl;
	}
	else if (this->ex = 2) {
		/*��������*///////////////////////////////////////////////////
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
/*���������
l - ����� ����
n - ����� ������� � ���� ��� �������� ������ ���������� ����
in - �������� ����� �������� nl[l-1]*/
double ns::_nn::ws(int l, int n, double* in)    {
	double out = 0;// new double[this->nl[l]];
    //for(int i = 0; i < nl[l]; i++)
    for(int j = 0; j< ((l==0) ? this->s_in : nl[l-1]);j++)
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

ns::loader::loader()
{
}

ns::loader::~loader()
{
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
		std::cerr << e.r << " " << e.ir;
		_getch();
	}
	//std::cout << ((double*)w_)[0] <<" " << ((double*)w_)[0];
	return 0;
}

ns::_nn* ns::loader::load(/* _nn *n,*/ std::wstring path, std::wstring name, int v)
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
		if ((GetLastError() == ERROR_NOT_SUPPORTED)||(file_ == INVALID_HANDLE_VALUE))
			throw ns::ex_(6, "File not open");
		DWORD mfl = 0;
		DWORD fl = 0;
		int v = 5;
		::SetFilePointer(file_, 0, 0, FILE_BEGIN);
		::ReadFile(file_, &v, sizeof v, &fl, NULL);
		if (v != GV_LI)
			throw ns::ex_(7, "no my version");
		::SetFilePointer(file_, fl, 0, FILE_BEGIN);
		 
		::ReadFile(file_, l_, sizeof (*l_), &fl, NULL);
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
		qw_ += s_in_*nl_[0];
		for (int i = 0; i < *l_ - 1; i++)
			qw_ += nl_[i] * nl_[i+1];
		
		
		w_ = new double[qw_];	//�����
	/*	for (int i = 0; i < *l_; i++) {	//�����	
			w_[i] = new double*[nl_[i]];	//�����
			for (int j = 0; j < nl_[i]; j++) {	//�����
				w_[i][j] = new double[(i == 0) ? s_in_ :
					(nl_[j])];	//�����
			}	//�����
		}*/

		::ReadFile(file_, (w_), sizeof(*w_)*qw_, &fl, NULL);
		::SetFilePointer(file_, mfl, 0, FILE_CURRENT);
		byte ends = 0;
		::ReadFile(file_, &ends, sizeof ends, &fl, NULL);
		if (ends == 16) {
		/*	n->l = l_;
			n->s_in = s_in_;
			n->q_w = qw_;
			n->nl = nl_;
			n->correctW = corrW_;
			n->w = w_;
			n->cact = cact_;
			*/
			ac_ = new char[*l_];
			for (int i = 0; i < *l_; i++)
				ac_[i] = cact_[i];
			

		}
		else
			throw ns::ex_(7, "Can't read network");

		return  new ns::_nn(l_, nl_,/* (double*&)*/w_, ac_, corrW_, s_in_);
	}
	catch (ns::ex_ e)
	{
		std::cerr << "Error: " << e.ir << " " << e.r;
		_getch();
	}

	//return 0;
}
