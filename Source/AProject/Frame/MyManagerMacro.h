#pragma once

// Fast FrameWork Access

#define FS_FRMAE_CHECK()	UFSBlueprintFuncLibrary::IsFrame()
#define FS_FRMAE()			UFSBlueprintFuncLibrary::GetFrame()
#define FS_INSTANCE()		FS_FRMAE()->GetGameInstance()
#define	FS_WORLD()			FS_FRMAE()->GetGameWorld()

#define	FS_CONFIG()			FS_FRMAE()->GetConfig()
#define	FS_LUA()			FS_FRMAE()->GetLua()
#define	FS_TABLE()			FS_FRMAE()->GetTable()
#define	FS_STREAM()			FS_FRMAE()->GetStream()
#define	FS_INPUT()			FS_FRMAE()->GetInput()
#define	FS_CAMERA()			FS_FRMAE()->GetCamera()
#define	FS_SPAWN()			FS_FRMAE()->GetSpawn()
#define	FS_STATE()			FS_FRMAE()->GetState()
#define	FS_LEVEL()			FS_FRMAE()->GetLevel()
#define	FS_UMG()			FS_FRMAE()->GetUMG()
#define	FS_SOUND()			FS_FRMAE()->GetSound()
#define	FS_NETWORK()		FS_FRMAE()->GetNetwork()

