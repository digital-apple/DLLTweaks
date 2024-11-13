#pragma once

struct Settings
{
    static void Load();

    static void ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, bool& a_setting);
    static void ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, float& a_setting);
    static void ReadSetting(CSimpleIni& a_ini, const char* a_section, const char* a_key, std::uint32_t& a_setting);

    static inline bool NordRaceStats = true;
    static inline bool ScaleMovementSpeed = true;

    static inline bool AbsorptionChance = true;
    static inline bool ConcentrationCasting = true;

    static inline bool SneakJumpHeight = true;
    static inline float SneakJumpHeightMod = 0.55f;

    inline static std::filesystem::path INI_PATH = L"DLLTweaks.ini";
};