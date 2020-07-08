#include "Polynomial.h"

Polynomial::Polynomial(double coefficients[], int number) : deg(number)
{
	try
	{
		this->coef = new double[this->deg];
	}
	catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= this->deg; i++) {
		coef[i] = coefficients[i];
	}
}

Polynomial::Polynomial(Polynomial &ob) {
	this->deg = ob.deg;
	try
	{
		this->coef = new double[this->deg];
	}
	catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= deg; i++)
	{
		this->coef[i] = ob.coef[i];
	}
}

Polynomial::~Polynomial() {
	if (this->coef != nullptr)				//verific daca pointerul catre vectorul de coeficienti nu pointeaza spre o zona null
		for (int i = this->deg; i > 0; i--)
			this->delCoef(i);
	this->deg = 0;
}

Polynomial& Polynomial::operator = (const Polynomial& obj)
{
	if (this != &obj)								//Testing to avoid situations like A = A;
	{	
		this->deg = obj.deg;
		try
		{
			this->coef = new double[this->deg];
		}
		catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i <= obj.deg; i++)
			this->coef[i] = obj.coef[i];
	}
	return *this;
}

istream& operator >> (istream& in, Polynomial& obj) 
{ 
	cout << "Introduceti gradul polinomului : ";
	in >> obj.deg;
	cout << endl;
	try
	{
		obj.coef = new double[obj.deg];
	}
	catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= obj.deg; i++)
	{
		cout << "Introduceti coeficientul de grad " << i << " al polinomului:";
		in >> obj.coef[i];
		cout << endl;
	}
	return in;
}

ostream& operator << (ostream& out, const Polynomial& obj) 
{
	out << "Gradul polinomului introdus este de " << obj.deg << endl;
	out << "Polinomul este de forma : ";
	for (int i = 0; i <= obj.deg; i++)
	{	
		if (obj.coef[i] != 0)
		{
			if (obj.coef[i] < 0)
				out << '(' << obj.coef[i] << ')';
			else
				out << obj.coef[i];
			if (i > 1)
				out << "*x^" << i;
			if (i == 1)
				out << "*x";
			if (i != obj.deg)
				out << " + ";
		}
	}
	out << endl <<endl;
	return out;
}

Polynomial Polynomial::operator+ (const Polynomial& obj) const
{
	Polynomial aux;

	if (obj.deg >= deg)
	{
		aux.deg = obj.deg;
		try
		{
			aux.coef = new double[obj.deg];
		}
		catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i <= deg; i++)
			aux.coef[i] = obj.coef[i] + coef[i];

		for (int i = deg + 1; i <= obj.deg; i++)
			aux.coef[i] = obj.coef[i];
	}
	else // obj.deg < this->deg
	{
		aux.deg = deg;
		try
		{
			aux.coef = new double[deg];
		}
		catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i <= obj.deg; i++)
		{
			aux.coef[i] = obj.coef[i] + coef[i];
		}

		for (int i = obj.deg + 1; i <= deg; i++)
		{
			aux.coef[i] = coef[i];
		}
	}
	
	return aux;
}

double Polynomial::operator[] (const unsigned int pos) const
{
	if (pos > this->deg) {
		throw std::out_of_range("Index mai mare ca dimensiunea polinomului");
	}
	return this->coef[pos];
}

Polynomial Polynomial::operator * (const int scalar) const
{
	Polynomial aux;
	aux.deg = this->deg;
	try
	{
		aux.coef = new double[aux.deg];
	}
	catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= aux.deg; i++)
		aux.coef[i] = this->coef[i] * scalar;			//înmulțesc fiecare coeficient cu scalarul și îl salvez.
	return aux;
}

Polynomial operator * (const int &scalar, const Polynomial &obj) 
{
	return obj*scalar;	//înmulțirea fiind comutativă, apeleze înmulțirea cu scalarul invers și o returnez.
}

Polynomial Polynomial::operator * (const Polynomial& obj) const
{
	Polynomial aux;
	aux.deg = obj.deg + this->deg;				//Polinomul returnat o sa aiba gradul egal cu gradul primului termen adunat cu gradul celui de al doilea
	try
	{
		aux.coef = new double[aux.getDeg()];
	}
	catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
	{
		cout << " Allocation Failure ";
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i <= aux.getDeg(); i++)
		aux.addCoef(0, i);						//Pun 0 pe fiecare pozitie in polinomul final				

	for (int i = 0; i <= this->deg; i++)
		for (int j = 0; j <= obj.deg; j++)
			aux.coef[i+j] += (this->coef[i]) * obj.coef[j];		//Pe fiecare pozitie adun termenii ce rezulta din inmultirea fiecarui termen cu fiecare ai caror suma a pozitiilor corespunde.
	
	return aux;
}

Polynomial operator / (Polynomial obj1, Polynomial& obj2)
{
	if ((obj2.getDeg() == 0 && obj2.coef[0] == 0))					//Daca al doilea polinom este 0 (deg = 0 si coef[0] = 0) atunci arunc exceptia -1; (impartirea la 0 nu are sens)
	{
		throw - 1;
	}
	else if ((obj1.getDeg() == 0 && obj1.coef[0] == 0) || obj1.getDeg() < obj2.getDeg())
	{
		return Polynomial();										  // Daca obj1 este null sau obj1 are gradul mai mic decat obj2, atunci returnez un polinom gol
	}
	else if (obj1.getDeg() >= obj2.getDeg())						  // Cazul in care gradul lui obj1 este mai mare sau egal
	{
		Polynomial objFinal;										  // objFinal reprezinta catul care va fi returnat.
		objFinal.deg = obj1.getDeg() - obj2.getDeg();				  // gradul catului va fi diferenta gradelor celor doua polinoame
		try
		{
			objFinal.coef = new double[objFinal.deg];
		}
		catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		for (int i = objFinal.getDeg(); i >= 0; i--)				  // parcurg vectorul coeficientilor catului
		{
			objFinal.coef[i] = obj1.coef[obj1.deg] / obj2.coef[obj2.getDeg()]; // impartirt pentru a determina valoarea coeficientului
			for (int j = obj2.getDeg(); j >= 0; j--)					   	   // scad din primul obiect gradele celui de al doilea
			{
				obj1.coef[j + i] -= objFinal.coef[i] * obj2.coef[j];
			}
			obj1.deg--;
			while (obj1.coef[obj1.deg] == 0)								   // scad gradul polinomului pentru a nu avea 0-uri degeaba in el
			{
				obj1.deg--;
			}
		}
		return objFinal;
	}
}

double Polynomial::eval(const int x) {
	double sum = 0;
	for (int i = 0; i <= this->deg; i++)
	{
		if (i == 0)					//daca i=0 atunci x este 1  ( x^0 = 1 )
			sum += this->coef[0];
		else
		{
			int aux = i;
			int xaux = x;			//incep prin a pune x in aux
			aux--;
			while (aux != 0)		//cat timp aux!=0 inseamna ca trebuie sa mai ridic x-ul la putere
			{
				xaux *= x;
				aux--;
			}
			sum += this->coef[i] * xaux;	//la final inmultesc x^i cu coeficientul corespunzator si il adun la suma
		}
	}
	return sum;
}

void Polynomial::addCoef(const double NewCoef,const int pos)
{
	if (pos < 0)		//daca pozitia pe care vreau sa adaug este mai mica ca 0 atunci nu adaug nimic
		return;
	if (pos > this->deg)	//Daca pozitia pe care vreau sa adaug este mai mare ca gradul polinomului atunci creez un nou polinom cu gradul egal cu pozitia
	{						//pe care o sa adaug coeficientul
		double *newCoef;
		try
		{
			newCoef = new double[pos];
		}
		catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
		{
			cout << " Allocation Failure ";
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i <= this->deg; i++)
			newCoef[i] = this->coef[i];
		for (int i = this->deg + 1; i < pos; i++)
			newCoef[i] = 0;
		newCoef[pos] = NewCoef;
		this->coef = newCoef;
		this->deg = pos;
		return;
	}
	else
	{
		this->coef[pos] = NewCoef;	//În orice alt caz, pur și simplu il pun direct pe pozitia corespunzatoare.
	}
}

void Polynomial::delCoef(int pos) 
{
	if (pos > this->deg || pos < 0 )	//Daca pozitia de pe care incerc sa sterg coeficientul este mai mare ca gradul sau mai mica ca 0 nu fac nimic
		return;			
	if (pos == this->deg)				//Daca este egal cu gradul atunci il sterg si creez un nou vector de coeficienti
	{
		this->coef[pos] = 0;
		int degNoua = pos - 1;
		while (this->coef[pos] == 0 && pos != 0)		//caut nout grad al polinomului
			pos--;
		if (pos == 0 && this->coef[pos] == 0)			//daca polinomul devine null, atunci distrug obiectul
		{
			delete[]this->coef;
			this->deg = 0;
		}
		else                                            //altfel imi creez un nou polinom care este salvat in locul lui, pentru eficiență
		{
			this->deg = pos;
			double *aux;
			try
			{
				aux = new double[pos];
			}
			catch (bad_alloc coef) //daca nu exista loc in memorie afiseaza allocation failure si programul se opreste
			{
				cout << " Allocation Failure ";
				exit(EXIT_FAILURE);
			}
			for (int i = 0; i <= pos; i++)
				aux[i] = this->coef[i];
			this->coef = aux;
		}
	}
	else
	{									//Pe orice alta pozitie, pur si simplu coeficientul corespunzator respectivului grad devine 0
		this->coef[pos] = 0;
	}
}