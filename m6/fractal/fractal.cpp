// $ cc -O3 -o neon_fractal neon_fractal.cpp -lm
// $ ./neon_fractal
// $ ffmpeg -i frame-%03d.ppm -r 60 output_fractal.mp4

/*
GEMINI: 
Here is a different take on the "shader math" style. This program generates a hypnotic, glowing neon fractal 
animation.
It uses a technique called space folding (via the fract function) combined with iterative distance scaling 
to create an infinite, kaleidoscope-like structure. The colors are driven by a cosine-based palette 
popularized by Inigo Quilez, which smoothly cycles through a spectrum as time and spatial coordinates change.
*/

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct vec2 {
    float x, y;
    vec2(float x = 0, float y = 0) : x(x), y(y) {}
};

struct vec3 {
    float x, y, z;
    vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

// --- Vector Math Operators ---
vec2 operator*(const vec2 &a, float s) { return vec2(a.x * s, a.y * s); }
vec2 operator/(const vec2 &a, float s) { return vec2(a.x / s, a.y / s); }
vec2 operator+(const vec2 &a, const vec2 &b) { return vec2(a.x + b.x, a.y + b.y); }
vec2 operator-(const vec2 &a, const vec2 &b) { return vec2(a.x - b.x, a.y - b.y); }
vec2 operator-(const vec2 &a, float s) { return vec2(a.x - s, a.y - s); }

vec3 operator*(const vec3 &a, const vec3 &b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
vec3 operator*(const vec3 &a, float s) { return vec3(a.x * s, a.y * s, a.z * s); }
vec3 operator+(const vec3 &a, const vec3 &b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }

// --- Shader Functions ---
float length(const vec2 &a) { return sqrtf(a.x * a.x + a.y * a.y); }
vec2 fract(const vec2 &a) { return vec2(a.x - floorf(a.x), a.y - floorf(a.y)); }
vec3 cos_v(const vec3 &a) { return vec3(cosf(a.x), cosf(a.y), cosf(a.z)); }

// Smooth color palette generator 
vec3 palette(float t) {
    vec3 a(0.5f, 0.5f, 0.5f);
    vec3 b(0.5f, 0.5f, 0.5f);
    vec3 c(1.0f, 1.0f, 1.0f);
    vec3 d(0.263f, 0.416f, 0.557f);
    return a + b * cos_v((c * t + d) * (2.0f * M_PI));
}

int main() {
    char buf[256];
    const int num_frames = 240;
    const int w = 16 * 60;
    const int h =  9 * 60;

    for (int i = 0; i < num_frames; ++i) {
        snprintf(buf, sizeof(buf), "frame-%03d.ppm", i);
        const char *output_path = buf;
        FILE *f = fopen(output_path, "wb");
        
        fprintf(f, "P6\n");
        fprintf(f, "%d %d\n", w, h);
        fprintf(f, "255\n");
        
        vec2 r = {(float)w, (float)h};
        // Normalize time to a full 2*PI loop for a perfect looping animation
        float t = ((float)i / num_frames) * 2.0f * M_PI; 

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                vec2 FC = {(float)x, (float)(h - 1 - y)}; // Flip Y axis to match standard shader coordinates
                
                // Normalize pixel coordinates (from -1 to 1) and fix aspect ratio
                vec2 uv = (FC * 2.0f - r) / r.y;
                vec2 uv0 = uv;
                vec3 finalColor(0, 0, 0);

                // Fractal iteration loop
                for (float j = 0.0f; j < 4.0f; j++) {
                    uv = fract(uv * 1.5f) - 0.5f;

                    float d = length(uv) * expf(-length(uv0));
                    vec3 col = palette(length(uv0) + j * 0.4f + t);

                    d = sinf(d * 8.0f + t) / 8.0f;
                    d = fabsf(d);
                    
                    // Creates the glowing/neon edges
                    d = powf(0.01f / d, 1.2f);

                    finalColor = finalColor + col * d;
                }

                // Clamp colors to [0.0, 1.0] and output to 8-bit PPM
                fputc((unsigned char)(fminf(finalColor.x, 1.0f) * 255.0f), f);
                fputc((unsigned char)(fminf(finalColor.y, 1.0f) * 255.0f), f);
                fputc((unsigned char)(fminf(finalColor.z, 1.0f) * 255.0f), f);
            }
        }
        fclose(f);
        printf("Generated %s (%3d/%3d)\n", output_path, i + 1, num_frames);
    }
    return 0;
}