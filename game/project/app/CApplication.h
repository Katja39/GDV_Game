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
			CRectangle* m_Background;
			CRectangle* m_BottomLine;;

			CGame* m_pGame;
			
			KeyState m_KeyState;

			gfx::BHandle m_pPlayerMesh;
			gfx::BHandle m_pEnemyMesh;
			gfx::BHandle m_pBackgroundMesh;
			gfx::BHandle m_pBottomLineMesh;

			//gfx::BHandle m_BackgroundTexture;

			float m_FieldOfViewY;

		private:
			 bool InternOnStartup();
			 bool InternOnShutdown();
			// bool InternOnCreateTextures(); TODO
			// bool InternOnReleaseTextures();
			 bool InternOnCreateMeshes();
			 bool InternOnReleaseMeshes();
			 bool InternOnResize(int _Width, int _Height);
			 bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown,bool _IsAltDown);
			 bool InternOnUpdate();
			 bool InternOnFrame();
};
