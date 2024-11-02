#include "Settings.h"

void Settings::Load()
{
    INFO("FTweaks @ Loading Settings...");

    CSimpleIniA ini;

    ini.SetUnicode();

    ini.LoadFile(INI_PATH.data());

    ReadSetting(ini, "Fixes", "bNordRaceStats", NordRaceStats);
    ReadSetting(ini, "Fixes", "bScaleMovementSpeed", ScaleMovementSpeed);

    ReadSetting(ini, "Tweaks", "bAbsorptionChance", AbsorptionChance);

    INFO("FTweaks @ Settings Loaded!");
}

void Settings::ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, bool& a_setting)
{
    auto found = a_ini.GetValue(a_section, a_key);

    if (found)
    {
        a_setting = a_ini.GetBoolValue(a_section, a_key);
    }
}