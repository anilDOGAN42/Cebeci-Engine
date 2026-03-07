#define STB_IMAGE_IMPLEMENTATION
#include <stbi_load/stb_image.h>
#include "stbi_impl.hpp"

void stbi_init(){
    stbi_set_flip_vertically_on_load(true);
}