#include "Hooks.h"
#include "Settings.h"

namespace Fixes
{
    // Starting the game as a Nord no longer breaks intended mechanics.

    void NordRaceStats::Install()
    {
        if (Settings::NordRaceStats) {
            const auto player = RE::PlayerCharacter::GetSingleton();

            if (!player) { return; }

            player->InitValues();

            INFO("Fixes @ Installed <{}>", typeid(NordRaceStats).name());
        }
    }

    // The player's racial scale no longer grants different movement speed.

    struct ScaleMovementSpeed
    {
        static float Call(RE::TESObjectREFR* a_reference)
        {
            const auto scale = Callback(a_reference);

            if (a_reference->As<RE::Actor>() == RE::PlayerCharacter::GetSingleton()) {
                return a_reference->GetReferenceRuntimeData().refScale / 100.f;
            }

            return scale;
        }
        static inline REL::Relocation<decltype(Call)> Callback;
    };

    void Install()
    {
        if (Settings::ScaleMovementSpeed) {
            REL::Relocation target{ RELOCATION_ID(37013, 38041), REL::Relocate(0x1A, 0x1F) };
            stl::write_thunk_call<ScaleMovementSpeed>(target.address());

            INFO("Fixes @ Installed <{}>", typeid(ScaleMovementSpeed).name());
        }
    }
}

namespace Tweaks
{
    // Caps the maximum spell absorption chance to the fPlayerMaxResistance game setting value; 

    struct AbsorptionChance
    {
        static auto Call(RE::ActorValueOwner* a_actor, RE::ActorValue a_value) -> std::uint32_t
        {
            const auto currentChance = a_actor->GetActorValue(a_value);
            const auto fPlayerMaxResistance = RE::GameSettingCollection::GetSingleton()->GetSetting("fPlayerMaxResistance")->GetFloat();

            return static_cast<std::uint32_t>(currentChance > fPlayerMaxResistance ? fPlayerMaxResistance : currentChance);
        }
    };

    void Install()
    {
        if (Settings::AbsorptionChance) {
            REL::Relocation target{ RELOCATION_ID(37792, 38741), REL::Relocate(0x53, 0x55) };
            stl::write_call<AbsorptionChance>(target.address());

            // Clean up garbage instructions.

            std::uint8_t NOP[] = { 0x90, 0x90, 0x90 };
            REL::safe_write(target.address() + 0x5, NOP, 3);

            INFO("Tweaks @ Installed <{}>", typeid(AbsorptionChance).name());
        }
    }
}