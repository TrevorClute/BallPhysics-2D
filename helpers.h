#pragma once
#ifndef HELPERS_H
#define HELPERS_H

#include "Ball.h"
#include <math.h>
#include <stdint.h>
#include <vector>

namespace helpers {
float cosDegree(float degree) {
  float radians = (degree * M_PI / 180);
  return cos(radians);
}
float sinDegree(float degree) {
  float radians = (degree * M_PI / 180);
  return sin(radians);
}
float asinDegree(float degree) {
  float radians = degree * M_PI / 180;
  return asin(radians);
}
float atanDegree(float degree) {
  float radians = degree * M_PI / 180;
  return atan(radians);
}
float findDistance(float x1, float y1, float x2, float y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
float pythag(float x, float y) { return sqrt(pow((x), 2) + pow((y), 2)); }

const uint8_t *keyboard;

double delta;

} // namespace helpers

#endif
