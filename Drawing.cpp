#include "Drawing.h"
#include <cmath>

namespace Drawing {

/**
 * @brief Draws a circle on the grayscale image using Bresenham's circle algorithm
 * @param img Grayscale image to draw on
 * @param center Center point of the circle
 * @param radius Radius of the circle
 * @param value Grayscale value to use for drawing (0-255)
 * @details Uses Bresenham's circle algorithm to determine circle points.
 *          Handles circles of any radius.
 *          Checks bounds before drawing each point.
 *          Uses the provided grayscale value for all points.
 */
void drawCircle(Image& img, Point center, int radius, unsigned char value) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    
    while (x <= y) { // One octant
        // Draw points in all octants
        if (center.getX() + x >= 0 && center.getX() + x < img.width() && // Draw point at coords if its inside bounds
            center.getY() + y >= 0 && center.getY() + y < img.height())
            img.at(center.getY() + y, center.getX() + x) = value;
        if (center.getX() + y >= 0 && center.getX() + y < img.width() && //2nd octant
            center.getY() + x >= 0 && center.getY() + x < img.height())
            img.at(center.getY() + x, center.getX() + y) = value;
        if (center.getX() - x >= 0 && center.getX() - x < img.width() && // 3rd octant
            center.getY() + y >= 0 && center.getY() + y < img.height())
            img.at(center.getY() + y, center.getX() - x) = value;
        if (center.getX() - y >= 0 && center.getX() - y < img.width() && // 4th octant
            center.getY() + x >= 0 && center.getY() + x < img.height())
            img.at(center.getY() + x, center.getX() - y) = value;
        if (center.getX() + x >= 0 && center.getX() + x < img.width() && //5th octant
            center.getY() - y >= 0 && center.getY() - y < img.height())
            img.at(center.getY() - y, center.getX() + x) = value;
        if (center.getX() + y >= 0 && center.getX() + y < img.width() && // 6th octant
            center.getY() - x >= 0 && center.getY() - x < img.height())
            img.at(center.getY() - x, center.getX() + y) = value;
        if (center.getX() - x >= 0 && center.getX() - x < img.width() && // 7th octant
            center.getY() - y >= 0 && center.getY() - y < img.height())
            img.at(center.getY() - y, center.getX() - x) = value;
        if (center.getX() - y >= 0 && center.getX() - y < img.width() && // 8th octant
            center.getY() - x >= 0 && center.getY() - x < img.height())
            img.at(center.getY() - x, center.getX() - y) = value;
        
        if (d < 0) { // Point is inside the circle
            d += 4 * x + 6; // Move horizontally
        } else {
            d += 4 * (x - y) + 10; // Move diagonally
            y--;
        }
        x++;
    }
}

/**
 * @brief Draws a line on the grayscale image using Bresenham's line algorithm
 * @param img Grayscale image to draw on
 * @param p1 Start point of the line
 * @param p2 End point of the line
 * @param value Grayscale value to use for drawing (0-255)
 * @details Uses Bresenham's line algorithm to determine line points.
 *          Handles lines in any direction (horizontal, vertical, diagonal).
 *          Checks bounds before drawing each point.
 *          Uses the provided grayscale value for all points.
 */
void drawLine(Image& img, Point p1, Point p2, unsigned char value) {
    int x1 = p1.getX(); // Start coordinates
    int y1 = p1.getY();
    int x2 = p2.getX(); // End coords
    int y2 = p2.getY();
    
    int dx = abs(x2 - x1);    // Calculate distance
    int dy = abs(y2 - y1); // between each set
    int sx = (x1 < x2) ? 1 : -1; // This tells us if we have to move left/right
    int sy = (y1 < y2) ? 1 : -1; // or up/down
    int err = dx - dy; // Error term that tells us when to move vertically or horizontally if we are off from the line
    
    while (true) {
        if (x1 >= 0 && x1 < img.width() && y1 >= 0 && y1 < img.height()) {
            img.at(x1, y1) = value; // Set pixel
        }
        
        if (x1 == x2 && y1 == y2) break; // eNd of line
        
        int e2 = 2 * err;
        if (e2 > -dy) { // Error is moving more vertically
            err -= dy;
            x1 += sx; // Move right or left
        }
        if (e2 < dx) { // Error is moving more horizontally
            err += dx;
            y1 += sy; // Move up/down
        }
    }
}

/**
 * @brief Draws a rectangle on the grayscale image using a Rectangle object
 * @param img Grayscale image to draw on
 * @param r Rectangle to draw
 * @param value Grayscale value to use for drawing (0-255)
 * @details Draws the rectangle by connecting its corners with lines.
 *          Uses the provided grayscale value for all points.
 */
void drawRectangle(Image& img, Rectangle r, unsigned char value) {
    Point tl = r.getTopLeft();
    Point br = r.getBottomRight();
    drawRectangle(img, tl, br, value);
}

/**
 * @brief Draws a rectangle on the grayscale image using corner points
 * @param img Grayscale image to draw on
 * @param tl Top-left corner point
 * @param br Bottom-right corner point
 * @param value Grayscale value to use for drawing (0-255)
 * @details Draws the rectangle by connecting its corners with lines.
 *          Uses the provided grayscale value for all points.
 */
void drawRectangle(Image& img, Point tl, Point br, unsigned char value) {
    Point tr(br.getX(), tl.getY());
    Point bl(tl.getX(), br.getY());
    
    drawLine(img, tl, tr, value);
    drawLine(img, tr, br, value);
    drawLine(img, br, bl, value);
    drawLine(img, bl, tl, value);
}

}