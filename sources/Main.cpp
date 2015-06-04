#include <iostream>
#include <sstream>
#include "FactoryFigures.h"
#include <ctime>

std::string IntToStr(int x)
{
	std::stringstream r;
	r << x;
	return r.str();
}

void testXList()
{
	std::cout << "Testing XList..." << std::endl;

	XList <std::string> MyList;

	for (int i = 0; i < 25; ++i)
	{
		MyList.AddEnd(IntToStr(rand()%100));
	}

	MyList.AddFront("987");

	std::cout << "---------------------" << std::endl;
	MyList.Show();
	std::cout << "---------------------" << std::endl;

	std::cout << "Size of list:\t" << MyList.GetLength() << std::endl;
	std::cout << "First element:\t" << MyList.GetFirst() << std::endl;
	std::cout << "Last element:\t" << MyList.GetLast() << std::endl;
	
	MyList.RemoveFront();
	std::cout << std::endl;
	std::cout << "After delete first element: ";
	std::cout << "First element: " << MyList.GetFirst() << std::endl;

	MyList.RemoveEnd();
	std::cout << std::endl;
	std::cout << "After delete last element: ";
	std::cout << "Last element: " << MyList.GetLast() << std::endl;

	MyList.Clear();
	std::cout << std::endl;
	std::cout << "After list clean: ";
	std::cout << "List is empty? " << MyList.IsEmpty() << std::endl;
}

void testFactory()
{
	FactoryFigures factory;
	XList<Shape *> shapes;

	for (int i = 0; i < 20; ++i)
	{
		shapes.AddEnd(factory.CreateRandomShape("S" + IntToStr(i + 1)));
	}

	shapes.IteratorInitial();//Set on begin of the list
	
	int i = 0;
	while (!shapes.IteratorIsEnd())
	{
		i++;
		std::cout <<i<<") "<< * dynamic_cast<Printable *>(shapes.IteratorGetValue());
		shapes.IteratorToNext();
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Count of shapes:\t" << Shape::GetCount() << std::endl;
	std::cout << "Count of points:\t" << Point::GetCount() << std::endl;
	std::cout << "Count of rectangles:\t" << Rect::GetCount() << std::endl;
	std::cout << "Count of circles:\t" << Circle::GetCount() << std::endl;
	std::cout << "Count of polyline:\t" << Polyline::GetCount() << std::endl;
	std::cout << "Count of polygon:\t" << Polygon::GetCount() << std::endl;

	shapes.IteratorInitial();
	while (!shapes.IteratorIsEnd())
	{
		delete shapes.IteratorGetValue();
		shapes.IteratorToNext();
	}

	std::cout << std::endl;
	std::cout << "After memory clean: "  << std::endl << std::endl;
	std::cout << "Count of shapes:\t"	 << Shape::GetCount() << std::endl;
	std::cout << "Count of points:\t"	 << Point::GetCount() << std::endl;
	std::cout << "Count of rectangles:\t"<< Rect::GetCount() << std::endl;
	std::cout << "Count of circles:\t"	 << Circle::GetCount() << std::endl;
	std::cout << "Count of polyline:\t"	 << Polyline::GetCount() << std::endl;
	std::cout << "Count of polygon:\t"	 << Polygon::GetCount() << std::endl;
}

int main()
{
	srand(time(NULL)); //truly random
	//setlocale(LC_ALL, "Russian");
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);

	//testXList();
	testFactory();

	getchar();
	return 0;
}