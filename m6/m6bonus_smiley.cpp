#include <iostream>
#include <fstream>
#include <cmath>
/*
"Write a C++ program that creates a PPM image file. The image should be [describe what you want]. Use
ofstream for file output and nested for loops to write the pixel data." 
The image should be of a smiley face emoji, with a black background.
*/

using namespace std;

int main() {
    // Image dimensions
    const int width = 500;
    const int height = 500;

    ofstream image("smiley.ppm");

    // PPM Header: P3 means colors are in ASCII, then width, height, and max color value
    image << "P3" << endl;
    image << width << " " << height << endl;
    image << "255" << endl;

    // Center and radius for the face
    float centerX = width / 2.0;
    float centerY = height / 2.0;
    float faceRadius = 200.0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calculate distance from center for the yellow face
            float dx = x - centerX;
            float dy = y - centerY;
            float dist = sqrt(dx * dx + dy * dy);

            int r = 0, g = 0, b = 0; // Default Black Background

            // 1. Draw the yellow face circle
            if (dist < faceRadius) {
                r = 255; g = 255; b = 0; // Yellow

                // 2. Draw Eyes (Left eye at -70, -70; Right eye at 70, -70)
                float eyeDistL = sqrt(pow(dx + 70, 2) + pow(dy + 70, 2));
                float eyeDistR = sqrt(pow(dx - 70, 2) + pow(dy + 70, 2));
                
                if (eyeDistL < 25 || eyeDistR < 25) {
                    r = 0; g = 0; b = 0; // Black eyes
                }

                // 3. Draw Mouth (A simple semi-circle arc)
                // Checks if distance is within a range and if it's in the lower half (dy > 30)
                float mouthDist = sqrt(dx * dx + dy * dy);
                if (mouthDist > 100 && mouthDist < 120 && dy > 30 && abs(dx) < 100) {
                    r = 0; g = 0; b = 0; // Black mouth
                }
            }

            // Write the RGB triplets to the file
            image << r << " " << g << " " << b << "  ";
        }
        image << endl;
    }

    image.close();
    cout << "Image created: smiley.ppm" << endl;

    return 0;
}