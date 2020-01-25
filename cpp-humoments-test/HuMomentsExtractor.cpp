
#include "HuMomentsExtractor.hpp"



HuMomentsExtractor::HuMomentsExtractor(string outDir){
    this->outDir = outDir;
    this->operationMode = 1;
    this->hMax=180;
    this->sMax=255;
    this->vMax=255;
}


vector<double> HuMomentsExtractor::extractHuMoments(Mat imageO){

    Mat image;
    Mat hsv;
    Moments _moments;
    double huMoments[7];
    vector<double> huMomentsV;
    
    cvtColor(imageO,hsv,COLOR_BGR2HSV);
    imshow("hsv",hsv);
    
    inRange(hsv,Scalar(hMin,sMin,vMin),Scalar(hMax,sMax,vMax),imageThreshold);
    imshow("threshold",imageThreshold);

    _moments = moments(imageThreshold, true);
    HuMoments(_moments, huMoments);
    
    for (int i=0; i<7;i++){
        huMomentsV.push_back(0);
        huMomentsV[i] = huMoments[i];
        cout << huMoments[i] <<",";
    }
    cout << endl;

    return huMomentsV;
}

vector<double> HuMomentsExtractor::extractHuMoments(Mat imageO,int hmin,int smin,int vmin,int hmax,int smax,int vmax){

    Mat hsv;
    Moments _moments;
    double huMoments[7];
    vector<double> huMomentsV;

    cvtColor(imageO,hsv,COLOR_BGR2HSV);
    imshow("hsv",hsv);
    
    inRange(hsv,Scalar(hmin,smin,vmin),Scalar(hmax,smax,vmax),imageThreshold);
    imshow("threshold",imageThreshold);

    _moments = moments(imageThreshold, true);
    HuMoments(_moments, huMoments);
    
    for (int i=0; i<7;i++){
        huMomentsV.push_back(0);
        huMomentsV[i] = huMoments[i];
        cout << huMoments[i] <<"@";
    }
    huMomentsV.push_back(_moments.m10/_moments.m00);
    huMomentsV.push_back(_moments.m01/_moments.m00);
    cout << endl;

    return huMomentsV;
}

void HuMomentsExtractor::huFunc(int v,void* p){
    HuMomentsExtractor *hu = reinterpret_cast<HuMomentsExtractor *> (p);
    hu->refreshImg();
}

void HuMomentsExtractor::refreshImg(){
    imshow("threshold",imageThreshold);
    printHSV();
}

void HuMomentsExtractor::printHSV(){
    cout << "hsv-min (" << hMin << "," << sMin << "," << vMin << ")" << "hsv-max (" << hMax << "," << sMax << "," << vMax << ")" << endl;
}

int HuMomentsExtractor::euclideanDistance(vector<double> moms,int i){
    double d = 0.0;
    int index = -1;
    
    double thresholdm = 0.3;
    
    for (int j=0;j<7;j++){
        //cout << "m: " << moms[j] << " humoments: " << basehumoments[i][j] << ",";
        d+=((moms[j]-basehumoments[i][j])*(moms[j]-basehumoments[i][j]));
    }
    cout << endl;
    d = sqrt(d);
    //cout << "Distance: " << " i: " << i << " :: " << d << endl;

    if (i==2)
        thresholdm = 0.41;

    if (d<thresholdm)
        return i;
    
    return -1;
}

void HuMomentsExtractor::setOperationMode(int m){
	this->operationMode = m;
}

void HuMomentsExtractor::capture(){
    VideoCapture video(4);
    if (video.isOpened()){
	video.set(CAP_PROP_FRAME_WIDTH,800);
	video.set(CAP_PROP_FRAME_HEIGHT,600);

        Mat frame;

        namedWindow("video",WINDOW_AUTOSIZE);
        namedWindow("hsv",WINDOW_AUTOSIZE);
        namedWindow("threshold",WINDOW_AUTOSIZE);
        
        createTrackbar("HMin","video",&hMin, 180, HuMomentsExtractor::huFunc,static_cast<void *>(this));
        createTrackbar("SMin","video",&sMin, 255, HuMomentsExtractor::huFunc,static_cast<void *>(this));
        createTrackbar("VMin","video",&vMin, 255, HuMomentsExtractor::huFunc,static_cast<void *>(this));
        
        createTrackbar("HMax","video",&hMax, 180, HuMomentsExtractor::huFunc,static_cast<void *>(this));
        createTrackbar("SMax","video",&sMax, 255, HuMomentsExtractor::huFunc,static_cast<void *>(this));
        createTrackbar("VMax","video",&vMax, 255, HuMomentsExtractor::huFunc,static_cast<void *>(this));        
        
        vector<double> huMoments;
        int indexRed = -1;
        int indexBlue = -1;
        int indexGreen = -1;
        
        while(1==1){
            video >> frame;
            flip(frame,frame,1);

	    if (this->operationMode==1){ // In this mode you can use the trackbars to determine the HSV segmentation range
		huMoments = this->extractHuMoments(frame);
            }else if (this->operationMode==2){ // In this mode you can use test the values selected to perform the segmentation and Hu Moments extraction
	            huMoments = this->extractHuMoments(frame, 0,53,162,12,192,244);
	            indexRed = this->euclideanDistance(huMoments,0);
	            if (indexRed!=-1){
	                cout << "Red object: " << indexRed << endl;
	                putText(frame, "Object 1 Detected - Red", Point(huMoments[7],huMoments[8]), FONT_HERSHEY_DUPLEX, 1, Scalar(0,10,143), 2);
	            }else{
	            
	                huMoments = this->extractHuMoments(frame,83,125,183,137,186,232);
	                indexBlue = this->euclideanDistance(huMoments,1);
	                if (indexBlue!=-1){
	                    cout << "Blue object: " << indexBlue << endl;
	                    putText(frame, "Object 2 Detected - Blue", Point(huMoments[7],huMoments[8]), FONT_HERSHEY_DUPLEX, 1, Scalar(143,10,0), 2);
	                }else{
	                    huMoments = this->extractHuMoments(frame,35,52,99,62,172,204);
	                    indexGreen = this->euclideanDistance(huMoments,2);
	                    if (indexGreen!=-1){
	                        cout << "Object 3 Detected - Green: " << indexGreen << endl;
	                        putText(frame, "Object 3 Detected - Green: ", Point(huMoments[7],huMoments[8]), FONT_HERSHEY_DUPLEX, 1, Scalar(10,143,3), 2);
	                    }
	                }
	            }
	    }
            imshow("video",frame);
            if(waitKey(23)==27)
                break;
        }
    }
}
