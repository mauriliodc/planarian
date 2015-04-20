#include "libs/distancemaplib.h"


int main(int argc, char** argv){
    DistanceMapImage source = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    DistanceMapImage destination;
    clock_t begin = clock();
    ComputeDistanceMap(source, destination);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cerr <<" time needed: "<<elapsed_secs<<endl;
    uchar key=' ';
    int b = 1000;
    imshow("SRC",source);
    imwrite("distancemap.png",destination);
    while(key!='q'){
        key=waitKey(33);
        if(key=='w') b+=10;
        if(key=='s') b-=10;
        imshow("RES",destination*b);
    }

    return 0;
}

