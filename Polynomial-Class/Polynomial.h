#pragma once

#include <iostream>

//Pentru a nu include tot std-ul am ales doar ceea ce urmează să folosesc din el.
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;		
using std::bad_alloc;		//pentru a try-catch -urile ce tin de alocarea dinamica.

class Polynomial
{
	unsigned int deg;		//gradul polinomului
	double *coef;			//coeficienții polinomului alocați dinamic

public:
	Polynomial() : deg(0) {};

	Polynomial(double [], int);									    //constructor cu parametrii în care este dată o listă cu parametrii și gradul polinomului 
	
	Polynomial(Polynomial&);										//constructor de copiere

	Polynomial& operator = (const Polynomial&);						//supraîncarcarea operatorului = pentru a putea copia un polinom in alt polinom sub forma prin egalitate ( Polynomial A = B; )

	~Polynomial();													//destructor

	friend ostream &operator <<(ostream&, const Polynomial&);		//supraincarcarea operatorului de afișare pentru a putea afisa un polinom
		
	friend istream &operator >>(istream&, Polynomial&);				//supraincarcarea operatorului de citire pentru a putea citi un polinom

	Polynomial operator + (const const Polynomial&) const;			//supraincarcarea operatorului + pentru a aduna doua polinoame

	double operator[] (const unsigned int) const;					//supraincarcarea operatorului [] pentru a returna coeficientul n, ce tine de termenul de ordin n din polinom ( x^n ) 

	Polynomial operator * (const int) const;						//supraincarcea operatorului * pentru a accepta inmultirea unui polinom cu un scalar pe dreapta

	friend Polynomial operator * (const int&, const Polynomial&);   //supraincarcea operatorului * pentru a accepta inmultirea unui polinom cu un scalar pe stang

	Polynomial operator * (const Polynomial& obj) const;			//supraincarcea operatorului * pentru a accepta inmultirea unui polinom cu un polinom

	friend Polynomial operator / (Polynomial p1, Polynomial& p2);	//supraincarcarea operatorului / pentru impartirea a doua polinoame cu cât

	const unsigned int getDeg() { return this->deg; };				//Obtinerea gradului polinomului

	double eval(const int);											//Obținerea valori polinomului într-un punct dat 

	void addCoef(const double,const int);							//Adaugarea unui coeficient polinomului pe o pozitie data

	void delCoef(int);												//Stergerea unui coeficient din polinom de pe o pozitie data
};