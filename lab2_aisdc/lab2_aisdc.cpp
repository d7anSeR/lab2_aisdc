#include <iostream>
#include <cstdlib>
#include <math.h>
#include <conio.h>

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
		line = new PointsC[more_number];
		this->number_points = number_points;
	}
	int Get_number_points() const { return number_points; }
	int Get_more_points() const { return more_number; }
	PointsC* GetLine() const { return line; }
	Complex operator +(Complex& other) //конкатенация двух линий 
	{
		if (this->number_points + other.Get_number_points() >= this->more_number)
		{
			this->more_number = (this->Get_more_points() + other.Get_number_points());
			Complex* tmpline = new Complex[this->Get_more_points()];
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

	Complex operator +(PointsC& point)//сложение ломаной и точки, добавление в конец 
	{
		this->number_points++;
		if (this->Get_number_points() == this->Get_more_points())
		{
			this->more_number *= 2;
			Complex* tmpline = new Complex[this->Get_more_points()];
			tmpline = this;
			*this = *tmpline;
		}
		(*this)[this->Get_number_points() - 1] = point;
		return *this;
	}

	friend Complex operator +(PointsC& point, Complex& tmp_line)//сложение ломаной и точки +
	{
		tmp_line.number_points++;
		if (tmp_line.Get_number_points() == tmp_line.Get_more_points())
		{
			tmp_line.more_number *= 2;
			Complex* tline = new Complex[tmp_line.Get_more_points()];
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
	PointsC operator [] (int other_point) const //for reading
	{
		if (other_point >= 0 && other_point < number_points)
			return (line[other_point]);
		throw "!invalid index!";
	}
	PointsC& operator [] (int other_point) //for writing
	{
		if (other_point >= 0 && other_point < number_points)
			return (line[other_point]);
		throw "!invalid index!";
	}
	template<class C>
	double LengthC() const
	{
		this->PrintLineC();
		double len = 0, a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
		for (int i = 0; (i + 1) < this->Get_number_points(); i++)
		{
			a = (*this)[i + 1].reX - (*this)[i].reX; //действительная часть
			b = (*this)[i + 1].imX - (*this)[i].imX;//мнимая часть
			c = pow(a, 2) - pow(b, 2);
			d = 2 * a * b; //*i
			e = (*this)[i + 1].reY - (*this)[i].reY; //действительная часть
			f = (*this)[i + 1].imY - (*this)[i].imY;//мнимая часть
			g = pow(e, 2) - pow(f, 2);
			h = 2 * e * f; //*i
			len += sqrt(sqrt(pow(c + g, 2) + pow(d + h, 2)));
		}
		return double(len);
	}
	friend ostream& operator<<(ostream& out, Complex& a)
	{
		for (int i = 0; i < a.Get_number_points(); i++)
		{
			out << "[" << i+1 << "]" << "(" << "(" << a[i].reX << ";" << a[i].imX << ")" << "," << "(" << a[i].reY << ";" << a[i].imY << ")" << ")" << endl;

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
				if ((*this)[i].reX != other[i].reX || (*this)[i].reY != other[i].reY || (*this)[i].imX != other[i].imX || (*this)[i].imY != other[i].imY)
					return false;
			}
			return true;
		}
		return false;
	}
	bool operator != (const Complex& other)
	{
		if (this->Get_number_points() == other.Get_number_points())
		{
			for (int i = 0; i < this->Get_number_points(); i++)
			{
				if ((*this)[i].reX != other[i].reX || (*this)[i].reY != other[i].reY || (*this)[i].imX != other[i].imX || (*this)[i].imY != other[i].imY)
					return true;
			}
			return false;
		}
		return true;
	}

	template<class C>
	C Get_ReX()const {
		return line->reX;
	}
	C Get_ImX()const {
		return line->imX;
	}
	C Get_ReY()const {
		return line->reY;
	}
	C Get_ImY()const {
		return line->imY;
	}
	void PrintLineC()
	{
		std::cout << *this;
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
		std::cout << *this;
	}
};



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
Complex<C> CreatingLineC(Complex<C> start_line) {
	C x1 = 0, x2 = 0, y1 = 0, y2 =0;
	for (int i = 0; i < start_line.Get_number_points(); i++)
	{
		cout << endl << "Enter the coordinates of the point:" << endl;
		cout << "x1: ";
		cin >> x1;
		cout << "x2: ";
		cin >> x2;
		cout << "y1: ";
		cin >> y1;
		cout << "y2: ";
		cin >> y2;
		start_line[i].reX = x1;
		start_line[i].imX = x2;
		start_line[i].reY = y1;
		start_line[i].imY = y2;
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
		choice = _getch();
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
			start_line[index - 1].x = T(x);
			start_line[index - 1].y = T(y);
			std::cout << start_line << endl;
			std::cout << "Coordinates of the point with index " << index << " = (" << start_line[index - 1].x << "; " << start_line[index - 1].y << ")" << endl << endl;
		}
		std::cout << "Press 'Backspace' to return";
		choice = _getch();
		if (choice == 8) flag = true;
	}
	return -1;
}
template <class C>
int IndexPointC(Complex<C>& start_line, bool flag)
{
	system("cls");
	flag = true;
	int index = 0;
	while (flag)
	{
		int choice = 0;
		std::cout << endl << "To continue, press any key except 'Backspace'..." << endl;
		std::cout << endl << "or 'Backspace' because to back to main menu" << endl;
		choice = _getch();
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
		if (choice == 1) cout << "Coordinates: " << "(" << "(" << start_line[index - 1].reX << ";" << start_line[index - 1].imX << ")" << "," << "(" << start_line[index - 1].reY << ";" << start_line[index - 1].imY << ")" << ")" << endl;
		if (choice == 2)
		{
			int x1 = 0, x2 = 0, y1 = 0, y2 =0;
			std::cout << "Enter х1: ";
			std::cin >> x1;
			std::cout << "Enter x2: ";
			std::cin >> x2;
			std::cout << "Enter y1: ";
			std::cin >> y1;
			std::cout << "Enter y2: ";
			std::cin >> y2;
			start_line[index - 1].reX = C(x1);
			start_line[index - 1].imX = C(x2);
			start_line[index - 1].reY = C(y1);
			start_line[index - 1].imY = C(y2);
			std::cout << start_line << endl;
			std::cout << "Coordinates of the point with index " << index << " = (" << "(" << start_line[index - 1].reX << ";" << start_line[index - 1].imX << ")" << "," << "(" << start_line[index - 1].reY << ";" << start_line[index - 1].imY << ")" << ")" << endl << endl;
		}
		std::cout << "Press 'Backspace' to return";
		choice = _getch();
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
		choice = _getch();
		if (choice == 8) flag1 = true;
	}
	return -1;
}
template <class C>
int SumLineC(Complex<C>& start_line, bool flag)
{
	int choice = 0;
	bool flag1 = true;
	flag = true;
	int n = 0;
	std::cout << "Point coordinates of the first broken line" << endl;
	start_line.PrintLineC();
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
		Complex<C> tmp_line(n);
		Complex<C> new_line = CreatingLineC(tmp_line);
		flag1 = false;
		std::cout << "Point coordinates of the second broken line" << endl;
		new_line.PrintLineC();
		start_line = start_line + new_line;
		std::cout << endl << "Result: " << endl;
		start_line.PrintLineC();
		std::cout << "Press 'Backspace' to return" << endl << endl;
		choice = _getch();
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
		choice = _getch();
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
		choice = _getch();
		if (choice == 8) flag = true;
	}
	return -1;
}
template <class C>
int SumPoint_LineC(Complex<C>& start_line, bool flag)
{
	int choice = 0;
	flag = true;
	while (flag)
	{
		std::cout << endl << "To continue, press any key except 'Backspace'..." << endl;
		std::cout << endl << "or 'Backspace' because to back to main menu" << endl;
		choice = _getch();
		if (choice == 8) return choice;
		C x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		std::cout << "Press coordinates of the point which want to add: " << endl;
		std::cout << "x1 = ";
		cin >> x1;
		std::cout << "x2 = ";
		cin >> x2;
		std::cout << "y1 = ";
		cin >> y1;
		std::cout << "y2 = ";
		cin >> y2;
		Complex<C> point(1);
		point[0].reX = x1;
		point[0].imX = x2;
		point[0].reY = y1;
		point[0].imY = y2;
		Complex<C> tmp_line = point[0] + start_line;
		tmp_line.PrintLineC();
		start_line = tmp_line;
		std::cout << endl << "Press 'Backspace' if want to back" << endl << endl;
		choice = _getch();
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
		choice = _getch();
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
		choice = _getch();
		if (choice == 8) flag = true;
	}
	return -1;
}
template <class C>
int SumLine_PointC(Complex<C>& start_line, bool flag)
{
	int choice = 0;
	flag = true;
	while (flag)
	{
		std::cout << endl << "To continue, press any key except 'Backspace'..." << endl;
		std::cout << endl << "or 'Backspace' because to back to main menu" << endl;
		choice = _getch();
		if (choice == 8) return choice;
		C x1 = 0, x2 = 0, y1 = 0, y2 = 0;
		std::cout << "Press coordinates of the point which want to add: " << endl;
		std::cout << "x1 = ";
		std::cin >> x1;
		std::cout << "x2 = ";
		std::cin >> x2;
		std::cout << "y1 = ";
		std::cin >> y1;
		std::cout << "y2 = ";
		std::cin >> y2;
		Complex<C> point(1);
		point[0].reX = x1;
		point[0].imX = x2;
		point[0].reY = y1;
		point[0].imY = y2;
		Complex<C> tmp_line = start_line + point[0];
		start_line = tmp_line;
		tmp_line.PrintLineC();
		std::cout << endl << "Press 'Backspace' if want to back" << endl << endl;
		choice = _getch();
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
	choice = _getch();
	if (choice == 8) return choice;
	return -1;
}
template <class C>
int LenLineC(const Complex<C>& start_line)
{
	int choice = 0;
	/*double leng = start_line.LengthC();
	cout << "Length of the line: " << leng << endl;*/
	std::cout << endl << "Press 'Backspace' if want to back" << endl << endl;
	choice = _getch();
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
		choice = _getch();
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
		choice = _getch();
		if (choice == 8) flag1 = true;
	}
	return -1;
}
template <class C>
int CompareC(Complex<C>& start_line)
{
	int choice = 0;
	C x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	bool flag1 = true, flag = true;
	int n = 0;
	std::cout << "Point coordinates of the first broken line" << endl;
	start_line.PrintLineC();
	while (flag1)
	{
		choice = _getch();
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

		Complex<C> tmp_line(n);
		Complex<C> new_line = CreatingLineC(tmp_line);
		flag1 = false;
		new_line.PrintLineC();
		if (start_line == new_line) cout << "The broken lines are equal!" << endl;
		if (start_line != new_line) cout << "The broken lines are unequal!" << endl;
		std::cout << "Press 'Backspace' to return" << endl << endl;
		choice = _getch();
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
void AutoCreateLineC(C x1, C x2, C y1, C y2, Complex<C>& line, C a, C b, C h)
{
	line[0].reX = x1;
	line[0].imX = x2;
	line[0].reY = y1;
	line[0].imY = y2;
	line[1].reX = x1;
	line[1].imX = x2;
	line[1].reY = y1 + a;
	line[1].imY = y2 + a;
	line[2].reX = x1 + h;
	line[2].imX = x2 + h;
	line[2].reY = y1 + a;
	line[2].imY = y2 + a;
	line[3].reX = x1 + h;
	line[3].imX = x2 + h;
	line[3].reY = y1 + a - b;
	line[3].imY = y2 + a - b;
	line[4].reX = x1;
	line[4].imX = x2;
	line[4].reY = y1;
	line[4].imY = y2;
	line.PrintLineC();
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

template <class C>
Complex<C>& CreatingRecTrapezoidC(bool flag)
{
	Complex<C> line(5);
	int choice = 0;
	C a = 0, b = 0, h = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
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
	std::cout << "х1 = ";
	cin >> x1;
	std::cout << "х2 = ";
	cin >> x2;
	std::cout << "y1 = ";
	cin >> y1;
	std::cout << "y2 = ";
	cin >> y2;
	AutoCreateLineC(x1, x2, y1, y2, line, a, b, h);
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
template <class C>
bool JobWithLineC(bool flag, bool flag1, int choice, Complex<C>& start_line)
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
		if (IndexPointC(start_line, flag) == 8) flag1 = true;
	if (choice == 2)
		if (SumLineC(start_line, flag) == 8) flag1 = true;
	if (choice == 3)
		if (SumPoint_LineC(start_line, flag) == 8) flag1 = true;
	if (choice == 4)
		if (SumLine_PointC(start_line, flag) == 8) flag1 = true;
	if (choice == 5)
		if (LenLineC(start_line) == 8) flag1 = true;
	if (choice == 6)
		if (CompareC(start_line) == 8) flag1 = true;
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
					flag1 = JobWithLineC(flag, flag1, choice, start_line);
				break;
			}
			else if (type == 5) {
				Complex<double>tmp_line(n);
				Complex<double> start_line = CreatingLineC<double>(tmp_line);

				while (flag1)
					flag1 = JobWithLineC(flag, flag1, choice, start_line);
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
				Complex<float> line = CreatingRecTrapezoidC<float>(flag);
				while (flag1)
					flag1 = JobWithLineC(flag, flag1, choice, line);
				break;
			}

			else if (type == 5) {
				Complex<double> line = CreatingRecTrapezoidC<double>(flag);
				while (flag1)
					flag1 = JobWithLineC(flag, flag1, choice, line);
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

template class Complex <float>;
template class Complex<double>;
template class Line <int>;
template class Line<float>;
template class Line<double>;
