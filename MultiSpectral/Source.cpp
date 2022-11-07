#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <ostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <ranges>
#include <list>
#include <array>
#include <tuple>
#include <set>
#include "imstack.h"

void main()
{
	float scalef = 1;
	PixelarrayV UobjpixelsVColec;
	//read all folders to process 
	const std::filesystem::path localdir{ "C:/Users/DR ALFONSO GASTELUM/Pictures/tepalcates/" };
	std::vector<std::string> dirlist;
	for (auto& p : std::filesystem::directory_iterator(localdir))
		if (p.is_directory())
			dirlist.push_back(p.path().string());
	for (auto dir : dirlist)
	{
		imstack ImgI;
		std::string colordir = dir;
		std::string multidir = dir + "/ms/";
		std::string multidirout = multidir + "out/";
		std::filesystem::create_directory(multidirout);

		std::string labeldir = multidirout + "label/";
		std::filesystem::create_directory(labeldir);

		ImgI.colorread(colordir, scalef);
		ImgI.getfiles(multidir);
		ImgI.createmask(45, 50, scalef, 0.124f, 21, 21);
		//ImgI.createmask(45, 50, scalef,0.144f); 
		//
		ImgI.readstackv(scalef);
		ImgI.UobjpixelsV.val_v = UobjpixelsVColec.val_v;
		for (int idx = 1; idx < ImgI.statslabel.left.size(); idx++)
		{
			Rectangle tempr;
			tempr.left = ImgI.statslabel.left[idx];
			tempr.top = ImgI.statslabel.top[idx];
			tempr.width = ImgI.statslabel.width[idx];
			tempr.height = ImgI.statslabel.height[idx];
			ImgI.objpixelsv(tempr, idx, 0.05, multidirout); //here you can put different thresholds, lower values more unique pixels, try with .1, 0.05, 0.01, etc
			//ImgI.labelimag vector contains mat files with the label objects;
			//ImgI.UobjpixelsV list of pixels with unique values in v;
			std::string filename;
			filename = labeldir + std::to_string(idx) + ".tif";
			cv::imwrite(filename, ImgI.labelimag[idx - 1]);
		}
		UobjpixelsVColec.val_v.insert(UobjpixelsVColec.val_v.end(), ImgI.UobjpixelsV.val_v.begin(), ImgI.UobjpixelsV.val_v.end());
	}
	std::string filename;
	filename = localdir.string() + "uvalues.csv";
	std::ofstream outFile(filename);
	// the important part
	for (const auto& array : UobjpixelsVColec.val_v)
	{
		for (const auto& value : array)
		{
			outFile << value << ",";
		}
		outFile << std::endl;
	}
	outFile.close();

	int a = 0;
}