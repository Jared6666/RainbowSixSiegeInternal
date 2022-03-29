#pragma once
#include "../globals.hpp"
#include "../game/game.hpp"

namespace features {

	void nospread()
	{
		while (true) {
			if (GetAsyncKeyState(VK_INSERT)) {
				*reinterpret_cast<uint32_t*>(game::current_weapon(game::localplayer()) + 0x60) = 0x76FE6EE0;
				Sleep(200);
			}
		}
	}

	void outlines() {

		while (true) {

			for (int i = 0; i < game::controller_count(); i++ )
			{
				const auto player_controller = game::player_controller_c{ *reinterpret_cast<uint64_t*>(game::controller_list() + (i * sizeof(uint64_t))) };
				if (!player_controller.address)
					continue;

				const auto pawn_component = game::player_controller_c::pawn_component_c{ _rotl64(*reinterpret_cast<uint64_t*>(player_controller.address + 0x38) - 0x211C0F86ED634100i64, 0x3B) - 0x2F };
				if (!pawn_component.address)
					continue;

				const auto actor = game::player_controller_c::pawn_component_c::actor_c{ (_rotl64(*reinterpret_cast<uint64_t*>(pawn_component.address + 0x18), 0x1A) ^ 0xBCC79864C12C2B1Fui64) - 0x5C };
				if (!actor.address)
					continue;

				game::outline_actor(actor);
			}
		}
	}
}
