#pragma once
#include <string>
#include <utility>

#include "XInputController.hpp"
#include "WheelDirectInput.hpp"
#include "NativeController.h"

struct Device {
    Device(std::string name, GUID guid)
        : name(std::move(name)), guid(guid) {}
    std::string name;
    GUID guid;
};

class CarControls {
public:
    enum class ControllerControlType {
        ShiftUp,
        ShiftDown,
        Clutch,
        Throttle,
        Brake,
        Toggle,
        ToggleH,
        Engine,
        SwitchAssist,
        SIZEOF_ControllerControlType
    };

    enum class LegacyControlType {
        ShiftUp,
        ShiftDown,
        Clutch,
        Throttle,
        Brake,
        Toggle,
        ToggleH,
        Engine,
        SwitchAssist,
        SIZEOF_LegacyControlType
    };

    enum class KeyboardControlType : uint32_t {
        HR = 0,
        H1 = 1,
        H2 = 2,
        H3 = 3,
        H4 = 4,
        H5 = 5,
        H6 = 6,
        H7 = 7,
        H8 = 8,
        H9 = 9,
        H10 = 10,
        HN,
        ShiftUp,
        ShiftDown,
        Clutch,
        Throttle,
        Brake,
        Engine,
        Toggle,
        ToggleH,
        SwitchAssist,
        SIZEOF_KeyboardControlType
    };

    enum class WheelControlType : uint32_t {
        HR = 0,
        H1 = 1,
        H2 = 2,
        H3 = 3,
        H4 = 4,
        H5 = 5,
        H6 = 6,
        H7 = 7,
        H8 = 8,
        H9 = 9,
        H10 = 10,
        HN,
        ShiftUp,
        ShiftDown,
        Clutch,
        Throttle,
        Brake,
        Engine,
        Toggle,
        ToggleH,
        Handbrake,
        Horn,
        Lights,
        LookBack,
        LookLeft,
        LookRight,
        Camera,
        RadioPrev,
        RadioNext,
        IndicatorLeft,
        IndicatorRight,
        IndicatorHazard,
        APark,
        AReverse,
        ANeutral,
        ADrive,
        SwitchAssist,
        UNKNOWN,
        SIZEOF_WheelControlType
    };

    enum class WheelAxisType {
        Throttle,
        Brake,
        Clutch,
        Steer,
        Handbrake,
        ForceFeedback,
        SIZEOF_WheelAxisType
    };

    enum InputDevices {
        Keyboard = 0,
        Controller = 1,
        Wheel = 2
    };

    const std::vector<std::pair<std::string, int>> LegacyControlsMap = {
        { "ControlFrontendDown",		187 },
        { "ControlFrontendUp",			188 },
        { "ControlFrontendLeft",		189 },
        { "ControlFrontendRight",		190 },
        { "ControlFrontendRdown",		191 },
        { "ControlFrontendRup",			192 },
        { "ControlFrontendRleft",		193 },
        { "ControlFrontendRright",		194 },
        { "ControlFrontendAxisX",		195 },
        { "ControlFrontendAxisY",		196 },
        { "ControlFrontendRightAxisX",	197 },
        { "ControlFrontendRightAxisY",	198 },
        { "ControlFrontendPause",		199 },
        { "ControlFrontendAccept",		201 },
        { "ControlFrontendCancel",		202 },
        { "ControlFrontendX",			203 },
        { "ControlFrontendY",			204 },
        { "ControlFrontendLb",			205 },
        { "ControlFrontendRb",			206 },
        { "ControlFrontendLt",			207 },
        { "ControlFrontendRt",			208 },
        { "ControlFrontendLs",			209 },
        { "ControlFrontendRs",			210 },
        { "ControlFrontendDelete",		214 },
        { "ControlFrontendSelect",		217 },
    };

    CarControls();
    ~CarControls();

    void InitWheel();
    void InitFFB();
    void updateKeyboard();
    void updateController();
    float getInputValue(WheelAxisType axisType, WheelControlType buttonType, float minRaw, float maxRaw);
    float filterDeadzone(float input, float deadzone, float deadzoneOffset);
    void updateWheel();
    void UpdateValues(InputDevices prevInput, bool skipKeyboardInput);
    InputDevices GetLastInputDevice(InputDevices previousInput, bool enableWheel = true);

    // Keyboard controls	
    bool ButtonJustPressed(KeyboardControlType control);
    bool IsKeyPressed(int key);
    bool IsKeyJustPressed(int key, KeyboardControlType control);

    // Controller controls
    bool ButtonJustPressed(ControllerControlType control);
    bool ButtonReleased(ControllerControlType control);
    bool ButtonReleasedAfter(ControllerControlType control, int time);
    bool ButtonHeld(ControllerControlType control);
    bool ButtonHeldOver(ControllerControlType control, int millis);
    XInputController::TapState ButtonTapped(ControllerControlType control);
    bool ButtonIn(ControllerControlType control);

    bool ButtonJustPressed(LegacyControlType control);
    bool ButtonReleased(LegacyControlType control);
    bool ButtonHeld(LegacyControlType control);
    bool ButtonHeldOver(LegacyControlType control, int millis);
    bool ButtonIn(LegacyControlType control);
    NativeController::TapState ButtonTapped(LegacyControlType control);
    bool ButtonReleasedAfter(LegacyControlType control, int time);

    // Wheel controls
    bool ButtonJustPressed(WheelControlType control);
    bool ButtonReleased(WheelControlType control);
    bool ButtonHeld(WheelControlType control, int delay);
    bool ButtonIn(WheelControlType control);
    void CheckCustomButtons();

    void CheckGUIDs(const std::vector<_GUID> &guids);
    void PlayFFBDynamics(int totalForce, int damperForce);
    void PlayFFBCollision(int collisionForce);
    void PlayLEDs(float rpm, float firstLed, float lastLed);
    float GetAxisSpeed(WheelAxisType axis);
    bool WheelAvailable();
    WheelDirectInput& GetWheel();

    InputDevices PrevInput = Controller;

    float ThrottleVal = 0.0f;
    float BrakeVal = 0.0f;
    float ClutchVal = 0.0f; 	// 1 = Pressed, 0 = Not pressed
    float SteerVal = 0.5f;
    float SteerValRaw = 0.0f;   // For readout purposes. SteerVal is used for gameplay.
    float HandbrakeVal = 0.0f;

    //int ThrottleMin = 0;
    //int ThrottleMax = 0;
    //int BrakeMin = 0;
    //int BrakeMax = 0;
    //int ClutchMin = 0;
    //int ClutchMax = 0;
    //int SteerMin = 0;
    //int SteerMax = 0;
    //int HandbrakeMax = 0;
    //int HandbrakeMin = 0;

    std::array<std::string, static_cast<int>(ControllerControlType::SIZEOF_ControllerControlType)> ControlXbox = {};
    std::array<int, static_cast<int>(ControllerControlType::SIZEOF_ControllerControlType)> ControlXboxBlocks = {};

    std::array<int, static_cast<int>(LegacyControlType::SIZEOF_LegacyControlType)> LegacyControls = {};
    std::array<int, static_cast<int>(LegacyControlType::SIZEOF_LegacyControlType)> ControlNativeBlocks = {};

    std::array<int, static_cast<int>(KeyboardControlType::SIZEOF_KeyboardControlType)> KBControl = {};
    
    std::array<std::string, static_cast<int>(WheelAxisType::SIZEOF_WheelAxisType)> WheelAxes = {};
    std::array<GUID, static_cast<int>(WheelAxisType::SIZEOF_WheelAxisType)> WheelAxesGUIDs = {};
    std::array<int, static_cast<int>(WheelControlType::SIZEOF_WheelControlType)> WheelButton = {};
    std::array<GUID, static_cast<int>(WheelControlType::SIZEOF_WheelControlType)> WheelButtonGUIDs = {};
    std::array<int, MAX_RGBBUTTONS> WheelToKey = {};

    GUID WheelToKeyGUID = {};

    std::vector<Device> FreeDevices{};

    XInputController& GetController() {
        return mXInputController;
    }

    int ConfTagKB2key(const std::string &confTag) {
        if (confTag == "Toggle") return KBControl[static_cast<int>(KeyboardControlType::Toggle)];
        if (confTag == "ToggleH") return KBControl[static_cast<int>(KeyboardControlType::ToggleH)];
        if (confTag == "ShiftUp") return KBControl[static_cast<int>(KeyboardControlType::ShiftUp)];
        if (confTag == "ShiftDown") return KBControl[static_cast<int>(KeyboardControlType::ShiftDown)];
        if (confTag == "Clutch") return KBControl[static_cast<int>(KeyboardControlType::Clutch)];
        if (confTag == "Engine") return KBControl[static_cast<int>(KeyboardControlType::Engine)];
        if (confTag == "Throttle") return KBControl[static_cast<int>(KeyboardControlType::Throttle)];
        if (confTag == "Brake") return KBControl[static_cast<int>(KeyboardControlType::Brake)];
        if (confTag == "HR") return KBControl[static_cast<int>(KeyboardControlType::HR)];
        if (confTag == "H1") return KBControl[static_cast<int>(KeyboardControlType::H1)];
        if (confTag == "H2") return KBControl[static_cast<int>(KeyboardControlType::H2)];
        if (confTag == "H3") return KBControl[static_cast<int>(KeyboardControlType::H3)];
        if (confTag == "H4") return KBControl[static_cast<int>(KeyboardControlType::H4)];
        if (confTag == "H5") return KBControl[static_cast<int>(KeyboardControlType::H5)];
        if (confTag == "H6") return KBControl[static_cast<int>(KeyboardControlType::H6)];
        if (confTag == "H7") return KBControl[static_cast<int>(KeyboardControlType::H7)];
        if (confTag == "H8") return KBControl[static_cast<int>(KeyboardControlType::H8)];
        if (confTag == "H9") return KBControl[static_cast<int>(KeyboardControlType::H9)];
        if (confTag == "H10") return KBControl[static_cast<int>(KeyboardControlType::H10)];
        if (confTag == "HN") return KBControl[static_cast<int>(KeyboardControlType::HN)];
        if (confTag == "SwitchAssist") return KBControl[static_cast<int>(KeyboardControlType::SwitchAssist)];
        return -1;
    }

    std::string ConfTagController2Value(const std::string &confTag) {
        if (confTag == "Toggle") return ControlXbox[static_cast<int>(ControllerControlType::Toggle)];
        if (confTag == "ToggleShift") return ControlXbox[static_cast<int>(ControllerControlType::ToggleH)];
        if (confTag == "ShiftUp") return ControlXbox[static_cast<int>(ControllerControlType::ShiftUp)];
        if (confTag == "ShiftDown") return ControlXbox[static_cast<int>(ControllerControlType::ShiftDown)];
        if (confTag == "Clutch") return ControlXbox[static_cast<int>(ControllerControlType::Clutch)];
        if (confTag == "Engine") return ControlXbox[static_cast<int>(ControllerControlType::Engine)];
        if (confTag == "Throttle") return ControlXbox[static_cast<int>(ControllerControlType::Throttle)];
        if (confTag == "Brake") return ControlXbox[static_cast<int>(ControllerControlType::Brake)];
        if (confTag == "SwitchAssist") return ControlXbox[static_cast<int>(ControllerControlType::SwitchAssist)];

        return "UNKNOWN";
    }

    int ConfTagLController2Value(const std::string &confTag) {
        if (confTag == "Toggle")		return LegacyControls[static_cast<int>(LegacyControlType::Toggle)];
        if (confTag == "ToggleShift")	return LegacyControls[static_cast<int>(LegacyControlType::ToggleH)];
        if (confTag == "ShiftUp")		return LegacyControls[static_cast<int>(LegacyControlType::ShiftUp)];
        if (confTag == "ShiftDown")		return LegacyControls[static_cast<int>(LegacyControlType::ShiftDown)];
        if (confTag == "Clutch")		return LegacyControls[static_cast<int>(LegacyControlType::Clutch)];
        if (confTag == "Engine")		return LegacyControls[static_cast<int>(LegacyControlType::Engine)];
        if (confTag == "Throttle")		return LegacyControls[static_cast<int>(LegacyControlType::Throttle)];
        if (confTag == "Brake")			return LegacyControls[static_cast<int>(LegacyControlType::Brake)];
        if (confTag == "SwitchAssist")	return LegacyControls[static_cast<int>(LegacyControlType::SwitchAssist)];

        return -1;
    }

    std::string NativeControl2Text(int nativeControl) const {
        for (const auto& mapItem : LegacyControlsMap) {
            if (mapItem.second == nativeControl) {
                return mapItem.first;
            }
        }
        return std::to_string(nativeControl);
    }

    int ConfTagWheel2Value(const std::string &confTag) {
        if (confTag == "TOGGLE_MOD"			) return WheelButton[static_cast<int>(WheelControlType::Toggle)];
        if (confTag == "CHANGE_SHIFTMODE"	) return WheelButton[static_cast<int>(WheelControlType::ToggleH)];
        if (confTag == "THROTTLE_BUTTON") return WheelButton[static_cast<int>(WheelControlType::Throttle)];
        if (confTag == "BRAKE_BUTTON") return WheelButton[static_cast<int>(WheelControlType::Brake)];
        if (confTag == "CLUTCH_BUTTON"		) return WheelButton[static_cast<int>(WheelControlType::Clutch)];
        if (confTag == "SHIFT_UP"			) return WheelButton[static_cast<int>(WheelControlType::ShiftUp)];
        if (confTag == "SHIFT_DOWN"			) return WheelButton[static_cast<int>(WheelControlType::ShiftDown)];
        if (confTag == "ENGINE"				) return WheelButton[static_cast<int>(WheelControlType::Engine)];
        if (confTag == "HANDBRAKE"			) return WheelButton[static_cast<int>(WheelControlType::Handbrake)];
        if (confTag == "HORN"				) return WheelButton[static_cast<int>(WheelControlType::Horn)];
        if (confTag == "LIGHTS"				) return WheelButton[static_cast<int>(WheelControlType::Lights)];
        if (confTag == "LOOK_BACK"			) return WheelButton[static_cast<int>(WheelControlType::LookBack)];
        if (confTag == "LOOK_LEFT"			) return WheelButton[static_cast<int>(WheelControlType::LookLeft)];
        if (confTag == "LOOK_RIGHT"			) return WheelButton[static_cast<int>(WheelControlType::LookRight)];
        if (confTag == "CHANGE_CAMERA"		) return WheelButton[static_cast<int>(WheelControlType::Camera)];
        if (confTag == "RADIO_NEXT"			) return WheelButton[static_cast<int>(WheelControlType::RadioNext)];
        if (confTag == "RADIO_PREVIOUS"		) return WheelButton[static_cast<int>(WheelControlType::RadioPrev)];
        if (confTag == "INDICATOR_LEFT"		) return WheelButton[static_cast<int>(WheelControlType::IndicatorLeft)];
        if (confTag == "INDICATOR_RIGHT"	) return WheelButton[static_cast<int>(WheelControlType::IndicatorRight)];
        if (confTag == "INDICATOR_HAZARD") return WheelButton[static_cast<int>(WheelControlType::IndicatorHazard)];
        if (confTag == "SWITCH_ASSIST") return WheelButton[static_cast<int>(WheelControlType::SwitchAssist)];

        return -1;
    }

private:
    WheelDirectInput mWheelInput;
    NativeController mNativeController;
    XInputController mXInputController;

    bool KBControlCurr[static_cast<int>(KeyboardControlType::SIZEOF_KeyboardControlType)] = {};
    bool KBControlPrev[static_cast<int>(KeyboardControlType::SIZEOF_KeyboardControlType)] = {};
};
