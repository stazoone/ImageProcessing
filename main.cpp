#include "Image.h"
#include "ImageProcessing.h"
#include "Drawing.h"
#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Validates if a file is a valid PGM file
 * @param filename The path to the file to validate
 * @return true if the file exists and has a .pgm extension, false otherwise
 */
bool isValidPGMFile(const std::string& filename) {
    // Check if file exists
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file.close(); // Free

    // Check if file has .pgm extension
    if (filename.length() < 4) {
        return false;
    }
    std::string extension = filename.substr(filename.length() - 4);
    return extension == ".pgm";
}

/**
 * @brief Prints the main menu of the image processing application
 * @details Displays all available options for image processing operations
 */
void printMenu() {
    std::cout << "\n=== Image Processing Menu ===\n"
              << "1) Input/change the path to a PGM file\n"
              << "2) Set output directory path\n"
              << "3) Apply brightness/contrast adjustment\n"
              << "4) Apply gamma correction\n"
              << "5) Apply convolution\n"
              << "6) Draw shape\n"
              << "0) Exit program\n"
              << "==========================\n";
}

/**
 * @brief Handles brightness and contrast adjustment of an image
 * @param img The source image to process
 * @param outputPath The directory path where the processed image will be saved
 * @details Prompts user for alpha (contrast) and beta (brightness) values,
 *          applies the adjustment, and saves the result
 */
void handleBrightnessContrast(Image& img, const std::string& outputPath) {
    double alpha;
    int beta;
    std::cout << "Enter contrast factor (alpha): ";
    std::cin >> alpha;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any leftover newline for preventing buffer bugs
    
    std::cout << "Enter brightness value (beta): ";
    std::cin >> beta;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Image result;
    BrightnessContrastAdjustment bca(alpha, beta);
    bca.process(img, result);

    std::string outputFile = outputPath.empty() ? 
        "brightness_contrast.pgm" :  // Save to output path if specified
        outputPath + "/brightness_contrast.pgm";
    
    if (result.save(outputFile)) {
        std::cout << "Saved brightness/contrast adjusted image to: " << outputFile << std::endl;
    } else {
        std::cout << "Error saving the image" << std::endl;
    }
}

/**
 * @brief Handles gamma correction of an image
 * @param img The source image to process
 * @param outputPath The directory path where the processed image will be saved
 * @details Prompts user for gamma value, applies the correction, and saves the result
 */

void handleGammaCorrection(Image& img, const std::string& outputPath) {
    double gamma;
    std::cout << "Enter gamma value: ";
    std::cin >> gamma;

    Image result;
    GammaCorrection gc(gamma);
    gc.process(img, result);

    std::string outputFile = outputPath.empty() ? 
        "gamma_corrected.pgm" : 
        outputPath + "/gamma_corrected.pgm";
    
    if (result.save(outputFile)) {
        std::cout << "Saved gamma-corrected image to: " << outputFile << std::endl;
    } else {
        std::cout << "Error saving the image" << std::endl;
    }
}

/**
 * @brief Handles convolution operations on an image
 * @param img The source image to process
 * @param outputPath The directory path where the processed image will be saved
 * @details Prompts user to select a kernel type, applies the convolution,
 *          and saves the result. Available kernels are:
 *          - Identity kernel
 *          - Mean blur kernel
 *          - 3x3 Gaussian blur kernel
 *          - Horizontal Sobel kernel
 *          - Vertical Sobel kernel
 */
void handleConvolution(Image& img, const std::string& outputPath) {
    std::cout << "Select kernel type:\n"
              << "1) Identity kernel\n"
              << "2) Mean blur kernel\n"
              << "3) 3x3 Gaussian blur kernel\n"
              << "4) Horizontal Sobel kernel\n"
              << "5) Vertical Sobel kernel\n"
              << "Enter choice: ";
    
    int kernelChoice;
    std::cin >> kernelChoice;

    double** kernel = nullptr;
    int width = 3, height = 3;

    switch (kernelChoice) {
        case 1: // Identity
            kernel = new double*[3] {
                new double[3]{0, 0, 0},
                new double[3]{0, 1, 0},
                new double[3]{0, 0, 0}
            };
            break;
        case 2: // Mean blur
            kernel = new double*[3] {
                new double[3]{1.0/9, 1.0/9, 1.0/9},
                new double[3]{1.0/9, 1.0/9, 1.0/9},
                new double[3]{1.0/9, 1.0/9, 1.0/9}
            };
            break;
        case 3: // Gaussian blur
            kernel = new double*[3] {
                new double[3]{1.0/16, 2.0/16, 1.0/16},
                new double[3]{2.0/16, 4.0/16, 2.0/16},
                new double[3]{1.0/16, 2.0/16, 1.0/16}
            };
            break;
        case 4: // Horizontal Sobel
            kernel = new double*[3] {
                new double[3]{-1, -2, -1},
                new double[3]{0, 0, 0},
                new double[3]{1, 2, 1}
            };
            break;
        case 5: // Vertical Sobel
            kernel = new double*[3] {
                new double[3]{-1, 0, 1},
                new double[3]{-2, 0, 2},
                new double[3]{-1, 0, 1}
            };
            break;
        default:
            std::cout << "Invalid kernel choice" << std::endl;
            return;
    }

    Image result;
    Convolution conv(kernel, width, height, [](double x) { return x; });
    conv.process(img, result);

    std::string kernelNames[] = {"identity", "mean_blur", "gaussian_blur", "sobel_h", "sobel_v"};
    std::string outputFile = outputPath.empty() ? 
        kernelNames[kernelChoice-1] + ".pgm" : 
        outputPath + "/" + kernelNames[kernelChoice-1] + ".pgm";

    if (result.save(outputFile)) {
        std::cout << "Saved convolved image to: " << outputFile << std::endl;
    } else {
        std::cout << "Error saving the image" << std::endl;
    }
}

/**
 * @brief Handles drawing operations on an image
 * @param img The source image to process
 * @param outputPath The directory path where the processed image will be saved
 * @details Prompts user to select a shape type and its parameters,
 *          draws the shape on the image, and saves the result.
 *          Available shapes are:
 *          - Line (requires start and end points)
 *          - Rectangle (requires top-left corner and dimensions)
 *          - Circle (requires center point and radius)
 */

void drawShape(Image& img, const std::string& outputPath) {
    std::cout << "\nDrawing Options:\n";
    std::cout << "1. Draw Circle\n";
    std::cout << "2. Draw Line\n";
    std::cout << "3. Draw Rectangle\n";
    std::cout << "Enter your choice (1-3): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Clear the newline character ( because otherwise due to buffering it may give errors)
    
    unsigned char value;
    std::cout << "Enter pixel value (0-255): ";
    std::cin >> value;
    std::cin.ignore();

    switch (choice) {
        case 1: {
            int x, y, radius;

            std::cout << "Enter center X and Y coordinates (e.g. 5 6): ";
            std::cin >> x >> y;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // This function discards everything in the input buffer until the next newline/ flush everything left in the buffer

            std::cout << "Enter radius: ";
            std::cin >> radius;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Drawing::drawCircle(img, Point(x, y), radius, value);
            break;
        }
        case 2: {
            int x1, y1, x2, y2;

            std::cout << "Enter start X and Y coordinates (e.g. 10 15): ";
            std::cin >> x1 >> y1;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Enter end X and Y coordinates (e.g. 20 25): ";
            std::cin >> x2 >> y2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            Drawing::drawLine(img, Point(x1, y1), Point(x2, y2), value);
            break;
        }
        case 3: {
            int x1, y1, x2, y2;

            std::cout << "Enter top-left X and Y coordinates (e.g. 5 5): ";
            std::cin >> x1 >> y1;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Enter bottom-right X and Y coordinates (e.g. 15 15): ";
            std::cin >> x2 >> y2;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            Drawing::drawRectangle(img, Point(x1, y1), Point(x2, y2), value);
            break;
        }
        default:
            std::cout << "Invalid choice!\n";
    }
    
    std::string outputFile = outputPath.empty() ?
        "drawn_shape.pgm" :  // Save to output path if specified
        outputPath + "/drawn_shape.pgm";

    if (img.save(outputFile)) {
        std::cout << "Saved drawn image to: " << outputFile << std::endl;
    } else {
        std::cout << "Error saving the image" << std::endl;
    }
}

int main() {
    std::string inputPath;
    std::string outputPath;
    Image img;
    bool imageLoaded = false;

    while (true) {
        printMenu();
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Same reason as before ( to prevent \n in buffer)

        switch (choice) {
            case 0: // Exit
                std::cout << "Exiting program..." << std::endl;
                return 0;

            case 1: // Input/change PGM file path
                std::cout << "Enter the path to your PGM file: ";
                std::getline(std::cin, inputPath);
                if (!isValidPGMFile(inputPath)) {
                    std::cout << "Invalid format. Please provide a valid PGM file." << std::endl;
                    break;
                }
                if (!img.load(inputPath)) {
                    std::cout << "Error loading the image. Please check if the file is corrupted." << std::endl;
                    break;
                }
                imageLoaded = true;
                std::cout << "Image loaded successfully!" << std::endl;
                break;

            case 2: // Set output path
                std::cout << "Enter the output directory path: ";
                std::getline(std::cin, outputPath);
                if (!fs::exists(outputPath)) {
                    std::cout << "Creating directory: " << outputPath << std::endl;
                    fs::create_directories(outputPath);
                }
                break;

            case 3: // Brightness/Contrast
                if (!imageLoaded) {
                    std::cout << "Please load an image first (Option 1)" << std::endl;
                    break;
                }
                handleBrightnessContrast(img, outputPath);
                break;

            case 4: // Gamma Correction
                if (!imageLoaded) {
                    std::cout << "Please load an image first (Option 1)" << std::endl;
                    break;
                }
                handleGammaCorrection(img, outputPath);
                break;

            case 5: // Convolution
                if (!imageLoaded) {
                    std::cout << "Please load an image first (Option 1)" << std::endl;
                    break;
                }
                handleConvolution(img, outputPath);
                break;

            case 6: // Draw shape
                if (!imageLoaded) {
                    std::cout << "Please load an image first (Option 1)" << std::endl;
                    break;
                }
                drawShape(img, outputPath);
                break;

            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.