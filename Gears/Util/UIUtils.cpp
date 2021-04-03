#include "UIUtils.h"

#include "inc/natives.h"
#include "inc/enums.h"
#include "fmt/format.h"
#include <algorithm>

#include "../Constants.h"
#include "../ScriptSettings.hpp"

extern ScriptSettings g_settings;

namespace {
    const size_t maxStringLength = 99;
    int notificationHandle = 0;
}

void showNotification(const std::string& message, int* prevNotification) {
    if (prevNotification != nullptr && *prevNotification != 0) {
        HUD::THEFEED_REMOVE_ITEM(*prevNotification);
    }
    HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");

    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.c_str());

    int id = HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
    if (prevNotification != nullptr) {
        *prevNotification = id;
    }
}

float UI::GetStringWidth(const std::string& text, float scale, int font) {
    HUD::_BEGIN_TEXT_COMMAND_GET_WIDTH("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
    HUD::SET_TEXT_FONT(font);
    HUD::SET_TEXT_SCALE(scale, scale);
    return HUD::_END_TEXT_COMMAND_GET_WIDTH(true);
}

void UI::Notify(int level, const std::string& message) {
    Notify(level, message, true);
}

void UI::Notify(int level, const std::string& message, bool removePrevious) {
    if (level < g_settings.HUD.NotifyLevel)
        return;

    int* notifHandleAddr = nullptr;
    if (removePrevious) {
        notifHandleAddr = &notificationHandle;
    }
    showNotification(fmt::format("{}\n{}", Constants::NotificationPrefix, message), notifHandleAddr);
}

void UI::ShowText(float x, float y, float scale, const std::string &text,
    int font, const Util::ColorI &rgba, bool outline) {
    HUD::SET_TEXT_FONT(font);
    HUD::SET_TEXT_SCALE(scale, scale);
    HUD::SET_TEXT_COLOUR(rgba.R, rgba.G, rgba.B, rgba.A);
    HUD::SET_TEXT_WRAP(0.0, 1.0);
    HUD::SET_TEXT_CENTRE(0);
    if (outline) HUD::SET_TEXT_OUTLINE();
    HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
    HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
    HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 0);
}

void UI::ShowText3D(Vector3 location, const std::vector<std::string> &textLines,
    const Util::ColorI& backgroundColor, const Util::ColorI& fontColor) {
    float height = 0.0125f;

    GRAPHICS::SET_DRAW_ORIGIN(location.x, location.y, location.z, 0);
    int i = 0;

    float szX = 0.060f;
    for (const auto& line : textLines) {
        ShowText(0, 0 + height * static_cast<float>(i), 0.2f, line, 0, fontColor, true);
        float currWidth = UI::GetStringWidth(line, 0.2f, 0);
        if (currWidth > szX) {
            szX = currWidth;
        }
        i++;
    }

    float szY = (height * static_cast<float>(i)) + 0.02f;
    GRAPHICS::DRAW_RECT(0.027f, (height * static_cast<float>(i)) / 2.0f, szX, szY,
        backgroundColor.R, backgroundColor.G, backgroundColor.B, backgroundColor.A, 0);
    GRAPHICS::CLEAR_DRAW_ORIGIN();
}

void UI::ShowText3DColors(Vector3 location, const std::vector<std::pair<std::string, Util::ColorI>> &textLines,
    const Util::ColorI& backgroundColor) {
    float height = 0.0125f;

    GRAPHICS::SET_DRAW_ORIGIN(location.x, location.y, location.z, 0);
    int i = 0;

    float szX = 0.060f;
    for (const auto& line : textLines) {
        ShowText(0, 0 + height * static_cast<float>(i), 0.2f, line.first, 0, line.second, true);
        float currWidth = UI::GetStringWidth(line.first, 0.2f, 0);
        if (currWidth > szX) {
            szX = currWidth;
        }
        i++;
    }

    float szY = (height * static_cast<float>(i)) + 0.02f;
    GRAPHICS::DRAW_RECT(0.027f, (height * static_cast<float>(i)) / 2.0f, szX, szY,
        backgroundColor.R, backgroundColor.G, backgroundColor.B, backgroundColor.A, 0);
    GRAPHICS::CLEAR_DRAW_ORIGIN();
}

void UI::ShowSubtitle(const std::string &message, int duration) {
    HUD::BEGIN_TEXT_COMMAND_PRINT("CELL_EMAIL_BCON");

    for (size_t i = 0; i < message.size(); i += maxStringLength) {
        size_t npos = std::min(maxStringLength, static_cast<int>(message.size()) - i);
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.substr(i, npos).c_str());
    }

    HUD::END_TEXT_COMMAND_PRINT(duration, 1);
}

void UI::ShowHelpText(const std::string& message) {
    HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("CELL_EMAIL_BCON");

    for (size_t i = 0; i < message.size(); i += maxStringLength) {
        size_t npos = std::min(maxStringLength, static_cast<int>(message.size()) - i);
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(message.substr(i, npos).c_str());
    }

    HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, false, false, -1);
}

void UI::DrawSphere(Vector3 p, float scale, const Util::ColorI& c) {
    GRAPHICS::DRAW_MARKER(eMarkerType::MarkerTypeDebugSphere,
                          p.x, p.y, p.z,
                          0.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 0.0f,
                          scale, scale, scale,
                          c.R, c.G, c.B, c.A,
                          false, false, 2, false, nullptr, nullptr, false);
}

void UI::DrawLine(Vector3 a, Vector3 b, const Util::ColorI& c) {
    GRAPHICS::DRAW_LINE(a.x, a.y, a.z,
        b.x, b.y, b.z, c.R, c.G, c.B, c.A);
}

void UI::DrawBar(float x, float y, float width, float height, Util::ColorI fg, Util::ColorI bg, float value) {
    float bgpaddingx = 0.00f;
    float bgpaddingy = 0.01f;
    // background
    GRAPHICS::DRAW_RECT(x, y, width + bgpaddingx, height + bgpaddingy, bg.R, bg.G, bg.B, bg.A, 0);

    // rpm bar
    GRAPHICS::DRAW_RECT(x - width * 0.5f + value * width * 0.5f, y, width * value, height, fg.R, fg.G, fg.B, fg.A, 0);
}
