#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
template<class C>
class Complex {
private:
	struct PointsC
	{
		C reX = 0, imX = 0, reY = 0, imY = 0;
	};
	PointsC* line = NULL;
	int number_points = 0, more_number = 0;
public:
	Complex<C>(int number_points = 0)
	{
		if (number_points == 0)
		{
			this->number_points = number_points;
			return;
		}
		more_number = number_points * 2;
		line = new Complex[more_number];
		this->number_points = number_points;
	}
	int Get_number_points() const { return number_points; }
	Complex operator +(Complex& other) //конкатенация двух линий 
	{
		if (this->number_points + other.Get_number_points() >= this->more_number)
		{
			this->more_number = (this->Get_more_points() + other.Get_number_points());
			Line* tmpline = new Line[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		for (int i = 0, j = this->number_points; i < other.Get_number_points(); i++, j++)
		{
			this->line[j] = other[i];
		}
		this->number_points += other.Get_number_points();
		return *this;
	}

	Line operator +(Points& point)//сложение ломаной и точки, добавление в конец 
	{
		this->number_points++;
		if (this->Get_number_points() == this->Get_more_points())
		{
			this->more_number *= 2;
			Line* tmpline = new Line[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		(*this)[this->Get_number_points() - 1] = point;
		return *this;
	}
	friend Line operator +(Points& point, Line& tmp_line)//сложение ломаной и точки +
	{
		tmp_line.number_points++;
		if (tmp_line.Get_number_points() == tmp_line.Get_more_points())
		{
			tmp_line.more_number *= 2;
			Line* tline = new Line[tmp_line.Get_more_points()];
			tline = &tmp_line;
			tmp_line = *tline;
		}
		for (int i = tmp_line.Get_number_points() - 1; i != 0; i--)
		{
			tmp_line[i] = tmp_line[i - 1];
		}
		tmp_line[0] = point;
		return tmp_line;
	}
	Complex operator [] (int other_point) const //for reading
	{
		if (other_point >= 0 && other_point < number_points)
			return (line[other_point]);
		throw "!invalid index!";
	}
	Complex& operator [] (int other_point) //for writing
	{
		if (other_point >= 0 && other_point < number_points)
			return (line[other_point]);
		throw "!invalid index!";
	}
	template<class C>
	double Length()
	{
		cout << this;
		double len = 0;
		for (int i = 0; (i + 1) < this->Get_number_points(); i++)
			len += sqrt(pow((*this)[i].reX - (*this)[i + 1].reX + (*this)[i].imX- (*this)[i].imX, 2) + pow((*this)[i].reY - (*this)[i + 1].reY + (*this)[i].imY - (*this)[i].imY, 2));
		return len;
	}

	/*friend istream& operator>>(istream& in, Complex<C>& a)
	{
		for (int i = 0; i < a.Get_number_points(); i++)
		{
			cout << "[" << i + 1 << "] :";
			in >> a.Get_ReX() << " + " << a.Get_ImX() << " * i" << ")" << "," << "(" << a.Get_ReY() << " + " << a.Get_ImY() << " * i" << ")" << ")" << endl;

		}
		return in;
	}
	}*/
	friend ostream& operator<<(ostream& out, Complex<C>& a)
	{
		for (int i = 0; i < a.Get_number_points(); i++)
		{
			out << "[" << i+1 << "]" << "(" << "(" << a.Get_ReX() << " + " << a.Get_ImX() << " * i" << ")" << "," << "(" << a.Get_ReY() << " + " << a.Get_ImY() << " * i" << ")" << ")" << endl;

		}
		return out;
	}
	Complex operator=(const Complex& other)
	{
		for (int i = 0; i < other.Get_number_points(); i++)
		{
			(*this)[i].reX = other[i].reX;
			(*this)[i].reY = other[i].reY;
			(*this)[i].imX = other[i].imX;
			(*this)[i].imY = other[i].imY;
		}
		return *this;
	}
	
	bool operator == (const Complex& other)
	{
		if (this->Get_number_points() == other.Get_number_points())
		{
			for (int i = 0; i < this->Get_number_points(); i++)
			{
				if ((*this)[i].reX != other_line[i].reX || (*this)[i].reY != other_line[i].reY || (*this)[i].imX != other_line[i].imX || (*this)[i].imY != other_line[i].imY)
					return false;
			}
			return true;
		}
		return false;
	}
	bool operator != (const Complex& other)
	{
		if (this->Get_number_points() == other_line.Get_number_points())
		{
			for (int i = 0; i < this->Get_number_points(); i++)
			{
				if ((*this)[i].reX != other_line[i].reX || (*this)[i].reY != other_line[i].reY || (*this)[i].imX != other_line[i].imX || (*this)[i].imY != other_line[i].imY)
					return true;
			}
			return false;
		}
		return true;
	}

	template<class C>
	C Get_ReX()const {
		return this->line->reX;
	}


	C Get_ImX()const {
		return this->line->imX;
	}
	C Get_ReY()const {
		return this->line->reY;
	}


	C Get_ImY()const {
		return this->line->imY;
	}

	void PrintLineC() const
	{
		std::cout << this;
	}
};


template <typename T>
class Line
{
private:
	//
	struct Points
	{
		T x = 0, y = 0;
	};
	//
	Points* line = NULL;
	int number_points = 0, more_number = 0;

public:
	Line<T>(int number_points = 0)
	{
		if (number_points == 0)
		{
			this->number_points = number_points;
			return;
		}
		more_number = number_points * 2;
		line = new Points[more_number];
		this->number_points = number_points;
	}
	Points* GetLine() const { return line; }
	T GetX() const { return line->x; }

	T GetY() const { return line->y; }
	int Get_number_points() const { return number_points; }
	int Get_more_points() const { return more_number; }


	friend std::ostream& operator << (std::ostream& os, const Line point)
	{
		for (int i = 0; i < point.Get_number_points(); i++)
		{
			os << '(' << point[i].x << ';' << point[i].y << ')' << endl;

		}
		return os;
	}


	Points operator [] (int other_point) const //for reading
	{
		if (other_point >= 0 && other_point < number_points)
			return (line[other_point]);
		throw "!invalid index!";
	}
	Points& operator [] (int other_point) //for writing
	{
		if (other_point >= 0 && other_point < number_points)
			return (line[other_point]);
		throw "!invalid index!";
	}//////////////

	Line operator +(Line& other) //конкатенация двух линий 
	{
		if (this->number_points + other.Get_number_points() >= this->more_number)
		{
			this->more_number = (this->Get_more_points() + other.Get_number_points());
			Line* tmpline = new Line[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		for (int i = 0, j = this->number_points; i < other.Get_number_points(); i++, j++)
		{
			this->line[j] = other[i];
		}
		this->number_points += other.Get_number_points();
		return *this;
	}

	Line operator +(Points& point)//сложение ломаной и точки, добавление в конец 
	{
		this->number_points++;
		if (this->Get_number_points() == this->Get_more_points())
		{
			this->more_number *= 2;
			Line* tmpline = new Line[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		(*this)[this->Get_number_points() - 1] = point;
		return *this;
	}
	friend Line operator +(Points& point, Line& tmp_line)//сложение ломаной и точки +
	{
		tmp_line.number_points++;
		if (tmp_line.Get_number_points() == tmp_line.Get_more_points())
		{
			tmp_line.more_number *= 2;
			Line* tline = new Line[tmp_line.Get_more_points()];
			tline = &tmp_line;
			tmp_line = *tline;
		}
		for (int i = tmp_line.Get_number_points() - 1; i != 0; i--)
		{
			tmp_line[i] = tmp_line[i - 1];
		}
		tmp_line[0] = point;
		return tmp_line;
	}
	//template<class C>
	//void SetRe(C Re)
	//{
	//	this->re = Re;
	//}

	//template<class C>
	//void SetIm(C Im)
	//{
	//	this->im = Im;
	//}
	Line operator =(const Line& tmp_line)
	{
		for (int i = 0; i < tmp_line.Get_number_points(); i++)
		{
			(*this)[i] = tmp_line[i];
		}
		return *this;
	}
	bool operator == (const Line& other_line)
	{
		if (this->Get_number_points() == other_line.Get_number_points())
		{
			for (int i = 0; i < this->Get_number_points(); i++)
			{
				if ((*this)[i].x != other_line[i].x || (*this)[i].y != other_line[i].y)
					return false;
			}
			return true;
		}
		return false;
	}
	bool operator != (const Line& other_line)
	{
		if (this->Get_number_points() == other_line.Get_number_points())
		{
			for (int i = 0; i < this->Get_number_points(); i++)
			{
				if ((*this)[i].x != other_line[i].x || (*this)[i].y != other_line[i].y)
					return true;
			}
			return false;
		}
		return true;
	}
	double Length()
	{
		for (int i = 0; i < this->Get_number_points(); i++)
			cout << "[" << i + 1 << "]" << " = " << "(" << (*this)[i].x << ";" << (*this)[i].y << ")" << endl;
		double len = 0;
		for (int i = 0; (i + 1) < this->Get_number_points(); i++)
			len += pow(pow(abs((*this)[i + 1].x - (*this)[i].x), 2) + pow(abs((*this)[i + 1].y - (*this)[i].y), 2), 0.5);
		return len;
	}
	void PrintLine() const
	{
		std::cout << this[0];
	}
};


//
template <class T>
Line<T> CreatingLine(Line<T>& start_line) {
	T x, y;
	for (int i = 0; i < start_line.Get_number_points(); i++)
	{
		std::cout << endl << "Enter the coordinates of the point:" << endl;
		std::cout << endl << "x = ";
		std::cin >> x;
		std::cout << endl << "y = ";
		std::cin >> y;
		start_line[i].x = x;
		start_line[i].y = y;
	}
	return start_line;
}

template <class C>
Complex<C> CreatingLineC(Complex<C>& start_line) {
	C x, y;
	for (int i = 0; i < start_line.Get_number_points(); i++)
	{
		cout << endl << "Enter the coordinates of the point:" << endl;
		cout << "x: ";
		cin >> x;
		cout << "y: ";
		cin >> y;
		start_line[i].x. = x;
		start_line[i].y = y;
	}
	return start_line;
}

//

template <class T>
int IndexPoint(Line<T>& start_line, bool flag)
{
	system("cls");
	flag = true;
	int index = 0;
	while (flag)
	{
		int choice = 0;
		std::cout << endl << "To continue, press any key except 'Backspace'..." << endl;
		std::cout << endl << "or 'Backspace' because to back to main menu" << endl;
		choice = getchar();
		if (choice == 8) return choice;
		while (flag)
		{
			std::cout << endl << "Enter index:" << endl;
			std::cin >> index;
			try {
				if (index <= 0 || index > start_line.Get_number_points()) throw "!There is no such index point!";
				flag = false;
			}
			catch (const char* ex)
			{
				std::cout << ex << endl;
				std::cout << endl << "Try again" << endl;
			}
		}
		flag = true;
		while (flag)
		{
			try {
				std::cout << "Select:" << endl;
				std::cout << "1) Read coordinates";
				std::cout << "   2) Change coordinates" << endl;
				cin >> choice;
				if (choice != 1 && choice != 2) throw"!There is no such index point";
				flag = false;
			}
			catch (const char* ex)
			{
				std::cout << ex << endl;
				std::cout << endl << "Try again" << endl;
			}
		}
		if (choice == 1) cout << "Coordinates: " << "(" << start_line[index - 1].x << ";" << start_line[index - 1].y << ")" << endl << endl;
		if (choice == 2)
		{
			int x = 0, y = 0;
			std::cout << "Enter х: ";
			std::cin >> x;
			std::cout << "Enter y: ";
			std::cin >> y;
			start_line[index - 1].x = x;
			start_line[index - 1].y = y;
			std::cout << start_line << endl;
			std::cout << "Coordinates of the point with index " << index << " = (" << start_line[index - 1].x << "; " << start_line[index - 1].y << ")" << endl << endl;
		}
		std::cout << "Press 'Backspace' to return";
		choice = getchar();
		if (choice == 8) flag = true;
	}
	return -1;
}

template <class T>
int SumLine(Line<T>& start_line, bool flag)
{
	int choice = 0;
	bool flag1 = true;
	flag = true;
	int n = 0;
	std::cout << "Point coordinates of the first broken line" << endl;
	start_line.PrintLine();
	while (flag1)
	{
		try {
			std::cout << "Press the second broken line " << endl;
			flag = true;

			while (flag)
			{
				try
				{
					std::cout << "Number of points: ";
					cin >> n;
					if (n < 2) throw "The numbers of points must be >= 2";
					flag = false;
				}
				catch (const char* ex)
				{
					std::cout << ex << endl;
					std::cout << endl << "Try again" << endl;
				}
			}
		}
		catch (const char* ex)
		{
			std::cout << ex << endl;
			std::cout << endl << "Try again" << endl;
		}
		Line<T> tmp_line(n);
		Line<T> new_line = CreatingLine(tmp_line);
		flag1 = false;
		std::cout << "Point coordinates of the second broken line" << endl;
		new_line.PrintLine();
		start_line = start_line + new_line;
		std::cout << endl << "Result: " << endl;
		start_line.PrintLine();
		std::cout << "Press 'Backspace' to return" << endl << endl;
		choice = getchar();
		if (choice == 8) flag1 = true;
	}
	return -1;
}

template <class T>
int SumPoint_Line(Line<T>& start_line, bool flag)
{
	int choice = 0;
	flag = true;
	while (flag)
	{
		std::cout << endl << "To continue, press any key except 'Backspace'..." << endl;
		std::cout << endl << "or 'Backspace' because to back to main menu" << endl;
		choice = getchar();
		if (choice == 8) return choice;
		T x = 0, y = 0;
		std::cout << "Press coordinates of the point which want to add: " << endl;
		std::cout << "x = ";
		cin >> x;
		std::cout << "y = ";
		cin >> y;
		Line<T> point(1);
		point[0].x = x;
		point[0].y = y;
		Line<T> tmp_line = point[0] + start_line;
		tmp_line.PrintLine();
		start_line = tmp_line;
		std::cout << endl << "Press 'Backspace' if want to back" << endl << endl;
		choice = getchar();
		if (choice == 8) flag = true;
	}
	return -1;
}

template <class T>
int SumLine_Point(Line<T>& start_line, bool flag)
{
	int choice = 0;
	flag = true;
	while (flag)
	{
		std::cout << endl << "To continue, press any key except 'Backspace'..." << endl;
		std::cout << endl << "or 'Backspace' because to back to main menu" << endl;
		choice = getchar();
		if (choice == 8) return choice;
		T x = 0, y = 0;
		std::cout << "Press coordinates of the point which want to add: " << endl;
		std::cout << "x = ";
		std::cin >> x;
		std::cout << "y = ";
		std::cin >> y;
		Line<T> point(1);
		point[0].x = x;
		point[0].y = y;
		Line<T> tmp_line = start_line + point[0];
		start_line = tmp_line;
		tmp_line.PrintLine();
		std::cout << endl << "Press 'Backspace' if want to back" << endl << endl;
		choice = getchar();
		if (choice == 8) flag = true;
	}
	return -1;
}

template <class T>
int LenLine(Line<T>& start_line)
{
	int choice = 0;
	std::cout << "Length of the line: " << start_line.Length() << endl;
	std::cout << endl << "Press 'Backspace' if want to back" << endl << endl;
	choice = getchar();
	if (choice == 8) return choice;
	return -1;
}

template <class T>
int Compare(Line<T>& start_line)
{
	int choice = 0;
	T x = 0, y = 0;
	bool flag1 = true, flag = true;
	int n = 0;
	std::cout << "Point coordinates of the first broken line" << endl;
	start_line.PrintLine();
	while (flag1)
	{
		choice = getchar();
		if (choice == 8) return choice;
		try {
			std::cout << "Press the second broken line " << endl;
			flag = true;

			while (flag)
			{
				try
				{
					std::cout << "Number of points: ";
					std::cin >> n;
					if (n < 2) throw "The numbers of points must be >= 2";
					flag = false;
					flag1 = false;
				}
				catch (const char* ex)
				{
					std::cout << ex << endl;
					std::cout << endl << "Try again" << endl;
				}
			}
		}
		catch (const char* ex)
		{
			std::cout << ex << endl;
			std::cout << endl << "Try again" << endl;
		}

		Line<T> tmp_line(n);
		Line<T> new_line = CreatingLine(tmp_line);
		flag1 = false;
		new_line.PrintLine();
		if (start_line == new_line) cout << "The broken lines are equal!" << endl;
		if (start_line != new_line) cout << "The broken lines are unequal!" << endl;
		std::cout << "Press 'Backspace' to return" << endl << endl;
		choice = getchar();
		if (choice == 8) flag1 = true;
	}
	return -1;
}

void menu0()
{
	system("cls");
	std::cout << endl << "Choose where you want to start" << endl << endl;
	std::cout << "1. Create a broken line" << endl;
	std::cout << "2. Build a rectangular trapezoid" << endl;
	std::cout << "3. Complete the job" << endl;

}

void menu1()
{
	std::cout << endl << endl << "Next choice: " << endl;
	std::cout << "1. Know/change point coordinates of the broken line" << endl;
	std::cout << "2. Broken lines concatenation" << endl;
	std::cout << "3. Add the line to the point (add a point at the start of the line)" << endl;
	std::cout << "4. Add the point to the line (add a point at the finish of the line)" << endl;
	std::cout << "5. Calculate the length of the line" << endl;
	std::cout << "6. Compare broken lines" << endl;
	std::cout << "7. Back to main menu" << endl;
}

template <class T>
void AutoCreateLine(T x, T y, Line<T>& line, T a, T b, T h)
{
	line[0].x = x;
	line[0].y = y;
	line[1].x = x;
	line[1].y = y + a;
	line[2].x = x + h;
	line[2].y = y + a;
	line[3].x = x + h;
	line[3].y = y + a - b;
	line[4].x = x;
	line[4].y = y;
	line.PrintLine();
}

template <class C>
void AutoCreateLineC(Complex<C> x, Complex<C> y, Line<C>& line, Complex<C> a, Complex<C> b, Complex<C> h)
{

	line[0].x = x.Get_Re();
	line[0].y = y.Get_Im();
	line[1].x = x.Get_Re();
	line[1].y = y.Get_Im() + a.Get_Im();
	line[2].x = x.Get_Re() + h.Get_Re();
	line[2].y = y.Get_Im() + a.Get_Im();
	line[3].x = x.Get_Re() + h.Get_Re();

	line[3].y = y.Get_Im() + a.Get_Im() - b.Get_Im();
	line[4].x = x.Get_Re();
	line[5].y = y.Get_Im();
	line.PrintLine();
}

template <class T>
Line<T>& CreatingRecTrapezoid(bool flag)
{
	Line<T> line(5);
	int choice = 0;
	T a = 0, b = 0, h = 0, x = 0, y = 0;
	system("cls");
	flag = true;
	while (flag)
	{
		try {
			std::cout << "Enter the bases ( a and b )  and height h:" << endl;
			std::cout << "a: ";
			std::cin >> a;
			if (a <= 0) throw "Value a must be > 0";
			std::cout << "b: ";
			std::cin >> b;
			if (b <= 0) throw "Value b must be > 0";
			std::cout << "h: ";
			std::cin >> h;
			if (h <= 0) throw "Value h must be > 0";
			flag = false;
		}
		catch (const char* ex)
		{
			cout << ex << endl;
			cout << endl << "Try again" << endl;
		}
	}
	std::cout << "Press coordinaes of the first point" << endl;
	std::cout << "х = ";
	cin >> x;
	std::cout << "y = ";
	cin >> y;
	AutoCreateLine(x, y, line, a, b, h);
	return line;
}

template <typename C>
Line<C>& CreatingRecTrapezoidC(bool flag)
{
	Line<C> line(5);
	int choice = 0;
	Complex<C> a, b, h, x, y;
	system("cls");
	flag = true;
	while (flag)
	{
		try {
			std::cout << "Enter the bases ( a and b )  and height h:" << endl;
			std::cout << "a: ";
			std::cin >> a;
			std::cout << "b: ";
			std::cin >> b;
			std::cout << "h: ";
			std::cin >> h;

			flag = false;
		}
		catch (const char* ex)
		{
			cout << ex << endl;
			cout << endl << "Try again" << endl;
		}
	}
	std::cout << "Press coordinaes of the first point" << endl;
	std::cout << "x = ";
	cin >> x;
	std::cout << "y = ";
	cin >> y;
	AutoCreateLineC(x, y, line, a, b, h);
	return line;
}

template <class T>
bool JobWithLine(bool flag, bool flag1, int choice, Line<T>& start_line)
{
	menu1();
	flag = true;
	while (flag)
	{
		try {
			std::cin >> choice;
			if (choice > 8 || choice < 1) throw "!There is no such option!";
			flag = false;
		}
		catch (const char* ex)
		{
			std::cout << ex << endl;
			std::cout << endl << "Try again" << endl;
		}
	}
	if (choice == 1)
		if (IndexPoint(start_line, flag) == 8) flag1 = true;
	if (choice == 2)
		if (SumLine(start_line, flag) == 8) flag1 = true;
	if (choice == 3)
		if (SumPoint_Line(start_line, flag) == 8) flag1 = true;
	if (choice == 4)
		if (SumLine_Point(start_line, flag) == 8) flag1 = true;
	if (choice == 5)
		if (LenLine(start_line) == 8) flag1 = true;
	if (choice == 6)
		if (Compare(start_line) == 8) flag1 = true;
	if (choice == 7)
	{
		flag = true;
		flag1 = false;
	}

	return flag1;
}

int main()
{
	int choice = 0;
	int type = 0;
	bool flag = true, flag1 = true;
	while (flag)
	{
		menu0();
		std::cout << "Choice: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{

			flag = true;
			int n = 0;

			while (flag)
			{
				try
				{
					std::cout << "Number of points: ";
					std::cin >> n;
					if (n < 2) throw "The numbers of points muct be >= 2";
					flag = false;
				}
				catch (const char* ex)
				{
					std::cout << ex << endl;
					std::cout << endl << "Try again" << endl;
				}
			}
			std::cout << "Choice data type: 1 - int, 2 - float, 3 - double, 4 - complex float, 5 - complex double: ";
			std::cin >> type;
			flag = true;
			flag1 = true;

			if (type == 1) {
				Line<int> tmp_line(n);
				Line<int> start_line = CreatingLine<int>(tmp_line);
				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, start_line);
				break;

			}
			else if (type == 2) {
				Line<float> tmp_line(n);
				Line<float> start_line = CreatingLine<float>(tmp_line);

				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, start_line);
				break;
			}
			else if (type == 3) {
				Line<double> tmp_line(n);
				Line<double> start_line = CreatingLine<double>(tmp_line);

				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, start_line);
				break;
			}
			else if (type == 4) {
				Complex<float> tmp_line(n);
				Complex<float> start_line = CreatingLineC<float>(tmp_line);

				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, start_line);
				break;
			}
			else if (type == 5) {
				Line<double>tmp_line(n);
				Line<double> start_line = CreatingLineC<double>(tmp_line);

				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, start_line);
				break;
			}

		}
		case 2:
		{
			std::cout << "Choice data type:1 - int, 2 - float, 3 - double, 4 - complex float, 5 - complex double\n";
			std::cin >> type;
			flag = true;
			flag1 = true;
			if (type == 1) {
				Line<int> line = CreatingRecTrapezoid<int>(flag);
				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, line);
				break;

			}
			if (type == 2) {
				Line<float> line = CreatingRecTrapezoid<float>(flag);
				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, line);
				break;
			}
			if (type == 3) {
				Line<double> line = CreatingRecTrapezoid<double>(flag);
				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, line);
				break;
			}
			else if (type == 4) {
				Line<float> line = CreatingRecTrapezoidC<float>(flag);
				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, line);
				break;
			}

			else if (type == 5) {
				Line<double> line = CreatingRecTrapezoidC<double>(flag);
				while (flag1)
					flag1 = JobWithLine(flag, flag1, choice, line);
				break;

			}

		}
		case 3:
		{
			return 0;
		}
		default:
			try {
				if (choice != 1 && choice != 2) throw "!There is no such option!";
			}
			catch (const char* ex)
			{
				std::cout << ex << endl;
				std::cout << endl << "Try again" << endl;
			}
			break;
		}
	}
}
