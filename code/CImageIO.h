#ifndef CImageIO_H_
#define CImageIO_H_

#include <iostream>
#include <fstream>
#include <string>
#include<conio.h>
#include<cstring> // This function wasn't defined for strncmp

#include "CImage.h"

using namespace std;

class CImageIO
{

private:  char* m_szFileData;
          int m_nFlag;

public:
       CImageIO (){}
       ~CImageIO(){delete [] m_szFileData;}
       
void LoadPgm (CImage* img, char* szFileName) 
       {       
       char caHeader [500], *szTemp; 
       ifstream ifp;
       
       ifp.open(szFileName, ios::binary);
       if (!ifp) 
       {
        cout << "Can't read image: " << szFileName << endl;
        std::getchar();
        exit(1);
       }
        // read header
        ifp.getline(caHeader,500,'\n');        
        if (strncmp(caHeader,"P5", 2))
	    {
	       if (strncmp(caHeader,"P2", 2))
           {
             cout << "Image " << szFileName << " is not valid PGM" << endl;
             std::getchar();
             exit(1);
           }
           else 
		   m_nFlag = 2;
	    }
        else 
	    m_nFlag = 5;
        ifp.getline(caHeader,500,'\n');
        while(caHeader[0]=='#')
        ifp.getline(caHeader,500,'\n');       
        img->SetWidth(strtol(caHeader,&szTemp,0));
        img->SetHeight(atoi(szTemp));
        ifp.getline(caHeader,500,'\n');
        img->SetMaxVal(strtol(caHeader,&szTemp,0));
        m_szFileData = new char[img->GetWidth()*img->GetHeight()];  
        ifp.read(m_szFileData, img->GetWidth()*img->GetHeight() );        
        
        img->SetRawBuffer((unsigned char*)m_szFileData);
            
        if (ifp.fail()) {
        cout << "Image " << szFileName << " has wrong size" << endl;
        std::getchar();
        exit(1);
        } 
       
        ifp.close();
}
        
void SavePgm(CImage* img, char* szFileName) //File Path
        { 
        ofstream ofp;
        ofp.open(szFileName, ios::binary);
        if (!ofp) 
        {
        cout << "Can't open image: " << szFileName << endl;
        std::getchar();
        exit(1);
        }
        //Write Header

        if ( img->GetWidth() == 0 && img->GetHeight()==0)
        {
        cout << "Image is not loaded" <<endl;
        std::getchar();
        exit(1);
        }
        if (m_nFlag == 5)
        ofp<<"P5"<<"\n";
        if (m_nFlag == 2)
        ofp<<"P2"<<"\n";
        ofp<<img->GetWidth()<<" "<<img->GetHeight()<<"\n";
        ofp<<"#"<<"\n";
        ofp<<img->GetMaxVal()<<"\n";
        ofp.write((char*)img->GetRawBuffer(), img->GetWidth() *img->GetHeight());
        ofp.close();

}
          
};

#endif //CImageIO_H_


