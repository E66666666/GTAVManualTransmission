#include "ScriptSettings.hpp"

#include <string>
#ifdef GAME_BUILD
#include <inc/enums.h>
#include "menucontrols.h"
#include "menu.h"
#endif
#include "../thirdparty/simpleini/SimpleIni.h"
#include "Util/Logger.hpp"
#include "Input/keyboard.h"
#include "Input/ScriptControls.hpp"

#include "Util/Versions.h"

ScriptSettings::ScriptSettings(const std::string &general,
	                           const std::string &wheel) :
	nDevices(0),
    settingsGeneralFile(general),
    settingsWheelFile(wheel) {

}

void ScriptSettings::SetFiles(const std::string &general, const std::string &wheel) {
	settingsGeneralFile = general;
	settingsWheelFile = wheel;
}

void ScriptSettings::SetMenuFile(const std::string &menu) {
	settingsMenuFile = menu;
}


void ScriptSettings::Read(ScriptControls* scriptControl) {
	parseSettingsGeneral(scriptControl);
	parseSettingsWheel(scriptControl);
}
#ifdef GAME_BUILD
void ScriptSettings::Read(NativeMenu::MenuControls* menuControl, NativeMenu::Menu *menuOpts) {
	parseSettingsMenu(menuControl,menuOpts);
}
#endif
void ScriptSettings::SaveGeneral() const {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	
	// [OPTIONS]
	settingsGeneral.SetBoolValue("OPTIONS", "Enable", EnableManual);
	settingsGeneral.SetLongValue("OPTIONS", "ShiftMode", ShiftMode);

	settingsGeneral.SetLongValue("OPTIONS", "ShiftMode", ShiftMode);
	settingsGeneral.SetBoolValue("OPTIONS", "SimpleBike", SimpleBike);
	settingsGeneral.SetBoolValue("OPTIONS", "EngineDamage", EngDamage);
	settingsGeneral.SetBoolValue("OPTIONS", "EngineStalling", EngStall);
	settingsGeneral.SetBoolValue("OPTIONS", "EngineBraking", EngBrake);
	settingsGeneral.SetBoolValue("OPTIONS", "ClutchCatching", ClutchCatching);
	settingsGeneral.SetBoolValue("OPTIONS", "ClutchShiftingH", ClutchShiftingH);
	settingsGeneral.SetBoolValue("OPTIONS", "ClutchShiftingS", ClutchShiftingS);
	settingsGeneral.SetBoolValue("OPTIONS", "DefaultNeutral", DefaultNeutral);

	//TODO: Something about these factors :$
	settingsGeneral.SetDoubleValue("OPTIONS", "ClutchCatchpoint", ClutchCatchpoint * 100);
	settingsGeneral.SetDoubleValue("OPTIONS", "StallingThreshold", StallingThreshold * 100);
	settingsGeneral.SetDoubleValue("OPTIONS", "RPMDamage", RPMDamage * 100);
	settingsGeneral.SetDoubleValue("OPTIONS", "MisshiftDamage", MisshiftDamage);

	settingsGeneral.SetBoolValue("OPTIONS", "HillBrakeWorkaround", HillBrakeWorkaround);
	settingsGeneral.SetBoolValue("OPTIONS", "AutoGear1", AutoGear1);
	settingsGeneral.SetBoolValue("OPTIONS", "AutoLookBack", AutoLookBack);
	settingsGeneral.SetBoolValue("OPTIONS", "ThrottleStart", ThrottleStart);

	settingsGeneral.SetBoolValue("OPTIONS", "CrossScript", CrossScript);

	// [HUD]
	settingsGeneral.SetBoolValue("HUD", "EnableHUD", HUD);
	settingsGeneral.SetLongValue("HUD", "HUDFont", HUDFont);
	settingsGeneral.SetDoubleValue("HUD", "GearXpos", GearXpos);
	settingsGeneral.SetDoubleValue("HUD", "GearYpos", GearYpos);
	settingsGeneral.SetDoubleValue("HUD", "GearSize", GearSize);
	settingsGeneral.SetLongValue("HUD", "GearTopColorR", GearTopColorR);
	settingsGeneral.SetLongValue("HUD", "GearTopColorG", GearTopColorG);
	settingsGeneral.SetLongValue("HUD", "GearTopColorB", GearTopColorB);

	settingsGeneral.SetDoubleValue("HUD", "ShiftModeXpos", ShiftModeXpos);
	settingsGeneral.SetDoubleValue("HUD", "ShiftModeYpos", ShiftModeYpos);
	settingsGeneral.SetDoubleValue("HUD", "ShiftModeSize", ShiftModeSize);

	settingsGeneral.SetValue("HUD", "Speedo", Speedo.c_str());
	settingsGeneral.SetBoolValue("HUD", "SpeedoShowUnit", SpeedoShowUnit);
	settingsGeneral.SetDoubleValue("HUD", "SpeedoXpos", SpeedoXpos);
	settingsGeneral.SetDoubleValue("HUD", "SpeedoYpos", SpeedoYpos);
	settingsGeneral.SetDoubleValue("HUD", "SpeedoSize", SpeedoSize);

	settingsGeneral.SetBoolValue("HUD", "EnableRPMIndicator", RPMIndicator);
	settingsGeneral.SetDoubleValue("HUD", "RPMIndicatorXpos", RPMIndicatorXpos);
	settingsGeneral.SetDoubleValue("HUD", "RPMIndicatorYpos", RPMIndicatorYpos);
	settingsGeneral.SetDoubleValue("HUD", "RPMIndicatorWidth", RPMIndicatorWidth);
	settingsGeneral.SetDoubleValue("HUD", "RPMIndicatorHeight", RPMIndicatorHeight);
	settingsGeneral.SetDoubleValue("HUD", "RPMIndicatorRedline", RPMIndicatorRedline);

	settingsGeneral.SetLongValue("HUD", "RPMIndicatorBackgroundR", RPMIndicatorBackgroundR);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorBackgroundG", RPMIndicatorBackgroundG);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorBackgroundB", RPMIndicatorBackgroundB);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorBackgroundA", RPMIndicatorBackgroundA);

	settingsGeneral.SetLongValue("HUD", "RPMIndicatorForegroundR", RPMIndicatorForegroundR);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorForegroundG", RPMIndicatorForegroundG);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorForegroundB", RPMIndicatorForegroundB);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorForegroundA", RPMIndicatorForegroundA);

	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRedlineR", RPMIndicatorRedlineR);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRedlineG", RPMIndicatorRedlineG);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRedlineB", RPMIndicatorRedlineB);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRedlineA", RPMIndicatorRedlineA);

	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRevlimitR", RPMIndicatorRevlimitR);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRevlimitG", RPMIndicatorRevlimitG);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRevlimitB", RPMIndicatorRevlimitB);
	settingsGeneral.SetLongValue("HUD", "RPMIndicatorRevlimitA", RPMIndicatorRevlimitA);

	// [DEBUG]
	settingsGeneral.SetBoolValue("DEBUG", "DisplayInfo", DisplayInfo);
	settingsGeneral.SetBoolValue("DEBUG", "LogCar", LogCar);

	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

void ScriptSettings::SaveController(ScriptControls *scriptControl) const {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	
	// [CONTROLLER]
	settingsGeneral.SetBoolValue("CONTROLLER", "ToggleEngine", ToggleEngine);
	settingsGeneral.SetLongValue("CONTROLLER", "ToggleTime", scriptControl->CToggleTime); 
	settingsGeneral.SetDoubleValue("CONTROLLER", "TriggerValue", scriptControl->GetXboxTrigger());

#ifdef GAME_BUILD
	settingsGeneral.SetBoolValue("CONTROLLER_LEGACY", "Enable", scriptControl->UseLegacyController);
#endif

	settingsGeneral.SaveFile(settingsGeneralFile.c_str());
}

// Axis information is saved by its own calibration methods
void ScriptSettings::SaveWheel(ScriptControls *scriptControl) const {
	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());

	// [OPTIONS]
	settingsWheel.SetBoolValue("OPTIONS", "EnableWheel", EnableWheel);
	settingsWheel.SetBoolValue("OPTIONS", "WheelWithoutManual", WheelWithoutManual);
	settingsWheel.SetBoolValue("OPTIONS", "WheelBoatPlanes", AltControls);
	settingsWheel.SetBoolValue("OPTIONS", "PatchSteering", PatchSteering);
	settingsWheel.SetBoolValue("OPTIONS", "PatchSteeringAlways", PatchSteeringAlways);
	settingsWheel.SetBoolValue("OPTIONS", "LogitechLEDs", LogiLEDs);

	settingsWheel.SetBoolValue("OPTIONS", "InvertSteer", scriptControl->InvertSteer);
	settingsWheel.SetBoolValue("OPTIONS", "InvertThrottle", scriptControl->InvertThrottle);
	settingsWheel.SetBoolValue("OPTIONS", "InvertBrake", scriptControl->InvertBrake);
	settingsWheel.SetBoolValue("OPTIONS", "InvertClutch", scriptControl->InvertClutch);
	
	// [FORCE_FEEDBACK]
	settingsWheel.SetBoolValue("FORCE_FEEDBACK", "Enable", EnableFFB);
	settingsWheel.SetDoubleValue("FORCE_FEEDBACK", "GlobalMult", FFGlobalMult);
	settingsWheel.SetLongValue("FORCE_FEEDBACK", "DamperMax", DamperMax);
	settingsWheel.SetLongValue("FORCE_FEEDBACK", "DamperMin", DamperMin);
	settingsWheel.SetDoubleValue("FORCE_FEEDBACK", "DamperTargetSpeed", TargetSpeed);
	settingsWheel.SetDoubleValue("FORCE_FEEDBACK", "PhysicsStrength", PhysicsStrength);
	settingsWheel.SetDoubleValue("FORCE_FEEDBACK", "DetailStrength", DetailStrength);

	// [STEER]
	settingsWheel.SetDoubleValue("STEER", "SteerAngleMax", SteerAngleMax );
	settingsWheel.SetDoubleValue("STEER", "SteerAngleCar", SteerAngleCar );
	settingsWheel.SetDoubleValue("STEER", "SteerAngleBike",SteerAngleBike);
	settingsWheel.SetDoubleValue("STEER", "SteerAngleAlt", SteerAngleAlt );
	settingsWheel.SetDoubleValue("STEER", "GameSteerMult", GameSteerMult );

	settingsWheel.SaveFile(settingsWheelFile.c_str());
}
#ifdef GAME_BUILD
void ScriptSettings::SaveMenu(NativeMenu::Menu *menuOpts) const {
	CSimpleIniA settingsMenu;
	settingsMenu.SetUnicode();
	settingsMenu.LoadFile(settingsMenuFile.c_str());

	// [MENU]
	settingsMenu.SetDoubleValue("MENU", "MenuX", menuOpts->menux);
	settingsMenu.SetDoubleValue("MENU", "MenuY", menuOpts->menuy);

	settingsMenu.SaveFile(settingsMenuFile.c_str());
}
#endif

bool ScriptSettings::IsCorrectVersion() const {
	if (settings_general_version != CORRECTVGENERAL || settings_wheel_version != CORRECTVWHEEL)
		return false;
	return true;
}

std::string ScriptSettings::GetVersionError() {
	if (settings_general_version != CORRECTVGENERAL && settings_wheel_version != CORRECTVWHEEL)
		return std::string("Wrong settings_general.ini version\nWrong settings_wheel.ini version");
	if (settings_general_version != CORRECTVGENERAL)
		return std::string("Wrong settings_general.ini version");
	if (settings_wheel_version != CORRECTVWHEEL)
		return std::string("Wrong settings_wheel.ini version");
	return "";
}

std::vector<GUID> ScriptSettings::GetGuids() {
	return reggdGuids;
}

void ScriptSettings::parseSettingsGeneral(ScriptControls *scriptControl) {
#pragma warning(push)
#pragma warning(disable: 4244) // Make everything doubles later...
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());

	settingsGeneral.GetBoolValue("OPTIONS", "Enable", true);
	// [OPTIONS]
	EnableManual = settingsGeneral.GetBoolValue("OPTIONS", "Enable", true);
	ShiftMode = settingsGeneral.GetLongValue("OPTIONS", "ShiftMode", 0);
	SimpleBike = settingsGeneral.GetBoolValue("OPTIONS", "SimpleBike", false);
	EngDamage = settingsGeneral.GetBoolValue("OPTIONS", "EngineDamage", false);
	EngStall = settingsGeneral.GetBoolValue("OPTIONS", "EngineStalling", false);
	EngBrake = settingsGeneral.GetBoolValue("OPTIONS", "EngineBraking", false);
	ClutchCatching = settingsGeneral.GetBoolValue("OPTIONS", "ClutchCatching", false);
	ClutchShiftingH = settingsGeneral.GetBoolValue("OPTIONS", "ClutchShiftingH", false);
	ClutchShiftingS = settingsGeneral.GetBoolValue("OPTIONS", "ClutchShiftingS", false);
	DefaultNeutral = settingsGeneral.GetBoolValue("OPTIONS", "DefaultNeutral", true);

	ClutchCatchpoint = settingsGeneral.GetDoubleValue("OPTIONS", "ClutchCatchpoint", 15.0) / 100.0f;
	StallingThreshold = settingsGeneral.GetDoubleValue("OPTIONS", "StallingThreshold", 75.0) / 100.0f;
	RPMDamage = settingsGeneral.GetDoubleValue("OPTIONS", "RPMDamage", 15.0) / 100.0f;
	MisshiftDamage = settingsGeneral.GetDoubleValue("OPTIONS", "MisshiftDamage", 10.0);

	HillBrakeWorkaround = settingsGeneral.GetBoolValue("OPTIONS", "HillBrakeWorkaround", false);
	AutoGear1 = settingsGeneral.GetBoolValue("OPTIONS", "AutoGear1", false);
	AutoLookBack = settingsGeneral.GetBoolValue("OPTIONS", "AutoLookBack", false);
	ThrottleStart = settingsGeneral.GetBoolValue("OPTIONS", "ThrottleStart", false);

	CrossScript = settingsGeneral.GetBoolValue("OPTIONS", "CrossScript", false);

	// [HUD]
	HUD = settingsGeneral.GetBoolValue			("HUD", "EnableHUD", true);
	HUDFont = settingsGeneral.GetLongValue		("HUD", "HUDFont", 0);
	GearXpos = settingsGeneral.GetDoubleValue	("HUD", "GearXpos", 0.95);
	GearYpos = settingsGeneral.GetDoubleValue	("HUD", "GearYpos", 0.95);
	GearSize = settingsGeneral.GetDoubleValue	("HUD", "GearSize", 1.50);
	GearTopColorR = settingsGeneral.GetLongValue("HUD", "GearTopColorR", 255);
	GearTopColorG = settingsGeneral.GetLongValue("HUD", "GearTopColorG", 0);
	GearTopColorB = settingsGeneral.GetLongValue("HUD", "GearTopColorB", 0);

	ShiftModeXpos = settingsGeneral.GetDoubleValue("HUD", "ShiftModeXpos", 0.925);
	ShiftModeYpos = settingsGeneral.GetDoubleValue("HUD", "ShiftModeYpos", 0.90);
	ShiftModeSize = settingsGeneral.GetDoubleValue("HUD", "ShiftModeSize", 1.50);

	Speedo = settingsGeneral.GetValue("HUD", "Speedo", "kph");
	SpeedoShowUnit = settingsGeneral.GetBoolValue("HUD", "SpeedoShowUnit", false);
	SpeedoXpos = settingsGeneral.GetDoubleValue("HUD", "SpeedoXpos", 0.90);
	SpeedoYpos = settingsGeneral.GetDoubleValue("HUD", "SpeedoYpos", 0.85);
	SpeedoSize = settingsGeneral.GetDoubleValue("HUD", "SpeedoSize", 1.00);

	RPMIndicator = settingsGeneral.GetBoolValue("HUD", "EnableRPMIndicator", true);
	RPMIndicatorXpos = settingsGeneral.GetDoubleValue("HUD", "RPMIndicatorXpos", 0.475);
	RPMIndicatorYpos = settingsGeneral.GetDoubleValue("HUD", "RPMIndicatorYpos", 0.950);
	RPMIndicatorWidth = settingsGeneral.GetDoubleValue("HUD", "RPMIndicatorWidth", 0.0);
	RPMIndicatorHeight = settingsGeneral.GetDoubleValue("HUD", "RPMIndicatorHeight", 0.0);
	RPMIndicatorRedline = settingsGeneral.GetDoubleValue("HUD", "RPMIndicatorRedline", 1.0);

	RPMIndicatorBackgroundR = settingsGeneral.GetLongValue("HUD", "RPMIndicatorBackgroundR", 0);
	RPMIndicatorBackgroundG = settingsGeneral.GetLongValue("HUD", "RPMIndicatorBackgroundG", 0);
	RPMIndicatorBackgroundB = settingsGeneral.GetLongValue("HUD", "RPMIndicatorBackgroundB", 0);
	RPMIndicatorBackgroundA = settingsGeneral.GetLongValue("HUD", "RPMIndicatorBackgroundA", 255);
									
	RPMIndicatorForegroundR = settingsGeneral.GetLongValue("HUD", "RPMIndicatorForegroundR", 255);
	RPMIndicatorForegroundG = settingsGeneral.GetLongValue("HUD", "RPMIndicatorForegroundG", 255);
	RPMIndicatorForegroundB = settingsGeneral.GetLongValue("HUD", "RPMIndicatorForegroundB", 255);
	RPMIndicatorForegroundA = settingsGeneral.GetLongValue("HUD", "RPMIndicatorForegroundA", 0);
									
	RPMIndicatorRedlineR = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRedlineR", 255);
	RPMIndicatorRedlineG = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRedlineG", 0);
	RPMIndicatorRedlineB = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRedlineB", 0);
	RPMIndicatorRedlineA = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRedlineA", 255);

	RPMIndicatorRevlimitR = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRevlimitR", 255);
	RPMIndicatorRevlimitG = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRevlimitG", 0);
	RPMIndicatorRevlimitB = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRevlimitB", 0);
	RPMIndicatorRevlimitA = settingsGeneral.GetLongValue("HUD", "RPMIndicatorRevlimitA", 255);

	// [CONTROLLER]
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::Toggle)] = settingsGeneral.GetValue("CONTROLLER", "Toggle", "DpadRight");
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::ToggleH)] = settingsGeneral.GetValue("CONTROLLER", "ToggleShift", "B");
	scriptControl->CToggleTime = settingsGeneral.GetLongValue("CONTROLLER", "ToggleTime", 500);

	double tval = settingsGeneral.GetDoubleValue("CONTROLLER", "TriggerValue", 0.75);
	if (tval > 1.0 || tval < 0.1) {
		tval = 0.75;
	}
	scriptControl->SetXboxTrigger(tval);

	ToggleEngine = settingsGeneral.GetBoolValue("CONTROLLER", "ToggleEngine", "0");

	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::ShiftUp)] = settingsGeneral.GetValue("CONTROLLER", "ShiftUp", "A");
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::ShiftDown)] = settingsGeneral.GetValue("CONTROLLER", "ShiftDown", "X");
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::Clutch)] = settingsGeneral.GetValue("CONTROLLER", "Clutch", "LeftThumbDown");
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::Engine)] = settingsGeneral.GetValue("CONTROLLER", "Engine", "DpadDown");
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::Throttle)] = settingsGeneral.GetValue("CONTROLLER", "Throttle", "RightTrigger");
	scriptControl->ControlXbox[static_cast<int>(ScriptControls::ControllerControlType::Brake)] = settingsGeneral.GetValue("CONTROLLER", "Brake", "LeftTrigger");

#ifdef GAME_BUILD
	// [CONTROLLER_LEGACY]
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::Toggle)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "Toggle", ControlFrontendRight);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::ToggleH)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "ToggleH", ControlFrontendCancel);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::ShiftUp)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "ShiftUp", ControlFrontendAccept);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::ShiftDown)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "ShiftDown", ControlFrontendX);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::Clutch)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "Clutch", ControlFrontendRightAxisY);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::Engine)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "Engine", ControlFrontendDown);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::Throttle)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "Throttle", ControlFrontendLt);
	scriptControl->LegacyControls[static_cast<int>(ScriptControls::LegacyControlType::Brake)] = settingsGeneral.GetLongValue("CONTROLLER_LEGACY", "Brake", ControlFrontendRt);
	scriptControl->UseLegacyController = settingsGeneral.GetBoolValue("CONTROLLER_LEGACY", "Enable", false);
#endif

	// [KEYBOARD]
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::Toggle)] = str2key(settingsGeneral.GetValue("KEYBOARD", "Toggle", "VK_OEM_5"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::ToggleH)] = str2key(settingsGeneral.GetValue("KEYBOARD", "ToggleH", "VK_OEM_6"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::ShiftUp)] = str2key(settingsGeneral.GetValue("KEYBOARD", "ShiftUp", "SHIFT"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::ShiftDown)] = str2key(settingsGeneral.GetValue("KEYBOARD", "ShiftDown", "CTRL"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::Clutch)] = str2key(settingsGeneral.GetValue("KEYBOARD", "Clutch", "X"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::Engine)] = str2key(settingsGeneral.GetValue("KEYBOARD", "Engine", "C"));

	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::Throttle)] = str2key(settingsGeneral.GetValue("KEYBOARD", "Throttle", "W"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::Brake)] = str2key(settingsGeneral.GetValue("KEYBOARD", "Brake", "S"));

	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::HR)] = str2key(settingsGeneral.GetValue("KEYBOARD", "HR", "NUM0"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H1)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H1", "NUM1"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H2)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H2", "NUM2"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H3)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H3", "NUM3"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H4)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H4", "NUM4"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H5)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H5", "NUM5"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H6)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H6", "NUM6"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::H7)] = str2key(settingsGeneral.GetValue("KEYBOARD", "H7", "NUM7"));
	scriptControl->KBControl[static_cast<int>(ScriptControls::KeyboardControlType::HN)] = str2key(settingsGeneral.GetValue("KEYBOARD", "HN", "NUM9"));



	// [DEBUG]
	DisplayInfo = settingsGeneral.GetBoolValue("DEBUG", "DisplayInfo", false);
	LogCar = settingsGeneral.GetBoolValue("DEBUG", "LogCar", false);

	// [FILEVERSION]
	settings_general_version = settingsGeneral.GetValue("FILEVERSION", "VERSION", "000");
#pragma warning(pop)

}
#ifdef GAME_BUILD
void ScriptSettings::parseSettingsMenu(NativeMenu::MenuControls *menuControl, NativeMenu::Menu *menuOpts) {
	CSimpleIniA settingsMenu;
	settingsMenu.SetUnicode();
	settingsMenu.LoadFile(settingsMenuFile.c_str());

	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuKey] = str2key(settingsMenu.GetValue("MENU", "MenuKey", "VK_OEM_4"));
	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuUp] = str2key(settingsMenu.GetValue("MENU", "MenuUp", "UP"));
	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuDown] = str2key(settingsMenu.GetValue("MENU", "MenuDown", "DOWN"));
	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuLeft] = str2key(settingsMenu.GetValue("MENU", "MenuLeft", "LEFT"));
	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuRight] = str2key(settingsMenu.GetValue("MENU", "MenuRight", "RIGHT"));
	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuSelect] = str2key(settingsMenu.GetValue("MENU", "MenuSelect", "RETURN"));
	menuControl->ControlKeys[NativeMenu::MenuControls::ControlType::MenuCancel] = str2key(settingsMenu.GetValue("MENU", "MenuCancel", "BACKSPACE"));

	menuControl->ControllerButton1 = settingsMenu.GetLongValue("MENU", "ControllerButton1", -1);
	menuControl->ControllerButton2 = settingsMenu.GetLongValue("MENU", "ControllerButton2", -1);

#pragma warning(push)
#pragma warning(disable: 4244)
	menuOpts->menux = settingsMenu.GetDoubleValue("MENU", "MenuX", 0.2);
	menuOpts->menuy = settingsMenu.GetDoubleValue("MENU", "MenuY", 0.125);
#pragma warning(pop)

}
#endif

void ScriptSettings::parseSettingsWheel(ScriptControls *scriptControl) {
#pragma warning(push)
#pragma warning(disable: 4244) // Make everything doubles later...
	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());

	// [OPTIONS]
	EnableWheel = settingsWheel.GetBoolValue("OPTIONS", "EnableWheel", false);
	WheelWithoutManual = settingsWheel.GetBoolValue("OPTIONS", "WheelWithoutManual", true);
	AltControls = settingsWheel.GetBoolValue("OPTIONS", "WheelBoatPlanes", false);
	PatchSteering = settingsWheel.GetBoolValue("OPTIONS", "PatchSteering", false);
	PatchSteeringAlways = settingsWheel.GetBoolValue("OPTIONS", "PatchSteeringAlways", false);
	LogiLEDs = settingsWheel.GetBoolValue("OPTIONS", "LogitechLEDs", false);

	scriptControl->InvertSteer =	settingsWheel.GetBoolValue("OPTIONS", "InvertSteer", false);
	scriptControl->InvertThrottle = settingsWheel.GetBoolValue("OPTIONS", "InvertThrottle", false);
	scriptControl->InvertBrake =	settingsWheel.GetBoolValue("OPTIONS", "InvertBrake", false);
	scriptControl->InvertClutch =	settingsWheel.GetBoolValue("OPTIONS", "InvertClutch", false);

	// [FORCE_FEEDBACK]
	EnableFFB = settingsWheel.GetBoolValue("FORCE_FEEDBACK", "FFEnable", true);
	FFGlobalMult = settingsWheel.GetDoubleValue("FORCE_FEEDBACK", "FFGlobalMult", 1.0);
	DamperMax = settingsWheel.GetLongValue("FORCE_FEEDBACK", "DamperMax", 50);
	DamperMin = settingsWheel.GetLongValue("FORCE_FEEDBACK", "DamperMin", 20);
	TargetSpeed = settingsWheel.GetDoubleValue("FORCE_FEEDBACK", "DamperTargetSpeed", 1.0);
	PhysicsStrength = settingsWheel.GetDoubleValue("FORCE_FEEDBACK", "PhysicsStrength", 1.0);
	DetailStrength = settingsWheel.GetDoubleValue("FORCE_FEEDBACK", "DetailStrength", 1.0);


	// The DEVICE in the following sections should only be read by the directinput control parts
	// I'll need to write a program that fills these or at least configures this part of the file
	// idk somebody buy me a fancy fanatec set of stuff so i can pretend to care
	// i need a handbrake
	// santa pls

	// [INPUT_DEVICES]
	int it = 0;
	reggdGuids.clear();
	while (true) {
		std::string currDevIndex = std::string("DEV") + std::to_string(it);
		std::string currGuidIndex = std::string("GUID") + std::to_string(it);

		std::string currDevice = settingsWheel.GetValue("INPUT_DEVICES", currDevIndex.c_str(), "");
		if (currDevice == "")
			break;
		std::string currGuid = settingsWheel.GetValue("INPUT_DEVICES", currGuidIndex.c_str(), "");
		if (currGuid == "")
			break;

		std::wstring clsidStr;
		clsidStr.assign(currGuid.begin(), currGuid.end());
		GUID guid;
		HRESULT hr = CLSIDFromString(clsidStr.c_str(), &guid);
		if (hr != NOERROR) {
			std::string errStr;
			switch (hr) {
				case CO_E_CLASSSTRING:
					errStr = "The class string was improperly formatted.";
					break;
				case REGDB_E_CLASSNOTREG:
					errStr = "The CLSID corresponding to the class string was not found in the registry.";
					break;
				case REGDB_E_READREGDB:
					errStr = "The registry could not be opened for reading.";
					break;
				default:
					errStr = "Something went terribly wrong.";
					break;
			}
			logger.Write("CLSIDFromString error: " + errStr);
		}
		reggdGuids.push_back(guid);		
		it++;
	}
	nDevices = it;

	// [TOGGLE_MOD]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Toggle)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("TOGGLE_MOD", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Toggle)] =
		settingsWheel.GetLongValue("TOGGLE_MOD", "BUTTON", -1);

	// [CHANGE_SHIFTMODE]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::ToggleH)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("CHANGE_SHIFTMODE", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::ToggleH)] =
		settingsWheel.GetLongValue("CHANGE_SHIFTMODE", "BUTTON", -1);


	// [STEER]
	scriptControl->WheelAxesGUIDs[static_cast<int>(ScriptControls::WheelAxisType::Steer)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("STEER", "DEVICE", -1), reggdGuids);
	scriptControl->WheelAxes[static_cast<int>(ScriptControls::WheelAxisType::Steer)] =
		settingsWheel.GetValue("STEER", "AXLE", "");
	scriptControl->WheelAxes[static_cast<int>(ScriptControls::WheelAxisType::ForceFeedback)] =
		settingsWheel.GetValue("STEER", "FFB", "");
	scriptControl->SteerLeft = settingsWheel.GetLongValue("STEER", "MIN", -1);
	scriptControl->SteerRight = settingsWheel.GetLongValue("STEER", "MAX", -1);
	SteerAngleMax = settingsWheel.GetDoubleValue("STEER", "SteerAngleMax", 900.0);
	SteerAngleCar = settingsWheel.GetDoubleValue("STEER", "SteerAngleCar", 720.0);
	SteerAngleBike = settingsWheel.GetDoubleValue("STEER", "SteerAngleBike", 180.0);
	SteerAngleAlt = settingsWheel.GetDoubleValue("STEER", "SteerAngleAlt", 180.0);
	GameSteerMult = settingsWheel.GetDoubleValue("STEER", "GameSteerMult", 1.0);

	// [THROTTLE]
	scriptControl->WheelAxesGUIDs[static_cast<int>(ScriptControls::WheelAxisType::Throttle)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("THROTTLE", "DEVICE", -1), reggdGuids);
	scriptControl->WheelAxes[static_cast<int>(ScriptControls::WheelAxisType::Throttle)] =
		settingsWheel.GetValue("THROTTLE", "AXLE", "");
	scriptControl->ThrottleUp = settingsWheel.GetLongValue("THROTTLE", "MIN", -1);
	scriptControl->ThrottleDown = settingsWheel.GetLongValue("THROTTLE", "MAX", -1);

	// [BRAKES]
	scriptControl->WheelAxesGUIDs[static_cast<int>(ScriptControls::WheelAxisType::Brake)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("BRAKES", "DEVICE", -1), reggdGuids);
	scriptControl->WheelAxes[static_cast<int>(ScriptControls::WheelAxisType::Brake)] =
		settingsWheel.GetValue("BRAKES", "AXLE", "");
	scriptControl->BrakeUp = settingsWheel.GetLongValue("BRAKES", "MIN", -1);
	scriptControl->BrakeDown = settingsWheel.GetLongValue("BRAKES", "MAX", -1);

	// [CLUTCH]
	scriptControl->WheelAxesGUIDs[static_cast<int>(ScriptControls::WheelAxisType::Clutch)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("CLUTCH", "DEVICE", -1), reggdGuids);
	scriptControl->WheelAxes[static_cast<int>(ScriptControls::WheelAxisType::Clutch)] =
		settingsWheel.GetValue("CLUTCH", "AXLE", "");
	scriptControl->ClutchUp = settingsWheel.GetLongValue("CLUTCH", "MIN", -1);
	scriptControl->ClutchDown = settingsWheel.GetLongValue("CLUTCH", "MAX", -1);

	// [HANDBRAKE_ANALOG]
	scriptControl->WheelAxesGUIDs[static_cast<int>(ScriptControls::WheelAxisType::Handbrake)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("HANDBRAKE_ANALOG", "DEVICE", -1), reggdGuids);
	scriptControl->WheelAxes[static_cast<int>(ScriptControls::WheelAxisType::Handbrake)] =
		settingsWheel.GetValue("HANDBRAKE_ANALOG", "AXLE", "");
	scriptControl->HandbrakeDown = settingsWheel.GetLongValue("HANDBRAKE_ANALOG", "MIN", -1);
	scriptControl->HandbrakeUp = settingsWheel.GetLongValue("HANDBRAKE_ANALOG", "MAX", -1);

	// [SHIFTER]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H1)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H2)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H3)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H4)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H5)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H6)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::H7)] =
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::HR)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("SHIFTER", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H1)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_1", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H2)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_2", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H3)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_3", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H4)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_4", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H5)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_5", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H6)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_6", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::H7)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_7", -1);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::HR)] =
		settingsWheel.GetLongValue("SHIFTER", "GEAR_R", -1);

	// [CLUTCH_BUTTON]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Clutch)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("CLUTCH_BUTTON", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Clutch)] =
		settingsWheel.GetLongValue("CLUTCH_BUTTON", "BUTTON", -1);

	// [SHIFT_UP]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::ShiftUp)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("SHIFT_UP", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::ShiftUp)] =
		settingsWheel.GetLongValue("SHIFT_UP", "BUTTON", -1);

	// [SHIFT_DOWN]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::ShiftDown)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("SHIFT_DOWN", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::ShiftDown)] =
		settingsWheel.GetLongValue("SHIFT_DOWN", "BUTTON", -1);

	// [HANDBRAKE]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Handbrake)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("HANDBRAKE", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Handbrake)] =
		settingsWheel.GetLongValue("HANDBRAKE", "BUTTON", -1);

	// [ENGINE]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Engine)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("ENGINE", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Engine)] =
		settingsWheel.GetLongValue("ENGINE", "BUTTON", -1);

	// [LIGHTS]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Lights)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("LIGHTS", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Lights)] =
		settingsWheel.GetLongValue("LIGHTS", "BUTTON", -1);

	// [HORN]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Horn)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("HORN", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Horn)] =
		settingsWheel.GetLongValue("HORN", "BUTTON", -1);

	// [LOOK_BACK]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::LookBack)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("LOOK_BACK", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::LookBack)] =
		settingsWheel.GetLongValue("LOOK_BACK", "BUTTON", -1);
	
	// [LOOK_LEFT]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::LookLeft)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("LOOK_LEFT", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::LookLeft)] =
		settingsWheel.GetLongValue("LOOK_LEFT", "BUTTON", -1);
	
	// [LOOK_RIGHT]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::LookRight)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("LOOK_RIGHT", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::LookRight)] =
		settingsWheel.GetLongValue("LOOK_RIGHT", "BUTTON", -1);

	// [CHANGE_CAMERA]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::Camera)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("CHANGE_CAMERA", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::Camera)] =
		settingsWheel.GetLongValue("CHANGE_CAMERA", "BUTTON", -1);

	// [RADIO_NEXT]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::RadioNext)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("RADIO_NEXT", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::RadioNext)] =
		settingsWheel.GetLongValue("RADIO_NEXT", "BUTTON", -1);

	// [RADIO_PREVIOUS]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::RadioPrev)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("RADIO_PREVIOUS", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::RadioPrev)] =
		settingsWheel.GetLongValue("RADIO_PREVIOUS", "BUTTON", -1);

	// [INDICATOR_LEFT]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::IndicatorLeft)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("INDICATOR_LEFT", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::IndicatorLeft)] =
		settingsWheel.GetLongValue("INDICATOR_LEFT", "BUTTON", -1);

	// [INDICATOR_RIGHT]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::IndicatorRight)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("INDICATOR_RIGHT", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::IndicatorRight)] =
		settingsWheel.GetLongValue("INDICATOR_RIGHT", "BUTTON", -1);

	// [INDICATOR_HAZARD]
	scriptControl->WheelButtonGUIDs[static_cast<int>(ScriptControls::WheelControlType::IndicatorHazard)] =
		DeviceIndexToGUID(settingsWheel.GetLongValue("INDICATOR_HAZARD", "DEVICE", -1), reggdGuids);
	scriptControl->WheelButton[static_cast<int>(ScriptControls::WheelControlType::IndicatorHazard)] =
		settingsWheel.GetLongValue("INDICATOR_HAZARD", "BUTTON", -1);
	
	// [TO_KEYBOARD]
	scriptControl->WheelToKeyGUID = 
		DeviceIndexToGUID(settingsWheel.GetLongValue("TO_KEYBOARD", "DEVICE", -1), reggdGuids);
	for (int i = 0; i < MAX_RGBBUTTONS; i++) { // Ouch
		std::string entryString = settingsWheel.GetValue("TO_KEYBOARD", std::to_string(i).c_str(), "UNKNOWN");
		if (std::string(entryString).compare("UNKNOWN") == 0) {
			scriptControl->WheelToKey[i] = -1;
		}
		else {
			scriptControl->WheelToKey[i] = str2key(entryString);
		}
	}

	// [FILEVERSION]
	settings_wheel_version = settingsWheel.GetValue("FILEVERSION", "VERSION", "000");
#pragma warning(pop)

}

ptrdiff_t ScriptSettings::SteeringAppendDevice(const GUID &dev_guid, std::string dev_name) {
	auto found = find(reggdGuids.begin(), reggdGuids.end(), dev_guid);
	if (found != reggdGuids.end()) {
		// present! Return index
		// Dependent on implementation of reading this but it should work(TM). Lotsa assumptions.
		return distance(reggdGuids.begin(), found);
	}
	// missing! Add & return index afterwards
	auto newIndex = distance(reggdGuids.begin(), reggdGuids.end());
	std::string newDEV = "DEV" + std::to_string(newIndex);
	std::string newGUID = "GUID" + std::to_string(newIndex);


	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());
	settingsWheel.SetValue("INPUT_DEVICES", newDEV.c_str(), dev_name.c_str());
	settingsWheel.SetValue("INPUT_DEVICES", newGUID.c_str(), GUID2String(dev_guid).c_str());
	int err = settingsWheel.SaveFile(settingsWheelFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsWheelFile);
	return newIndex;
}
void ScriptSettings::SteeringSaveAxis(const std::string &confTag, ptrdiff_t index, const std::string & axis, int minVal, int maxVal) {
	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());
	settingsWheel.SetValue(confTag.c_str(), "DEVICE", std::to_string(index).c_str());
	settingsWheel.SetValue(confTag.c_str(), "AXLE", axis.c_str());
	settingsWheel.SetValue(confTag.c_str(), "MIN", std::to_string(minVal).c_str());
	settingsWheel.SetValue(confTag.c_str(), "MAX", std::to_string(maxVal).c_str());
	int err = settingsWheel.SaveFile(settingsWheelFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsWheelFile);
}

void ScriptSettings::SteeringSaveFFBAxis(const std::string & confTag, ptrdiff_t index, const std::string & axis) {
	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());
	settingsWheel.SetValue(confTag.c_str(), "DEVICE", std::to_string(index).c_str());
	settingsWheel.SetValue(confTag.c_str(), "FFB", axis.c_str());
	int err = settingsWheel.SaveFile(settingsWheelFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsWheelFile);
}

void ScriptSettings::SteeringSaveButton(const std::string & confTag, ptrdiff_t index, int button) {
	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());
	settingsWheel.SetValue(confTag.c_str(), "DEVICE", std::to_string(index).c_str());
	settingsWheel.SetLongValue(confTag.c_str(), "BUTTON", button);
	int err = settingsWheel.SaveFile(settingsWheelFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsWheelFile);
}

void ScriptSettings::SteeringSaveHShifter(const std::string & confTag, ptrdiff_t index, int button[numGears]) {
	CSimpleIniA settingsWheel;
	settingsWheel.SetUnicode();
	settingsWheel.LoadFile(settingsWheelFile.c_str());
	settingsWheel.SetValue(confTag.c_str(), "DEVICE", std::to_string(index).c_str());
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_R", button[0]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_1", button[1]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_2", button[2]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_3", button[3]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_4", button[4]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_5", button[5]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_6", button[6]);
	settingsWheel.SetLongValue(confTag.c_str(), "GEAR_7", button[7]);
	int err = settingsWheel.SaveFile(settingsWheelFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsWheelFile);
}

void ScriptSettings::KeyboardSaveKey(const std::string &confTag, const std::string &key) {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	settingsGeneral.SetValue("KEYBOARD", confTag.c_str(), key.c_str());
	int err = settingsGeneral.SaveFile(settingsGeneralFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsGeneralFile);
}
void ScriptSettings::ControllerSaveButton(const std::string &confTag, const std::string &button) {
	CSimpleIniA settingsGeneral;
	settingsGeneral.SetUnicode();
	settingsGeneral.LoadFile(settingsGeneralFile.c_str());
	settingsGeneral.SetValue("CONTROLLER", confTag.c_str(), button.c_str());
	int err = settingsGeneral.SaveFile(settingsGeneralFile.c_str());
	if (err < 0)
		logger.Write("Unable to save to " + settingsGeneralFile);
}

GUID ScriptSettings::DeviceIndexToGUID(int device, std::vector<GUID> guids) {
	if (device < 0) {
		return{};
	}
	if (device > nDevices - 1) {
		return{};
	}
	return guids[device];
}
