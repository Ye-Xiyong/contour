//
//  find_contour.h
//  contour
//
//  Created by Yanzixu on 15-1-31.
//  Copyright (c) 2015年 Yanzixu. All rights reserved.
//

#ifndef __contour__find_contour__
#define __contour__find_contour__

#include <iostream>
#include <vector>
using namespace std;

/*
use your own defination if feasible and comment mine below.
 An example of subsituting mine with cv::Point2d might be:
 
 typedef cv::Point2d yzx_point;
 
REMEMBER: 
 scalar member x,y in point structure must come in double type! int is NOT tolerated!
*/
typedef struct yzx_point{
    double x;
    double y;
} yzx_point;



namespace YZX {
    /**
     *  find the combined contour from 2 separated contours
     *
     *  @param in_pt1  first point series representing contour No.1
     *  @param in_pt2  second point series representing contour No.2
     *  @param out_pts output combined contour
     *  @note
        the output format comes in vector<vector<Point>>;
        the first vector<> indicates how many contours reside in output
        the second vector<> represents point series in each contour.
     */
    void find_contour(
                      const vector<yzx_point>& in_pt1,
                      const vector<yzx_point>& in_pt2,
                      vector<vector<yzx_point>>& out_pts
    );
}

#endif /* defined(__contour__find_contour__) */
