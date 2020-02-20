/*
 * project2.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: Ike Meiring
 */

#include <iostream>

using namespace std;

template <class DT>
class Point;    //class prototype

template <class DT>
ostream& operator <<(ostream& s, Point<DT>& otherOne);

template <class DT>
class Point	{
	friend ostream& operator << <DT>(ostream& s, Point<DT>& otherOne);
public:
	DT* x;
	DT* y;
	Point();
	Point(DT xvalue, DT yvalue);
	Point(Point<DT>& P); //copy constructor
	Point<DT>& operator=(Point<DT>& P); //overloaded = operator
	void display();
	virtual ~Point(); //destructor

	void setLocation(DT xvalue, DT yvalue);
	 //function prototype

};
double round(double var)
{
    double value = (int)(var * 100.0);
    return (double)value / 100.0;
}

template <class DT>
Point<DT>::Point()
{
	x = NULL;
	y = NULL;
}

template <class DT>
Point<DT>::Point(DT xvalue, DT yvalue)
{
	x = new DT(xvalue);     //this constructor will be called when creating new points
	y = new DT(yvalue);
}

template <class DT>
void Point<DT>::setLocation(DT xvalue, DT yvalue)
{
	x = xvalue;
	y = yvalue;
}

// copy constructor
template <class DT>
Point<DT>::Point(Point<DT>& P)
{
	x = (*(P.x));    //this copy constructor will be used to access the points across classes
	y = (*(P.y));
}

template <class DT>
Point<DT>& Point<DT>::operator=(Point<DT>& P)
{
	x = new DT(*(P.x));
	y = new DT(*(P.y));
	//cout << "Inside the overloaded = operator" << endl;
	return (*this);
}

template <class DT>
void Point<DT>::display()
{
	cout << "(" << round(*x) << ", " << round(*y) << ")" << endl;
}

template <class DT>
ostream& operator << (ostream& s, Point<DT>& otherOne)
{
	s << "(" << (*otherOne.x) << ", " << (*otherOne.y) << ")";
	return s;
}

template <class DT>
Point <DT>:: ~Point()
{
	//cout << "A Point Object was destroyed" << endl;
}

template <class DT>
class LineSegment;

template <class DT>
ostream& operator <<(ostream& s, LineSegment<DT>& one);

/*
template <class DT>
class LineSegment {
public:
	DT* PointOne;
	DT* PointTwo;
	LineSegment();
	LineSegment(DT PointOne, DT PointTwo);
	 Function Prototypes
	double lengthOfLine();
	Point midpoint();
	Point xIntercept();
	Point yIntercept();
	double slope();
	double squareroot(double a);
	bool itIntersects(LineSegment L);

	Point intersectionPoint(LineSegment L);
	bool isParallel(LineSegment L);
	void displayEquation();
	void displayLineSegment(); //optional added

};



LineSegment::LineSegment()
{
	P1.setLocation(0.0, 0.0);
	P2.setLocation(0.0, 0.0);
}

LineSegment::LineSegment(Point one, Point two)
{
	P1 = one;
	P2 = two;

}

void LineSegment::displayLineSegment()
{
	//rounding on the display instead of during calculation will produce less errors
	cout << "(" << round(P1.getXValue()) << ", " << round(P1.getYValue()) << "),"
	 << "(" << round(P2.getXValue()) << ", " << round(P2.getYValue()) << ")" << endl;
}

double LineSegment::slope()
{
	double slope;
	slope = (P2.getYValue() - P1.getYValue()) / (P2.getXValue() - P1.getXValue());
	return slope;
}

double LineSegment::squareroot(double a)
{

	//given square root function, modified by passing in a variable and setting k = a so i
	//could calculate a specefic spot in the segments array
    double eps = 1e-6;
    double k = a;
    double l = 0.0, r, mid;

    if (k>=1) {
        r = k;
    }
    if (k<1)  {
        r = 1;
    }

    while (l-k/l > eps || l-k/l < -eps)
    {
        mid = l + (r - l) /2 ;
        if (mid<k/mid)
        {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    return l;
}

bool LineSegment::itIntersects(LineSegment L)
{

	// Points P and Q
	Point one(this->P1);
	Point two(this->P2);
	Point thisOne(L.P1);
	Point thisTwo(L.P2);

	//cross product obtained from reference sheet

	double x1 = one.getXValue();
	double x2 = two.getXValue();
	double x3 = thisOne.getXValue();
	double x4 = thisTwo.getXValue();

	double y1 = one.getYValue();
	double y2 = two.getYValue();
	double y3 = thisOne.getYValue();
	double y4 = thisTwo.getYValue();

	//cross product applied here
	double d1 = ((x2 - x1)*(y3 - y1)) - ((x3 - x1)*(y2 - y1));
	double d2 = ((x2 - x1)*(y4 - y1)) - ((x4 - x1)*(y2 - y1));
	double d3 = ((x4 - x3)*(y1 - y3)) - ((x1 - x3)*(y4 - y3));
	double d4 = ((x4 - x3)*(y2 - y1)) - ((x2 - x1)*(y4 - y3));

	//checking if lines intersect
	if((d1*d2) <= 0 && (d3*d4) <= 0)
	{
		return true;
	}
	return false;
}

bool LineSegment::isParallel(LineSegment L)
{
	return (L.slope() == this->slope());
}

Point LineSegment::intersectionPoint(LineSegment L)
{
	double c1 = L.yIntercept().getYValue();
	double c2 = this->yIntercept().getYValue(); //this represents the other yint being calculated

	double m1 = L.slope();
	double m2 = this->slope();

	double xintersect = (c2 - c1)/(m1-m2);                   //got equations from reference sheet
	double yintersect = ((c1*m2) - (c2*m1))/(m2-m1);

	Point intersectionPoint(xintersect, yintersect);

	return intersectionPoint;

}

double LineSegment::lengthOfLine()
{
	double length;
	double x1 = P1.getXValue();
	double y1 = P1.getYValue();
	double x2 = P2.getXValue();
	double y2 = P2.getYValue();
	length = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	length = squareroot(length);
 	return length;
}


Point LineSegment::midpoint()
{
	double xm = (P1.getXValue() + P2.getXValue())/2;
	double ym = (P1.getYValue() + P2.getYValue())/2; //from reference sheet
	Point midPoint(xm, ym);
	return midPoint;
}

Point LineSegment::xIntercept()
{
	double x;
	double x1 = P1.getXValue();
	double y1 = P1.getYValue();
	double x2 = P2.getXValue();
	double y2 = P2.getYValue();
	x = x1 - y1*(x2-x1)/(y2-y1);
	Point xint(x, 0);  // y = 0 because thats how x-int is found
	return xint;
}

Point LineSegment::yIntercept()
{
	double c;
	double y1 = P1.getYValue();
	double x1 = P1.getXValue();
	double y2 = P2.getYValue();
	double x2 = P2.getXValue();
	c = y1 - ((y2 - y1)/(x2 - x1))*x1;
	Point yint(0, c); //setting x = 0 because thats how the y-int is found
	return yint;
}

class Intervals	{
public:
	//changed these variables from protected to public so i can access them
	LineSegment* segments;
	int count;
	int maxSize;
	Intervals ();
	Intervals (int size);
	void addLineSegment(LineSegment L);
	void display();

};

Intervals::Intervals()
{
	segments = new LineSegment[0];
	count = 0;
	maxSize = 0;
}

Intervals::Intervals(int size)
{
	segments = new LineSegment[size];
	count = 0;
	maxSize = 0;
}

void Intervals::addLineSegment(LineSegment L)
{
	segments[count] = L;
	++count; //increment count to store lineSegments properly
}

int main()
{

	int numOfSegments;
	double x1, y1, x2, y2;

	Intervals*interval = new Intervals(numOfSegments);

	cin >> numOfSegments;

	for (int i = 0; i < numOfSegments; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		Point pointOne(x1, y1);
		Point pointTwo(x2, y2);
		LineSegment segment(pointOne, pointTwo);
		interval->segments[i] = segment;
	}
	/*
	 * rounded on the ouputs to have every calculation go through the rounding function

	for (int i = 0; i < numOfSegments; i++)
	{
		/*
		 * all rounding done here on output to avoid autograder error

		cout << "Line Segment " << (i + 1) << ":" << endl; //colon number needs to be 1 ahead of the increment
		interval->addLineSegment(interval->segments[i]);
		interval->segments[i].displayLineSegment();
		cout << "Slope:" << round(interval->segments[i].slope()) << endl;
		Point seg(interval->segments[i].midpoint());
		cout << "Midpoint:";
		seg.display();
		cout << "X Intercept:";
		Point Xint(interval->segments[i].xIntercept());
		cout << round(Xint.getXValue()) << endl;
		cout << "Y Intercept:";
		Point Yint(interval->segments[i].yIntercept());
		cout << round(Yint.getYValue()) << endl;
		cout << "Length:";
		cout << round(interval->segments[i].lengthOfLine()) << endl;
		cout << "y=" << round(interval->segments[i].slope()) << "*x+" << round(Yint.getYValue()) << endl;

	}

	for (int i = 0; i < numOfSegments - 1; i++) //always want the outer loop one behind the inner loop
	{
		for (int j = i + 1; j < numOfSegments; j++) //want to start the inner loop 1 ahead
		{

			if (interval->segments[i].itIntersects(interval->segments[j]))
			{
				cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: ";
				cout << "Intersection Point :";
				interval->segments[i].intersectionPoint(interval->segments[j]).display();

			}
			else if (interval->segments[i].isParallel(interval->segments[j]))
			{
				cout << "The line segments compared are segments[" << i << "] and segments"
						"[" << j << "]: Lines are Parallel" << endl;
			}
			else
			{
				cout << "The line segments compared are segments[" << i << "] and segments"
						"[" << j << "]: Not Parallel and not Intersecting" << endl;
 			}


		}

	}

}

*/

int main()	{

}











