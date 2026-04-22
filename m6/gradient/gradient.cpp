/*
Today's assignment is to make a short animation, which will be built by programatically generating 
240 PPM frames that the user will stitch together with ffmpeg.
ADDITIONAL INSTRUCTIONS: generate the image frames as 16x9, the animation should be an interesting 
rotating gradient across a checkerboard pattern
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <filesystem>
#include <iomanip>
#include <sstream>

// --- CONFIGURATION ---
const int WIDTH = 640;          // 16:9 Aspect Ratio width
const int HEIGHT = 360;         // 16:9 Aspect Ratio height
const int FRAMES = 240;         // Total number of frames for the animation
const int SQUARE_SIZE = 40;     // Size of the checkerboard squares
const std::string OUTPUT_DIR = "frames";

// Cross-platform Pi definition
const double PI = std::acos(-1.0);

int main() {
    // Create the output directory if it doesn't exist ʕ•ᴥ•ʔ
    if (!std::filesystem::exists(OUTPUT_DIR)) {
        std::filesystem::create_directory(OUTPUT_DIR);
    }

    // Center coordinates of the image
    double cx = WIDTH / 2.0;
    double cy = HEIGHT / 2.0;

    std::cout << "Pre-computing spatial grid for optimization (uwu)..." << std::endl;
    
    // Pre-computing the checkerboard matrix and atan2 angles saves massive amounts 
    // of calculation time!
    std::vector<std::vector<double>> grid_angles(HEIGHT, std::vector<double>(WIDTH));
    std::vector<std::vector<bool>> grid_checker(HEIGHT, std::vector<bool>(WIDTH));
    
    for (int y = 0; y < HEIGHT; ++y) {
        double dy = y - cy;
        int check_y = y / SQUARE_SIZE;
        
        for (int x = 0; x < WIDTH; ++x) {
            double dx = x - cx;
            // Calculate polar angle from the center (returns -pi to pi)
            grid_angles[y][x] = std::atan2(dy, dx);
            
            // Mathematical relationship for a checkerboard pattern
            int check_x = x / SQUARE_SIZE;
            grid_checker[y][x] = ((check_x + check_y) % 2 == 0);
        }
    }

    std::cout << "Generating " << FRAMES << " PPM frames..." << std::endl;
    
    // Phase shifts for RGB color wheels (120 degrees apart)
    double phase_g = 2.0 * PI / 3.0;
    double phase_b = 4.0 * PI / 3.0;

    for (int frame = 0; frame < FRAMES; ++frame) {
        // Calculate rotation offset for this specific frame.
        // It transitions smoothly from 0 to 2*pi over 240 frames.
        double angle_offset = (static_cast<double>(frame) / FRAMES) * 2.0 * PI;
        
        // Buffer for image data. Using a flat vector for P6 format is highly efficient.
        std::vector<uint8_t> pixel_data(WIDTH * HEIGHT * 3);
        int idx = 0;
        
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                // If the current pixel falls on an "active" checkerboard square
                if (grid_checker[y][x]) {
                    // Add the frame's offset to the pixel's inherent angle
                    double effective_angle = grid_angles[y][x] + angle_offset;
                    
                    // Map the angle smoothly to RGB values using sine waves.
                    // sine returns [-1, 1]. We shift to [0, 2] and multiply by 127.5 to get [0, 255]
                    uint8_t r = static_cast<uint8_t>((std::sin(effective_angle) + 1.0) * 127.5);
                    uint8_t g = static_cast<uint8_t>((std::sin(effective_angle + phase_g) + 1.0) * 127.5);
                    uint8_t b = static_cast<uint8_t>((std::sin(effective_angle + phase_b) + 1.0) * 127.5);
                    
                    pixel_data[idx] = r;
                    pixel_data[idx+1] = g;
                    pixel_data[idx+2] = b;
                } else {
                    // Dark gray background for the alternating inactive squares
                    pixel_data[idx] = 20;
                    pixel_data[idx+1] = 20;
                    pixel_data[idx+2] = 20;
                }
                idx += 3;
            }
        }
                
        // Format the filename (e.g., frame_000.ppm, frame_001.ppm)
        std::ostringstream filename;
        filename << OUTPUT_DIR << "/frame_" << std::setfill('0') << std::setw(3) << frame << ".ppm";
        
        // Write binary PPM file (P6 format)
        std::ofstream file(filename.str(), std::ios::binary);
        if (file) {
            // Header: Format (P6), Width, Height, Max Color Value (255)
            file << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
            file.write(reinterpret_cast<const char*>(pixel_data.data()), pixel_data.size());
            file.close();
        } else {
            std::cerr << "Failed to open file: " << filename.str() << " (Ó╭╮Ò)" << std::endl;
            return 1;
        }
            
        // Display progress in the console
        if ((frame + 1) % 24 == 0 || frame == 0) {
            std::cout << "Completed frame " << frame + 1 << "/" << FRAMES << "..." << std::endl;
        }
    }

    std::cout << "\n✅ Animation frames generated successfully (づ｡◕‿‿◕｡)づ" << std::endl;
    std::cout << "To stitch these together, use the following FFmpeg command:" << std::endl;
    std::cout << "ffmpeg -framerate 30 -i frames/frame_%03d.ppm -c:v libx264 -pix_fmt yuv420p output.mp4" << std::endl;

    return 0;
}