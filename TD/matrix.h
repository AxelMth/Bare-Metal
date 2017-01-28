#ifndef MATRIX_H
#define MATRIX_H

void matrix_init(void);
void test_pixels(void);
void display_image(void);
void display_frame(void);

// Définition de la structure des pixels
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

#endif // MATRIX_H
