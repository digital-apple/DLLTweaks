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
    // Caps the maximum spell absorption chance to the fPlayerMaxResistance game setting value.

    struct AbsorptionChance
    {
        static auto Call(RE::ActorValueOwner* a_actor, RE::ActorValue a_value) -> std::uint32_t
        {
            const auto currentChance = a_actor->GetActorValue(a_value);
            const auto fPlayerMaxResistance = RE::GameSettingCollection::GetSingleton()->GetSetting("fPlayerMaxResistance")->GetFloat();

            return static_cast<std::uint32_t>(currentChance > fPlayerMaxResistance ? fPlayerMaxResistance : currentChance);
        }
    };

    // Concentration spells that costs more (per second) than the current magicka amount can no longer be casted.

    struct ConcentrationCasting
    {
        static auto Call(RE::Actor* a_actor, RE::ActorValue a_value, RE::MagicItem* a_spell, float a_cost, bool a_useBaseValueForCost) -> bool
        {
            INFO("Actor: <{}> | Actor Value: <{}> | Spell: <{}> | Cost: <{}> | Use Base Value: <{}>", a_actor->GetName(), std::to_string(a_value).c_str(), a_spell->GetName(), a_cost, a_useBaseValueForCost);

            const auto result = a_useBaseValueForCost ? a_actor->AsActorValueOwner()->GetBaseActorValue(a_value) : a_actor->AsActorValueOwner()->GetActorValue(a_value);

            if (a_spell->GetCastingType() == RE::MagicSystem::CastingType::kConcentration) {
                const auto value_maximum = a_actor->AsActorValueOwner()->GetPermanentActorValue(a_value);

                INFO("Value Maximum: <{}>", value_maximum);

                return value_maximum >= a_cost;
            }

            INFO("Result: <{}>", result);

            return result >= a_cost;
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

        if (Settings::ConcentrationCasting) {
            REL::Relocation target{ RELOCATION_ID(33364, 0), REL::Relocate(0x1B4, 0x0) };

            ///// MOV    RCX, [RBX+0xB8] == Actor*
            stl::safe_write(target.address() + 0x00, std::array<std::uint8_t, 7>{ 0x48, 0x8B, 0x8B, 0xB8, 0x00, 0x00, 0x00 });

            ///// MOV    EDX, EBP == Actor Value
            stl::safe_write(target.address() + 0x07, std::array<std::uint8_t, 2>{ 0x89, 0xEA });

            ///// MOV    R8, RDI == MagicItem*
            stl::safe_write(target.address() + 0x09, std::array<std::uint8_t, 3>{ 0x49, 0x89, 0xF8 });

            // MOVAPS    XMM3, XMM7 == Cost
            stl::safe_write(target.address() + 0x0C, std::array<std::uint8_t, 3>{ 0x0F, 0x28, 0xDF });

            ///// MOV    AL, [RSP+0xC8] 
            stl::safe_write(target.address() + 0x0F, std::array<std::uint8_t, 7>{ 0x8A, 0x84, 0x24, 0xC8, 0x00, 0x00, 0x00 });

            ///// MOV    [RSP+0x20], AL == Use Base Cost
            stl::safe_write(target.address() + 0x16, std::array<std::uint8_t, 4>{ 0x88, 0x44, 0x24, 0x20 });

            stl::write_call<ConcentrationCasting>(target.address() + 0x1A);

            stl::safe_write(target.address() + 0x1F, std::array<std::uint8_t, 25>{ 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });

            INFO("Tweaks @ Installed <{}>", typeid(ConcentrationCasting).name());
        }
    }
}