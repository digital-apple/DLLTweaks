#include "Hooks.h"
#include "Settings.h"

namespace Addresses
{
	auto CheckAbsorbPatch(RE::ActorValueOwner* a_actor, RE::ActorValue a_value) -> std::uint32_t 
	{
		auto currentValue = a_actor->GetActorValue(a_value);
		auto fPlayerMaxResistance = RE::GameSettingCollection::GetSingleton()->GetSetting("fPlayerMaxResistance")->GetFloat();

		return static_cast<std::uint32_t>(currentValue > fPlayerMaxResistance ? fPlayerMaxResistance : currentValue);
	}

	struct PlayerScaleMovementPatch
	{
		static float thunk(RE::TESObjectREFR* a_reference)
		{
			auto scale = func(a_reference);
			
			if (a_reference->As<RE::Actor>() == RE::PlayerCharacter::GetSingleton()) {
				return a_reference->GetReferenceRuntimeData().refScale / 100.0F;
			}
			return scale;
		}
		static inline REL::Relocation<decltype(thunk)> func;
	};

	void Hook()
	{
		if (*Settings::AbsorbChancePatch) {
			REL::Relocation<std::uintptr_t> function{ RELOCATION_ID(37792, 38741), REL::Relocate(0x53, 0x55) };

			auto& trampoline = SKSE::GetTrampoline();
			SKSE::AllocTrampoline(14);
			trampoline.write_call<5>(function.address(), CheckAbsorbPatch);

			std::uint8_t NOP[] = { 0x90, 0x90, 0x90 };
			REL::safe_write(function.address() + 0x5, NOP, 3);

			logs::info("Addresses :: Patched 'AbsorbChance'.");
		}

		if (*Settings::PlayerScaleMovementPatch) {
			REL::Relocation<std::uintptr_t> function{ RELOCATION_ID(37013, 38041), REL::Relocate(0x1A, 0x1F) };
			
			stl::write_thunk_call<PlayerScaleMovementPatch>(function.address());

			logs::info("Addresses :: Patched 'PlayerScaleMovement'.");
		}
	}
}