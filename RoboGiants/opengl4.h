#pragma once
#include <iostream>
#include "lib/glcorearb.h"

class GL
{
public:	
	static PFNGLINVALIDATEBUFFERDATAPROC InvalidateBuffer;
	static PFNGLGENBUFFERSPROC GenBuffer;
	static PFNGLBINDBUFFERPROC BindBuffer;
};