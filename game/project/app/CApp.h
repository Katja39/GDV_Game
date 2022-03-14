#pragma once
#include "yoshix_fix_function.h"

#include <iostream>
#include <math.h>

using namespace gfx;

class CApplication : public gfx::IApplication
{
		public:
			CApplication();
			virtual ~CApplication();

		private:
			float   m_FieldOfViewY;
			BHandle m_pTriangleMesh;

		private:
			virtual bool InternOnCreateMeshes();
			virtual bool InternOnReleaseMeshes();
			virtual bool InternOnResize(int _Width, int _Height);
			virtual bool InternOnUpdate();
			virtual bool InternOnFrame();
};