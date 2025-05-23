#include "Image.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

/**
 * @brief Default constructor for Image class
 * @details Initializes an empty image with null data pointer and zero dimensions
 */
Image::Image() : m_data(nullptr), m_width(0), m_height(0), m_isGrayscale(true) {}

/**
 * @brief Constructor that creates a image with specified dimensions
 * @param w Width of the image
 * @param h Height of the image
 * @details Allocates memory for the image
 */
Image::Image(unsigned int w, unsigned int h) : m_width(w), m_height(h), m_isGrayscale(true) {
    allocateMemory();
}

/**
 * @brief Copy constructor
 * @param other Source image to copy from
 * @details Creates a new image with the same dimensions and data as the source image
 */
Image::Image(const Image& other) : m_data(nullptr), m_width(0), m_height(0), m_isGrayscale(true) {
    copyFrom(other);
}

/**
 * @brief Destructor
 * @details Frees all allocated memory for the image data
 */
Image::~Image() {
    deallocateMemory();
}

/**
 * @brief Allocates memory for the image
 * @details Creates a 2D array of values with dimensions m_height x m_width.
 * Each pixel is initialized to black (0)
 */
void Image::allocateMemory() {
    m_data = new unsigned char*[m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new unsigned char[m_width]; // create
    }
}

/**
 * @brief Deallocates memory used by the image
 * @details Frees each row of the 2D array and then the array itself.
 * Sets m_data pointer to nullptr
 */
void Image::deallocateMemory() {
    if (m_data != nullptr) {
        for (unsigned int i = 0; i < m_height; ++i) {
            delete[] m_data[i];
        }
        delete[] m_data;
        m_data = nullptr;
    }
}

/**
 * @brief Copies data from another image
 * @param other Source image to copy from
 * @details Copies each pixel's grayscale value from the source image to this image
 */
void Image::copyFrom(const Image& other) {
    m_width = other.m_width;
    m_height = other.m_height;
    m_isGrayscale = other.m_isGrayscale;
    allocateMemory();
    
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            m_data[i][j] = other.m_data[i][j];
        }
    }
}

/**
 * @brief Loads a PGM image from a file
 * @param imagePath Path to the PGM image file
 * @return true if loading was successful, false otherwise
 * @details Supports only PGM format:
 * - Reads binary grayscale data directly into the image buffer
 * - Expects P5 magic number in header
 * - Expects width, height, and max value (255) in header
 */
bool Image::load(std::string imagePath) {
    std::ifstream file(imagePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    std::string magic;
    file >> magic;
    
    if (magic != "P5") {  // Only support binary PGM
        return false;
    }

    m_isGrayscale = true;
    file >> m_width >> m_height;
    int maxVal;
    file >> maxVal;
    file.get();  // Skip newline, throws errors otherwise
    
    deallocateMemory();
    allocateMemory();
    
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            unsigned char gray; // Pixel color
            file.read(reinterpret_cast<char*>(&gray), 1); // reinterpret_cast used because file.read expects a char*, n=1 is 1 character that the function is reading
            m_data[i][j] = gray;
        }
    }
    
    return true;
}

/**
 * @brief Saves the image to a PGM file
 * @param imagePath Path where to save the image
 * @return true if saving was successful, false otherwise
 * @details Saves the image in PGM format:
 * - Writes P5 magic number
 * - Writes dimensions and max value (255)
 * - Writes binary grayscale data
 */
bool Image::save(std::string imagePath) {
    std::ofstream file(imagePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file << "P5\n" << m_width << " " << m_height << "\n255\n";
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            file.write(reinterpret_cast<char*>(&m_data[i][j]), 1);
        }
    }
    return true;
}

/**
 * @brief Assignment operator
 * @param other Source image to copy from
 * @return Reference to this image
 * @details Performs deep copy of the grayscale image data:
 * 1. Releases current memory
 * 2. Copies dimensions
 * 3. Allocates new memory
 * 4. Copies pixel data
 */
Image& Image::operator=(const Image& other) {
    if (this != &other) {
        deallocateMemory();
        copyFrom(other);
    }
    return *this;
}

/**
 * @brief Adds two grayscale images together
 * @param i Image to add
 * @return New image containing the sum
 * @details Performs pixel-wise addition:
 * - Adds corresponding grayscale values
 * - Clamps results to [0,255]
 * Returns empty image if dimensions don't match
 */
Image Image::operator+(const Image& i) {
    // First check if dimensions match
    if (m_width != i.m_width || m_height != i.m_height) {
        return Image(); // Return empty image if dimensions don't match
    }

    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y][x] = std::min(255, m_data[y][x] + i.m_data[y][x]);
        }
    }
    return result;
}

/**
 * @brief Subtracts one grayscale image from another
 * @param i Image to subtract
 * @return New image containing the difference
 * @details Performs pixel-wise subtraction:
 * - Subtracts corresponding grayscale values
 * - Clamps results to [0,255]
 * Returns empty image if dimensions don't match
 */
Image Image::operator-(const Image& i) {
    if (m_width != i.m_width || m_height != i.m_height) {
        return Image();
    }
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y][x] = std::max(0, m_data[y][x] - i.m_data[y][x]);
        }
    }
    return result;
}

/**
 * @brief Adds a grayscale value to all pixels
 * @param value Grayscale value to add
 * @return New image with added value
 * @details Performs pixel-wise value addition:
 * - Adds value to each pixel's grayscale value
 * - Clamps results to [0,255]
 */
Image Image::operator+(unsigned char value) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y][x] = std::min(255, m_data[y][x] + value);
        }
    }
    return result;
}

/**
 * @brief Subtracts a grayscale value from all pixels
 * @param value Grayscale value to subtract
 * @return New image with subtracted value
 * @details Performs pixel-wise value subtraction:
 * - Subtracts value from each pixel's grayscale value
 * - Clamps results to [0,255]
 */
Image Image::operator-(unsigned char value) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y][x] = std::max(0, m_data[y][x] - value);
        }
    }
    return result;
}

/**
 * @brief Multiplies all pixels by a scalar
 * @param scalar Value to multiply by
 * @return New image with multiplied values
 * @details Performs pixel-wise multiplication:
 * - Multiplies each grayscale value by scalar
 * - Clamps results to [0,255]
 */
Image Image::operator*(double scalar) {
    Image result(m_width, m_height);
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            result.m_data[y][x] = std::min(255, static_cast<int>(m_data[y][x] * scalar));
        }
    }
    return result;
}

/**
 * @brief Extracts a region of interest (ROI)
 * @param roiImg Image to store the ROI
 * @param roiRect Rectangle defining the region of interest
 * @return true if ROI extraction was successful, false otherwise
 * @details Creates a new grayscale image containing the specified rectangular region:
 * - Checks if ROI is within image bounds
 */
bool Image::getROI(Image& roiImg, Rectangle roiRect) {
    return getROI(roiImg, roiRect.getTopLeft().getX(), roiRect.getTopLeft().getY(),
                 roiRect.getWidth(), roiRect.getHeight());
}

/**
 * @brief Extracts a region of interest (ROI) using coordinates
 * @param roiImg Image to store the ROI
 * @param x X-coordinate of top-left corner
 * @param y Y-coordinate of top-left corner
 * @param width Width of the ROI
 * @param height Height of the ROI
 * @return true if ROI extraction was successful, false otherwise
 */
bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width > m_width || y + height > m_height) {
        return false; // Check if coords fit into the picture
    }
    
    roiImg = Image(width, height);
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            roiImg.m_data[i][j] = m_data[y + i][x + j];
        }
    }
    return true;
}

/**
 * @brief Checks if the image is empty
 * @return true if image has no data or zero dimensions
 */
bool Image::isEmpty() const {
    return m_data == nullptr || m_width == 0 || m_height == 0;
}

/**
 * @brief Gets the width of the image
 * @return Width in pixels
 */
unsigned int Image::width() const {
    return m_width;
}

/**
 * @brief Gets the height of the image
 * @return Height in pixels
 */
unsigned int Image::height() const {
    return m_height;
}

/**
 * @brief Access pixel at specified coordinates
 * @param x X-coordinate
 * @param y Y-coordinate
 * @return Reference to grayscale pixel value
 */
unsigned char& Image::at(unsigned int x, unsigned int y) {
    return m_data[y][x]; // y is height(rows) x is width(columns)
}

/**
 * @brief Access pixel at specified coordinates ( const version for operating on const Images)
 * @param x X-coordinate
 * @param y Y-coordinate
 * @return Const reference to grayscale pixel value
 */
const unsigned char& Image::at(unsigned int x, unsigned int y) const {
    return m_data[y][x];
}

/**
 * @brief Access pixel at specified point
 * @param pt Point containing coordinates
 * @return Reference to grayscale pixel value
 */
unsigned char& Image::at(Point pt) {
    return m_data[pt.getY()][pt.getX()];
}

/**
 * @brief Access pixel at specified point
 * @param pt Point containing coordinates
 * @return Const reference to grayscale pixel value
 */
const unsigned char& Image::at(Point pt) const {
    return m_data[pt.getY()][pt.getX()];
}

/**
 * @brief Get pointer to a row of pixels
 * @param y Row index
 * @return Pointer to the row data
 */
unsigned char* Image::row(int y) {
    return m_data[y];
}

/**
 * @brief Get pointer to a row of pixels
 * @param y Row index
 * @return Const pointer to the row data
 */
const unsigned char* Image::row(int y) const {
    return m_data[y];
}

void Image::release() {
    deallocateMemory();
    m_width = 0;
    m_height = 0;
}

/**
 * @brief Output stream operator for Image
 * @param os Output stream
 * @param img Image to output
 * @return Reference to output stream
 */
std::ostream& operator<<(std::ostream& os, const Image& img) {
    for (unsigned int i = 0; i < img.m_height; ++i) {
        for (unsigned int j = 0; j < img.m_width; ++j) {
            os << std::setw(3) << static_cast<int>(img.m_data[i][j]) << " ";
        }
        os << std::endl;
    }
    return os;
}

/**
 * @brief Creates an image filled with zeros (black)
 * @param width Width of the image
 * @param height Height of the image
 * @return New grayscale image filled with zeros
 */
Image Image::zeros(unsigned int width, unsigned int height) {
    Image result(width, height);
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            result.m_data[i][j] = 0;
        }
    }
    return result;
}

/**
 * @brief Creates an image filled with ones (white)
 * @param width Width of the image
 * @param height Height of the image
 * @return New grayscale image filled with ones (255)
 */
Image Image::ones(unsigned int width, unsigned int height) {
    Image result(width, height);
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            result.m_data[i][j] = 255;
        }
    }
    return result;
}