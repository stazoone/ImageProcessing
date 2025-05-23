#pragma once

#include <iostream>

/**
 * @brief Structure representing a 2D point
 * @details Stores x and y coordinates as integers and provides basic point operations
 */
struct Point {
    int x;  ///< X coordinate of the point
    int y;  ///< Y coordinate of the point

    /**
     * @brief Default constructor
     * @details Initializes point coordinates to (0,0)
     */
    Point();

    /**
     * @brief Constructor with coordinates
     * @param x X coordinate
     * @param y Y coordinate
     */
    Point(int x, int y);
    
    /**
     * @brief Gets the X coordinate
     * @return X coordinate value
     */
    int getX() const;

    /**
     * @brief Gets the Y coordinate
     * @return Y coordinate value
     */
    int getY() const;

    /**
     * @brief Sets the X coordinate
     * @param x New X coordinate value
     */
    void setX(int x);

    /**
     * @brief Sets the Y coordinate
     * @param y New Y coordinate value
     */
    void setY(int y);
    
    /**
     * @brief Addition operator
     * @param other Point to add
     * @return New point with coordinates (x1+x2, y1+y2)
     */
    Point operator+(const Point& other) const;

    /**
     * @brief Subtraction operator
     * @param other Point to subtract
     * @return New point with coordinates (x1-x2, y1-y2)
     */
    Point operator-(const Point& other) const;
    
    /**
     * @brief Output stream operator
     * @param os Output stream
     * @param pt Point to output
     * @return Output stream
     * @details Outputs point in format "(x,y)"
     */
    friend std::ostream& operator<<(std::ostream& os, const Point& pt);

    /**
     * @brief Input stream operator
     * @param is Input stream
     * @param pt Point to read into
     * @return Input stream
     * @details Reads point coordinates in format "(x,y)"
     */
    friend std::istream& operator>>(std::istream& is, Point& pt);
}; 