#include "libs/baseplannerlib.h"
#include "libs/baseplannerlib.h"

int main(int argc, char** argv){
    DistanceMapImage source = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    DistanceMapImage destination;
    ComputeDistanceMap(source, destination);
    Mat3f plan;
    ComputePath(cv::Point(10,10),cv::Point(540,340),destination,plan);
    imshow("Plan",plan);
    waitKey(0);
    return 0;
}

