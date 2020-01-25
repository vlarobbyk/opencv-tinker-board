#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>

#include <dirent.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

#include <math.h>

using namespace std;
using namespace cv;

class HuMomentsExtractor{
    
    private:
        string outDir;
        int hMin, sMin, vMin;
        int hMax, sMax, vMax;
	int operationMode;

        Mat imageThreshold;
        
        // Hu Moments previously extracted for Red, Blue, and Green colors:
        
        double basehumoments[3][7] = {{0.234715,0.0205154,2.50687e-05,4.16411e-05,1.10422e-09,5.33478e-06,7.68625e-10},
                {0.221254,0.00779996,6.52606e-05,3.53464e-06,5.01449e-11,2.99813e-07,1.91687e-11},
                {0.201101,1.04941e-05,6.05104e-06,5.06225e-06,2.80052e-11,-6.2913e-09,-8.31543e-13}};
        
        // Red: hsv-min (0,53,162)    hsv-max (12,192,244)
        // Blue: hsv-min (83,125,183)   hsv-max (137,186,232)
        // Green: hsv-min (36,85,134) hsv-max (53,196,201)
        
        

        
        static void huFunc(int,void*);
        void printHSV();

        
        int euclideanDistance(vector<double>,int);
        
        void refreshImg();
        /*
        static void hMax(int,void*);
        static void sMax(int,void*);
        static void vMax(int,void*);
        static void hMin(int,void*);
        static void sMin(int,void*);
        static void vMin(int,void*);
        */

    public:
        HuMomentsExtractor(string = "fichero.txt");
        vector<double> extractHuMoments(Mat);
        vector<double> extractHuMoments(Mat,int,int,int,int,int,int);
        void capture();
        void setOperationMode(int);
};
