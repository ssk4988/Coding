/*
  slice.cpp
  Any Way You Slice It, MCPC 2012 Problem C
  C++ solution by Gabriel Foust
*/

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#define VERIFY

ifstream fin( "slice.in" );

struct Vector;

struct Point
{
  double x, y;

  Point() { }
  Point( double x, double y ) : x( x ), y( y ) { }

  void move( Vector& dir, double mag );
};

struct Vector
{
  double x, y;

  Vector() { }
  Vector( double x, double y ) : x( x ), y( y ) { }

  Vector( Point& p1, Point& p2 )
    : x( p2.x - p1.x ), y( p2.y - p1.y )
  { }

  void turn( double theta )
  {
    Vector old= *this;
    x=  old.x*cos( theta ) - old.y*sin( theta );
    y=  old.x*sin( theta ) + old.y*cos( theta );
  }

  double cross( const Vector& other )
  {
    return x*other.y - other.x*y;
  }
};

inline void Point::move( Vector& dir, double mag )
{
  x+= mag*dir.x;
  y+= mag*dir.y;
}

struct Line
{
  Point begin, end;

  double left() { return min( begin.x, end.x ); }
  double right() { return max( begin.x, end.x ); }
  double bottom() { return min( begin.y, end.y ); }
  double top() { return max( begin.y, end.y ); }

  bool intersect( Line other )
  {
    // bounding boxes intersect
    if (left() > other.right() || right() < other.left() ||
	bottom() > other.top() || top() < other.bottom())
      return false;

    // second crosses the first
    Vector v( begin, end );
    double cross1= v.cross( Vector( begin, other.begin ) );
    double cross2= v.cross( Vector( begin, other.end ) );
    if ((cross1 > 0 && cross2 > 0) ||
        (cross1 < 0 && cross2 < 0)   )
      return false;

    // first crosses the second
    Vector u( other.begin, other.end );
    cross1= u.cross( Vector( other.begin, begin ) );
    cross2= u.cross( Vector( other.begin, end ) );
    return
      (cross1 <= 0 && cross2 >= 0) ||
      (cross1 >= 0 && cross2 <= 0);
  }
};

#ifdef VERIFY
ostream& operator<<( ostream& out, const Line& line )
{
  out << '(' << line.begin.x << ", " << line.begin.y << ")-("
      << line.end.x << ", " << line.end.y << ')';
}

bool verify( Line& l1, Line& l2, bool intersect )
{
  const double eps= 0.0001;
  Line a, b;
  for (int i= 0; i < 256; ++i)
  {
    a.begin.x= l1.begin.x + (i & 1 ? eps : -eps);
    a.begin.y= l1.begin.y + (i & 2 ? eps : -eps);
    a.end.x=   l1.end.x   + (i & 4 ? eps : -eps);
    a.end.y=   l1.end.y   + (i & 8 ? eps : -eps);
    b.begin.x= l2.begin.x + (i & 16 ? eps : -eps);
    b.begin.y= l2.begin.y + (i & 32 ? eps : -eps);
    b.end.x=   l2.end.x   + (i & 64 ? eps : -eps);
    b.end.y=   l2.end.y   + (i & 128 ? eps : -eps);
    if (a.intersect( b ) != intersect)
      return false;
  }
  return true;
}

int ang( Vector dir )
{
  int a= int(atan( dir.y / dir.x )/M_PI*180);
  if (dir.x < 0)
    a+= 180;
  return a;
}
#endif

int main()
{
  int count;

  while (fin >> count && count > 0)
  {
    vector<Line> lines;
    Point loc( 0, 0 );
    Vector dir( 0, 1 );
    double distance, angle;
    int intersection;

    while (count > 0)
    {
      --count;
      intersection= -1;

      fin >> angle;
      angle *= M_PI/180;
      dir.turn( angle );

      Line line;
      line.begin= loc;
      fin >> distance;
      loc.move( dir, distance );
      line.end= loc;

#ifdef VERIFY
      cerr << ang(dir) << " (" << loc.x << ", " << loc.y << ")" << endl;
#endif

      for (int i= 0; i + 1 < lines.size(); ++i)
      {
        bool intersect= line.intersect( lines[i] );
#ifdef VERIFY
        if (! verify( line, lines[i], intersect ))
        {
          cerr << "Getting a little too close: " << line << " & " << lines[i] << endl;
        }
#endif
        if (intersect)
        {
          intersection= lines.size() + 1;
          break;
        }
      }
      if (intersection >= 0)
        break;

      lines.push_back( line );
    }

    while (count > 0)
    {
      --count;
      fin >> angle;
      fin >> distance;
    }

    if (intersection < 0)
      cout << "SAFE" << endl;
    else
      cout << intersection << endl;
  }

  return 0;
}
