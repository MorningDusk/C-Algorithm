//week 9
//friend function declaration and definition
#include<iostream>
using namespace std;
class sample {
	int a, b;
	friend void display(sample);		//send object as argument
public:
	sample() {
		a = 0; b = 0;
	}
};
void display(sample s) {
	s.a = 10;
	s.b = 20;
	cout << "a = " << s.a << endl;
	cout << "b = " << s.b << endl;
}
int main() {
	sample s;
	display(s);		//send object as argument
	return 0;
}

//friend function with multiple classes
class test2;
class test1 {
	int a;
public:
	void geta() {
		cout << "Enter a value: ";
		cin >> a;
	}
	friend void big(test1, test2);
};
class test2 {
	int b;
public:
	void getb() {
		cout << "Enter b value: ";
		cin >> b;
	}
	friend void big(test1, test2);
};
void big(test1 t1, test2 t2) {		//pass object as argument
	if (t1.a > t2.b)
		cout << "a is bigger";
	else if (t1.a < t2.b)
		cout << "b is bigger";
	else
		cout << "Both are equal";
}
int main() {
	test1 t1;
	test2 t2;
	t1.geta();
	t2.getb();
	big(t1, t2);		//pass object as argument
	return 0;
}

//binary overloading +: arthimetic plus
#include<iostream>
using namespace std;
class complex {
private:
	int a, b;
public:
	void setdata(int x, int y) {
		a = x; b = y;
	}
	void showdata() {
		cout << "a: " << a << " b: " << b << endl;
	}
	complex operator + (complex obj) {
		complex temp;
		temp.a = a + obj.a;
		temp.b = b + obj.b;
		return temp;
	}
};
int main() {
	complex obj1, obj2, obj3;
	obj1.setdata(3, 4);
	obj2.setdata(5, 6);
	obj3 = obj1 + obj2;
	obj3.showdata();
	return 0;
}

//friend function and operator + overloading
#include<iostream>
using namespace std;
class complex {
	int a, b;
public:
	void setdata(int x, int y) {
		a = x; b = y;
	}
	void showdata() {
		cout << "a: " << a << " b: " << b << endl;
	}
	friend complex operator +(complex, complex);
};
complex operator (complex x, complex y) {
	complex temp;
	temp.a = x.a + y.a;
	temp.b = x.b + y.b;
	return temp;
}
int main() {
	complex a, b, c;
	a.setdata(3, 4);
	b.setdata(5, 6);
	c = a + b;
	c.showdata();
	return 0;
}

//binary operator > overloading and friend function
#include<iostream>
using namespace std;
class test2;
class test1 {
	int a;
public:
	void geta() {
		cout << "Enter obj1 a value->";
		cin >> a;
	}
	friend void operator >(test1, test2);		//friend to both classes
};
class test2 {
	int b;
public:
	void getb() {
		cout << "Enter obj2 b value->";
		cin >> b;
	}
	friend void operator >(test1, test2);		//friend to both classes
};
void operator >(test1 x, test2 y) {
	(x.a > y.b ? cout << "YES" : cout << "NO");		//we need dot operator to access member
}
int main() {
	cout << "Is obj1>obj2?" << endl;
	test1 obj1;
	test2 obj2;
	obj1.geta();
	obj2.getb();
	obj1 > obj2;
	return 0;
}

//overloading binary operator + for string
#include<iostream>
#include<string.h>
using namespace std;
class test {
	char st[100];
public:
	void read() {
		cout << "Enter string:";
		cin >> st;
	}
	void display() {
		cout << "string = " << st << endl;
	}
	test operator +(test t2) {
		test t3;
		strcpy(t3.st, st);		//st = t1.st
		strcat(t3.st, " ");
		strcat(t3.st, t2.st);
		return t3;
	}
};
int main() {
	test t1, t2, t3;
	t1.read();
	t2.read();
	t3 = t1 + t2;
	t3.display();
}

//overloading operator << and >>
#include<iostream>
using namespace std;
class student {
	int id;
	char name[20];
public:
	friend void operator >>(istream &in, student &s);		//reference object to cin
	friend void operator <<(ostream &out, student &s);		//reference object to cout
};
void operator >>(istream &in, student &s) {
	cout << "Enter student name: ";
	in >> s.id >> s.name;
}
void operator <<(ostream &out, student &s) {
	out << "ID: " << s.id << endl;
	out << "name: " << s.name << endl;
}
int main() {
	student s;
	cin >> s;		//overloading >>
	cout << s;		//overloading <<
}

//friend class accepting private and public
#include<iostream>
using namespace std;
class test1 {
	int a, b;
public:
	friend class test2;
	void getab() {
		cin >> a, b;
	}
};
class test2 {
public:
	void putab(test1 t1) {
		cout << t1.a << t1.b << endl;
	}
};
int main() {
	test1 t1;
	test2 t2;
	t1.getab();
	t2.putab(t1);
}

/**********************************************************************************************************************************************************/

//week 10
//single level inheritance visibility mode: public
#include<iostream>
using namespace std;
class student {
	int id;
	char name[20];
public:
	void getstudent() {
		cout << "Enter student name";
		cin >> name;
		cout << "Enter id:";
		cin >> id;
	}
	void putstudent() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
	}
};
class computer :public student {
	float height, weight;
public:
	void getphysical() {
		cout << "Enter student height and weight";
		cin >> height >> weight;
	}
	void putphysical() {
		cout << "Height: " << height << endl;
		cout << "Weight: " << weight << endl;
	}
};
int main() {
	computer obj;
	obj.getstudent();
	obj.getphysical();
	obj.putstudent();
	obj.putphysical();
}

//single level inheritance visibility mode: private
#include<iostream>
using namespace std;
class student {
	int id;
	char name[20];
public:
	void getstudent() {
		cout << "Enter student name: ";
		cin >> name;
		cout << "Enter id: ";
		cin >> id;
	}
	void putstudent() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
	}
};
class computer :private student {
	float height, weight;
public:
	void getphysical() {
		getstudent();		//access through member function
		cout << "Enter student height and weight";
		cin >> height >> weight;
	}
	void putphysical() {
		putstudent();		//access through member function
		cout << "Height: " << height << endl;
		cout << "Weight: " << weight << endl;
	}
};
int main() {
	computer obj;
	obj.getphysical();
	obj.putphysical();
}

//multiple inheritance
#include<iostream>
using namespace std;
class student {
	int id;
	char name[20];
public:
	void getstudent() {
		cout << "Enter student name: ";
		cin >> name;
		cout << "Enter id: ";
		cin >> id;
	}
	void putstudent() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
	}
};
class marks {
protected:
	int m1, m2, m3;
public:
	void getmarks() {
		cout << "Enter three marks: ";
		cin >> m1 >> m2 >> m3;
	}
	void putmarks() {
		cout << "M1: " << m1 << endl;
		cout << "M2: " << m2 << endl;
		cout << "M3: " << m3 << endl;
	}
};
class result :public student, public marks {
	int total;
	float average;
public:
	void show() {
		total = m1 + m2 + m3;
		average = total / 3.0;
		cout << "Total: " << total << endl;
		cout << "Average: " << average << endl;
	}
};
int main() {
	result obj;
	obj.getstudent();
	obj.getmarks();
	obj.putstudent();
	obj.putmarks();
	obj.show();
}

//multi-level inheritance
#include<iostream>
using namespace std;
class student {
	int id;
	char name[20];
public:
	void getstudent() {
		cout << "Enter student name: ";
		cin >> name;
		cout << "Enter id: ";
		cin >> id;
	}
	void putstudent() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
	}
};
class marks :public student {
protected:
	int m1, m2, m3;
public:
	void getmarks() {
		cout << "Enter three marks: ";
		cin >> m1 >> m2 >> m3;
	}
	void putmarks() {
		cout << "M1: " << m1 << endl;
		cout << "M2: " << m2 << endl;
		cout << "M3: " << m3 << endl;
	}
};
class result :public marks {
	int total;
	float average;
public:
	void show() {
		total = m1 + m2 + m3;
		average = total / 3.0;
		cout << "Total: " << total << endl;
		cout << "Average: " << average << endl;
	}
};
int main() {
	result obj;
	obj.getstudent();
	obj.getmarks();
	obj.putstudent();
	obj.putmarks();
	obj.show();
}

//hierarchial inheritance
#include<iostream>
using namespace std;
class A {
protected:
	int n;
public:
	void getn() {
		cout << "Enter n: ";
		cin >> n;
	}
};
class B :public A {
public:
	void square() {
		int sq;
		sq = n * n;
		cout << "square of n: " << sq << endl;
	}
};
class C :public A {
public:
	void cube() {
		int cube;
		cube = n * n*n;
		cout << "cube of n: " << cube << endl;
	}
};
int main() {
	B bobj;
	C cobj;
	bobj.getn();
	bobj.square();
	cobj.getn();
	cobj.cube();
}

/**********************************************************************************************************************************************************/

//week 11
//pointer and reference variable
#include<iostream>
using namespace std;
void sqap(int &x, int &y);		//void sqap(int *x, int *y)
int main() {
	int a = 5, b = 9;
	cout << "Swap the content of two variable" << endl;
	cout << "Values before the exchange: " << endl;
	cout << "a = " << a << "b = " << b << endl;
	swap(a, b);
	cout << "Values after the exchange: " << endl;
	cout << "a = " << a << "b = " << b << endl;
}
void swap(int &x, int &y) {
	int tmp;
	tmp = x;
	x = y;
	x = tmp;
	return;
}

//object pointer ex1
#include<iostream>
using namespace std;
class box {
	int l, b, h;
public:
	void setDimension(int x, int y, int z) {
		l = x; b = y; h = z;
	}
	void showDimension() {
		cout << "L: " << l << "\t";
		cout << "B: " << b << "\t";
		cout << "H: " << h << endl;
	}
};
int main() {
	box *ptr;
	box obj;
	ptr = &obj;
	ptr->setDimension(5, 10, 15);	//(*ptr).setDimension(5, 10, 15);
	ptr->showDimension();		//(*ptr).showDimension();
}

//this pointer ex1
#include<iostream>
using namespace std;
class box {
	int l, b, h;
public:
	void setDimension(int x, int y, int z) {
		this->l = l;	//(*this).l = l;
		this->b = b;	//(*this).b = b;
		this->h = h;	//(*this).h = h;
	}
	void showDimension() {
		cout << "L: " << l << "\t";
		cout << "B: " << b << "\t";
		cout << "H: " << h << endl;
	}
};
int main() {
	box *ptr;
	box obj;
	ptr = &obj;
	ptr->setDimension(5, 10, 15);	//(*ptr).setDimension(5, 10, 15);
	ptr->showDimension();		//(*ptr).showDimension();
}

//this pointer ex2
#include<iostream>
using namespace std;
class test {
	int a, b;
public:
	void show() {
		a = 10;
		b = 20;
		cout << "Object address: " << this << endl;
		cout << "a: " << this->a << endl;
		cout << "b: " << this->b << endl;
	}
};
int main() {
	test *ptr;
	test t;
	ptr = &t;
	ptr->show();
}

//dynamic one dimensional array
#include<iostream>
using namespace std;
int main() {
	int n, i, sum = 0;
	int *ptr;
	cout << "Enter array size: ";
	cin >> n;
	ptr = new int[n];
	if (ptr == NULL)
		return -1;
	cout << "Memory has been created" << endl;
	cout << "Starting address" << ptr << endl;
	for (i = 0; i < n; i++) {
		cin >> *(ptr + i);
		sum = sum + *(ptr + i);
	}
	cout << "output" << endl;
	cout << "elements are: ";
	for (i = 0; i < n; i++)
		cout << *(ptr + i) << endl;
	cout << "sum: " << sum << endl;
	delete[]ptr;
}

//dynamic object array
#include<iostream>
using namespace std;
class dma {
public:
	dma() {
		cout << "Constructor called" << endl;
	}
	~dma() {
		cout << "Destructor called" << endl;
	}
};
int main() {
	dma *obj;
	obj = new dma[4];
	delete[]obj;
	return 0;
}

/**********************************************************************************************************************************************************/

//week 12
//using parameterized constructor
#include<fstream>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main() {
	char name[20];
	int id;
	ofstream outf("D:\\test\\cplus.txt");
	if (!outf) {		//if (!outf.is_open())	//if (outf.fail())
		cout << "Input file opening failed";
		exit(1);
	}
	cout << "Enter Student name: ";
	cin >> name;
	cout << "Enter id: ";
	cin >> id;
	outf << name << "\n";
	outf << id << "\n";
	outf.close();
	return 0;
}

//stream: fstream
#include<fstream>
#include<iostream>
#include<stdlib.h>
using namespace std;
int main() {
	char name[20];
	int id;
	fstream outf("D:\\test\\test.txt", ios::out);		
	if (!outf) {		
		cout << "Input file opening failed";
		exit(1);
	}
	cout << "Enter Student name: ";
	cin >> name;
	cout << "Enter id: ";
	cin >> id;
	outf << name << "\n";
	outf << id << "\n";
	outf.close();
	return 0;
}

//parameterized constructor
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char name[20];
	int id;
	ifstream inf("D:\\test\\cplus.txt");
	inf >> name;
	inf >> id;
	cout << name;
	cout << "\n" << id << endl;
	inf.close();
	return 0;
}

//stream: ofstream and ifstream
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char name[20];
	int id;
	ofstream outf("D:\\test\\test.txt");
	cout << "Enter Student name: ";
	cin >> name;
	cout << "Enter id: ";
	cin >> id;
	outf << name << "\n";
	outf << id << "\n";
	outf.close();
	ifstream inf("D:\\test\\test.txt");
	inf >> name;
	inf >> id;
	cout << name << endl;
	cout << id;
	inf.close();
	return 0;
}

//stream: ofstream
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	ofstream fout;
	fout.open("D:test\\cplus.txt");
	fout << "Sejong" << endl;
	fout << "2012" << endl;
	fout.close();
}

//stream: ifstream
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char name[100];
	int id;
	ifstream fin;
	fin.open("D:test\\cplus.txt");
	fin >> name;
	fin >> id;
	cout << name << endl;
	cout << id << endl;
}

//stream: ofstream and ifstream reading and writing mode
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char name[20];
	int id;
	fstream outf;
	outf.open("D:\\test\\test.txt", ios::out | ios::in);		//file is open for reading and writing purposes
	if (!outf)
		exit(1);
	cout << "Enter Student name: ";
	cin >> name;
	cout << "Enter id: ";
	cin >> id;
	outf << name << "\n";
	outf << id << "\n";
	fstream inf;
	if (!inf)
		exit(1);
	cout << "File content" << endl;
	inf >> name;
	inf >> id;
	cout << name << endl;
	cout << id;
	inf.close();
	return 0;
}

//file handling mode: append mode
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char name[100];
	int id;
	ofstream fout;
	fout.open("D:test\\cplus.txt", ios::app);
	cin >> name;
	cin >> id;
	fout << name << endl;
	fout << id << endl;
	fout.close();
}

//file handling mode: trunc mode
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char name[100];
	int id;
	ofstream fout;
	fout.open("D:test\\cplus.txt", ios::trunc);
	cin >> name;
	cin >> id;
	fout << name << endl;
	fout << id << endl;
	fout.close();
}

//eof() function
#include<fstream>
#include<iostream>
using namespace std;
int main() {
	fstream fin;
	char name[100];
	fin.open("D:\\test\\cplus.txt", ios::in);
	if (!fin.is_open())
		exit(1);
	while (!fin.eof()) {
		fin >> name;
		cout << name << endl;
	}
	fin.close();
}

/**********************************************************************************************************************************************************/

//week 13
//function template ex1
#include<iostream>
using namespace std;
template <class t>
t big(t a, t b) {
	if (a > b)
		return a;
	else
		return b;
}
int main() {
	cout << big(10, 13) << endl;		//t becomes integer for first call
	cout << big(14.5, 15, 6) << endl;		//t becomes integer for second call
}

//function template ex2
#include<iostream>
using namespace std;
template <class t1, class t2>
float big(t1 a, t2 b) {
	if (a > b)
		return a;
	else
		return b;
}
int main() {
	cout << big(15.5, 13) << endl;
	cout << big(10, 14.5) << endl;
	cout << big(10, 14) << endl;
}

//function template array
#include<iostream>
using namespace std;
template <class t>
t sum(t x[], int s) {
	t sum = 0;
	for (int i = 0; i < s; i++)
		sum += x[i];
	return sum;
}
int main() {
	int x[5] = { 0,10,15,14,20 };
	float y[3] = { 10.5,2.5,1.5 };
	cout << sum(x, 5) << endl;
	cout << sum(y, 3) << endl;
	return 0;
}

//overloading function template
#include<iostream>
using namespace std;
template <class t>
t sum(t a, t b) {
	return a + b;
}
template <class t>
t sum(t a, t b, t c) {
	return a + b + c;
}
int main() {
	cout << sum(10, 20) << endl;
	cout << sum(10.1, 9.9) << endl;
	cout << sum(10.2, 8.1, 3.2) << endl;
	cout << sum(1, 4, 8) << endl;
}

//defining template inside class
#include<iostream>
using namespace std;
template <class t>
class test {
	t a, b;
public:
	void get() {
		cin >> a >> b;
	}
	t sum() {
		return a + b;
	}
};
int main() {
	test <int> obj1;
	test <float> obj2;
	obj1.get();
	cout << obj1.sum() << endl;
	obj2.get();
	cout << obj2.sum() << endl;
	return 0;
}

//defining template outside class
#include<iostream>
using namespace std;
template <class t>
class test {
	t a, b;
public:
	void get() {
		cin >> a >> b;
	}
	t sum();
};
template <class t>
t test<t>::sum() {
	return a + b;
}
int main() {
	test <int> obj1;
	test <float> obj2;
	obj1.get();
	cout << obj1.sum() << endl;
	obj2.get();
	cout << obj2.sum() << endl;
	return 0;
}

/**********************************************************************************************************************************************************/

//week 14
//before, after throw
#include<iostream>
using namespace std;
int main() {
	try {
		cout << "Before throw" << endl;
		throw 1;
		cout << "After throw" << endl;
	}
	catch (int x)
		cout << x << "is printed" << endl;
	cout << "Thank you";
}

//throw integer type data
#include<iostream>
using namespace std;
int main() {
	int a, b;
	try {
		cin >> a >> b;
		if (b == 0)
			throw 0;
		cout << "Division: " << a / b;
	}
	catch (int x)
		cout << "Division not possible";
	return 0;
}

//throw character type data
#include<iostream>
using namespace std;
int main() {
	int a, b;
	try {
		cin >> a >> b;
		if (b == 0)
			throw 'a';
		cout << a / b;
	}
	catch (char a)
		cout << "Division is not possible";
}

//ex4
#include<iostream>
using namespace std;
int main() {
	int a, b, x;
	cin >> a >> b;
	x = (a - b);
	try {
		if (x != 0)
			cout << "result: " << (a / (a - b)) << endl;
		else
			throw x;
	}
	catch (int x)
		cout << "Division by zero";
}

//multiple catch ex5
#include<iostream>
using namespace std;
int main() {
	int a = 2;
	try {
		if (a == 1)
			throw a;
		else if (a == 2)
			throw 'A';
		else if (a == 3)
			throw 4.5;
	}
	catch (int a)
		cout << "Integer exception caught" << endl;
	catch (char ch)
		cout << "Character exception caught" << endl;
	catch (double d)
		cout << "Double exception caught" << endl;
	cout << "End of program";
}

//multiple catch ex6
#include<iostream>
using namespace std;
void test(int x) {
	try {
		if (x > 0)
			throw x;
		else
			throw 'A';
	}
	catch (int n)
		cout << "Detected an integer: " << n;
	catch (int c)
		cout << "Detected a character: " << c;
}
int main() {
	int a;
	cout << "Multiple catch statements: ";
	cin >> a;
	test(a);
	return 0;
}

//exception in file handling
#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
int main() {
	char name[100];
	int id;
	ofstream outf("D:\\test1\\test.txt");
	try {
		if (!outf)
			throw 0;
		else {
			cin >> name;
			cin >> id;
			outf << name << endl;
			outf << id;
		}
	}
	catch (int x) {
		cout << "Error occurs in file operation";
		exit(1);
	}
	return 0;
}

//single catch any thrown value
#include<iostream>
using namespace std;
void test(int x) {
	try {
		if (x > 0)
			throw x;
		else
			throw 'A';
	}
	catch (...) {
		cout << "Exception occured: ";
	}
}
int main() {
	int a;
	cout << "Multiple catch statements: ";
	cin >> a;
	test(a);
	return 0;
}

//rethrowing an exception
#include<iostream>
using namespace std;
int main() {
	int a = 1;
	try {
		try
			throw a;
		catch (int x) {
			cout << "Exception in inner try-catch block" << endl;
			throw x;
		}
	}
	catch (int n)
		cout << "Exception in outer try-catch block" << endl;
	cout << "End of program";
}

//exception handling in class
#include<iostream>
using namespace std;
class test {
public:
	test() {
		cout << "I am the constructor" << endl;
	}
	~test() {
		cout << "I am the destructor" << endl;
	}
};
int main() {
	try {
		cout << "Welcome to exception" << endl;
		test t;
		throw 10;
		cout << "testing destructor";
	}
	catch (...) {
		cout << "Thank you" << endl;
	}
}

/**********************************************************************************************************************************************************/

//week 15
//at()
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 5>data_array = { 10, 20, 12, 45, 10 };
	cout << data_array.at(3);
}

//exception with size
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 4>arr = { 10, 20,30,40 };
	try
		cout << arr.at(4);
	catch (...)
		cout << "exception" << endl;
}

//[]operator
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 5>data_array = { 10,20,12,45,100 };
	cout << data_array[2];
}

//front() and back()
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 5>data_array = { 10,20,12,45,100 };
	cout << data_array.front() << endl;
	cout << data_array.back() << endl;
}

//fill()
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 5>data_array = { 10,20,12,45,100 };
	data_array.fill(20);
	for (int i = 0; i < 5; i++)
		cout << data_array[i] << "\t";
}

//empty()
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 2>a1 = { 1,2 };
	array<int, 0>a2;
	cout << a1.empty() << endl;
	cout << a2.empty() << endl;
}

//swap()
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 5>data_array1 = { 10,20,12,45,100 };
	array<int, 5>data_array2 = { 15,30,21,5,0 };
	data_array1.swap(data_array2);
	for (int i = 0; i < 5; i++)
		cout << data_array1[i] << "\t";
	cout << endl;
	for (int i = 0; i < 5; i++)
		cout << data_array2[i] << "\t";
	return 0;
}

//size()
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<int, 5>data_array = { 10,20,12,45,100 };
	cout << data_array.size() << endl;
	return 0;
}

//multi dimensional array
#include<iostream>
#include<array>
using namespace std;
int main() {
	array<array<int, 3>, 3>a{ {{1,2,3},{4,5,6},{7,8,9}} };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << a[i][j] << "\t";
		cout << endl;
	}
	return 0;
}

//iterator
#include<iostream>
#include<array>
#include<iterator>
using namespace std;
int main() {
	array<int, 4>a{ 1,2,3,4 };
	array<int, 4>::iterator ptr;
	for (ptr = a.begin(); ptr != a.end(); ptr++)
		cout << *ptr << endl;
	return 0;
}

//iterator with auto
#include<iostream>
#include<array>
#include<iterator>
using namespace std;
int main() {
	array<int, 4>a{ 1,2,3,4 };
	for (auto i = a.begin(); i != a.end(); i++)
		cout << *i << endl;
	return 0;
}

//sort()
#include<iostream>
#include<array>
#include<iterator>
#include<algorithm>
using namespace std;
int main() {
	array<int, 4>a{ 47,23,90,1 };
	sort(a.begin(), a.end());
	for (int i = a.begin(); i != a.end(); i++)
		cout << *i << endl;
}

#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<int>v1{ 10,11,12 };
	vector<char>v2(4);
	vector<int>v3(5, 10);
	vector<string>v4(3, "hello");
	cout << v4[0] << endl;
	cout << v4[1] << endl;
	cout << v4[2] << endl;
	for (int i = 0; i < 3; i++)
		cout << v1[i] << endl;
	cout << v1.capacity();
}

//setting iterator to vector
#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<int>v1{ 10,11,12 };
	cout << "size = " << v1.size() << endl;
	vector<int>::iterator itr = v1.begin();
	cout << *itr;
	return 0;
}

