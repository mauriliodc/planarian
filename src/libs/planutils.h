#ifndef _PLANUTILS
#define _PLANUTILS

#include <opencv2/opencv.hpp>
#include <iostream>
#include <queue>
#include <stdint.h>
#include <ctime>

using namespace cv;
using namespace std;

struct Cell{
    Point point;
    Point parent;
    ushort value;
};


struct FloatCell{
    Point point;
    float value;
};

struct cell_comparator{
    bool operator() (const Cell& lhs, const Cell& rhs) const
    {return lhs.value>rhs.value;}
};

struct float_cell_comparator{
    bool operator() (const FloatCell& lhs, const FloatCell& rhs) const
    {return lhs.value>rhs.value;}
};

typedef vector<Cell> EightExpansionUtil;
typedef std::priority_queue<Cell,vector<Cell>,cell_comparator> CellContainer;
typedef std::priority_queue<FloatCell,vector<FloatCell>,float_cell_comparator> FloatCellContainer;
typedef cv::Mat1w DistanceMapImage;


void EightExpansion_init(EightExpansionUtil& e);

#endif
