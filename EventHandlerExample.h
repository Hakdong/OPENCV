#pragma once
#include "FormViewExample.h"
using namespace Ravid;
using namespace Ravid::Framework;

class CEventHandlerExample : public Ravid::Framework::CEventHandlerBase
{
public:
	CEventHandlerExample();
	virtual ~CEventHandlerExample();

	virtual void OnInspect(_In_ Algorithms::CRavidImage* pImgInfo, _In_ int nInspectionType, _In_opt_ CRavidImageView* pView = nullptr, _In_opt_ int nChannel = -1);
	virtual void OnTeach(_In_ Algorithms::CRavidImage* pImgInfo, _In_ CTeachingObject* pTeachingObject, _In_opt_ CRavidImageView* pView = nullptr, _In_opt_ int nChannel = -1);
	virtual void OnAcquisition(_In_ Ravid::Algorithms::CRavidImage* pImgInfo, _In_ int nChannel, _In_opt_ Ravid::Framework::CRavidImageView* pView = nullptr, _In_opt_ Ravid::Device::CDeviceBase* pDevice = nullptr) { }
	virtual void OnReceivingPacket(_In_ CPacket* pPacket, _In_ Device::CDeviceBase* pDevice) { }
	virtual void OnLogMessage(_In_ SRavidLogData* pLogData) { }

	virtual void OnSequenceStart() { }
	virtual void OnSequencePause() { }
	virtual void OnSequenceStop() { }

	virtual void OnOpenModel(_In_ CModelInfo* pModelInfo) { }
	virtual void OnCloseModel(_In_ CModelInfo* pModelInfo) { }

	
	bool OnStartInspection(_In_ CRavidImageView* pView);
	bool CEventHandlerExample::DoSingleThreshold(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoDoubleThreshold(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoOtsuThreshold(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::GetOtsuThreshold(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoAdaptiveThreshold(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoISOThreshold(_In_ CRavidImage& imgInfo);
	void CEventHandlerExample::DrawGraph(CRavidGraphView* pGraph, const std::vector<CRavidPoint<double>>& vctData, double dblStd);
	void CEventHandlerExample::UpdateResult(std::vector<CMultipleVariable> vctResults);
	bool CEventHandlerExample::DoHistogram(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoNormalize(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoConversion(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoDepth(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoConvolution(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoComponent(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoDrawforCC(_In_ CConnectedComponent& cc, _In_ int nView);
	bool CEventHandlerExample::DoExtration(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoMask(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoMorphology(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoMorphology2(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoOperation(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoOperation2(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoPaste(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoPointGuage(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoLineGuage(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoRectGuage(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoQudraGuage(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoProject(_In_ CRavidImage& imgInfo);
	void CEventHandlerExample::DrawGraph1(CRavidGraphView* pGraph, const std::vector<CRavidPoint<double>>& vctData, double dblStd, double dblStd1);

	bool CEventHandlerExample::DoCanny(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoHarryCorner(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoHoughLine(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoHoughCircle(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoFInder(_In_ CRavidImage& imgInfo);
	bool CEventHandlerExample::DoShapeFInder(_In_ CRavidImage& imgInfo);
	CRavidRect<double> m_rrMeasurement;
	CRavidRect<double> m_rrMeasureObject;

	std::vector<double> m_vctMeasured;
};

