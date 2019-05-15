#include "../point/Point.hpp"
#include "../line/Line.hpp"

const int MAXPOLY = 200;
 
class Polygon
{
    private:
    public:
        Polygon(unsigned int);
        void addPoint(Point);
        int lineCount();
        Line* toLineArray();
        double area();
        int n;
        unsigned int sz;
        Point* p;
};
