#pragma once

#include "Point.h"
#include "Rectangle.h"
#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Class representing a 2D grayscale image
 * @details Handles image data storage, manipulation, and file I/O operations for P5 (binary) PGM format images
 */
class Image {
private:
    unsigned char** m_data;  ///< 2D array of grayscale pixel values (0-255)
    unsigned int m_width;    ///< Width of the image
    unsigned int m_height;   ///< Height of the image
    bool m_isGrayscale;      ///< Flag indicating if image is grayscale (always true in current implementation)

    /**
     * @brief Allocates memory for the image data
     * @details Creates a 2D array of grayscale pixel values
     */
    void allocateMemory();

    /**
     * @brief Deallocates memory used by the image data
     * @details Frees the 2D array of pixel values
     */
    void deallocateMemory();

    /**
     * @brief Copies data from another image
     * @param other Source image to copy from
     */
    void copyFrom(const Image& other);

public:
    /**
     * @brief Default constructor
     * @details Creates an empty grayscale image
     */
    Image();

    /**
     * @brief Constructor with dimensions
     * @param w Width of the image
     * @param h Height of the image
     * @details Creates a grayscale image with specified dimensions
     */
    Image(unsigned int w, unsigned int h);

    /**
     * @brief Copy constructor
     * @param other Image to copy from
     */
    Image(const Image& other);

    /**
     * @brief Destructor
     * @details Frees allocated memory
     */
    ~Image();

    /**
     * @brief Loads a P5 (binary) PGM image from a file
     * @param imagePath Path to the P5 PGM image file
     * @return true if loading was successful, false otherwise
     */
    bool load(std::string imagePath);

    /**
     * @brief Saves the image to a P5 (binary) PGM file
     * @param imagePath Path where to save the P5 PGM image
     * @return true if saving was successful, false otherwise
     */
    bool save(std::string imagePath);

    /**
     * @brief Checks if the image is empty
     * @return true if image has no data, false otherwise
     */
    bool isEmpty() const;

    /**
     * @brief Gets the width of the image
     * @return Width in pixels
     */
    unsigned int width() const;

    /**
     * @brief Gets the height of the image
     * @return Height in pixels
     */
    unsigned int height() const;

    /**
     * @brief Checks if the image is grayscale
     * @return true if image is grayscale, false otherwise
     */
    bool isGrayscale() const { return m_isGrayscale; }

    /**
     * @brief Accesses a pixel at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Reference to the pixel value
     */
    unsigned char& at(unsigned int x, unsigned int y);

    /**
     * @brief Accesses a pixel at specified coordinates (const version)
     * @param x X coordinate
     * @param y Y coordinate
     * @return Const reference to the pixel value
     */
    const unsigned char& at(unsigned int x, unsigned int y) const;

    /**
     * @brief Accesses a pixel at specified point
     * @param pt Point containing coordinates
     * @return Reference to the pixel value
     */
    unsigned char& at(Point pt);

    /**
     * @brief Accesses a pixel at specified point (const version)
     * @param pt Point containing coordinates
     * @return Const reference to the pixel value
     */
    const unsigned char& at(Point pt) const;

    /**
     * @brief Gets a row of pixels
     * @param y Row index
     * @return Pointer to the first pixel in the row
     */
    unsigned char* row(int y);

    /**
     * @brief Gets a row of pixels (const version)
     * @param y Row index
     * @return Const pointer to the first pixel in the row
     */
    const unsigned char* row(int y) const;

    /**
     * @brief Assignment operator
     * @param other Image to copy from
     * @return Reference to this image
     */
    Image& operator=(const Image& other);

    /**
     * @brief Addition operator
     * @param i Image to add
     * @return New image with added pixel values
     */
    Image operator+(const Image& i);

    /**
     * @brief Subtraction operator
     * @param i Image to subtract
     * @return New image with subtracted pixel values
     */
    Image operator-(const Image& i);

    /**
     * @brief Addition operator with value
     * @param value Value to add to each pixel
     * @return New image with value added to each pixel
     */
    Image operator+(unsigned char value);

    /**
     * @brief Subtraction operator with value
     * @param value Value to subtract from each pixel
     * @return New image with value subtracted from each pixel
     */
    Image operator-(unsigned char value);

    /**
     * @brief Multiplication operator with scalar
     * @param scalar Value to multiply each pixel by
     * @return New image with scaled pixel values
     */
    Image operator*(double scalar);

    /**
     * @brief Gets a region of interest from the image
     * @param roiImg Image to store the ROI
     * @param roiRect Rectangle defining the region
     * @return true if ROI was successfully extracted, false otherwise
     */
    bool getROI(Image& roiImg, Rectangle roiRect);

    /**
     * @brief Gets a region of interest from the image
     * @param roiImg Image to store the ROI
     * @param x X coordinate of top-left corner
     * @param y Y coordinate of top-left corner
     * @param width Width of the region
     * @param height Height of the region
     * @return true if ROI was successfully extracted, false otherwise
     */
    bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    /**
     * @brief Releases all memory used by the image
     * @details Sets width and height to 0 and frees pixel data
     */
    void release();

    /**
     * @brief Creates an image filled with zeros
     * @param width Width of the image
     * @param height Height of the image
     * @return New image with all pixels set to 0
     */
    static Image zeros(unsigned int width, unsigned int height);

    /**
     * @brief Creates an image filled with ones
     * @param width Width of the image
     * @param height Height of the image
     * @return New image with all pixels set to 1
     */
    static Image ones(unsigned int width, unsigned int height);

    /**
     * @brief Output stream operator
     * @param os Output stream
     * @param img Image to output
     * @return Output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Image& img);
}; 