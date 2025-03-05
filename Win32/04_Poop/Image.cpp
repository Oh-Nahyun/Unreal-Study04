/////

#include "framework.h"

CImage::CImage(TCHAR* szFilename, tagImageInfo Info)
{
    m_Info  = Info;

    HDC hdc = GetDC(g_hWnd);
    m_memDC = CreateCompatibleDC(hdc);
    m_bit   = GetBit(szFilename);
    m_obit  = (HBITMAP)SelectObject(m_memDC, m_bit);

    ReleaseDC(g_hWnd, hdc);
}

CImage::~CImage()
{
    SelectObject(m_memDC, m_obit);
    DeleteObject(m_bit);
    DeleteDC(m_memDC);
}

/// <summary>
/// 비트맵 파일을 읽은 다음 HBITMAP 형을 리턴하는 함수
/// (((이 방법 외에도 다른 방법도 많으니 찾아보고 다르게 구현해도 된다.)))
/// </summary>
HBITMAP CImage::GetBit(TCHAR* szFilename)
{
    HANDLE              hFile;
    BITMAPFILEHEADER    fh;
    BITMAPINFO*         ih;
    DWORD               dwRead;
    DWORD               dwInfoSize;
    HBITMAP             bit;

    ///// 파일
    hFile = CreateFile(szFilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    ///// 파일 헤더
    ReadFile(hFile, &fh, sizeof(fh), &dwRead, NULL);
    dwInfoSize = fh.bfOffBits - sizeof(fh);
    ih = (BITMAPINFO*) new BYTE[dwInfoSize];

    ///// 인포 헤더
    ReadFile(hFile, ih, dwInfoSize, &dwRead, NULL);

    ih->bmiHeader.biHeight *= -1;
    bit = CreateDIBSection(NULL, ih, DIB_RGB_COLORS, (void**)&m_pData, NULL, 0);
    ih->bmiHeader.biHeight *= -1;

    m_Info.nWidth   = ih->bmiHeader.biWidth;
    m_Info.nHeight  = ih->bmiHeader.biHeight;
    m_Info.nFWidth  = m_Info.nWidth  / m_Info.nFrameXMax;
    m_Info.nFHeight = m_Info.nHeight / m_Info.nFrameYMax;
    m_dwPitch       = (m_Info.nWidth * (ih->bmiHeader.biBitCount >> 3)) + 3 & ~3;   ///// ~3 (0011 의 반전을 뜻하여 1100 을 의미한다.) 4 의 배수가 아닌 수는 뒷자리에서 걸러낸다. 
                                                                                    ///// (((Pitch 값을 구하는 공식)))

    ///// 파일 종료
    CloseHandle(hFile);
    delete[] ih;

    return bit;
}

void CImage::Flip()
{
    int i;
    BYTE* pTemp;

    pTemp = new BYTE[m_dwPitch];

    for (i = 0; i < m_Info.nHeight / 2; i++)
    {
        memcpy(pTemp, &m_pData[i * m_dwPitch], m_dwPitch);
        memcpy(&m_pData[i * m_dwPitch], &m_pData[m_Info.nHeight - 1 - i], m_dwPitch);
        memcpy(&m_pData[m_Info.nHeight - 1 - i], pTemp, m_dwPitch);
    }
    delete[] pTemp;
}

/// <summary>
/// 화면 (출력) 프레임으로 출력하는 함수
/// </summary>
void CImage::Render(HDC hDest, int nX, int nY, bool bColorKey, int nFrameX, int nFrameY)
{
    if (bColorKey)
    {
        TransparentBlt(hDest, nX, nY, m_Info.nFWidth, m_Info.nFHeight, m_memDC,
            nFrameX * m_Info.nFWidth, nFrameY * m_Info.nFHeight, 
            m_Info.nFWidth, m_Info.nFHeight, RGB_VALUE);
    }
    else
    {
        BitBlt(hDest, nX, nY, m_Info.nFWidth, m_Info.nFHeight, m_memDC,
            nFrameX * m_Info.nFWidth, nFrameY * m_Info.nFHeight, SRCCOPY);
    }
}

/// <summary>
/// 투명값을 (조절) 적용하여 출력하는 함수
/// </summary>
void CImage::RenderAlpha(HDC hDest, HDC hAlpha, int nX, int nY, bool bColorKey, int nFrameX, int nFrameY, int Alpha)
{
    int TempX = 1, TempY = 1;
    int TempRivisionX = 0, TempRivisionY = 0;

    if (nX < 0)
    {
        TempX = 0;
        TempRivisionX = nX * -1;
    }

    if (nY < 0)
    {
        TempY = 0;
        TempRivisionY = nY * -1;
    }

    ///// 알파블랜드 memDC 에 배경을 복사한다.
    TransparentBlt(hAlpha, 0, 0, m_Info.nFWidth, m_Info.nFHeight, 
        hDest, nX * TempX, nY * TempY, 
        m_Info.nFWidth - TempRivisionX, m_Info.nFHeight - TempRivisionY, RGB_VALUE);

    ///// 알파블랜드 memDC 에 블랜드 대상을 복사한다.
    TransparentBlt(hAlpha, 0, 0, m_Info.nFWidth, m_Info.nFHeight,
        m_memDC, nFrameX * m_Info.nFWidth * TempX + TempRivisionX, nFrameY * m_Info.nFHeight * TempY + TempRivisionY, 
        m_Info.nFWidth - TempRivisionX, m_Info.nFHeight - TempRivisionY, RGB_VALUE);

    ///// 투명값을 조절한다.
    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = Alpha;     ///// 투명값을 조절해주는 인자값 (0 : 투명, 255 : 불투명)
    bf.AlphaFormat = 0;

    ///// 백버퍼에 완성된 알파블랜드 memDC 를 보낸다.
    AlphaBlend(hDest, nX * TempX, nY * TempY, m_Info.nFWidth - TempRivisionX, m_Info.nFHeight - TempRivisionY, 
        hAlpha, 0, 0, m_Info.nFWidth, m_Info.nFHeight, bf);
}

