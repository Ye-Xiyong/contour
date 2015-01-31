//
//  find_contour.cpp
//  contour
//
//  Created by Yanzixu on 15-1-31.
//  Copyright (c) 2015年 Yanzixu. All rights reserved.
//

//#pragma once
#include "find_contour.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <stdexcept>

using namespace cv;

namespace YZX {
    
    void findMinMax(const vector<yzx_point>& in_pts,
                    Point2d& xMM,
                    Point2d& yMM)
    {
        size_t sz = in_pts.size();
        for (size_t i = 0; i<sz; i++) {
            if(xMM.x>in_pts[i].x) xMM.x = in_pts[i].x;
            if(xMM.y<in_pts[i].x) xMM.y = in_pts[i].x;
            if(yMM.x>in_pts[i].y) yMM.x = in_pts[i].y;
            if(yMM.y<in_pts[i].y) yMM.y = in_pts[i].y;
        }
    }
    
    void DrawMask(const vector<yzx_point>& in_pts,
                  double magnifier,
                  Mat& output)
    {
        Mat mask_tmp;
        output.copyTo(mask_tmp);
        mask_tmp.setTo(Scalar(0));
        
        for (int i=0; i<in_pts.size()-1; i++) {
            Point2i st(in_pts[i].x,in_pts[i].y);
            Point2i ed(in_pts[i+1].x,in_pts[i+1].y);
            st*=magnifier;
            ed*=magnifier;
            cv::line(mask_tmp, st, ed, Scalar(1));
        }
        Point2i st(in_pts.front().x,in_pts.front().y);
        Point2i ed(in_pts.back().x,in_pts.back().y);
        st*=magnifier;
        ed*=magnifier;
        cv::line(mask_tmp, st, ed, Scalar(1));
        
        cv::floodFill(mask_tmp, Point2i(1,1), Scalar(1));
        mask_tmp = 1- mask_tmp;
        cv::bitwise_or(mask_tmp, output, output);
    }
    
    void find_contour(
                      const vector<yzx_point>& in_pt1,
                      const vector<yzx_point>& in_pt2,
                      vector<vector<yzx_point>>& out_pts
                      )
    {
        if(3 >= in_pt2.size() || 3 >= in_pt1.size())
            throw std::runtime_error("input point series error");
        
        Point2d xMM(99999,-99999);
        Point2d yMM = xMM;
        findMinMax(in_pt1, xMM, yMM);
        findMinMax(in_pt2, xMM, yMM);
        
        int nWidth = xMM.y-xMM.x;
        int nHeight = yMM.y-yMM.x;
        
        if(nWidth<=0 || nHeight<=0)
            throw std::runtime_error("input point series error");
        
        double magnifier = 1.0;
        if(nWidth<100 || nHeight<100)
        {
            magnifier = (std::max)(100.0/nWidth,100.0/nHeight);
        }
        
        //cout<<magnifier<<endl;
        
        int draw_width = (xMM.y+10)*magnifier;
        int draw_height = (yMM.y+10)*magnifier;
        
        Mat mask(draw_height,draw_width,CV_8UC1);
        mask.setTo(Scalar(0));
        
        //先画出来
        
        DrawMask(in_pt1, magnifier,mask);
        DrawMask(in_pt2, magnifier,mask);
        
        //imshow("maskTmp",mask*255);
        //waitKey(0);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        try{
        findContours( mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
        }
        catch(cv::Exception& e)
        {
            throw std::runtime_error(e.what());
        }
        if(contours.size() == 0)
            throw std::runtime_error("internal error: no contours found");
        

        out_pts.clear();
        out_pts.resize(contours.size());
        for (int i=0; i<out_pts.size(); i++) {
            out_pts[i].resize(contours[i].size());
            for (int j=0; j<out_pts[i].size(); j++) {
                yzx_point yzxPoint;
                yzxPoint.x = contours[i][j].x / magnifier;
                yzxPoint.y = contours[i][j].y / magnifier;
                
                out_pts[i][j]=yzxPoint;
            }
            
        }

        
        
        
    }
}