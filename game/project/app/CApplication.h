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
		CGame* m_pGame;
		
		KeyState m_KeyState;

		gfx::BHandle m_pPlayerMesh;
		gfx::BHandle m_pEnemyMesh;
		gfx::BHandle m_pLeftLineMesh;
		gfx::BHandle m_pBackgroundMesh;
		gfx::BHandle m_pPowerUpMesh;

		float m_FieldOfViewY;

	private:
		bool InternOnStartup();
		bool InternOnShutdown();
		bool InternOnCreateMeshes();
		bool InternOnReleaseMeshes();
		bool InternOnResize(int _Width, int _Height);
		bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown,bool _IsAltDown);
		bool InternOnUpdate();
		bool InternOnFrame();
};
