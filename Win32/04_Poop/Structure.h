/////

#pragma once

///// 이미지 정보 태그
struct tagImageInfo
{
	int nWidth;
	int nHeight;
	int nFWidth;
	int nFHeight;
	int nFrameXMax;		///// 가로축으로 몇장의 그림이 있다.
	int nFrameYMax;		///// 세로축으로 몇장의 그림이 있다.
};

///// 싱글톤
template<class T> class CSSINGLETON
{
private:
	static T* m_pInstance;

public:
	CSSINGLETON() { m_pInstance = (T*)this; }
	~CSSINGLETON() { m_pInstance = 0; }

	static T& GetInstance() { return (*m_pInstance); }
	static T& GetInstancePtr() { return m_pInstance; }
};
template<class T> T* CSSINGLETON<T>::m_pInstance = 0;

