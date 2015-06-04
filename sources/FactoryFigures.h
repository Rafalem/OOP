#include "Shapes.h"

class FactoryFigures
{
public:
	Point * CreatePoint(std::string const &);
	Rect * CreateRect(std::string const &);
	Circle * CreateCircle(std::string const &);
	Polyline * CreatePolyline(std::string const &);
	Polygon * CreatePolygon(std::string const &);

	Shape * CreateRandomShape(std::string const &);
};

Point * FactoryFigures::CreatePoint(std::string const & name)
{
	uint32_t x = rand() % 100;
	uint32_t y = rand() % 100;

	return new Point(name, x, y);
}
Rect * FactoryFigures::CreateRect(std::string const & name)
{
	Point * position = CreatePoint("pos");
	uint32_t h = rand() % 99 + 1;
	uint32_t w = rand() % 99 + 1;

	return new Rect(name, h, w, *position);
}

Circle * FactoryFigures::CreateCircle(std::string const & name)
{
	Point * center = CreatePoint("cent");
	uint32_t radius = rand() % 99 + 1;

	return new Circle(name, radius, * center);
}

Polyline * FactoryFigures::CreatePolyline(std::string const & name)
{
	int numPoints = rand() % 4 + 2;//2...5 points
	Polyline * p = new Polyline(name);
	
	for (int i = numPoints; i>0; --i)
	{
		std::stringstream r;
		r << i;
		p->AddPoint(CreatePoint("P" + r.str()));
	}
	return p;
}

Polygon * FactoryFigures::CreatePolygon(std::string const & name)
{
	int numPoints = rand() % 3 + 3;//3...5 points
	XList<Point * > points;

	for (int i = 0; i<numPoints; ++i)
	{
		std::stringstream r;
		r << (i+1);
		points.AddEnd(CreatePoint("P" + r.str()));
	}
	return new Polygon(name, points);
}


Shape * FactoryFigures::CreateRandomShape(std::string const & name)
{
	int i = rand() % 5 + 1;

	switch (i)
	{
	case 1: { return CreatePoint(name); }
	case 2: { return CreateRect(name); }
	case 3: { return CreateCircle(name); }
	case 4: { return CreatePolyline(name); }
	case 5: { return CreatePolygon(name);  }

	default: {return CreatePoint(name); }
	}
}