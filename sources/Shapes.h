#include "Base.h"
#include "XList.h"

class Shape : public virtual Named
{
public:
	virtual ~Shape() { --sm_counter; }
	static uint32_t GetCount() { return sm_counter; }
	Shape(std::string const & name) : Named(name) { ++sm_counter; }

private:
	static uint32_t sm_counter;
};

class Point : public Printable, public Shape
{
public:
	Point(std::string const & name, uint32_t const & x, uint32_t const & y) : Shape(name), Printable(name), Named(name)
	{
		m_x = x;  m_y = y;
		++sm_pointCounter;
	}
	Point() : Shape("some point"), Printable("some point"), Named("some point")
	{
		m_x = 0;  m_y = 0;
		++sm_pointCounter;
	}
	Point(Point const & point) : Shape(point.m_name), Printable(point.m_name), Named(point.m_name)
	{
		m_x = point.m_x;  m_y = point.m_y;
		++sm_pointCounter;
	}

	~Point()
	{
		--sm_pointCounter;
	}

	static uint32_t GetCount() { return sm_pointCounter; }

	virtual void Print(std::ostream & out)
	{
		out << Named::m_name << "(" << m_x << "," << m_y << ")";
	}

	uint32_t GetX() const{ return m_x; }
	uint32_t GetY() const{ return m_y; }

private:
	uint32_t m_x, m_y;
	static uint32_t sm_pointCounter;
};

class Rect : public Printable, public Shape
{
public:
	Rect(std::string const & name, uint32_t const & height, uint32_t const & width,
		Point const & position) : Shape(name), Printable(name), Named(name)
	{
		try
		{
			if (height == width)
				throw "Generation error: height = width!";

			m_height = height;
			m_width = width;
			m_leftUp = position;
			++sm_rectCounter;
		}
		catch (char * str)
		{
			std::cout << str << std::endl;
		}
	}
	~Rect()
	{
		m_leftUp.~Point();
		--sm_rectCounter;
	}

	static uint32_t GetCount() { return sm_rectCounter; }

	virtual void Print(std::ostream & out)
	{
		out << "Rectangle " << Named::m_name << " ["
			<< "height: " << m_height << ", "
			<< "width: " << m_width << ", "
			<< "position: (" << m_leftUp.GetX() << "," << m_leftUp.GetY() << ")]";
	}

private:
	uint32_t m_height, m_width;
	Point m_leftUp;
	static uint32_t sm_rectCounter;
};

class Circle : public Printable, public Shape
{
public:
	Circle(std::string const & name, uint32_t const & radius,
		Point const & center) : Shape(name), Printable(name), Named(name), m_center(center), m_radius(radius)
	{
		++sm_circleCounter;
	}
	~Circle()
	{
		m_center.~Point();
		--sm_circleCounter;
	}

	static uint32_t GetCount() { return sm_circleCounter; }

	virtual void Print(std::ostream & out)
	{
		out << "Circle " << Named::m_name << " ["
			<< "radius: " << m_radius << ", "
			<< "square: " << (M_PI*m_radius*m_radius) << ", "
			<< "center position: (" << m_center.GetX() << "," << m_center.GetY() << ")]";
	}
private:
	uint32_t m_radius;
	Point m_center;
	static uint32_t sm_circleCounter;
};

class Polyline : public Printable, public Shape
{
public:
	Polyline(std::string const & name) : Shape(name), Printable(name), Named(name) 
	{ 
		++sm_polylineCounter;
	}

	~Polyline()
	{
		m_points.IteratorInitial();
		while (!m_points.IteratorIsEnd())
		{
			(*m_points.IteratorGetValue()).~Point();
			m_points.IteratorToNext();
		}
		--sm_polylineCounter;
	}

	void AddPoint(Point * point)
	{
		m_points.AddFront(point);
	}

	static uint32_t GetCount() { return sm_polylineCounter; }

	virtual void Print(std::ostream & out)
	{
		m_points.IteratorInitial();

		out << "Polyline " << Named::m_name;
		if (m_points.GetLength() > 0)
		{
			out << "[Points: ";
			while (!m_points.IteratorIsEnd())
			{
				(*m_points.IteratorGetValue()).Print(out);
				m_points.IteratorToNext();

				if (!m_points.IteratorIsEnd()) out << ", ";
			}
			out << "]";
		}
	}
protected:
	XList<Point *> m_points;
private:
	static uint32_t sm_polylineCounter;
};

class Polygon : public Polyline
{
public:
	Polygon(std::string const & name, XList<Point *> const & points) 
		: Named(name), Polyline(name)
	{
		m_points = points;
		++sm_polygonCounter;
	}
	~Polygon()
	{
		--sm_polygonCounter;
	}
	
	static uint32_t GetCount() { return sm_polygonCounter; }

	virtual void Print(std::ostream & out)
	{
		m_points.IteratorInitial();

		out << "Polygon " << Named::m_name;
		if (m_points.GetLength() > 0)
		{
			out << "[Points: ";

			while (!m_points.IteratorIsEnd())
			{
				(*m_points.IteratorGetValue()).Print(out);
				m_points.IteratorToNext();

				if (!m_points.IteratorIsEnd()) out << ", ";
			}
			out << "]";
		}
	}
private:
	static uint32_t sm_polygonCounter;
};

uint32_t Shape::sm_counter = 0;
uint32_t Point::sm_pointCounter = 0;
uint32_t Rect::sm_rectCounter = 0;
uint32_t Circle::sm_circleCounter = 0;
uint32_t Polyline::sm_polylineCounter = 0;
uint32_t Polygon::sm_polygonCounter = 0;