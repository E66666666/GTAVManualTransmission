/*
THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
http://dev-c.com
(C) Alexander Blade 2015
*/
#pragma once

#include "..\..\ScriptHookV_SDK\inc\main.h"
#include "script.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		clearLog();
		writeToLog("Script loaded");
		start = time(0);
		scriptRegister(hInstance, ScriptMain);
		break;
	case DLL_PROCESS_DETACH:
		scriptUnregister(hInstance);
		bool success = restoreClutchInstructions();
		if (success) {
			writeToLog("Shut down script successfully");
		}
		else {
			writeToLog("Shut down script with leftovers");
		}
		break;
	}
	return TRUE;
}