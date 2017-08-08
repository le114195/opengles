//
//  MatLib.hpp
//  Opengles3D
//
//  Created by 勒俊 on 2017/8/8.
//  Copyright © 2017年 XunLei. All rights reserved.
//

#ifndef MatLib_hpp
#define MatLib_hpp

#include <opencv2/opencv.hpp>
#include <sstream>
#include <iostream>
#include <string>

cv::Mat psf2otf(const cv::Mat &psf, const cv::Size &outSize);

void circshift(cv::Mat &A, int shift_row, int shift_col);

template<typename T>
T sqr(const T x) {return x*x;}

class QDebug {
    public :
    QDebug(const std::string &_end, const std::string &_seperator) : end(_end), seperator(_seperator) {}
    QDebug(const QDebug &){}
    ~QDebug(){
        std::cout << oss.str() << end;
    }
    
    template<typename T>
    inline QDebug & operator << ( const T & rhs) {
        oss << rhs ;
        oss << seperator ;
        return *this ;
    }
    private :
    std::ostringstream oss ;
    std::string end, seperator;
};

inline QDebug info(std::string end = "\n", std::string seperator = " ") {
    return QDebug (end, seperator);
}

#endif /* MatLib_hpp */
