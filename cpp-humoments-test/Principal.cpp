
#include "HuMomentsExtractor.hpp"


int main(int argc, char *argv[]){
    
    int mode = 1;
    if (argc>1){
    	stringstream ss;
	ss << argv[1];
	ss >> mode;
	mode = (mode!=1 && mode!=2)?1:mode;
    }
    HuMomentsExtractor *huM = new HuMomentsExtractor();
    huM->setOperationMode(mode);
    huM->capture();
    

    delete huM;
    return 0;
}
