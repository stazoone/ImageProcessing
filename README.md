# Image Processing Application

A C++ application for processing and manipulating PGM (Portable Gray Map) images with various operations including brightness/contrast adjustment, gamma correction, convolution filters, and shape drawing capabilities made for my OOP course.

## Features

- **Image Loading and Saving**: Support for PGM image format
- **Basic Image Processing**:
  - Brightness and contrast adjustment
  - Gamma correction
- **Convolution Filters**:
  - Identity kernel
  - Mean blur
  - 3x3 Gaussian blur
  - Horizontal Sobel
  - Vertical Sobel
- **Drawing Capabilities**:
  - Line drawing
  - Shape drawing
- **Custom Output Directory**: Flexible output path configuration

After building, run the executable:
```bash
./ImageProcessing
```

The application provides an interactive menu with the following options:

1. Input/change the path to a PGM file
2. Set output directory path
3. Apply brightness/contrast adjustment
4. Apply gamma correction
5. Apply convolution
6. Draw shape
0. Exit program

### Example Operations

#### Brightness and Contrast Adjustment
- Adjusts image brightness and contrast using alpha (contrast) and beta (brightness) parameters
- Output is saved as "brightness_contrast.pgm"

#### Gamma Correction
- Applies gamma correction to the image
- Output is saved as "gamma_corrected.pgm"

#### Convolution Filters
- Identity kernel: Preserves original image
- Mean blur: Applies averaging filter
- Gaussian blur: Applies 3x3 Gaussian blur
- Sobel filters: Edge detection (horizontal and vertical)

## Project Structure

- `main.cpp`: Main application entry point and menu interface
- `Image.h/cpp`: Core image class implementation
- `ImageProcessing.h/cpp`: Image processing operations
- `Drawing.h/cpp`: Drawing functionality
- `Point.h/cpp`: Point class for coordinate handling
- `Rectangle.h/cpp`: Rectangle class for shape drawing
- `CMakeLists.txt`: Build configuration

