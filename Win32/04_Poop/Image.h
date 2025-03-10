/////

#pragma once

class CImage
{
private:
	HDC				m_MemDC;			///// 메모리 DC (이곳에 그림이 저장된다.)
	HBITMAP			m_bit, m_obit;
	BYTE*			m_pData;
	DWORD			m_dwPitch;
	tagImageInfo	m_Info;

private:
	HBITMAP GetBit(TCHAR* szFileName);
	void Flip();

public:
	CImage(TCHAR* szFileName, tagImageInfo Info);
	virtual ~CImage();

	void Render(HDC hDest, int nX, int nY, bool bColorKey = false, int nFrameX = 0, int nFrameY = 0);
	void RenderAlpha(HDC hDest, HDC hAlpha, int nX, int nY, bool bColorKey = false, int nFrameX = 0, int nFrameY = 0, int Alpha = 255);

	HDC GetMemDC() { return m_MemDC; }
	int GetImageWidth() const { return m_Info.nFWidth; }
	int GetImageHeight() const { return m_Info.nFHeight; }
	int GetMaxFrameX() { return m_Info.nFrameXMax; }
};

///// 이미지 매니저
class CImageManager : public CSSINGLETON <CImageManager>
{
private:
	std::vector<CImage*> m_vImage;

	HDC m_hdc;			///// 화면 DC
	HDC m_back;			///// 백버퍼 DC
	HDC m_Alpha;		///// 알파블랜드 DC (투명값)

public:
	CImageManager();
	virtual ~CImageManager();

	bool Init();		///// 초기화 (생성자에서 초기화를 하게 될 경우, HDC = GetDC(g_hWnd) 에서 버그 발생하기 때문에 초기화를 따로 해준다.)
	bool Release();
	void CreateImage(TCHAR* szFileName, int FrameXMax, int FrameYMax);

	CImage* GetImage(int Number) { return m_vImage[Number]; }
	HDC GetHdc() { return m_hdc; }
	HDC GetBack() { return m_back; }
	HDC GetAlpha() { return m_Alpha; }

	CImage* operator[](int Index) { return m_vImage[Index]; }
};

#define S_IMAGE CImageManager::GetInstance()		///// !! 주요 렌더링을 위한 정의

