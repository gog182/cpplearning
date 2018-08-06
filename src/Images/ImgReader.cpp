#include "ImgReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

using namespace std;

ImgReader::ImgReader() {
}

ImgReader::ImgReader(string t_labelsPath, string t_imagesPath) {

	// Opens file
	cout << "opening " << t_labelsPath << endl;
	m_labelFile.open(t_labelsPath.c_str(), ios::in | ios::binary);

	cout << "opening " << t_imagesPath << endl;
	m_imgFile.open(t_imagesPath.c_str(), ios::in | ios::binary);

}

int ImgReader::ReadImages() {
	unsigned int magic_number;		// 0000     32 bit integer  0x00000801(2049) magic number (MSB first) 
	unsigned int number_of_items;	// 0004     32 bit integer  60000            number of items
	unsigned int number_of_rows;	// 0008     32 bit integer  60000            number of rows
	unsigned int number_of_columns;	// 0012     32 bit integer  60000            number of columns
	unsigned char byte;

	// 0000 : first four bytes (magic number)
	m_imgFile.read((char*)&byte, 1);
	magic_number = byte;
	for (int i = 0; i < 3; i++) {
		m_imgFile.read((char*)&byte, 1);
		magic_number <<= 8;
		magic_number |= byte;
	}
	cout << magic_number << endl;

	if (magic_number == MAGIC_NB_IMAGES) {
		cout << ":) Magic number correctly retrieved! ("<<magic_number<<")" << endl;
	}
	else {
		cout << ":( Magic number could not be retrieved! halting..." << endl;
		return -1;
	}

	// 0004 : number of items
	m_imgFile.read((char*)&byte, 1);
	number_of_items = byte;
	for (int i = 0; i < 3; i++) {
		m_imgFile.read((char*)&byte, 1);
		number_of_items <<= 8;
		number_of_items |= byte;
	}
	cout << ":) Found " << number_of_items << " images." << endl;
	
	// 0008 : number of rows
	m_imgFile.read((char*)&byte, 1);
	number_of_rows = byte;
	for (int i = 0; i < 3; i++) {
		m_imgFile.read((char*)&byte, 1);
		number_of_rows <<= 8;
		number_of_rows |= byte;
	}
	if (number_of_rows == NB_ROWS) {
		cout << ":) Number of rows is correct: " << number_of_rows << "!" << endl;
	}
	else {
		cout << ":( Number of rows ("<< number_of_rows << ") is different from expected ("<<NB_ROWS <<"). Halting..." << endl;
		return -2;
	}

	// 0012 : number of columns
	m_imgFile.read((char*)&byte, 1);
	number_of_columns = byte;
	for (int i = 0; i < 3; i++) {
		m_imgFile.read((char*)&byte, 1);
		number_of_columns <<= 8;
		number_of_columns |= byte;
	}
	if (number_of_columns == NB_COLS) {
		cout << ":) Number of columns is correct: " << number_of_columns << "!" << endl;
	}
	else {
		cout << ":( Number of columns (" << number_of_columns << ") is different from expected (" << NB_COLS << "). Halting..." << endl;
		return -3;
	}

	// 0016     unsigned byte ? ? pixel 
	for (unsigned int j = 0; j<number_of_items; j++) {
		array<unsigned char, 784> imgdata;

		for (unsigned int x = 0; x < NB_ROWS*NB_COLS; x++) {
			m_imgFile.read((char*)&byte, 1);
			imgdata[x] = byte;
		}

		m_images.push_back(imgdata);
	}

	// Safe return
	return 0;
}

int ImgReader::ReadLabels() {
		unsigned int magic_number;		// 0000     32 bit integer  0x00000801(2049) magic number (MSB first) 
		unsigned int number_of_items;	// 0004     32 bit integer  60000            number of items
		unsigned char byte;

		// 0000 : first four bytes (magic number)
		m_labelFile.read((char*)&byte, 1);
		magic_number = byte;
		for (int i = 0; i < 3; i++) {
			m_labelFile.read((char*)&byte, 1);
			magic_number <<= 8;
			magic_number |= byte;
		}
		cout << magic_number << endl;
		if (magic_number == MAGIC_NB_LABELS) {		// Label MAGIC_NB_LABELS
			cout << ":) Magic number correctly retrieved! (" << magic_number << ")" << endl;
		} else {
			cout << ":( Magic number could not be retrieved! halting..." << endl;
			return -1;
		}

		// 0004 : number of items
		m_labelFile.read((char*)&byte, 1);
		number_of_items = byte;
		for (int i = 0; i < 3; i++) {
			m_labelFile.read((char*)&byte, 1);
			number_of_items <<= 8;
			number_of_items |= byte;
		}
		
		cout << ":) Found " << number_of_items << " labels."<< endl;

		// 0008     unsigned byte ? ? label
		for (unsigned int j=0;j<number_of_items;j++) {
			m_labelFile.read((char*)&byte, 1);
			if ((byte >= 0) && (byte <= 9)) {
				m_labels.push_back(byte);
			}
			else {
				cout << ":( Error retrieving label number " << j+1 << ". Invalid value '"<< byte << "' found! halting..." << endl;
				return -2;
			}
		}

		// Safe return
		return 0;
}


int ImgReader::PrintImage(unsigned int t_index) {
	if ((t_index >=0) && (t_index < m_images.size() ) ) {
		// Print label supposed to match
		printf("This is a %d\n", m_labels.at(t_index));
		
		// Get image matrix
		array<unsigned char, 784> imgdata = m_images.at(t_index);
		for (unsigned int x = 0; x < NB_ROWS; x++) {
			for (unsigned int y = 0; y < NB_COLS; y++) {
				printf("%03d,", imgdata[x*28+y]);
			}
			cout << ";" << endl;
		}
		// Safe return
		return 0;
	} else {
		cout << ":( Could not retrieve element " << t_index << ". Halting..." << endl;
		return -1;
	}
}


ImgReader::~ImgReader() {
	m_imgFile.close();
	m_labelFile.close();
}
