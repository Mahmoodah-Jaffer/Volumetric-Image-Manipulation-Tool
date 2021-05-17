#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "volimage.h"

int main(int argc, char* argv[]){

		using namespace std;
		using namespace JFFMAH001;
		VolImage vi; //instantiate object - constructor will be called automatically
		std::string filename;
		std::string operation;
		std::string fileseq;
		std::string imgslice1;
		std::string imgslice2;
//Get arguments entered by user
		if (argc == 5 ){
			fileseq = string(argv[1]);
			operation  = string(argv[2]);
			imgslice1 = string(argv[3]);
			filename = string(argv[4]);
		}
		else if (argc == 6){
			fileseq = string(argv[1]);
			operation  = string(argv[2]);
			imgslice1 = string(argv[3]);
			imgslice2 = string(argv[4]);
			filename = string(argv[5]);
		}
		else{
			fileseq = string(argv[1]);
		}
//compute difference map
		if(operation == "-d"){
			vi.readImages(fileseq);
			int slice1;
			std::istringstream (imgslice1) >> slice1;
			int slice2;
			std::istringstream (imgslice2) >> slice2;
			vi.diffmap(slice1,slice2, filename);
			vi.volImageSize();
			cout << "Difference Map operation completed" << endl;
//extract image slice given by user
		}else if(operation == "-x"){
			vi.readImages(fileseq);
			int slice;
			std::istringstream (imgslice1) >> slice;
			vi.extract(slice, filename);
			vi.volImageSize();
			cout << "Extraction operation completed" << endl;
//perform no operation
		}else{
			vi.readImages(fileseq);
			vi.volImageSize();
		}
		return 0;
}