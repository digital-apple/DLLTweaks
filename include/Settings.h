#pragma once

struct Settings
{
    static void Load();

    static void ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, bool& a_setting);

    static inline bool NordRaceStats = true;
    static inline bool ScaleMovementSpeed = true;

    static inline bool AbsorptionChance = true;
    static inline bool ConcentrationCasting = true;

    static constexpr std::string_view INI_PATH = "FTweaks.ini";
};