#include "distancemaplib.h"



void ComputeDistanceMap(const DistanceMapImage src, DistanceMapImage& dst, bool animation){
    Cell _c;
    Cell _eight_cell;
    ushort _value=0;
    ushort _updated_value=0;
    CellContainer _container;
    Point _expanded_point;

    EightExpansionUtil _eightExpansion;
    EightExpansion_init(_eightExpansion);
    int _cols=src.cols;
    int _rows=src.rows;
    dst = Mat::ones(_rows,_cols,CV_16UC1);
    dst.setTo(Scalar(65535));

    int _eightExpansion_size = _eightExpansion.size();
    //first iteration to get all the obstacles
    //they will be the seed of my next cycle
    for(int i =0;i<_rows; i++){
        for(int j =0;j<_cols; j++){
            _value = (ushort)src.at<ushort>(i,j);
            if(_value==0){
                _c.point.x = j;
                _c.point.y = i;
                _c.parent.x= j;
                _c.parent.y= i;
                _c.value = 0;
                _container.push(_c);
                dst.at<ushort>(_c.point) = 0;
            }
        }
    }

    //second cycle, region growing like
    int _cnt=0;
    while(!_container.empty()){
        if(animation){
            if(_cnt%1000==0){
                cv::normalize(dst,dst,0,65535,cv::NORM_MINMAX);
                imshow("animation",dst);
                waitKey(1);
            }
            _cnt++;
        }
        Cell current;
        Cell _cc = _container.top();
        _value = dst.at<ushort>(_cc.point);
        _container.pop();
        for(int i =0;i<_eightExpansion.size();i++){
            _expanded_point = _cc.point +_eightExpansion.at(i).point ;
            //_updated_value = _value + _eightExpansion.at(i).value;
            _updated_value = (pow((_cc.parent.x - _expanded_point.x),2)+pow((_cc.parent.y - _expanded_point.y),2));
            if( _expanded_point.x > 0 &&_expanded_point.x < _cols && _expanded_point.y > 0 && _expanded_point.y < _rows ){
                if( dst.at<ushort>(_expanded_point) !=0 && dst.at<ushort>(_expanded_point) > _updated_value){
                    dst.at<ushort>(_expanded_point) = _updated_value;
                    current.point= _expanded_point;
                    current.parent=_cc.parent;
                    current.value=_updated_value;
                    _container.push(current);
                }
            }
        }
    }


}
