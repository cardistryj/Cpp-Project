#pragma once
#include<cstdlib>
#include<ctime>

class Color
{
	//´æ´¢ÑÕÉ«µÄgrbÖµ
	unsigned char color[12][3] = {
		{ 0,255,255 },{ 0,255,127 },{ 255,215,0 }
		,{ 255,106,106 },{ 255,222,173 },{ 255,131,255 }
		,{ 30,144,255 },{ 255,255,0 },{ 160,32,240 }
		,{ 255,0,0 },{ 0,0,255 },{ 50,205,50 }
	};
public:
	Color() = default;
	inline unsigned char* getColor(unsigned randomnumber) {
		return *(color + randomnumber);
	}
};

