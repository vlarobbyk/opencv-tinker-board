
import cv2

class PTest:
    
    def __init__(self):
        self.cameraid = 4
        
    def start(self):
        video = cv2.VideoCapture(self.cameraid)
        
        while True:
            ret, frame = video.read()
            frame = cv2.flip(frame,1)
            cv2.imshow('video', frame)
            
            if cv2.waitKey(23) == 27:
                break
        video.release()
        cv2.destroyAllWindows()
        
        
if __name__=="__main__":
    ptest = PTest()
    ptest.start()
