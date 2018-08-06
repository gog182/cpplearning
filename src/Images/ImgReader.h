#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <array>

class ImgReader
{
	public:
		ImgReader();
		ImgReader(std::string t_labelsPath, std::string t_imagesPath);
		~ImgReader();

		int ReadLabels();
		int PrintImage(unsigned int t_index);
		int ReadImages();

	private:
		const unsigned int MAGIC_NB_LABELS = 2049;
		const unsigned int MAGIC_NB_IMAGES = 2051;

		const unsigned int NB_ROWS = 28;
		const unsigned int NB_COLS = 28;

		std::ifstream m_labelFile;
		std::ifstream m_imgFile;

		std::vector<unsigned char> m_labels;
		std::vector<std::array<unsigned char, 784> > m_images;
};

