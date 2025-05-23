#pragma once

#include "Image.h"
#include <functional>

/**
 * @brief Abstract base class for grayscale image processing operations
 * @details Defines the interface for all grayscale image processing operations
 */
class ImageProcessing {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~ImageProcessing() = default;

    /**
     * @brief Process the source grayscale image and store result in destination
     * @param src Source grayscale image to process
     * @param dst Destination grayscale image to store result
     */
    virtual void process(const Image& src, Image& dst) = 0;
};

/**
 * @brief Class for adjusting brightness and contrast of a grayscale image
 * @details Applies linear transformation to grayscale pixel values
 */
class BrightnessContrastAdjustment : public ImageProcessing {
private:
    double alpha;  ///< Contrast adjustment factor
    int beta;      ///< Brightness adjustment value

public:
    /**
     * @brief Constructor
     * @param alpha Contrast adjustment factor (default: 1.0)
     * @param beta Brightness adjustment value (default: 0)
     */
    BrightnessContrastAdjustment(double alpha = 1.0, int beta = 0);

    /**
     * @brief Process the grayscale image to adjust brightness and contrast
     * @param src Source grayscale image
     * @param dst Destination grayscale image
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @brief Class for applying gamma correction to a grayscale image
 * @details Adjusts the brightness of a grayscale image using a power function
 */
class GammaCorrection : public ImageProcessing {
private:
    double gamma;  ///< Gamma correction factor

public:
    /**
     * @brief Constructor
     * @param gamma Gamma correction factor (default: 1.0)
     */
    GammaCorrection(double gamma = 1.0);

    /**
     * @brief Process the grayscale image to apply gamma correction
     * @param src Source grayscale image
     * @param dst Destination grayscale image
     */
    void process(const Image& src, Image& dst) override;
};

/**
 * @brief Class for applying convolution operations to a grayscale image
 * @details Applies a kernel matrix to the grayscale image for filtering operations
 */
class Convolution : public ImageProcessing {
private:
    double** kernel;           ///< Convolution kernel matrix
    int kernelWidth;          ///< Width of the kernel
    int kernelHeight;         ///< Height of the kernel
    std::function<double(double)> scalingFunction;  ///< Function to scale convolution results

public:
    /**
     * @brief Constructor
     * @param kernel Convolution kernel matrix (takes ownership of the memory)
     * @param width Width of the kernel
     * @param height Height of the kernel
     * @param scalingFunc Function to scale convolution results
     */
    Convolution(double** kernel, int width, int height, std::function<double(double)> scalingFunc);

    /**
     * @brief Destructor
     * @details Frees memory allocated for the kernel
     */
    ~Convolution();

    /**
     * @brief Process the grayscale image using convolution
     * @param src Source grayscale image
     * @param dst Destination grayscale image
     */
    void process(const Image& src, Image& dst) override;

    // Delete copy constructor and assignment operator to prevent double-free
    Convolution(const Convolution&) = delete;
    Convolution& operator=(const Convolution&) = delete;
}; 