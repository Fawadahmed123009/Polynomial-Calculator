#include <iostream>
using namespace std;
class term {
public:
	int coef;	// coff->cofficient of term
	int exp;	// exp->exponent of term
	term* next;	// next->pointer to store next term address

	term()	// default constructor with initial value of coff,exp zero and next NULL
	{
		coef = 0;
		exp = 0;
		next = NULL;
	}

	term(int c, int e)	// paramiterized constructor that initializes coff with c ,exp with e and next with NULL
	{
		coef = c;
		exp = e;
		next = NULL;
	}
};
// This class contain all function like input, output, addition, multiplication and evaluation;
class polynomial {
private:
	term* head;	// pointer to store adress of first term of polynomial
	int size;	// variable to store number of terms of polynomial
public:
	polynomial() //default constructor with initial value of size 0 and head NULL
	{
		size = 0;
		head = NULL;
	}

	void insertionOfTerm(int c, int e)
	{
		term* newterm = new term(c, e);
		term* temp = head;
		if (head == NULL || e > head->exp) // if polynomial has no value 
		{
			newterm->next = head;
			head = newterm;
		}
		else // if polynomial have some value
		{
			while (temp->next != NULL && temp->next->exp > e) //check exponent and insert term in sorted order
			{
				temp = temp->next;
			}
			if (temp->next != NULL && temp->next->exp == e) // check if exponent of new term and already existing term is equal than add both coefficients and insert 
			{
				temp->next->coef = temp->next->coef + c;
			}
			else
			{
				newterm->next = temp->next;
				temp->next = newterm;
			}
		}
	}


	void input()// take number of term of polynomial and also ask values of term then call insertionOfterm(c,e)
	{
		cout << "Enter number of terms of polynomial : ";
		cin >> size;
		while (size != 0)
		{
			int c, e;
			cout << "Enter cofficient of term : ";
			cin >> c;
			cout << "Enter exponent of term : ";
			cin >> e;
			insertionOfTerm(c, e);
			size--;
		}
	}

	void output()	//Function to display polynomial 
	{
		int i = 0;
		term* temp = head;
		if (head == NULL)
		{
			cout << "!!! Polynomial contain no term !!!";
		}
		else
		{
			while (temp != NULL)
			{
				if (temp == head)
				{
					cout << temp->coef << "x ^ " << temp->exp;
				}
				else if (temp->exp == 0 && temp->coef>0)
				{
					cout << " + " << temp->coef;
				}
				else if (temp->exp == 0 && temp->coef < 0)
				{
					cout << " " << temp->coef;
				}
				else if(temp->coef>0)
				{
					cout << " + " << temp->coef << "x ^ " << temp->exp;
				}
				else
				{
					cout << " " << temp->coef << "x ^ " << temp->exp;
				}
				temp = temp->next;
			}
		}
	}

	polynomial operator=(polynomial& obj) // = operator
	{
		term* temp = head;
		term* temp1 = obj.head;
		term* temp2 = NULL;
		if (this != &obj)// delete all terms of current polynomial if both are not same and  copy terms from obj
		{
			while (temp != NULL)
			{
				temp2 = temp;
				delete temp2;
				temp = temp->next;
			}
			head = NULL;
			size = 0;
			while (temp1 != NULL)
			{
				insertionOfTerm(temp1->coef, temp1->exp);
				temp1 = temp1->next;
			}
		}
		return *this;
	}

	polynomial operator+(polynomial const& obj)	// Function to add two polynoial
	{
		polynomial result;
		term* temp1 = head;
		term* temp2 = obj.head;
		while (temp1 != NULL && temp2 != NULL)
		{
			if (temp1->exp > temp2->exp)	// first base case if first polynomial have greater exponent value them store term in result
			{
				result.insertionOfTerm(temp1->coef, temp1->exp);
				temp1 = temp1->next;
			}
			else if (temp1->exp < temp2->exp)	// second base case if second polynomial have greater value then store the term in result
			{
				result.insertionOfTerm(temp2->coef, temp2->exp);
				temp2 = temp2->next;
			}
			else	// third case when both coefficiant are equal add them and insert in result polynomial
			{
				int coef = temp1->coef + temp2->coef;
				if (coef != 0) {
					result.insertionOfTerm(coef, temp1->exp);
				}
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		while (temp1 != NULL) // insert all remaing values of polynomial 1 in result
		{
			result.insertionOfTerm(temp1->coef, temp1->exp);
			temp1 = temp1->next;
		}
		while (temp2 != NULL) // insert all remaing values of polynomial 2 in result
		{
			result.insertionOfTerm(temp2->coef, temp2->exp);
			temp2 = temp2->next;
		}
		return result;
	}

	polynomial operator*(polynomial const& obj)
	{
		double c;
		int e;
		polynomial result;
		for (term* temp1 = head; temp1 != NULL; temp1 = temp1->next)
		{
			for (term* temp2 = obj.head; temp2 != NULL; temp2 = temp2->next)
			{
				c = temp1->coef * temp2->coef;
				e = temp1->exp + temp2->exp;
				result.insertionOfTerm(c, e);
			}
		}
		return result;
	}

	double power(double x, int exp) // fuction to calculate power which we use in evaluate function
	{
		double result = 1;
		for (int i = 0; i < exp; i++)
		{
			result = result * x;
		}
		return result;
	}

	double evaluate(double n) // evaluate all value of polynomial by value given by user
	{
		double sum = 0;
		double x = 0, y = 0;
		term* temp = head;
		while (temp != NULL)
		{
			x = power(n, temp->exp);
			y = temp->coef * x;
			sum = sum + y;
			temp = temp->next;
		}
		return sum;
	}
	double operator[](double x) //operator to evaluate polynomial
	{
		return evaluate(x);
	}

	~polynomial() // destructor of polynomial class
	{
		term* temp = head;
		while (temp != NULL)
		{
			temp = temp->next;
			delete head;
			head = temp;
		}
	}

};
void menu()		// menu function
{
	polynomial obj1;
	polynomial obj2;
	int n;
	cout << "\t\t\t!!!			Polynomial Calculator			!!!";
	cout << "\n\n	1 => Input";
	cout << "\n	2 => Output";
	cout << "\n	3 => Addition";
	cout << "\n	4 => Multiplication";
	cout << "\n	5 => Evaluate";
	cout << "\n	-1 => Exit";
	cout << "\n Enter option : ";
	cin >> n;
	while (n != -1)
	{
		if (n == 1)
		{
			cout << "Enter First Polynomial : \n";
			obj1.input();
			cout << "\nEnter Second Polynomial : \n";
			obj2.input();
		}
		else if (n == 2)
		{
			cout << "\nFirst Polynomial : ";
			obj1.output();
			cout << "\n\nSecond Polynomial : ";
			obj2.output();
		}
		else if (n == 3)
		{
			polynomial obj = obj1 + obj2;
			cout << "Addition : ";
			obj.output();
		}
		else if (n == 4)
		{
			polynomial obj = obj1 * obj2;
			cout << "Multiplication : ";
			obj.output();
		}
		else if (n == 5)
		{
			double num;
			cout << "\nEnter the value of x to evaluate : ";
			cin >> num;
			double x = obj1[num];
			cout << "\nFirst Polynomial : ";
			obj1.output();
			cout << "\nAt x = " << num << " the polynomial value is : " << x;
			cout << "\nSecond Polynomial : ";
			double y = obj2[num];
			obj2.output();
			cout << "\nAt x = " << num << " the polynomial value is : " << y;
		}
		cout << "\n\n 1 => Input";
		cout << "\n 2 => Output";
		cout << "\n 3 => Addition";
		cout << "\n 4 => Multiplication";
		cout << "\n 5 => Evaluate";
		cout << "\n -1 => Exit";
		cout << "\n Enter option : ";
		cin >> n;
	}
}
int main()
{
	menu();
	return 0;
}
