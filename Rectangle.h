#pragma once

#include "Point.h"
#include <iostream>

/**
 * @brief Class representing a rectangle in 2D space
 * @details A rectangle is defined by its top-left and bottom-right points
 */
class Rectangle {
private:
    Point topLeft;      ///< Top-left corner of the rectangle
    Point bottomRight;  ///< Bottom-right corner of the rectangle

public:
    /**
     * @brief Default constructor
     * @details Creates an empty rectangle at origin (0,0) with zero dimensions
     */
    Rectangle();

    /**
     * @brief Constructor with two points
     * @param tl Top-left corner point
     * @param br Bottom-right corner point
     */
    Rectangle(const Point& tl, const Point& br);

    /**
     * @brief Constructor with position and dimensions
     * @param x X-coordinate of top-left corner
     * @param y Y-coordinate of top-left corner
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    Rectangle(int x, int y, unsigned int width, unsigned int height);
    
    /**
     * @brief Get the X-coordinate of the top-left corner
     * @return X-coordinate as integer
     */
    int getX() const;

    /**
     * @brief Get the Y-coordinate of the top-left corner
     * @return Y-coordinate as integer
     */
    int getY() const;

    /**
     * @brief Get the width of the rectangle
     * @return Width as unsigned integer
     */
    unsigned int getWidth() const;

    /**
     * @brief Get the height of the rectangle
     * @return Height as unsigned integer
     */
    unsigned int getHeight() const;
    
    /**
     * @brief Set the X-coordinate of the top-left corner
     * @param x New X-coordinate
     */
    void setX(int x);

    /**
     * @brief Set the Y-coordinate of the top-left corner
     * @param y New Y-coordinate
     */
    void setY(int y);

    /**
     * @brief Set the width of the rectangle
     * @param width New width
     */
    void setWidth(unsigned int width);

    /**
     * @brief Set the height of the rectangle
     * @param height New height
     */
    void setHeight(unsigned int height);
    
    /**
     * @brief Get the top-left corner point
     * @return Point object representing top-left corner
     */
    Point getTopLeft() const;

    /**
     * @brief Get the bottom-right corner point
     * @return Point object representing bottom-right corner
     */
    Point getBottomRight() const;
    
    /**
     * @brief Translate rectangle by a point
     * @param pt Point to translate by
     * @return New translated rectangle
     */
    Rectangle operator+(const Point& pt) const;

    /**
     * @brief Translate rectangle by negative of a point
     * @param pt Point to translate by (negatively)
     * @return New translated rectangle
     */
    Rectangle operator-(const Point& pt) const;

    /**
     * @brief Compute intersection of two rectangles
     * @param other Rectangle to intersect with
     * @return New rectangle representing the intersection
     */
    Rectangle operator&(const Rectangle& other) const;

    /**
     * @brief Compute union of two rectangles
     * @param other Rectangle to union with
     * @return New rectangle representing the union
     */
    Rectangle operator|(const Rectangle& other) const;
    
    /**
     * @brief Output stream operator for Rectangle
     * @param os Output stream
     * @param rect Rectangle to output
     * @return Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

    /**
     * @brief Input stream operator for Rectangle
     * @param is Input stream
     * @param rect Rectangle to input into
     * @return Reference to input stream
     */
    friend std::istream& operator>>(std::istream& is, Rectangle& rect);
}; 