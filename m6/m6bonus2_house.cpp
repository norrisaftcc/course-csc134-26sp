#include <iostream>
#include <fstream>

/*
PROMPT: "Write a C++ program that creates a PPM image file. The image should be [describe what you want]. Use
ofstream for file output and nested for loops to write the pixel data." 
Image should be of a house under a sunny sky.
*/

int main() {
    // 1. Define image dimensions (16:9 aspect ratio)
    const int width = 400;
    const int height = 225;

    // 2. Open the file using ofstream
    std::ofstream img("house.ppm");

    // Check if the file opened successfully
    if (!img.is_open()) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return 1;
    }

    // 3. Write the PPM header
    // "P3" means this is an ASCII RGB PPM file
    // "255" is the maximum color value
    img << "P3\n" << width << " " << height << "\n255\n";

    // 4. Generate the pixel data using nested loops
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            // Initialize with Sky color (Light Blue)
            int r = 135, g = 206, b = 235; 

            // -- Background Layer --
            
            // The Sun (Yellow circle in the top right)
            // Equation of a circle: (x - cx)^2 + (y - cy)^2 <= radius^2
            if ((x - 320) * (x - 320) + (y - 40) * (y - 40) <= 25 * 25) {
                r = 255; g = 255; b = 0;
            } 
            // The Ground (Green grass starting at row 180)
            else if (y >= 180) {
                r = 34; g = 139; b = 34;
            }

            // -- Foreground Layer (The House) --
            
            // House Roof (Dark Red Triangle)
            if (y >= 70 && y < 120) {
                // Calculate the width of the roof at the current height
                int half_width = (y - 70) * 60 / 50; 
                if (x >= 150 - half_width && x <= 150 + half_width) {
                    r = 139; g = 0; b = 0;
                }
            }
            // House Body (Brown Rectangle)
            if (y >= 120 && y < 180 && x >= 100 && x <= 200) {
                r = 210; g = 105; b = 30;
            }
            // Door (Darker Brown Rectangle inside the house)
            if (y >= 140 && y < 180 && x >= 135 && x <= 165) {
                r = 101; g = 67; b = 33;
            }

            // Write the RGB values to the file
            img << r << " " << g << " " << b << "\n";
        }
    }

    // Close the file output stream
    img.close();
    std::cout << "Success! 'house.ppm' has been created." << std::endl;

    return 0;
}