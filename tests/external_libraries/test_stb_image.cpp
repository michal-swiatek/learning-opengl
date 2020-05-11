/*
 *  Created by michal-swiatek on 11.05.2020.
 */

#include <cassert>

#include <stb_image/stb_image.h>

int main() {
    int width, height, channels;
    unsigned char* data = stbi_load("not existing path", &width, &height, &channels, 0);

    assert(data == nullptr);

    return 0;
}
