#ifndef COLOR_H
#define COLOR_H

typedef struct COLOR {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} COLOR;

static inline COLOR createColor(unsigned char red, unsigned char green, unsigned char blue) {
    // Create a color given values
    COLOR temp;
    temp.red = red;
    temp.green = green;
    temp.blue = blue;
    return temp;
}

#endif // COLOR_H
