#include <unordered_map>
#include <format>

#include <hyprland/src/managers/EventManager.hpp>
#include <hyprland/src/managers/input/InputManager.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/devices/IKeyboard.hpp>

#include "globals.hpp"

void onKeypress(void *self, std::any data) {
  auto map = std::any_cast<std::unordered_map<std::string, std::any>>(data);

  auto keyboard = std::any_cast<SP<IKeyboard>>(map["keyboard"]);
  auto e = std::any_cast<IKeyboard::SKeyEvent>( map["event"]);

  const auto MODS = g_pInputManager->accumulateModsFromAllKBs();
  const auto STATE = e.state == WL_KEYBOARD_KEY_STATE_PRESSED ? "down" : "up";
  const auto KEY = "";
  const auto KEYCODE = e.keycode + 8;

  g_pEventManager->postEvent(SHyprIPCEvent{
          "keypress", std::format("{},{},{},{},{}", keyboard->hlName, MODS, STATE, KEY, KEYCODE)
  });

  if (keyboard->hlName == "by-tech-usb-gaming-keyboard") {
      /* system("notify-send hi"); */
  }
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
  PHANDLE = handle;

  static auto P  = HyprlandAPI::registerCallbackDynamic(PHANDLE, "keyPress", [&](void* self, SCallbackInfo& info, std::any data) { onKeypress(self, data); });
  if (!P) {
    HyprlandAPI::addNotification(PHANDLE, "Failed to add handler",
                                 CColor{0.0, 1.0, 1.0, 1.0}, 5000);
  }
  return {"hykeys", "Sends keypress events to hyprland IPC socket\nThis allows for per keyboard bindings", "Euro", "0.1"};
}

APICALL EXPORT std::string PLUGIN_API_VERSION() { return HYPRLAND_API_VERSION; }

APICALL EXPORT void PLUGIN_EXIT() {}
