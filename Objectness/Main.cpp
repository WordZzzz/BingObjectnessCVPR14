/************************************************************************/
/* This source code is free for both academic and industry use.         */
/* Some important information for better using the source code could be */
/* found in the project page: http://mmcheng.net/bing					*/
/************************************************************************/

#include "stdafx.h"
#include "Objectness.h"
#include "ValStructVec.h"
#include "CmShow.h"

// Uncomment line line 14 in Objectness.cpp to remove counting times of image reading.

void RunObjectness(CStr &resName, double base, int W, int NSS, int numPerSz);

int main(int argc, char* argv[])
{
	//DataSetVOC::importImageNetBenchMark();
	//DataSetVOC::cvt2OpenCVYml("D:/WkDir/DetectionProposals/VOC2007/Annotations/");
	RunObjectness("WinRecall.m", 2, 8, 2, 130);
	return 0;
}

void RunObjectness(CStr &resName, double base, int W, int NSS, int numPerSz)
{
	srand((unsigned int)time(NULL));
	DataSetVOC voc2007("E:/BingObjectnessCVPR14/VOC2007/");
	voc2007.loadAnnotations();
	//voc2007.loadDataGenericOverCls();

	printf("Dataset:`%s' with %d training and %d testing\n", _S(voc2007.wkDir), voc2007.trainNum, voc2007.testNum);
	printf("%s Base = %g, W = %d, NSS = %d, perSz = %d\n", _S(resName), base, W, NSS, numPerSz);
	
	Objectness objNess(voc2007, base, W, NSS);

	Mat img;
	CStr imgPath = "E:/BingObjectnessCVPR14/VOC2007/img.jpg";
	img = imread(imgPath, CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);//读取单张照片，记得改路径
	//vector<vector<Vec4i>> boxesTests;
	ValStructVec<float, Vec4i> finalBoxes;
	//objNess.getObjBndBoxesForTests(boxesTests, 250);
	//objNess.getObjBndBoxesForTestsFast(boxesTests, numPerSz);
	objNess.getObjBndBoxesForSingleImage(img, finalBoxes, numPerSz);//获得单张照片的检测结果
	//objNess.getRandomBoxes(boxesTests);
	//objNess.evaluatePerClassRecall(boxesTests, resName, 1000);
	//objNess.illuTestReults(boxesTests);
	objNess.myilluTestReults(imgPath, finalBoxes);//输出加上检测框的检测结果，默认一张图一个框
}

