#pragma once
#include "yoshix_fix_function.h"

#include "CGame.h"
#include "KeyState.h"

class CApplication : public gfx::IApplication
{
		public:
			CApplication();
			~CApplication();

			CGame* m_pGame;

		private:
			float m_FieldOfViewY;

			
			KeyState m_KeyState;
			gfx::BHandle m_pPlayerMesh;

			gfx::BHandle m_pTriangleMesh;

		private:
			 bool InternOnStartup();
			 bool InternOnShutdown();
			 bool InternOnCreateMeshes();
			 bool InternOnReleaseMeshes();
			 bool InternOnResize(int _Width, int _Height);
			 bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown);
			 bool InternOnUpdate();
			 bool InternOnFrame();
};
