#include "pch-il2cpp.h"
#include "SettingsModule.h"

#include <imgui.h>

#include <helpers.h>
#include <il2cpp-appdata.h>
#include <common/Config.h>
#include <common/Logger.h>
#include <gui/gui-util.h>

void SettingsModule::Draw()
{
    BeginGroupPanel("Common", ImVec2(-1, 0));
    {
        ConfigWidget(Config::cfgDisableMhyprot,
            "Closing handle of mhyprot2.sys driver. (Changes will take effect after next launch)\n" \
            "It allows reading / writing process memory from another process.\n" \
            "For example, this allows Cheat engine read process.");

        ConfigWidget(Config::cfgMenuShowKey, false,
            "Key to toggle this menu visibility. Cannot be empty.\nIf you forget this key, you can see it in config file.");
    }
    EndGroupPanel();
    
    BeginGroupPanel("Logging", ImVec2(-1, 0));
    {
        bool consoleChanged = ConfigWidget(Config::cfgConsoleLogEnabled,
            "Enable console for logging information. (Enabling will take effect after next launch)");
        if (consoleChanged && !Config::cfgConsoleLogEnabled.GetValue()) {
            il2cppi_close_console();
            Logger::SetLevel(Logger::Level::None, Logger::LoggerType::ConsoleLogger);
        }

        bool fileLogging = ConfigWidget(Config::cfgFileLogEnabled,
            "Enable file logging. (Enabling will take effect after next launch)\n" \
            "That's mean that in cheat directory will be created folder which will be contain file with logs.");
        if (fileLogging && !Config::cfgFileLogEnabled.GetValue()) {
            Logger::SetLevel(Logger::Level::None, Logger::LoggerType::FileLogger);
        }
    }
    EndGroupPanel();


    BeginGroupPanel("Status window", ImVec2(-1, 0));
    {
        ConfigWidget(Config::cfgShowStatusWindow);
        ConfigWidget(Config::cfgMoveStatusWindow, "Give able to move 'Status' window.");
    }
    EndGroupPanel();

    BeginGroupPanel("Info window", ImVec2(-1, 0));
    {
        ConfigWidget(Config::cfgShowInfoWindow);
        ConfigWidget(Config::cfgMoveInfoWindow, "Give able to move 'Info' window.");
    }
    EndGroupPanel();
}

std::string SettingsModule::GetName()
{
	return "Settings";
}