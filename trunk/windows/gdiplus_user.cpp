
#include "gdiplus_user.h"
#include <objidl.h>

using namespace Gdiplus;

std::wstring MtbToWstr( const std::string& str, UINT uCodePage = CP_ACP )   
{   
	using namespace std;
	LPWSTR lpwszWide = NULL;   
	DWORD cbszWide = 0U;   
	DWORD dwRet = 0U;   
	wstring wstrRet;   

	/// calculate the require size   
	cbszWide = MultiByteToWideChar( uCodePage, 0U, str.c_str(), -1, lpwszWide, 0 );   
	if ( 0U == cbszWide )   
		goto Exit0;   

	/// allocate specify size   
	lpwszWide = (LPWSTR)HeapAlloc( GetProcessHeap(), 0, cbszWide * sizeof( WCHAR ) );   
	if ( NULL == lpwszWide )   
		goto Exit0;   

	/// start convert   
	dwRet = MultiByteToWideChar( uCodePage, 0U, str.c_str(), -1, lpwszWide, cbszWide );   
	if ( 0 == dwRet )   
		goto Exit0;   
	wstrRet = lpwszWide;   

Exit0:   
	if ( NULL != lpwszWide )   
		HeapFree( GetProcessHeap(), 0, lpwszWide );   
	return wstrRet;   
}  



namespace ns_gdiplus
{
	void draw_line(Gdiplus::Graphics& g, unsigned int color, float x1, float y1, float x2, float y2)
	{	
		Gdiplus::Color c(color);
		Gdiplus::Pen p(c );
		g.DrawLine(&p, x1, y1, x2, y2);
	};

	void draw_rect(Gdiplus::Graphics& g, bool solid, unsigned int color, float x1, float y1, float wid, float height)
	{
		if(!solid)
		{
			Gdiplus::Color c(color);
			Gdiplus::Pen p(c );
			g.DrawRectangle(&p, x1, y1, wid, height);
		}
		else
		{
			Gdiplus::Color c(color);
			Gdiplus::SolidBrush b(c );
			g.FillRectangle(&b, x1, y1, wid, height);
		}
	};

	void draw_text(Gdiplus::Graphics& g, const char* text, const char* str_font, unsigned int sz, unsigned int color, float x1, float y1)
	{
		Gdiplus::PointF pointF(x1,y1);
		Gdiplus::Color c(color);
		Gdiplus::SolidBrush brush( c );  
		std::wstring wstr = MtbToWstr(std::string(text) );

		std::wstring wstr1 = MtbToWstr(std::string(str_font) );
		Gdiplus::FontFamily fontFamily(wstr1.c_str() );         //选择一种字体
		Gdiplus::Font font(&fontFamily, sz, Gdiplus::FontStyleRegular,Gdiplus::UnitPixel);
		g.DrawString(wstr.c_str(), -1, &font, pointF, &brush);
	};
	
	static ULONG_PTR           gdiplusToken;
	void init()
	{
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}

	void release()
	{
		GdiplusShutdown(gdiplusToken);
	}
}

