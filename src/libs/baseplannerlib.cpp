#include "baseplannerlib.h"

void ComputePath(Point start, Point goal, const DistanceMapImage distancemap, Mat3f& plan,float alpha){
    int cols = distancemap.cols;
    int rows = distancemap.rows;
    EightExpansionUtil eightExpansion;
    EightExpansion_init(eightExpansion);
    FloatCellContainer path_to_expand;
    FloatCell c;
    FloatCell cc;
    float updated_value;
    float value;
    Point expanded_point;
    c.point = start;
    c.value = 0.0f;
    path_to_expand.push(c);
    Mat1f workarea = Mat1f::ones(rows,cols)*-1.0f;
    workarea.at<float>(start)=1.0f;
    workarea.at<float>(goal)=1.0f;
    int i =0;
    bool goal_found=false;
    while(!path_to_expand.empty() && !goal_found){
        cc = path_to_expand.top();
        value = cc.value;
        path_to_expand.pop();
        for(int i =0;i<eightExpansion.size();i++){
            expanded_point = cc.point + eightExpansion.at(i).point;
            updated_value = value + eightExpansion.at(i).value;
            if( expanded_point.x > 0 && expanded_point.x < cols && expanded_point.y > 0 && expanded_point.y < rows ){
                if(expanded_point==goal){
                    goal_found=true;
                }
                if(workarea.at<float>(expanded_point)==-1){
                    workarea.at<float>(expanded_point) = updated_value + 1.0f/((float)distancemap.at<ushort>(expanded_point)*alpha);
                    FloatCell newcell;
                    newcell.point = expanded_point;
                    newcell.value = updated_value + 1.0f/((float)distancemap.at<ushort>(expanded_point)*alpha);
                    path_to_expand.push(newcell);
                }
            }
        }
    }

    bool target_reached=false;
    Mat1f result= Mat1f::zeros(rows,cols);
    Point current = goal;
    while(!target_reached){
        float min=999999;
        int index=-1;
        for(int i =0;i<eightExpansion.size();i++){
            expanded_point =current + eightExpansion.at(i).point;
            if(expanded_point == start){
                target_reached=true;
            }
            else if( expanded_point.x > 0 && expanded_point.x < cols && expanded_point.y > 0 && expanded_point.y < rows ){
                if(workarea.at<float>(expanded_point)<min && workarea.at<float>(expanded_point)!=-1.0f && workarea.at<float>(expanded_point)!=1.0f){
                    min = workarea.at<float>(expanded_point);
                    index = i;
                }
            }
        }
        result.at<float>(current + eightExpansion.at(index).point)=1.0f;
        current =current + eightExpansion.at(index).point;
    }
    Mat all;
    Mat temp;
    std::vector<cv::Mat> array_to_merge;
    distancemap.convertTo(all,CV_32FC1);
    temp=all.mul(-(result-1.0f));
    array_to_merge.push_back(temp);
    array_to_merge.push_back(temp);
    array_to_merge.push_back(all);
    cv::merge(array_to_merge, plan);
}
