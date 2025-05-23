#include "Rectangle.h"
#include <algorithm>

/**
 * @brief Default constructor
 * @details Initializes rectangle at origin with zero dimensions
 */
Rectangle::Rectangle() : topLeft(), bottomRight() {}

/**
 * @brief Constructor with position and dimensions
 * @param x X-coordinate of top-left corner
 * @param y Y-coordinate of top-left corner
 * @param width Width of rectangle
 * @param height Height of rectangle
 */
Rectangle::Rectangle(int x, int y, unsigned int width, unsigned int height)
    : topLeft(x, y), bottomRight(x + width, y + height) {}

/**
 * @brief Constructor with corner points
 * @param tl Top-left corner point
 * @param br Bottom-right corner point
 */
Rectangle::Rectangle(const Point& tl, const Point& br)
    : topLeft(tl), bottomRight(br) {}

/**
 * @brief Gets the x-coordinate of the rectangle
 * @return X-coordinate of top-left corner
 */
int Rectangle::getX() const { 
    return topLeft.x; 
}

/**
 * @brief Gets the y-coordinate of the rectangle
 * @return Y-coordinate of top-left corner
 */
int Rectangle::getY() const { 
    return topLeft.y; 
}

/**
 * @brief Gets the width of the rectangle
 * @return Width of rectangle
 */
unsigned int Rectangle::getWidth() const { 
    return bottomRight.x - topLeft.x; 
}

/**
 * @brief Gets the height of the rectangle
 * @return Height of rectangle
 */
unsigned int Rectangle::getHeight() const { 
    return bottomRight.y - topLeft.y; 
}

/**
 * @brief Sets the x-coordinate of the rectangle
 * @param x New x-coordinate for top-left corner
 */
void Rectangle::setX(int x) { 
    int width = getWidth();
    topLeft.x = x;
    bottomRight.x = x + width;
}

/**
 * @brief Sets the y-coordinate of the rectangle
 * @param y New y-coordinate for top-left corner
 */
void Rectangle::setY(int y) { 
    int height = getHeight();
    topLeft.y = y;
    bottomRight.y = y + height;
}

/**
 * @brief Sets the width of the rectangle
 * @param width New width of rectangle
 */
void Rectangle::setWidth(unsigned int width) { 
    bottomRight.x = topLeft.x + width; 
}

/**
 * @brief Sets the height of the rectangle
 * @param height New height of rectangle
 */
void Rectangle::setHeight(unsigned int height) { 
    bottomRight.y = topLeft.y + height; 
}

/**
 * @brief Gets the top-left corner point
 * @return Point representing top-left corner
 */
Point Rectangle::getTopLeft() const { 
    return topLeft; 
}

/**
 * @brief Gets the bottom-right corner point
 * @return Point representing bottom-right corner
 */
Point Rectangle::getBottomRight() const { 
    return bottomRight; 
}

/**
 * @brief Translates rectangle by a point
 * @param pt Point to translate by
 * @return New rectangle shifted by the point's coordinates
 */
Rectangle Rectangle::operator+(const Point& pt) const {
    return Rectangle(topLeft + pt, bottomRight + pt);
}

/**
 * @brief Translates rectangle by negative point
 * @param pt Point to translate by (negatively)
 * @return New rectangle shifted by negative point coordinates
 */
Rectangle Rectangle::operator-(const Point& pt) const {
    return Rectangle(topLeft - pt, bottomRight - pt);
}

/**
 * @brief Intersection of two rectangles
 * @param other Rectangle to intersect with
 * @return New rectangle representing the overlap area, or empty rectangle if no overlap
 */
Rectangle Rectangle::operator&(const Rectangle& other) const {
    int x1 = std::max(getX(), other.getX()); // Gives the corner of the most right
    int y1 = std::max(getY(), other.getY()); // and down rectangle
    int x2 = std::min(getX() + getWidth(), other.getX() + other.getWidth());   //  Gives the corner of the most left
    int y2 = std::min(getY() + getHeight(), other.getY() + other.getHeight()); //  and up(?) rectangle

    if (x2 <= x1 || y2 <= y1) { // Width/heigth <= 0 so there is no valid overlap
        return Rectangle(); // Empty rectangle
    }

    return Rectangle(Point(x1, y1), Point(x2, y2));
}

/**
 * @brief Union of two rectangles
 * @param other Rectangle to union with
 * @return New rectangle that contains both rectangles
 */
Rectangle Rectangle::operator|(const Rectangle& other) const {
    int x1 = std::min(getX(), other.getX()); // Gives the corner of the most left
    int y1 = std::min(getY(), other.getY()); // and up rectangle
    int x2 = std::max(getX() + getWidth(), other.getX() + other.getWidth());   //  Gives the corner of the most right
    int y2 = std::max(getY() + getHeight(), other.getY() + other.getHeight()); //  and down rectangle
    
    return Rectangle(Point(x1, y1), Point(x2, y2));
}

/**
 * @brief Output stream operator
 * @param os Output stream
 * @param rect Rectangle to output
 * @return Output stream
 * @details Prints rectangle in format Rectangle(x, y, width, height)
 */
std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
    os << "Rectangle(" << rect.getX() << ", " << rect.getY() 
       << ", " << rect.getWidth() << ", " << rect.getHeight() << ")";
    return os;
}

/**
 * @brief Input stream operator
 * @param is Input stream
 * @param rect Rectangle to read into
 * @return Input stream
 * @details Reads x, y, width, and height values from input stream
 */
std::istream& operator>>(std::istream& is, Rectangle& rect) {
    int x, y;
    unsigned int width, height;
    is >> x >> y >> width >> height;
    rect = Rectangle(x, y, width, height);
    return is;
} 