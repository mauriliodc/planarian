#include "libs/baseplannerlib.h"
#include "libs/baseplannerlib.h"
#include <unistd.h>
using namespace std;
using namespace cv;

char lastkeypressed=-1;
Point start(-10,-10);
Point goal(-10,-10);
Mat3f plan;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN && lastkeypressed=='s')
    {
        cout <<"setting start"<<endl;
        start.x=x;
        start.y=y;
    }
    else if  ( event == EVENT_LBUTTONDOWN && lastkeypressed=='g')
    {
        cout <<"setting goal"<<endl;
        goal.x=x;
        goal.y=y;
    }
    //    else if  ( event == EVENT_RBUTTONDOWN )
    //    {
    //        cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    //    }
    //    else if  ( event == EVENT_MBUTTONDOWN )
    //    {
    //        cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    //    }
    else if ( event == EVENT_MOUSEMOVE && lastkeypressed=='p')
    {
        goal.x=x;
        goal.y=y;
    }
}

void banner(){
    std::cout<<"q to quit"<<endl;
    std::cout<<"s-rclick to set start"<<endl;
    std::cout<<"g-rclick to set goal"<<endl;
    std::cout<<"p to show plan"<<endl;
    std::cout<<"r to set reset"<<endl;

}
cv::Mat draw_markers(cv::Mat image, bool convert){
    if(convert){
        cvtColor(image,image,CV_GRAY2RGB);
    }
    cv::circle(image,start,3,Scalar(127,0,0),5);
    cv::circle(image,goal,3,Scalar(0,255,0),5);
    return image;
}

int main(int argc, char** argv){
    float mplier=1.0f;
    float alpha=1.0f;
    if(argc>=3){
        mplier=atoi(argv[2]);
    }
    if(argc>=4){
        alpha=atof(argv[3]);
    }
    banner();
    DistanceMapImage source = cv::imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
    DistanceMapImage destination;
    ComputeDistanceMap(source, destination);
    cv::namedWindow("distance map", 1);
    cv::setMouseCallback("distance map", CallBackFunc, NULL);
    char key=' ';

    while(key!='q'){
        lastkeypressed=key;
        cv::imshow("distance map",draw_markers(destination.clone(),true)*mplier);
        if(key=='r'){
            start.x=-10;
            start.y=-10;
            goal.x=-10;
            goal.y=-10;
        }
        else if(key=='p'){
            cerr<<"starting!"<<endl;
            ComputePath(start,goal,destination,plan,alpha);
            cv::imshow("plan",draw_markers(plan.clone(),false));
            cerr<<"computed!"<<endl;
        }
        key=cv::waitKey(330);


    }
    return 0;
}

