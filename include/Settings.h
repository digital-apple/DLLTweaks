#pragma once

class Settings
{
public:
    using bSetting = AutoTOML::bSetting;
    using fSetting = AutoTOML::fSetting;

    [[nodiscard]] static Settings* GetSingleton()
    {
        static Settings singleton;
        return std::addressof(singleton);
    }

    static inline bSetting AbsorbChancePatch{ "Patches", "AbsorbChance", true };
    static inline bSetting PlayerScaleMovementPatch{ "Patches", "PlayerScaleMovement", true };

    static bool load_config(const std::string& a_path)
    {
        try {
            const auto table = toml::parse_file(a_path);
            const auto& settings = ISetting::get_settings();

            for (const auto& setting : settings) {
                try {
                    setting->load(table);
                } catch (const std::exception& e) {
                    logs::warn(fmt::runtime(e.what()));
                }
            }
        } catch (const toml::parse_error& e) {
            std::ostringstream ss;
            ss
                << "Error parsing file \'" << *e.source().path
                << "\':\n"
                << e.description()
                << "\n  (" << e.source().begin << ")\n";
            logs::error(fmt::runtime(ss.str()));
            return false;
        }
        return true;
    }
private:
    using ISetting = AutoTOML::ISetting;

    Settings();
    Settings(const Settings&) = delete;
    Settings(Settings&&) = delete;

    ~Settings() = default;

    Settings& operator=(const Settings&) = delete;
    Settings& operator=(Settings&&) = delete;    
};