/*
 * project2.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: Ike Meiring
 */

#include <iostream>

using namespace std;

double round(double var)
{
    double value = (int)(var * 100.0);
    return (double)value / 100.0;
}

template <class DT>
class Point;    //class prototype

template <class DT>
ostream& operator <<(ostream& s, Point<DT>& otherOne);

template <class DT>
class Point	{
	friend ostream& operator << <DT>(ostream& s, Point<DT>& otherOne);
public:
	DT x;
	DT y;
	Point();
	Point(DT xvalue, DT yvalue);
	void setLocation(DT xvalue, DT yvalue);
	void display();
	virtual ~Point();
	 //function prototype

};

template <class DT>
Point<DT>::Point()
{
	x = 0.0;
	y = 0.0;
}

template <class DT>
Point<DT>::Point(DT xvalue, DT yvalue)
{
	x = xvalue;   //this constructor will be called when creating new points
	y = yvalue;
}

template <class DT>
void Point<DT>::setLocation(DT xvalue, DT yvalue)
{
	x = xvalue;
	y = yvalue;
}

template <class DT>
void Point<DT>::display()
{
	cout << "(" << round(x) << ", " << round(y) << ")" << endl;
}

template <class DT>
ostream& operator << (ostream& s, Point<DT>& otherOne)
{
	s << "(" << (otherOne.x) << ", " << (otherOne.y) << ")";
	return s;
}

template <class DT>
Point <DT>:: ~Point()
{
	//TODO
}

template <class DT>
class LineSegment;

template <class DT>
ostream& operator <<(ostream& s, LineSegment<DT>& one);

template <class DT>
class LineSegment {
public:
	Point<DT> PointOne;
	Point<DT> PointTwo;
	LineSegment();
	LineSegment(Point<DT> PointOne, Point<DT> PointTwo);
	double lengthOfLine();
	Point<DT> midpoint();
	Point<DT> xIntercept();
	Point<DT> yIntercept();
	double slope();
	double squareroot(double a);
	bool itIntersects(LineSegment<DT> L);

	Point<DT> intersectionPoint(LineSegment<DT> L);
	bool isParallel(LineSegment<DT> L);
	void displayEquation();
	void displayLineSegment(); //optional added

};


template<class DT>
LineSegment<DT>::LineSegment()
{
	PointOne.setLocation(0.0, 0.0);
	PointTwo.setLocation(0.0, 0.0);
}

template<class DT>
LineSegment<DT>::LineSegment(Point<DT> one,Point<DT> two)
{
	PointOne = one;
	PointTwo = two;
}

template<class DT>
ostream& operator <<(ostream& s, LineSegment<DT>& one)
{
	//rounding on the display instead of during calculation will produce less errors
	s << "(" << round(one.PointOne.x) << ", " << round(one.PointOne.y) << "),"
	 << "(" << round(one.PointTwo.x) << ", " << round(one.PointTwo.y) << ")";
	return s;
}

template<class DT>
double LineSegment<DT>::slope()
{
	double slope;
	double x1 = PointOne.x;
	double y1 = PointOne.y;
	double x2 = PointTwo.x;
	double y2 = PointTwo.y;
	slope = ((y2 - y1) / (x2 - x1));
	return slope;
}

template <class DT>
double LineSegment<DT>::squareroot(double a)
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

template<class DT>
bool LineSegment<DT>::itIntersects(LineSegment<DT> L)
{

	// Points P and Q
	Point<DT> one(this->PointOne);
	Point<DT> two(this->PointTwo);
	Point<DT> thisOne(L.PointOne);
	Point<DT> thisTwo(L.PointTwo);

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

template <class DT>
bool LineSegment<DT>::isParallel(LineSegment<DT> L)
{
	return (L.slope() == this->slope());
}

template <class DT>
Point<DT> LineSegment<DT>::intersectionPoint(LineSegment<DT> L)
{
	double c1 = L.yIntercept().getYValue();
	double c2 = this->yIntercept().getYValue(); //this represents the other yint being calculated

	double m1 = L.slope();
	double m2 = this->slope();

	double xintersect = (c2 - c1)/(m1-m2);                   //got equations from reference sheet
	double yintersect = ((c1*m2) - (c2*m1))/(m2-m1);

	LineSegment<DT>intersectionPoint = new Point<DT>(xintersect, yintersect);

	return intersectionPoint;

}

template <class DT>
double LineSegment<DT>::lengthOfLine()
{
	double length;
	double x1 = PointOne.x;
	double y1 = PointOne.y;
	double x2 = PointTwo.x;
	double y2 = PointTwo.y;
	length = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
	length = squareroot(length);
 	return length;
}

template <class DT>
Point<DT> LineSegment<DT>::midpoint()
{
	double xm = (PointOne.x + PointTwo.x)/2;
	double ym = (PointOne.x + PointTwo.y)/2; //from reference sheet
	Point<DT> midPoint(xm, ym);
	return midPoint;
}

template <class DT>
Point<DT>LineSegment<DT>::xIntercept()
{
	double x;
	double x1 = PointOne.x;
	double y1 = PointOne.y;
	double x2 = PointOne.x;
	double y2 = PointTwo.y;
	x = x1 - y1*(x2-x1)/(y2-y1);
	Point<DT> xint(x, 0);  // y = 0 because thats how x-int is found
	return xint;
}

template<class DT>
Point<DT> LineSegment<DT>::yIntercept()
{
	double c;
	double y1 = PointOne.y;
	double x1 = PointOne.x;
	double y2 = PointTwo.y;
	double x2 = PointTwo.x;
	c = y1 - ((y2 - y1)/(x2 - x1))*x1;
	Point<DT> yint(0, c); //setting x = 0 because thats how the y-int is found
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

	Point<double>* point = new Point<double>(1.2, 1.2);
	Point<double>* pointTwo = new Point<double>(1.0, 1.0);
	cout << *point;

	LineSegment<double>* segment = new LineSegment<double>(*point, *pointTwo);
	cout << *segment;
}











