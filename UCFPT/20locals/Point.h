template<class T>
struct Point {
    T x, y;
    Point(T x=0, T y=0) : x(x), y(y) {}
    Point operator+(Point p) const  { return Point(x + p.x, y + p.y); }
    Point operator-(Point p) const  { return Point(x - p.x, y - p.y); }
    Point operator*(T c)  const { return Point(x * c, y * c); }
    Point operator/(T c) const  { return Point(x / c, y / c); }
    T cross(Point p) const { return x * p.y - y * p.x; }
    T dot(Point p) const { return x * p.x + y * p.y; }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrtl(dist2()); };
    T cross(Point p, Point q) const {
        return (p-*this).cross(q-*this); 
    }
    
};
