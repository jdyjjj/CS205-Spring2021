#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
 
using namespace std;
using namespace cv;

int main()
{
    // Mat srcImage = imread("giveup.jpg");
    // imshow("源图像", srcImage);
    char ar[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    Mat a(3, 3, CV_8S, ar);
    imwrite("tImage.jpg", a);
 
    // waitKey(0);
 
    return 0;
}
// ————————————————
// 版权声明：本文为CSDN博主「梧桐栖鸦」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/keith_bb/article/details/52864851
