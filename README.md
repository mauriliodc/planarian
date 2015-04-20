# planarian
![alt tag](http://www.weinberg.northwestern.edu/images/research/huge.101.509767.JPG)

simple distance map based planner for mobile robots

#Building
```
mkdir build
cd build
cmake ..
make
```
you will find the executable into the *bin* folder

#Running
Try to run the example:

`./planning impossible.png`

the path will be showed as a red path

![alt tag](http://i.imgur.com/7oFx7Qe.png)

#Using it
Far from being complete at the moment but usable.

Take a look at the code into *planning.cpp* file, it's kinda self explanatory.
```c++
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
```
