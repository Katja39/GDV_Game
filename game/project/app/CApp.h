#pragma once
#include "yoshix_fix_function.h"

#include "CGame.h"
#include "KeyState.h"

class CApplication : public gfx::IApplication
{
		public:
			CApplication();
			~CApplication();

		private:
			float m_FieldOfViewY;

			CGame* m_pGame;
			KeyState m_KeyState;
			gfx::BHandle m_pPlayerMesh;

			gfx::BHandle m_pTriangleMesh;

		private:
			 bool InternOnStartup();
			 bool InternOnShutdown();
			 bool InternOnCreateMeshes();
			 bool InternOnReleaseMeshes();
			 bool InternOnResize(int _Width, int _Height);
			 bool InternOnKeyEvent();
			 bool InternOnUpdate();
			 bool InternOnFrame();
};
