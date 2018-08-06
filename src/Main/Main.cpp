#include <iostream>
#include <string>

#include "ImgReader.h"

using namespace std;


int main() {
		// Create image reader obj
	string labelsPath("c:\\tmp\\labels.idx1-ubyte");
	string imagesPath("c:\\tmp\\images.idx3-ubyte");
	ImgReader img(labelsPath, imagesPath);

	img.ReadLabels();
	img.ReadImages();
	unsigned int a;

	while(1) {
		cin >> a;
		cin.get();
		system("cls");
		cout << "image number " << a << endl;
		img.PrintImage(a);
	}
	
	return 0;
}