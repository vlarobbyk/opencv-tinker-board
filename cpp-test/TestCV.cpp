#include <iostream>
#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){

	VideoCapture video(4);

	if(video.isOpened()){
		video.set(CAP_PROP_FRAME_WIDTH,800);
		video.set(CAP_PROP_FRAME_HEIGHT,600);

		Mat frame;
		namedWindow("video",WINDOW_AUTOSIZE);
		while(1==1){
			video >> frame;
			//flip(frame,frame,1);
			imshow("video",frame);
			if(waitKey(23)==27)
				break;
		}
	}

	cout << "If you want to close the demo, press ESC again" << endl;

	Mat img = imread("Logo-GIIATa-small.jpg");
	imshow("logo",img);
	waitKey(0);

	return 0;
}
