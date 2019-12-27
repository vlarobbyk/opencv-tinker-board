all:
	g++ Principal.cpp HuMomentsExtractor.cpp -I//home/pi/opencv-4.1.1/opencv_4/include/opencv4/ -L/home/pi/opencv-4.1.1/opencv_4/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio -o huM.bin
	
run:
	./huM.bin


test:
	g++ TestCV.cpp -I/home/linaro/aplicaciones/Librerias/opencv/opencvi/include/opencv4 -L/home/linaro/aplicaciones/Librerias/opencv/opencvi/lib/ -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio -o test.bin

rtest:
	./test.bin
