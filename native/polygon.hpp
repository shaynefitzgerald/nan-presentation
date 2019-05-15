const int MAXPOLY = 200;

class Point
{
    private:
    public:
        double x, y;
};
 
class Polygon
{
    private:
    public:
        Polygon(unsigned int);
        void addPoint(Point);
        double area();
        int n;
        unsigned int sz;
        Point* p;
};
