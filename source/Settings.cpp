#include "Settings.h"

void Settings::Load()
{
    INFO("DLLTweaks @ Loading Settings...");

    CSimpleIniA ini;

    ini.SetUnicode();

    ini.LoadFile(INI_PATH.string().data());

    ReadSetting(ini, "Fixes", "bNordRaceStats", NordRaceStats);
    ReadSetting(ini, "Fixes", "bScaleMovementSpeed", ScaleMovementSpeed);
    ReadSetting(ini, "Tweaks", "bAbsorptionChance", AbsorptionChance);
    ReadSetting(ini, "Tweaks", "bConcentrationCasting", ConcentrationCasting);
    ReadSetting(ini, "Tweaks", "bSneakJumpHeight", SneakJumpHeight);
    ReadSetting(ini, "Tweaks", "fSneakJumpModifier", SneakJumpHeightMod);

    INFO("DLLTweaks @ Settings Loaded!");
}

void Settings::ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, bool& a_setting)
{
    auto found = a_ini.GetValue(a_section, a_key);

    if (found)
    {
        a_setting = a_ini.GetBoolValue(a_section, a_key);
    }
}

void Settings::ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, float& a_setting)
{
    auto found = a_ini.GetValue(a_section, a_key);

    if (found)
    {
        a_setting = static_cast<float>(a_ini.GetDoubleValue(a_section, a_key));
    }
}

void Settings::ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, std::uint32_t& a_setting)
{
    auto found = a_ini.GetValue(a_section, a_key);

    if (found)
    {
        a_setting = static_cast<std::uint32_t>(a_ini.GetLongValue(a_section, a_key));
    }
}