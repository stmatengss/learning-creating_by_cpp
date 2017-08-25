#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main() {
		cv::Mat img;
		cv::imread("a.jpg", 0).convertTo(img, CV_32FC1);
		float *res = (float *)img.data;
		cout << img.rows << endl;
		cout << img.cols << endl;
		cout << res[img.rows * img.cols - 3] << endl;
		cout << res[img.rows * img.cols - 2] << endl;
		cout << res[img.rows * img.cols - 1] << endl;
		cout << res[img.rows * img.cols ] << endl;
		cout << res[img.rows * img.cols + 1] << endl;
		cout << res[img.rows * img.cols + 2] << endl;
		cout << res[img.rows * img.cols + 3] << endl;
//		cout << length(res) << endl;
		
		return 0;
}
