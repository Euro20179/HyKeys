#define WLR_USE_UNSTABLE

#include <unordered_map>
#include <format>

#include <hyprland/src/managers/EventManager.hpp>
#include <hyprland/src/managers/input/InputManager.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>

#include "globals.hpp"

void onKeypress(void *self, std::any data) {
  auto map = std::any_cast<std::unordered_map<std::string, std::any>>(data);
  std::any k = map["keyboard"];
  wlr_keyboard_key_event *e =
      std::any_cast<wlr_keyboard_key_event *>(map["event"]);
  SKeyboard *keyboard = std::any_cast<SKeyboard *>(k);

  const auto MODS = g_pInputManager->accumulateModsFromAllKBs();
  const auto STATE = e->state == WL_KEYBOARD_KEY_STATE_PRESSED ? "down" : "up";
  const auto KEY = "";
  const auto KEYCODE = e->keycode + 8;

  g_pEventManager->postEvent(SHyprIPCEvent{
          "keypress", std::format("{},{},{},{},{}", keyboard->name , MODS, STATE, KEY, KEYCODE)
  });

  if (keyboard->name == "by-tech-usb-gaming-keyboard") {
      /* system("notify-send hi"); */
  }
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
  PHANDLE = handle;
  if (!HyprlandAPI::registerCallbackDynamic(
          PHANDLE, "keyPress",
          [&](void *self, SCallbackInfo &info, std::any data) {
            onKeypress(self, data);
          })) {
    HyprlandAPI::addNotification(PHANDLE, "Failed to add handler",
                                 CColor{0.0, 1.0, 1.0, 1.0}, 5000);
  }
  return {"hykeys", "Sends keypress events to hyprland IPC socket\nThis allows for per keyboard bindings", "Euro", "0.1"};
}

APICALL EXPORT std::string PLUGIN_API_VERSION() { return HYPRLAND_API_VERSION; }

APICALL EXPORT void PLUGIN_EXIT() {}
