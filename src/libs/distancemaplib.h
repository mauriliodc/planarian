#ifndef _DISTANCEMAPLIB
#define _DISTANCEMAPLIB

#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
#include <stdint.h>
#include <ctime>
#include "planutils.h"
using namespace cv;
using namespace std;

void ComputeDistanceMap(const DistanceMapImage src, DistanceMapImage& dst, bool animation=false);

#endif
