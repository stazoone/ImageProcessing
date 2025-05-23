#pragma once

#include "Image.h"
#include "Point.h"
#include "Rectangle.h"

/**
 * @brief Namespace containing drawing functions for grayscale images
 * @details Provides utility functions for drawing basic shapes on grayscale images
 */
namespace Drawing {
    /**
     * @brief Draws a circle on the grayscale image
     * @param img Grayscale image to draw on
     * @param center Center point of the circle
     * @param radius Radius of the circle
     * @param value Grayscale value to use for drawing (0-255)
     */
    void drawCircle(Image& img, Point center, int radius, unsigned char value);

    /**
     * @brief Draws a line on the grayscale image
     * @param img Grayscale image to draw on
     * @param p1 Starting point of the line
     * @param p2 Ending point of the line
     * @param value Grayscale value to use for drawing (0-255)
     */
    void drawLine(Image& img, Point p1, Point p2, unsigned char value);

    /**
     * @brief Draws a rectangle on the grayscale image using a Rectangle object
     * @param img Grayscale image to draw on
     * @param r Rectangle to draw
     * @param value Grayscale value to use for drawing (0-255)
     */
    void drawRectangle(Image& img, Rectangle r, unsigned char value);

    /**
     * @brief Draws a rectangle on the grayscale image using corner points
     * @param img Grayscale image to draw on
     * @param tl Top-left corner point
     * @param br Bottom-right corner point
     * @param value Grayscale value to use for drawing (0-255)
     */
    void drawRectangle(Image& img, Point tl, Point br, unsigned char value);
} 