#include <iostream>
#include <string>
#include "LinkedList.hpp"
#include <fstream>

using namespace std;

LinkedList<string> split(string x) {

	LinkedList<string> res;

	size_t k = 0;
	
	while (x.length() != 0) {

		k = x.find(",", 0);
		
		if (k == string::npos) {
			
			res.addLast(x.substr(0,x.length()));
			break;
		}
		res.addLast(x.substr(0, k));
		x = x.substr(k+1, x.length() -k);
	}
	return res;
}

//Complex number structure 
struct Complex {

	double re;
	double im;

	Complex() {
		re = 0.0, im = 0.0;
	}

	Complex(double r, double i) {

		re = r;
		im = i;
	}

	Complex add(Complex n) {

		return Complex(re + n.re, im + n.im);
	}

	Complex sub(Complex n) {
		return Complex(re - n.re, im - n.im);
	}

	Complex conjugate() {

		im = -im;
	}

	Complex mult(Complex n) {

		double re1 = re;
		double re2 = n.re;
		double im1 = im;
		double im2 = n.im;

		return Complex(re1 * re2 - im1 * im2, re1 * im2 + re2 * im1);
	}

	Complex power(int p) {

		Complex o(re, im);
		Complex z = o;

		if (p == 0) {

			return Complex(1,0);
		}

		for (int i = 1; i < p; i++) {

			z = z.mult(o);
		}

		return z;
		
	}

	string toString() {

		if (im == 0.0 && re != 0.0) {

			return "(" + to_string(re) + ")";
		}
		else if (re == 0 && im !=0) {

			if (im == 1) {

				return "(i)";
			}
			else if (im == -1) {
				return "(-i)";
			}

			return "(" +to_string(im) + "i)";
		}
		else if (im == 0.0 && re == 0.0) {

			return "0";
		}else {

			return "(" + to_string(re) + " + " + to_string(im) + "i)";
		}
	}
};

string to_lower(string s) {

	for (int i = 0; i < s.length(); i++) {

		tolower(s[i]);	
	}

	return s;
}

//Polynomial Term Structure
struct pTerm {

	int deg;
	Complex coeff;

	pTerm(int dg, double real, double imaginary) {

		deg = dg;
		coeff.re = real;
		coeff.im = imaginary;
	}

	pTerm(int dg, Complex z) {
		coeff = z;
		deg = dg;
	}
	pTerm() {
		deg = 0;
		coeff.im = 0;
		coeff.re = 0;
	}

	pTerm sum(pTerm term2) {


		return pTerm(deg, coeff.add(term2.coeff));
	}

	pTerm mult(pTerm term2) {

		return pTerm(deg + term2.deg, coeff.mult(term2.coeff));
	}

	string toString() {

		if (coeff.toString() == "0") {

			return "";
		}
		else if (deg == 1) {

			return coeff.toString() + "X";
		}
		else if (deg == 0) {

			return coeff.toString();

		}else {

			return coeff.toString() + "X^" + to_string(deg);
		}
	}
};

class Polynomial {

private:
	LinkedList<pTerm> poly;
	int deg;

public:

	Polynomial() {
		deg = 0;
	}
	~Polynomial() {}

	void displayPolynomial() {

		struct list_elem<pTerm>* aux = poly.pfirst;

		string sp = "";

		while (aux != NULL) {

			if (aux->info.coeff.toString() != "0") {

				if (aux->next != NULL) {

					sp += aux->info.toString() + " + ";
					
				}else{
					
					sp += aux->info.toString(); 
					
				}
			}

			aux = aux->next;
		}

		cout << "\nPrinting Polynomial of degree " << deg << ": ";
		cout << sp;
		cout << "\n\n";
	}

	void addLastTerm(pTerm term) {

		poly.addLast(term);
	}

	LinkedList<pTerm> simplify() {

		LinkedList<pTerm> res;

		struct list_elem<pTerm>* aux1 = poly.pfirst;
		struct list_elem<pTerm>* aux2;

		while (aux1 != NULL) {
			if (aux1->info.coeff.toString() != "0") {
				
				struct pTerm sumTerm = aux1->info;
				aux2 = poly.pfirst;

				while (aux2 != NULL) {
					if (aux2->info.coeff.toString() != "0" && aux1 != aux2) {

						if (sumTerm.deg == aux2->info.deg) {

							sumTerm = sumTerm.sum(aux2->info);
							aux2->info.coeff = Complex(0, 0);
						}
					}

					aux2 = aux2->next;
				}

				if (sumTerm.coeff.toString() != "0") {
					res.addLast(sumTerm);
				}	
			}
			aux1 = aux1->next;
		}

		return res;

	}

	bool containsDegree() {//a method used to check if the polynomial contains a term with the exponent equal to the max degree.

		struct list_elem<pTerm>* aux = poly.pfirst;

		while (aux != NULL) {

			if (aux->info.deg == deg && aux->info.coeff.toString() != "0") {
				
				return true;
			}
			aux = aux->next;
		}
		return false;
	}

	void readPolynomial(string path) {

		ifstream fileReader(path);
		
		string line;

		getline(fileReader, line);

		if (stoi(line) < 0) {

			cout << "\nNO NEGATIVE DEGREES ALLOWED\n";
			return;
		}

		if (stoi(line) < deg) {//removing terms with exponent higher than new degree


			struct list_elem<pTerm>* aux = poly.pfirst;

			while (aux != NULL) {

				if (aux->info.deg > stoi(line)) {

					if (aux == poly.pfirst) {

						aux = aux->next;
						poly.removeFirst();
						continue;

					}else if (aux == poly.plast) {

						aux = aux->next;
						poly.removeLast();
						continue;
					
					}else {

						struct list_elem<pTerm>* nxt = aux->next;
						struct list_elem<pTerm>* prv = aux->prev;

						delete aux;

						nxt->prev = prv;
						prv->next = nxt;

						aux = prv;
					}
				}
				aux = aux->next;
			}

		}

		deg = stoi(line);//string to int function


		while (getline(fileReader, line)) {

			if (!line.empty()) {
				
				int termDeg;
				double re, im;


				LinkedList<string> infoList = split(line);
				
				termDeg = stoi(infoList.pfirst->info);

				if (termDeg > deg || termDeg < 0) {
					continue;
				}

				re = stod(infoList.pfirst->next->info);
				im = stod(infoList.plast->info);//String to double function

				if (re == 0 && im == 0) {
					continue;
				}

				pTerm aux(termDeg, re, im);
				poly.addLast(aux);
			}
		}
		fileReader.close();
		
		poly = simplify();

		if (poly.isEmpty() || containsDegree() == false){

			poly.addLast(pTerm(deg,1,0));
		}
		
	}

	void computeValue(Complex z) {

		Complex o(0, 0);

		struct list_elem<pTerm>* aux = poly.pfirst;

		while (aux != NULL) {

			o = o.add(aux->info.coeff.mult(z.power(aux->info.deg)));

			aux = aux->next;
		}

		cout << "\nThe value of the polynomial at X = " << z.toString() << "  , is: " << o.toString() << "\n";

	}

	Polynomial sum(Polynomial p2) {

		Polynomial res;

		res.deg = max(deg, p2.deg);
		struct list_elem<pTerm>* aux2 = p2.poly.pfirst;
		struct list_elem<pTerm>* aux1 = poly.pfirst;

		while (aux1 != NULL) {

			res.addLastTerm(aux1->info);
			aux1 = aux1->next;

		}

		while (aux2 != NULL) {

			res.addLastTerm(aux2->info);
			aux2 = aux2->next;
		}
		res.poly = res.simplify();
		return res;

	}

	Polynomial mult(Polynomial p2) {

		Polynomial res;
		res.deg = deg + p2.deg;

		LinkedList<pTerm> poly2 = p2.poly;

		struct list_elem<pTerm>* aux1 = poly.pfirst;
		struct list_elem<pTerm>* aux2;

		while (aux1 != NULL) {

			aux2 = poly2.pfirst;

			while (aux2 != NULL) {

				res.poly.addLast(aux1->info.mult(aux2->info));

				aux2 = aux2->next;
			}
			aux1 = aux1->next;

		}

		res.poly = res.simplify();
		return res;
	}
};

int main() {


	string op;

	do {
		cout << "\n\n*************************\n\n";
		cout << "Choose an Operation with polynomials from the following:\n";
		cout << "[SUM], [MULT], [DISPLAY], [VAL], [EXIT]: ";

		cin >> op;

		op = to_lower(op);

		if (op == "sum") {

			Polynomial p1, p2, p3;

			cout << "Insert a path to a txt file for the first polynomial to be read: ";
			cin >> op;
			p1.readPolynomial(op);

			cout << "Insert a path to a txt file for the second polynomial to be read: ";
			cin >> op;
			p2.readPolynomial(op);

			cout << "Summing these polynomials: \n";
			p1.displayPolynomial();
			p2.displayPolynomial();

			p3 = p1.sum(p2);

			cout << "Result is: ";
			p3.displayPolynomial();

		}
		else if (op == "mult") {

			Polynomial p1, p2, p3;

			cout << "Insert a path to a txt file for the first polynomial to be read: ";
			cin >> op;
			p1.readPolynomial(op);

			cout << "Insert a path to a txt file for the second polynomial to be read: ";
			cin >> op;
			p2.readPolynomial(op);

			cout << "Multiplying these polynomials: \n";
			p1.displayPolynomial();
			p2.displayPolynomial();

			p3 = p1.mult(p2);

			cout << "Result is: ";
			p3.displayPolynomial();

		}
		else if (op == "display") {

			Polynomial p1;

			cout << "Insert a path to a txt file for the polynomial to be read: ";
			cin >> op;
			p1.readPolynomial(op);
			p1.displayPolynomial();

		}
		else if (op == "val") {

			Polynomial p1;
			LinkedList<string> cNum;
			double re, im;

			cout << "Insert a path to a txt file for the polynomial to be read: ";
			cin >> op;
			p1.readPolynomial(op);
			p1.displayPolynomial();

			cout << "Insert [real part, imaginary part] of the complex number to compute the value of the polynomial: ";
			cin >> op;

			cNum = split(op);
			re = stod(cNum.pfirst->info);
			im = stod(cNum.plast->info);

			p1.computeValue(Complex(re, im));
			
		}
		else if (op == "exit") {

			break;
		}
		else {
			cout << "\nInvalid Option.\n";
		}

	} while (true);
}