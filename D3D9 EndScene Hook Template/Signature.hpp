#include <memory>

	class Signature
	{
	public:
		Signature();
		~Signature();

		void initSignatures();
		void initNetvars();

		// Signatures

		// client_panorama.dll
		ptrdiff_t dwLocalPlayer;
		ptrdiff_t dwEntityList;
		ptrdiff_t dwForceJump;
		ptrdiff_t dwForceAttack;
		ptrdiff_t dwGlowObjectManager;
		ptrdiff_t dwViewMatrix;
		ptrdiff_t dwGetAllClasses;

		// client_panorama.dll + dwLocalPlayer
		ptrdiff_t m_bDormant;

		// engine.dll
		ptrdiff_t model_ambient_min;
		ptrdiff_t dwClientState;

		// engine.dll + dwClientState
		ptrdiff_t dwClientState_ViewAngles;


		// Netvars

		// clien_panorama.dll + dwLocalPlayer
		ptrdiff_t m_iHealth;
		ptrdiff_t m_bSpotted;
		ptrdiff_t m_fFlags;
		ptrdiff_t m_flFlashDuration;
		ptrdiff_t m_iTeamNum;
		ptrdiff_t m_iCrosshairId;
		ptrdiff_t m_bIsDefusing;
		ptrdiff_t m_clrRender;
		ptrdiff_t m_aimPunchAngle;
		ptrdiff_t m_iShotsFired;
		ptrdiff_t m_lifeState;
		ptrdiff_t m_vecOrigin;
		ptrdiff_t m_dwBoneMatrix;

		// client_panorama.dll + dwGlowObjectManager
		ptrdiff_t m_iGlowIndex;
	};
	
	extern std::unique_ptr<Signature> gSignature;
