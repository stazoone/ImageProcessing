#include "ImageProcessing.h"
#include <cmath>
#include <algorithm>

/**
 * @brief Constructor for brightness and contrast adjustment
 * @param alpha Contrast adjustment factor
 * @param beta Brightness adjustment value
 */
BrightnessContrastAdjustment::BrightnessContrastAdjustment(double alpha, int beta)
    : alpha(alpha), beta(beta) {}

/**
 * @brief Process the grayscale image to adjust brightness and contrast
 * @param src Source  image
 * @param dst Destination  image
 * @details Applies formula: new_value = alpha * old_value + beta
 *          Clamps results to [0,255] range for values
 */
void BrightnessContrastAdjustment::process(const Image& src, Image& dst) {
    dst = Image(src.width(), src.height()); // Empty image
    
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            unsigned char srcPixel = src.at(x, y); // Get pixel
            unsigned char& dstPixel = dst.at(x, y); // Reference the pixel of the new photo
            
            dstPixel = std::min(255, std::max(0, static_cast<int>(srcPixel * alpha + beta))); // alpha for contrast , beta for brightness, min() ensures we stay in the range (0,255)
        }
    }
}

/**
 * @brief Constructor for gamma correction
 * @param gamma Gamma correction factor
 * @details Gamma > 1 makes grayscale image darker, < 1 makes it brighter
 */
GammaCorrection::GammaCorrection(double gamma) : gamma(gamma) {}

/**
 * @brief Process the grayscale image to apply gamma correction
 * @param src Source image
 * @param dst Destination image
 * @details Applies formula: new_value = 255 * (old_value/255)^gamma
 *          Clamps results to [0,255] range for values
 */
void GammaCorrection::process(const Image& src, Image& dst) {
    dst = Image(src.width(), src.height()); // eEmpty image
    
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            unsigned char srcPixel = src.at(x, y); // Get pixel from source image
            unsigned char& dstPixel = dst.at(x, y); // Destination pixel
            
            dstPixel = std::min(255, static_cast<int>(255 * pow(srcPixel / 255.0, gamma))); // gamma<1 brigtens dark regions while >1 darkens bright regions
        }
    }
}

/**
 * @brief Constructor for convolution operation
 * @param kernel Convolution kernel matrix
 * @param width Width of the kernel
 * @param height Height of the kernel
 * @param scalingFunc Function to scale convolution results
 */
Convolution::Convolution(double** kernel, int width, int height, std::function<double(double)> scalingFunc)
    : kernel(kernel), kernelWidth(width), kernelHeight(height), scalingFunction(scalingFunc) {}

/**
 * @brief Destructor for convolution
 * @details Frees memory allocated for the kernel matrix
 */
Convolution::~Convolution() {
    for (int i = 0; i < kernelHeight; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;
}

/**
 * @brief Process the grayscale image using convolution
 * @param src Source grayscale image
 * @param dst Destination grayscale image
 * @details For each pixel:
 *          1. Multiplies surrounding grayscale pixels by kernel values
 *          2. Sums the results
 *          3. Applies scaling function
 *          4. Clamps results to [0,255] range for grayscale values
 */
void Convolution::process(const Image& src, Image& dst) {
    dst = Image(src.width(), src.height()); // New image
    
    int kernelRadiusX = kernelWidth / 2; // Find how far the kernel stretches from the center
    int kernelRadiusY = kernelHeight / 2;
    
    for (unsigned int y = 0; y < src.height(); ++y) {
        for (unsigned int x = 0; x < src.width(); ++x) {
            double sum = 0.0;
            
            for (int ky = 0; ky < kernelHeight; ++ky) {
                for (int kx = 0; kx < kernelWidth; ++kx) {
                    int srcX = x + kx - kernelRadiusX; // Apply the kernel modifications
                    int srcY = y + ky - kernelRadiusY;
                    
                    if (srcX >= 0 && srcX < src.width() && srcY >= 0 && srcY < src.height()) { // Ensure the kernel doesn't go out of bounds
                        unsigned char srcPixel = src.at(srcX, srcY);
                        sum += srcPixel * kernel[ky][kx]; // Add the new pixel with kernel value to the sum
                    }
                }
            }
            
            unsigned char& dstPixel = dst.at(x, y);
            dstPixel = std::min(255, std::max(0, static_cast<int>(scalingFunction(sum)))); // Change the pixel with the new one by applying the scaling function of sum
        }
    }
} 