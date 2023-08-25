#pragma once

namespace Addresses
{
	auto CheckAbsorbPatch(RE::ActorValueOwner* a_actor, RE::ActorValue a_value) -> std::uint32_t;
	void Hook();
}