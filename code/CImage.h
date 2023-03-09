#ifndef _ITWM_IMAGE_H_
#define _ITWM_IMAGE_H_

#include <iostream>

using namespace std;

class CImage
{

private:
    int m_nSizeX;
    int m_nSizeY;
    unsigned char* m_szBuffer;
    int m_nMaxVal;
public:

    CImage() { m_nSizeX = 0; m_nSizeY = 0; }
    ~CImage() { delete[] m_szBuffer; }

    void SetWidth(int w) { m_nSizeX = w; }
    void SetHeight(int h) { m_nSizeY = h; }
    void SetRawBuffer(unsigned char* szImageData) { m_szBuffer = szImageData; }
    void SetMaxVal(int val) { m_nMaxVal = val; }

    void DisplayBuffer()
    {
        cout << "\nDisplaying Buffer\n";
        for (int i = 0; i < m_nSizeX * m_nSizeY; i++)
            cout << (int)m_szBuffer[i] << "\t";
    }

    int GetWidth() const { return m_nSizeX; }
    int GetHeight() const { return m_nSizeY; }
    unsigned char* GetRawBuffer() const { return m_szBuffer; }
    int GetMaxVal() const { return m_nMaxVal; }

};


#endif //_ITWM_IMAGE_H_


