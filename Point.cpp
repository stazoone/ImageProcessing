#include "Point.h"

/**
 * @brief Default constructor
 * @details Initializes point at origin (0,0)
 */
Point::Point() : x(0), y(0) {}

/**
 * @brief Constructor with coordinates
 * @param x X-coordinate
 * @param y Y-coordinate
 */
Point::Point(int x, int y) : x(x), y(y) {}

/**
 * @brief Gets the x-coordinate of the point
 * @return X-coordinate value
 */
int Point::getX() const {
    return x;
}

/**
 * @brief Gets the y-coordinate of the point
 * @return Y-coordinate value
 */
int Point::getY() const {
    return y;
}

/**
 * @brief Sets the x-coordinate of the point
 * @param x New x-coordinate value
 */
void Point::setX(int x) {
    this->x = x;
}

/**
 * @brief Sets the y-coordinate of the point
 * @param y New y-coordinate value
 */
void Point::setY(int y) {
    this->y = y;
}

/**
 * @brief Addition operator
 * @param other Point to add
 * @return New point with coordinates added
 */
Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

/**
 * @brief Subtraction operator
 * @param other Point to subtract
 * @return New point with coordinates subtracted
 */
Point Point::operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
}

/**
 * @brief Output stream operator
 * @param os Output stream
 * @param pt Point to output
 * @return Output stream
 * @details Prints point in format (x, y)
 */
std::ostream& operator<<(std::ostream& os, const Point& pt) {
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

/**
 * @brief Input stream operator
 * @param is Input stream
 * @param pt Point to read into
 * @return Input stream
 * @details Reads x and y values from input stream
 */
std::istream& operator>>(std::istream& is, Point& pt) {
    is >> pt.x >> pt.y;
    return is;
} 