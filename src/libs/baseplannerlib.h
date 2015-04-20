#ifndef _BASEPLANNER
#define _BASEPLANNER

#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
#include <stdint.h>
#include <ctime>
#include "planutils.h"
#include "distancemaplib.h"

using namespace cv;
using namespace std;

void ComputePath(Point start, Point goal,const DistanceMapImage distancemap, Mat3f& result,float alpha=1.0f);

#endif
