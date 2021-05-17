#include <string>   // Needed for strings
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream> 
#include <vector>
#include "volimage.h"

using namespace JFFMAH001;
using namespace std;

//define default constructor
JFFMAH001::VolImage::VolImage(){
	width = 0;
	height = 0;
} 

JFFMAH001::VolImage::~VolImage(){
	int size = slices.size();
	for (int k = 0; k < size; k++){
		for (int i = 0; i<height;i++){
			delete [] slices[k][i];
		}
		delete [] slices[k];
	}
}

bool JFFMAH001::VolImage::readImages(std::string baseName){	
	int num_img = 0;
	int dim[3] = {};
	std::string directory1 = "data/"; //directory
	std::string imgfile_initial = "data/";

	// obtain dimensions of image
	std::string dimfile = baseName;
	dimfile.append(".data");
	directory1.append(dimfile);
	ifstream in(directory1.c_str());
	if(!in) { 
		cout << "Couldn't open " << directory1 << endl; 
	}else{
		std::string token;
		int count = 0;
		int ran = 0;
		while (std::getline(in, token, ' ')){
			std::stringstream ss(token); // seperated word by word
			ss >> ran;
			dim[count] = ran;
			count++;
		}
		width = dim[0];
		height = dim[1];
		num_img = dim[2];
	}


	//create 2D buffer and read in raw files for each slice and add to slices vector
	imgfile_initial.append(baseName);
	for (int i = 0; i < num_img; i++){
		std::string imgfile = imgfile_initial;
		std::string s = std::to_string(i);
		imgfile.append(s);
		imgfile.append(".raw");

		//Initialise dynamic memory allocation for array with width and height
		ifstream rawfile(imgfile, ios::binary); //open file and specify it's a binary file
		unsigned char** imgslice = new unsigned char*[height];
		for(int j = 0; j < height; j++){
			imgslice[j] = new unsigned char[width];
			rawfile.read((char*)imgslice[j],width); 
		}
    	rawfile.close(); //close the file

		slices.push_back(imgslice);
	}
	return true;
}

void JFFMAH001::VolImage::diffmap(int sliceI, int sliceJ, std::string output_prefix){
	//output bytes to output raw file
	ofstream myfile;
	std::string raw = output_prefix;
	raw.append(".raw");
	myfile.open(raw);	
	for(int r = 0; r < height; ++r){
		for (int c = 0; c < width; c++){
				myfile << (unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);
		}
	}
	myfile.close();
}

void JFFMAH001::VolImage::extract(int sliceId, std::string output_prefix){
	//output dimensions to text file
	std::string data = output_prefix;
	data.append(".dat");
	ofstream dim;
	dim.open(data);

	dim << width << ' ' << height << ' ' << '1';
	dim.close();

	//output bytes to output raw file
	ofstream myfile;
	std::string raw = output_prefix;
	raw.append(".raw");
	myfile.open(raw);	
	for(int r = 0; r < height; ++r){
		for (int c = 0; c < width; c++){
				myfile << slices[sliceId][r][c];
		}
	}
	myfile.close();
}

int JFFMAH001::VolImage::volImageSize(void){
	int bytes = sizeof(unsigned char [width])*height*(slices.size());
	bytes += sizeof(unsigned char *)*height*slices.size();
	bytes += sizeof(unsigned char**)*slices.size();
	int images = slices.size();

	cout << "Number of images: " << images << endl;
	cout << "Number of bytes required: " << bytes << endl;
}

