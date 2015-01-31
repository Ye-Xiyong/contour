//
//  main.c
//  contour
//
//  Created by Yanzixu on 15-1-31.
//  Copyright (c) 2015年 Yanzixu. All rights reserved.
//

#include <stdio.h>

#include <iostream>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "find_contour.h"



using namespace cv;
using namespace std;


int main(int argc, const char * argv[])
{
 
    Mat image(500,500,CV_8UC3);
    
    vector<yzx_point> circle_1;
    vector<yzx_point> circle_2;
    
    for (int i=0; i<90; i++) {
        
        double theta = CV_PI*2*i/90.0;
        yzx_point p;
        p.x = 100*cos(theta)+200;
        p.y = 100.0*sin(theta) +200;
        circle_1.push_back(p);
        
        yzx_point p_2;
        p_2.x = 100*cos(theta)+300;
        p_2.y = 100.0*sin(theta) +200;
        circle_2.push_back(p_2);
    }
    
    vector<vector<yzx_point>> contours;
    try{
    YZX::find_contour(circle_1, circle_2, contours);
    }
    catch(std::runtime_error& err)
    {
        
        cout<<err.what()<<endl;
    }
//    cv::circle(image, Point2i(200,200), 100, Scalar(255,255,255),CV_FILLED);
//    cv::circle(image, Point2i(300,200), 100, Scalar(255,255,255),CV_FILLED);
//    cv::circle(image, Point2i(250,200), 40, Scalar(0,0,0),CV_FILLED);
//
//    Mat image_gray;
//    cvtColor(image, image_gray, CV_BGR2GRAY);
//    
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;
//
//    findContours( image_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
//    
//    cout<<contours.size()<<endl;
    
    for (int i=0; i<contours.size(); i++) {
        cout<<"current contour : "<<contours[i].size()<<endl;
        for (int j=0; j<contours[i].size()-1; j++) {
            cv::line(image, Point2i(contours[i][j].x,contours[i][j].y),
                     Point2i(contours[i][j+1].x,contours[i][j+1].y), Scalar(0,0,255),1);
        }
        cv::line(image, Point2i(contours[i][0].x,contours[i][0].y),
                 Point2i(contours[i].back().x,contours[i].back().y), Scalar(0,0,255),1);
    }
    
    
    imshow("image", image);
    waitKey(0);
    
    
    
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

