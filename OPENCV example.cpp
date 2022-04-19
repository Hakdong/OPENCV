#include "stdafx.h"
#include "EventHandlerExample.h"
#include "CommonUtillfunc.h"

CFormViewExample fe;

CEventHandlerExample::CEventHandlerExample()
{
}


CEventHandlerExample::~CEventHandlerExample()
{
}


void CEventHandlerExample::OnInspect(_In_ Algorithms::CRavidImage* pImgInfo, _In_ int nInspectionType, _In_opt_ CRavidImageView* pView , _In_opt_ int nChannel)
{
	do
	{
		OnStartInspection(pView);
	} while (false);
}

bool CEventHandlerExample::OnStartInspection(_In_ CRavidImageView* pView)
{
	bool bReturn = false;
	float fInspTime = 0.0f;

	CRavidImage* pImgInfo = nullptr;

	do
	{
		if (!pView)
			break;

		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		CRavidImageViewLayer* pLayer1 = pView->GetLayer(1);
		CRavidImageViewLayer* pLayer2 = pView->GetLayer(2);

		if (!pLayer0 || !pLayer1 || !pLayer2)
			break;

		pLayer0->Clear();
		pLayer1->Clear();
		pLayer2->Clear();

		pImgInfo = pView->GetImageInfo();

		if (!pImgInfo)
			break;

		CPerformanceCounter	pc;
		
		CRavidImage imgInfoInspect(pImgInfo);

		//Inspction 
		//1. Single threshold
		//DoShapeFInder(imgInfoInspect);
		DoProject2(imgInfoInspect);
		//
		pImgInfo->Copy(imgInfoInspect);

		fInspTime = pc.GetElapsedTime();

		// View 2//////////////////////////////////////
		CRavidImage imgView2;
		imgView2.Copy(imgInfoInspect);

		CRavidImageView* pView2 = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 1));
		CRavidImage* pImgInfo2 = nullptr;
		pView2->Open(L"C.bmp");

		pImgInfo2 = pView2->GetImageInfo();
		pImgInfo2->Copy(imgView2);
		pView2->ZoomFit();
		////////////////////////////////////////////////

		


		pView->Invalidate(false);
		bReturn = true;



	} while (false);

	return bReturn;
}

void CEventHandlerExample::OnTeach(_In_ Algorithms::CRavidImage* pImgInfo, _In_ CTeachingObject* pTeachingObject, _In_opt_ CRavidImageView* pView, _In_opt_ int nChannel)
{
	pView->GetLayer(0)->Clear();

	CRavidRect<double> pRect1 = (CRavidRect<double>*)pTeachingObject->GetAt(0);

	m_rrMeasurement = pRect1;

	pView->GetLayer(0)->DrawShape(pRect1, GREEN, 1);

	pView->Invalidate();
}

bool CEventHandlerExample::DoDoubleThreshold(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	CMultipleVariable mvLowThreshold;
	CMultipleVariable mvHighThreshold;
	CMultipleVariable mvRangeFillValue;
	CMultipleVariable mvLesserThanLowFillValue;
	CMultipleVariable mvGreaterThanHighFillValue;

	CRavidImage::EThresholdLogicalOperator eOperator = CRavidImage::EThresholdLogicalOperator_None;

	mvLowThreshold.AddValue(150.000);
	mvHighThreshold.AddValue(200.000);
	mvRangeFillValue.AddValue(150.000);
	mvLesserThanLowFillValue.AddValue(0.000);
	mvGreaterThanHighFillValue.AddValue(255.000);

	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
	riImageView1_Threshold.DoubleThreshold(mvLowThreshold, mvHighThreshold, mvRangeFillValue, mvLesserThanLowFillValue, mvGreaterThanHighFillValue);

	imgInfo.Swap(riImageView1_Threshold);
	//imgInfo.Save(L"test.jpg");

	bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoSingleThreshold(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	CMultipleVariable mvThreshold;
	CMultipleCondition mcCondition;
	CMultipleVariable mvRangeFillValue;
	CMultipleVariable mvOutOfRangeFillValue;

	CRavidImage::EThresholdLogicalOperator eOperator = CRavidImage::EThresholdLogicalOperator_None;

	mvThreshold.AddValue(127.000);
	mcCondition.AddValue(ELogicalCondition_Greater);
	mvRangeFillValue.AddValue(255.000);
	mvOutOfRangeFillValue.AddValue(0.000);

	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
		riImageView1_Threshold.SingleThreshold(mvThreshold, mcCondition, mvRangeFillValue, mvOutOfRangeFillValue, nullptr, eOperator);

		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoOtsuThreshold(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	riImageView1_Threshold.Copy(imgInfoInspct);

	CRavidGeometry* pSrcRG = nullptr;

	CRavidRect<int> rrRegion;
	rrRegion = CRavidRect<int>(riImageView1_Threshold);
	pSrcRG = &rrRegion;

	CMultipleCondition mcCondition;
	CMultipleVariable mvRangeFillValue;
	CMultipleVariable mvOutOfRangeFillValue;

	mcCondition.AddValue(ELogicalCondition_Greater);
	mvRangeFillValue.AddValue(255.000);
	mvOutOfRangeFillValue.AddValue(0.000);

	CMultipleVariable mvThreshold;
	mvThreshold = riImageView1_Threshold.GetOtsuThreshold(pSrcRG);

	double dTemp;
	dTemp = mvThreshold.GetAt(0);

	do
	{
		riImageView1_Threshold.OtsuThreshold(mcCondition, mvRangeFillValue, mvOutOfRangeFillValue, &mvThreshold);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoAdaptiveThreshold(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	riImageView1_Threshold.Copy(imgInfoInspct);

	CRavidImage::EAdaptiveThresholdType eType = CRavidImage::EAdaptiveThresholdType_Binary;
	CRavidImage::EAdaptiveThresholdMethod eMethod = CRavidImage::EAdaptiveThresholdMethod_Mean;
	CMultipleVariable rmvMaxValue_1 = 255;
	int nBlockSize = 3;
	CMultipleVariable rmvConstant_1 = 10.000;

	do
	{
		riImageView1_Threshold.AdaptiveThreshold(eType, eMethod, rmvMaxValue_1, nBlockSize, rmvConstant_1);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoISOThreshold(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	riImageView1_Threshold.Copy(imgInfoInspct);

	CMultipleCondition mcCondition;
	CMultipleVariable mvRangeFillValue;
	CMultipleVariable mvOutOfRangeFillValue;

	mcCondition.AddValue(ELogicalCondition_Greater);
	mvRangeFillValue.AddValue(255.000);
	mvOutOfRangeFillValue.AddValue(0.000);

	CMultipleVariable mvThreshold;


	do
	{
		riImageView1_Threshold.IsodataThreshold(mcCondition, mvRangeFillValue, mvOutOfRangeFillValue, &mvThreshold);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
void CEventHandlerExample::UpdateResult(std::vector<CMultipleVariable> vctResults)
{
	do
	{
		CRavidGraphView* pRgvHisto = dynamic_cast<CRavidGraphView*>(CUIManager::FindView(typeid(CRavidGraphView), 3));

		if (!pRgvHisto)
			break;

		// draw histogram graph
		pRgvHisto->ClearPlotInfo();
		pRgvHisto->SetXAxisUnit(_T("X (Value)"));
		pRgvHisto->SetYAxisUnit(_T("Y (Index)"));

		std::vector<CRavidPoint<double>> vctData;
		//
		int nCnt = 0;
		double dPlot = 0;
		for (auto& rp : vctResults)
		{
			dPlot = rp.GetAt(1);
			vctData.push_back(CRavidPoint<double>((double)nCnt, dPlot));
			nCnt++;
		}
		DrawGraph(pRgvHisto, vctData, dPlot);

	} while (false);
}
void CEventHandlerExample::DrawGraph(CRavidGraphView* pGraph, const std::vector<CRavidPoint<double>>& vctData, double dblStd)
{
	do
	{
		if (!pGraph)
			break;

		pGraph->ClearPlotInfo();

		if (vctData.empty())
			break;

		CRavidGraphViewPlotInfomation rgvDataStd;
		rgvDataStd.SetPlotType(ERavidGraphViewPlotType_Line);
		rgvDataStd.SetLineColor(LIGHTRED);
		rgvDataStd.SetLineWidth(1);

		bool bCheckNGPrev = vctData[0].y > dblStd || vctData[0].y == 0 ;

		CRavidGraphViewPlotInfomation rgvData;
		rgvData.SetPlotType(ERavidGraphViewPlotType_DotWithLine);
		rgvData.SetLineWidth(1);

		if (!bCheckNGPrev)
		{
			rgvData.SetLineColor(LIME);
			rgvData.SetDotColor(LIME);
		}
		else
		{
			rgvData.SetLineColor(LIGHTRED);
			rgvData.SetDotColor(LIGHTRED);
		}

		try
		{
			for (auto& rp : vctData)
			{
				bool bCheckNG = (rp.y > dblStd || rp.y == 0); // check NG status
				if (bCheckNGPrev != bCheckNG)
				{
					pGraph->AddPlotInfo(&rgvData); // add previous plot info

					rgvData.ClearPlot(); // new plot info
					rgvData.SetPlotType(ERavidGraphViewPlotType_DotWithLine);

					rgvData.SetLineWidth(1);

					if (bCheckNG) // current is NG
					{
						rgvData.SetLineColor(LIGHTRED);
						rgvData.SetDotColor(LIGHTRED);
					}
					else
					{
						rgvData.SetLineColor(LIME);
						rgvData.SetDotColor(LIME);
					}

					bCheckNGPrev = bCheckNG;
				}

				rgvData.AddPlot(rp.x, rp.y);
				rgvDataStd.AddPlot(rp.x, dblStd);
			}

			pGraph->AddPlotInfo(&rgvData);
			pGraph->AddPlotInfo(&rgvDataStd);

			pGraph->DrawGraph();
		}
		catch (const std::exception&)
		{
			pGraph->ClearPlotInfo();
		}
	} while (false);
}
bool CEventHandlerExample::DoHistogram(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;
	std::vector<CMultipleVariable> vctResults;
	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
		riImageView1_Threshold.Histogram(&vctResults, nullptr, nullptr);
		imgInfo.Swap(riImageView1_Threshold);
		UpdateResult(vctResults);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoNormalize(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;
	std::vector<CMultipleVariable> vctResults;
	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
		riImageView1_Threshold.Normalize();
		riImageView1_Threshold.Histogram(&vctResults, nullptr, nullptr);
		imgInfo.Swap(riImageView1_Threshold);
		UpdateResult(vctResults);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoConversion(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;
	std::vector<CMultipleVariable> vctResults;
	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
		//riImageView1_Threshold.ConvertRGBToYComponent();
		riImageView1_Threshold.ConvertRGBToGray();
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoDepth(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;
	std::vector<CMultipleVariable> vctResults;
	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
		riImageView1_Threshold.ConvertDepth(CRavidImage::EConvertDepth_ToU10, CRavidImage::EConvertDepthValueMode_KeepValue);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoConvolution(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;
	std::vector<CMultipleVariable> vctResults;
	riImageView1_Threshold.Copy(imgInfoInspct);

	do
	{
		//riImageView1_Threshold.Convolution(CRavidImage::EConvolutionPreset_SobelX, nullptr);
		riImageView1_Threshold.Convolution(CRavidImage::EConvolutionPreset_Sobel, nullptr);
		//riImageView1_Threshold.Convolution(CRavidImage::EConvolutionPreset_Gaussian3x3, nullptr);
		//riImageView1_Threshold.Convolution(CRavidImage::EConvolutionPreset_Gaussian5x5, nullptr);
		//riImageView1_Threshold.Convolution(CRavidImage::EConvolutionPreset_Gaussian7x7, nullptr);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;
	

}
bool CEventHandlerExample::DoComponent(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	//CRavidImage riImageView1_Threshold;
	CRavidImage image;

	image.Copy(imgInfoInspct);


	CMultipleVariable rmvThreshold;
	rmvThreshold.AddValue(128.000);

	CConnectedComponent cc;

	cc.SetSingleThreshold(rmvThreshold);
	cc.SetLogicalCondition(ELogicalCondition_Less);
	cc.SetMultipleChannelCondition(CConnectedComponent::EMultipleChannelCondition_1);

	cc.Encode(&image, nullptr);
	double dblFilterValue0 = 4000.000;


	do
	{
		cc.Filter(CConnectedComponent::EFilterItem_Area, dblFilterValue0, ELogicalCondition_Greater);
		DoDrawforCC(cc, 1);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoDrawforCC(_In_ CConnectedComponent& cc, _In_ int nView)
{
	bool bReturn = false;
	std::vector<size_t> vctArea;
	std::vector<CRavidRect<int>> vctRects;
	std::vector<CRavidPoint<int>> vctPts;

	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), nView));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		CRavidImageViewLayer* pLayer1 = pView->GetLayer(1);
		CRavidImageViewLayer* pLayer2 = pView->GetLayer(2);
		CRavidImageViewLayer* pLayer3 = pView->GetLayer(3);
		CRavidImageViewLayer* pLayer4 = pView->GetLayer(4);


		if (!pLayer0 || !pLayer1 || !pLayer2 || !pLayer3 || !pLayer4)
			break;

		//pLayer0->Clear(); pLayer1->Clear(); pLayer2->Clear(); pLayer3->Clear(); pLayer4->Clear();
		pLayer0->Show(true); pLayer1->Show(true); pLayer2->Show(true); pLayer3->Show(true); pLayer4->Show(true);

		vctRects = cc.GetBoundary();
		//pLayer0 : Area
		vctArea = cc.GetArea();
		CString	strValue;
		/*
		int i = 0;
		for (auto& m : vctArea)
		{
			strValue.Format(_T("Area:%d"), (int)m);
			pLayer0->DrawTextW(CRavidPoint<int>(vctRects.at(i).left, vctRects.at(i).bottom + 5), strValue, BLACK, BLACK, 20);
			i++;
		}
		*/
		//pLayer1 : Boundary
	//	vctRects = cc.GetBoundary();
		//CString	strValue;
		for (auto& r : vctRects)
		{
			pLayer1->DrawShape(r, LIGHTRED, 2);
			strValue.Format(_T("%d , %d (%d X %d)"), (int)r.GetCenter().x, (int)r.GetCenter().y, (int)r.GetWidth(), (int)r.GetHeight());
			pLayer1->DrawTextW(CRavidPoint<int>(r.left, r.top - 10), strValue, LIGHTRED, BLACK, 20);

			pLayer1->DrawShape(CRavidPoint<int>((int)r.GetCenter().x, (int)r.GetCenter().y), LIGHTRED, 2);

		}

		//pLayer2 : Convex hull
		//pLayer3 : Contour
		/*
		CRavidGeometryArray rga;

		cc.GetContour(&rga);
		pLayer3->DrawShape(rga, AQUA, 2);// , AQUA);

		//pLayer4 : Feret
		//pLayer5 : Gravity point
		*/


		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoExtration(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	riImageView1_Threshold.Copy(imgInfoInspct);

	CMultipleVariable mvFill;
	mvFill.AddValue(0.000);

	do
	{
		riImageView1_Threshold.ExtractChannelComponent(0, nullptr, mvFill);

		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;

}
bool CEventHandlerExample::DoMask(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;
	std::vector<CMultipleVariable> vctResults;
	riImageView1_Threshold.Copy(imgInfoInspct);

	CRavidCircle<double> rcImageView0_Floppy_ROI0;
	rcImageView0_Floppy_ROI0.rpCenter.x = 220.2354651;
	rcImageView0_Floppy_ROI0.rpCenter.y = 215.3924419;
	rcImageView0_Floppy_ROI0.radius = 72.9215116;
	rcImageView0_Floppy_ROI0.startDeg = 0.0000000;
	rcImageView0_Floppy_ROI0.deltaDeg = 360.0000000;

	CMultipleVariable mvFill;
	mvFill.AddValue(0.000);

	CRavidImage riTemp;

	riTemp.Copy(riImageView1_Threshold);

	CMultipleVariable rmvThreshold;
	rmvThreshold.AddValue(70.000);

	CConnectedComponent cc;

	cc.SetSingleThreshold(rmvThreshold);
	cc.SetLogicalCondition(ELogicalCondition_Greater);
	cc.SetMultipleChannelCondition(CConnectedComponent::EMultipleChannelCondition_1);

	cc.Encode(&riTemp, nullptr);

	double dblFilterValue0 = 15.000;
	cc.Filter(CConnectedComponent::EFilterItem_BoundingBoxWidth, dblFilterValue0, ELogicalCondition_Less);

	double dblFilterValue1 = 300.000;
	cc.Filter(CConnectedComponent::EFilterItem_BoundingBoxWidth, dblFilterValue1, ELogicalCondition_Greater);





	do
	{
		riTemp.Mask(mvFill, &rcImageView0_Floppy_ROI0);
	
		
		DoDrawforCC(cc, 1);
		imgInfo.Swap(riTemp);
		//imgInfo.Save(L"test.jpg");
		bReturn = true;

	} while (false);

	return bReturn;

}
bool CEventHandlerExample::DoMorphology(_In_ CRavidImage& imgInfo) 
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	CMultipleVariable mvThreshold;
	CMultipleCondition mcCondition;
	CMultipleVariable mvRangeFillValue;
	CMultipleVariable mvOutOfRangeFillValue;

	CRavidImage::EThresholdLogicalOperator eOperator = CRavidImage::EThresholdLogicalOperator_None;

	mvThreshold.AddValue(70.000);
	mcCondition.AddValue(ELogicalCondition_Greater);
	mvRangeFillValue.AddValue(255.000);
	mvOutOfRangeFillValue.AddValue(0.000);

	riImageView1_Threshold.Copy(imgInfoInspct);

	CRavidImage::EMorphologyMethod eMethod = CRavidImage::EMorphologyMethod_Erode;
	//CRavidImage::EMorphologyMethod eMethod = CRavidImage::EMorphologyMethod_Dilate;
	//CRavidImage::EMorphologyMethod eMethod = CRavidImage::EMorphologyMethod_Open;
	//CRavidImage::EMorphologyMethod eMethod = CRavidImage::EMorphologyMethod_Close;

	int nHalfWidth = 1;
	int nHalfHeight = 1;


	do
	{
		riImageView1_Threshold.SingleThreshold(mvThreshold, mcCondition, mvRangeFillValue, mvOutOfRangeFillValue, nullptr, eOperator);
		riImageView1_Threshold.Morphology(nHalfWidth, nHalfHeight, eMethod);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoMorphology2(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView1_Threshold;

	CMultipleVariable mvThreshold;
	CMultipleCondition mcCondition;
	CMultipleVariable mvRangeFillValue;
	CMultipleVariable mvOutOfRangeFillValue;

	CRavidImage::EThresholdLogicalOperator eOperator = CRavidImage::EThresholdLogicalOperator_None;

	mvThreshold.AddValue(40.000);
	mcCondition.AddValue(ELogicalCondition_Greater);
	mvRangeFillValue.AddValue(255.000);
	mvOutOfRangeFillValue.AddValue(0.000);

	riImageView1_Threshold.Copy(imgInfoInspct);

	CRavidImage::EMorphologyMethod eMethod = CRavidImage::EMorphologyMethod_WhiteTopHat;

	int nHalfWidth = 7;
	int nHalfHeight = 7;


	do
	{
		riImageView1_Threshold.Morphology(nHalfWidth, nHalfHeight, eMethod);
		riImageView1_Threshold.SingleThreshold(mvThreshold, mcCondition, mvRangeFillValue, mvOutOfRangeFillValue, nullptr, eOperator);
		imgInfo.Swap(riImageView1_Threshold);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoOperation(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);


	CRavidImage riImageView2_Operation;

	CImageOperationInfo::EDataType eDataType = CImageOperationInfo::EDataType_Const;
	CImageOperationInfo::EOperationType eOperationType = CImageOperationInfo::EOperationType_Add;
	CMultipleVariable mvConst;
	mvConst.AddValue(50.000);

	CImageOperationInfo ioi;
	ioi.SetImageOperationInfo(eOperationType, eDataType, &riImageView0_Floppy, &mvConst);


	CRavidImage riTemp(riImageView0_Floppy);

	do
	{
		riTemp.Operation(&ioi, nullptr, nullptr);

		riTemp.Paste(&riImageView0_Floppy, nullptr, nullptr);
		imgInfo.Swap(riTemp);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoOperation2(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	CRavidImage riImageView1_Floppy_cen;

	CRavidImageView* pView2 = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 1));
	CRavidImage* pImgInfo2 = nullptr;

	pImgInfo2 = pView2->GetImageInfo();
	riImageView1_Floppy_cen.Copy(pImgInfo2);
	CRavidImage riImageView2_Operation;


	CImageOperationInfo::EDataType eDataType = CImageOperationInfo::EDataType_Image;
	CImageOperationInfo::EOperationType eOperationType = CImageOperationInfo::EOperationType_Subtract;

	CImageOperationInfo ioi;
	ioi.SetImageOperationInfo(eOperationType, eDataType, &riImageView1_Floppy_cen, nullptr);


	CRavidImage riTemp(riImageView0_Floppy);

	do
	{
		riTemp.Operation(&ioi, nullptr, nullptr);

		riTemp.Paste(&riImageView0_Floppy, nullptr, nullptr);
		imgInfo.Swap(riTemp);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoPaste(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImageView* pView2 = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 1));
	CRavidImage* pImgInfo2 = nullptr;
	//pView2->Open(L"c.bmp");

	pImgInfo2 = pView2->GetImageInfo();
	CRavidImage imgPaste(pImgInfo2);

	CRavidImage imgInfoInspect(imgInfo);
	CRavidImage riImageView1_Ori;

	CRavidRect<int> rrImageView0_original_ROI0;
	rrImageView0_original_ROI0.left = 215;
	rrImageView0_original_ROI0.top = 216;
	rrImageView0_original_ROI0.right = 292;
	rrImageView0_original_ROI0.bottom = 293;
	rrImageView0_original_ROI0.angle = 0.0000000;

	CRavidRect<int> rrImageView1_ROI0_copy;
	rrImageView1_ROI0_copy = rrImageView0_original_ROI0;

	riImageView1_Ori.Copy(imgInfoInspect);

	do
	{
		riImageView1_Ori.Paste(imgPaste, &rrImageView0_original_ROI0, &rrImageView1_ROI0_copy);
		imgInfo.Swap(imgPaste);
		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoPointGuage(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	CRavidLine<double> m_rrMeasureline;
	m_rrMeasureline.rpPoints[0].y -= 160;
	m_rrMeasureline.rpPoints[1].y -= 160;

	CPointGauge pg;
	pg.SetTransitionType(CPointGauge::ETransitionType_BW);
	pg.SetTransitionChoice(CPointGauge::ETransitionChoice_All);
	pg.SetThreshold(20);
	pg.SetMinimumAmplitude(10);
	pg.SetThickness(1);
	pg.SetMeasurementRegion(m_rrMeasureline);




	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);

		pg.Measure(&riImageView0_Floppy);

		std::vector<CRavidPoint<double>> vctMeasuredPoints;

		pg.GetMeasuredPoints(vctMeasuredPoints);


		pLayer0->DrawShape(CRavidLine<double>(m_rrMeasureline.rpPoints[0], m_rrMeasureline.rpPoints[1]), LIGHTRED, 2);
		double xInfo = 0;
		int incorrect=0;

		for (auto& r : vctMeasuredPoints)
		{
			pLayer0->DrawShape(r, LIGHTGREEN, 5);

			if (r.x > 50)
			{
				if (r.x - xInfo > 60 || r.x - xInfo < 50)
				{
					pLayer0->DrawShape(r, LIGHTRED, 5);
					incorrect = 1;
				}
			}
				
			xInfo = r.x;
		}
		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");
		if (incorrect == 0)
		{
			CString strValue;
			strValue.Format(_T("OK"));
			pLayer0->DrawTextW(CRavidPoint<int>(0, 0), strValue, GREEN, BLACK, 20);
		}
		else
		{
			CString strValue;
			strValue.Format(_T("NG"));
			pLayer0->DrawTextW(CRavidPoint<int>(0, 0), strValue, RED, BLACK, 20);

		}

		m_rrMeasureline.rpPoints[0].y += 160;
		m_rrMeasureline.rpPoints[1].y += 160;
		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoLineGuage(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	CRavidLine<double> rlMeasurement;
	rlMeasurement.rpPoints[0].x = -32.3956159;
	rlMeasurement.rpPoints[0].y = 228.2902201;
	rlMeasurement.rpPoints[1].x = 855.6043841;
	rlMeasurement.rpPoints[1].y = 228.2902201;

	double dblTolerance = 78.709;

	CLineGauge lg;
	lg.SetTransitionType(CLineGauge::ETransitionType_BWorWB);
	lg.SetTransitionChoice(CLineGauge::ETransitionChoice_LargestAmplitude);
	lg.SetThreshold(20);
	lg.SetMinimumAmplitude(10);
	lg.SetThickness(1);
	lg.SetSamplingStep(5.000);
	lg.SetOutLiersThreshold(1.000);
	lg.SetNumOfPass(10);
	lg.SetMeasurementRegion(rlMeasurement, dblTolerance);

	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);

		lg.Measure(&riImageView0_Floppy);

		CRavidLine<double> rlMeasuredObject;
		std::vector<CRavidPoint<double> > vctMeasuredValidPoints;
		std::vector<CRavidPoint<double> > vctMeasuredInvalidPoints;

		lg.GetMeasuredObject(rlMeasuredObject);
		lg.GetMeasuredValidPoints(vctMeasuredValidPoints);
		lg.GetMeasuredInvalidPoints(vctMeasuredInvalidPoints);

		imgInfo.Swap(riImageView0_Floppy);

		pLayer0->DrawShape(CRavidLine<double>(rlMeasuredObject.rpPoints[0], rlMeasuredObject.rpPoints[1]), LIGHTRED, 2);
		for (auto& r : vctMeasuredValidPoints)
		{
			pLayer0->DrawShape(r, LIGHTGREEN, 1);
		}
		for (auto& r : vctMeasuredInvalidPoints)
		{
			pLayer0->DrawShape(r, LIGHTRED, 1);
		}
		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoRectGuage(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);
	riImageView0_Floppy.ConvertRGBToGray();

	CRavidRect<double> rrMeasurement;
	rrMeasurement.left = 276.0199667;
	rrMeasurement.top = 168.9875208;
	rrMeasurement.right = 756.4991681;
	rrMeasurement.bottom = 667.3569052;
	rrMeasurement.angle = 0.0000000;

	double dblTolerance = 42.979;

	CRectangleGauge rg;
	rg.SetTransitionType(CRectangleGauge::ETransitionType_BWorWB);
	rg.SetTransitionChoice(CRectangleGauge::ETransitionChoice_LargestAmplitude);
	rg.SetThreshold(20);
	rg.SetMinimumAmplitude(10);
	rg.SetThickness(1);
	rg.SetSamplingStep(5.000);
	rg.SetOutLiersThreshold(1.000);
	rg.SetNumOfPass(1);
	rg.SetMeasurementRegion(rrMeasurement, dblTolerance);



	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		

		pLayer0->Clear();
		pLayer0->Show(true);

		rg.Measure(&riImageView0_Floppy);

		CRavidRect<double> rqMeasuredObject;
		std::vector<CRavidPoint<double> > vctMeasuredValidPoints;
		std::vector<CRavidPoint<double> > vctMeasuredInvalidPoints;

		rg.GetMeasuredObject(rqMeasuredObject);
		rg.GetMeasuredValidPoints(vctMeasuredValidPoints);
		rg.GetMeasuredInvalidPoints(vctMeasuredInvalidPoints);


		pLayer0->DrawShape(rqMeasuredObject, LIGHTRED, 2);
		for (auto& r : vctMeasuredValidPoints)
		{
			pLayer0->DrawShape(r, LIGHTGREEN, 1);
		}
		for (auto& r : vctMeasuredInvalidPoints)
		{
			pLayer0->DrawShape(r, LIGHTRED, 1);
		}
		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoQudraGuage(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);
	riImageView0_Floppy.ConvertRGBToGray();

	CRavidQuadrangle<double> rqMeasurement;
	rqMeasurement.rpPoints[0].x = 167.4009983;
	rqMeasurement.rpPoints[0].y = 62.7753744;
	rqMeasurement.rpPoints[1].x = 581.4309484;
	rqMeasurement.rpPoints[1].y = 67.8868552;
	rqMeasurement.rpPoints[2].x = 573.1247920;
	rqMeasurement.rpPoints[2].y = 506.1963394;
	rqMeasurement.rpPoints[3].x = 99.0349418;
	rqMeasurement.rpPoints[3].y = 472.9717138;

	double dblTolerance = 32.234;

	CQuadrangleGauge rg;
	rg.SetTransitionType(CQuadrangleGauge::ETransitionType_BWorWB);
	rg.SetTransitionChoice(CQuadrangleGauge::ETransitionChoice_LargestAmplitude);
	rg.SetThreshold(20);
	rg.SetMinimumAmplitude(10);
	rg.SetThickness(1);
	rg.SetSamplingStep(5.000);
	rg.SetOutLiersThreshold(1.000);
	rg.SetNumOfPass(1);
	rg.SetMeasurementRegion(rqMeasurement, dblTolerance);

	rg.Measure(&riImageView0_Floppy);



	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;



		pLayer0->Clear();
		pLayer0->Show(true);

		rg.Measure(&riImageView0_Floppy);

		CRavidQuadrangle<double> rqMeasuredObject;
		std::vector<CRavidPoint<double> > vctMeasuredValidPoints;
		std::vector<CRavidPoint<double> > vctMeasuredInvalidPoints;

		rg.GetMeasuredObject(rqMeasuredObject);
		rg.GetMeasuredValidPoints(vctMeasuredValidPoints);
		rg.GetMeasuredInvalidPoints(vctMeasuredInvalidPoints);


		pLayer0->DrawShape(rqMeasuredObject, LIGHTRED, 2);
		for (auto& r : vctMeasuredValidPoints)
		{
			pLayer0->DrawShape(r, LIGHTGREEN, 1);
		}
		for (auto& r : vctMeasuredInvalidPoints)
		{
			pLayer0->DrawShape(r, LIGHTRED, 1);
		}
		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}

bool CEventHandlerExample::DoCanny(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	CRavidImage::ECannyEdgeDetectorThresholdType eType = CRavidImage::ECannyEdgeDetectorThresholdType_Absolute;
	int nGaussianBlurSize = 0;
	float fLowThreshold = 70.000;
	float fHighThreshold = 150.000;

	


	do
	{
		riImageView0_Floppy.CannyEdgeDetector(fLowThreshold, fHighThreshold, eType, nGaussianBlurSize);
		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");

		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoHarryCorner(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	CRavidImage::EHarrisCornerDetectorThresholdType eType = CRavidImage::EHarrisCornerDetectorThresholdType_Absolute;
	float fThreshold = 20.00000;
	float fCornerCoefficient = 0.04000;

	CRavidGeometryArray rgaResults;


	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);

		riImageView0_Floppy.HarrisCornerDetector(eType, fThreshold, &rgaResults, fCornerCoefficient, nullptr);

		imgInfo.Swap(riImageView0_Floppy);
		//imgInfo.Save(L"test.jpg");
		pLayer0->DrawShape(rgaResults, LIGHTGREEN, 5);
		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoHoughLine(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	CHoughTransformLine htl;
	std::vector<CRavidLine<int>> vctLines;

	htl.SetThreshold(12);
	htl.SetMaxLineCount(5);
	htl.SetRegionRange(1);



	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);


		htl.Transform(&riImageView0_Floppy, vctLines, nullptr);
		imgInfo.Swap(riImageView0_Floppy);
		for (auto& r : vctLines)
		{
			pLayer0->DrawShape(r, LIGHTRED, 2);
		}
		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoHoughCircle(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);

	riImageView0_Floppy.Stretch();


	CRavidImage::ECannyEdgeDetectorThresholdType eType = CRavidImage::ECannyEdgeDetectorThresholdType_Absolute;
	int nGaussianBlurSize = 1;
	float fLowThreshold = 14.000;
	float fHighThreshold = 100.000;

	riImageView0_Floppy.CannyEdgeDetector(fLowThreshold, fHighThreshold, eType, nGaussianBlurSize);


	CHoughTransformCircle htc;

	std::vector<CRavidCircle<int>> vctCircles;

	htc.SetThreshold(50);
	htc.SetMaxCircleCount(22);
	htc.SetRegionRange(2);
	htc.SetRadius(25, 60);

	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);


		htc.Transform(&riImageView0_Floppy, vctCircles, nullptr);
		imgInfo.Swap(riImageView0_Floppy);
		for (auto& r : vctCircles)
		{
			pLayer0->DrawShape(r, LIGHTRED, 2);
		}
		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoFInder(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);


	riImageView0_Floppy.ConvertRGBToYComponent();

	CObjectFinder of;
	of.SetMaxInstance(8);
	of.SetMinimalDetectingScore(0.800);
	of.SetAngleBias(0.000);
	of.SetAngleTolerance(0.000);
	of.SetScaleBias(1.000);
	of.SetScaleTolerance(0.000);
	of.SetInterpolation(true);
	
	of.Load(_T("123.rof"));

	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);


		of.Find(&riImageView0_Floppy, nullptr);

		imgInfo.Swap(riImageView0_Floppy);

		std::vector<CObjectFinder::SObjectFinderResult>	 vctResults;

		of.GetResults(vctResults);
		int nIndex = 0;
		CString strValue;
		for (auto& r : vctResults)
		{
			strValue.Format(_T("[ %d ] \n %.2f"), nIndex, r.fScore);
			pLayer0->DrawTextW(CRavidPoint<int>(r.rrResultRegion.left - 30, r.rrResultRegion.top - 10), strValue, LIMEGREEN, 10);
			pLayer0->DrawShape(r.rrResultRegion, LIMEGREEN, 3);
			nIndex++;
		}


		bReturn = true;
	} while (false);

	return bReturn;
}
bool CEventHandlerExample::DoShapeFInder(_In_ CRavidImage& imgInfo)
{
	bool bReturn = false;

	CRavidImage imgInfoInspct(imgInfo);
	CRavidImage riImageView0_Floppy;
	riImageView0_Floppy.Copy(imgInfoInspct);


	riImageView0_Floppy.ConvertRGBToYComponent();


	std::vector<CShapeFinder::SShapeFinderResult> vctResults;
	CShapeFinder sf;
	sf.SetInstanceNumber(1);
	sf.SetMinScore(0.800);
	sf.SetAngleStart(-0.000);
	sf.SetAngleEnd(90.000);
	sf.SetScaleMin(0.800);
	sf.SetScaleMax(1.200);
	sf.SetExtendedArea(0.500);
	sf.SetContrast(false);
	sf.SetMaxLevel(12);
	sf.SetMinFeaturePoints(16);
	sf.SetMaxFeaturePoints(1024);
	sf.SetStrengthModeAuto(true);
	sf.SetStrength(1.000);


	sf.Load(_T("456.rsf"));

	do
	{
		CRavidImageView* pView = dynamic_cast<CRavidImageView*>(CUIManager::FindView(typeid(CRavidImageView), 0));
		CRavidImageViewLayer* pLayer0 = pView->GetLayer(0);
		if (!pLayer0)
			break;

		pLayer0->Clear();
		pLayer0->Show(true);


		sf.Find(&riImageView0_Floppy, vctResults, nullptr);

		imgInfo.Swap(riImageView0_Floppy);

		int nIndex = 0;
		CString strValue;
		for (auto& r : vctResults)
		{
			strValue.Format(_T("[ %d ] \n %.2f"), nIndex, r.fScore);
			pLayer0->DrawTextW(CRavidPoint<int>(r.rrRegion.left - 30, r.rrRegion.top - 10), strValue, LIMEGREEN, 10);
			pLayer0->DrawShape(r.rrRegion, LIMEGREEN, 3);
			nIndex++;
		}


		bReturn = true;
	} while (false);

	return bReturn;
}

