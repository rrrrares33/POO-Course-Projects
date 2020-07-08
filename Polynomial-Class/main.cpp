#include "Polynomial.h"
#include <conio.h>		//Pentru a face ca output-ul sa rămână pe ecran cu _getch()
#include <assert.h>		//Pentru a utiliza procedura assert() pentru teste											

void testPolynomialAddCoef(Polynomial& A)
{
	//Verific dacă functia de adaugare unui nou coeficient functioneaza corect
	int aux1 = A.getDeg();
	A.addCoef(10, A.getDeg() + 1);
	int aux2 = A.getDeg();
	assert(aux1 == aux2 - 1);
	//-----------------------------				
}

void testPolynomialDelCoef(Polynomial& A)
{
	//Verific dacă functia pentru stergerea unui coeficient functioneaza curect;
	int aux1 = A.getDeg();
	A.delCoef(A.getDeg());
	int aux2 = A.getDeg();
	assert(aux1 == aux2 + 1);
	//---------------------	
}

void testPolynomialConsEvalParant()
{
	//Verific daca merge bine constructorul cu parametrii și
	double a[4] = { 10, 20, 30, 40 };
	Polynomial C(a, 3);
	//Verific daca merge supraîncărcarea operatorului [] în mod corect.
	assert(C[3] == 40);
	//Verific daca metoda eval funcționeaza corect prin testarea pe polinomul C care are gradul 3 și coeficientii 10 20 30 40
	assert(C.eval(2) == 490);
	//-----------------------
}

void testPolynomialEgal(Polynomial& A)
{
	//Verific daca merge supraîncărcarea operatorului = în mod corect.
	Polynomial D = A;
	assert(D[D.getDeg()] == A[A.getDeg()]);
}

void testPolynomialInmultireScalar()
{
	//Verific daca inmultirea cu un scalar functioneaza corect.
	double a[4] = { 10, 20, 30, 40 };
	Polynomial C(a, 3);
	C = C * 3;
	assert(C[3] == 120);
	C = 3 * C;
	assert(C[3] == 360);
	//-------------------
}

void testPolynomialAdunare(Polynomial& A, Polynomial& B)
{
	//Verific daca adunarea a doua polinoame se realizeaza corect. (prin testarea ultimul coeficient care depinde de care polinom are gradul mai mare)																
	if (A.getDeg() > B.getDeg())
		assert((A + B)[(A + B).getDeg()] == A[A.getDeg()]);
	else if (A.getDeg() < B.getDeg())
		assert((A + B)[(A + B).getDeg()] == B[B.getDeg()]);
	else
		assert((A + B)[(A + B).getDeg()] == A[A.getDeg()] + B[B.getDeg()]);
	//----------------------------------------------------------------------
}

void testPolynomialInmultirePol(Polynomial& A, Polynomial& B)
{
	//Verific dacă înmulțirea face ce ar trebui,atunci ar trebui ca: gradul Polinomul A*B = gradul lui A + gradul lui B;
	assert((A * B).getDeg() == A.getDeg() + B.getDeg());
	//--------------------------------------------------
}

void testPolynomialImpartirePol(Polynomial& A, Polynomial& B)
{
	//Operatorul returneaza doar câtul. Verific impartirea face ce ar trebui:
	// CÂTUL ÎMPARTIRII : cout << A / B; 
	// RESTUL ÎMPARTIRII : cout << A + (-1) * ((A / B) * B);
	if (A.getDeg() >= B.getDeg())
		assert((A / B).getDeg() == A.getDeg() - B.getDeg());	//daca marimea primului polinom este mai mica sau egala cu cel de al doilea atunci gradul impartirii este egal cu diferenta celor doua polinoame.
	else
		assert((A / B).getDeg() == 0);							//altfel, gradul impartirii ar trebui sa fie 0 mereu. (catul impartirii (polinom de grad mai mic / polinom de grad mai mare) = 0 mereu)
	//--------------------------------------------------
}

int main()
{
	//Verific daca functioneaza corect supraîncarcarea >> pentru citire și a lui << pentru afișare
	Polynomial A, B;
	cin >> A;
	cin >> B;
	cout << A << B;
	//--------------
	
	double arr[3];
	Polynomial C(arr,3);

	//BLOCK TESTE:
	testPolynomialAddCoef(A);
	testPolynomialDelCoef(A);
	testPolynomialConsEvalParant();
	testPolynomialAdunare(A, B);
	testPolynomialEgal(A);
	testPolynomialInmultireScalar();
	testPolynomialInmultirePol(A, B);
	testPolynomialImpartirePol(A, B);
	//-------------------------------

	_getch();
	return 0;
}
