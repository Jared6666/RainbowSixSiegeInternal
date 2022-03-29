#pragma once
#include "../globals.hpp"

namespace game {

    struct player_controller_c
    {
        uint64_t address;

        struct pawn_component_c
        {
            uint64_t address;

            struct actor_c
            {
                uint64_t address;
            };

        };
    };

    inline void outline_actor(player_controller_c::pawn_component_c::actor_c actor) {

        const auto visual_settings = _rotl64((*reinterpret_cast<uint64_t*>(actor.address + 0x1C8) + 0x7B7F518441D25D3F) ^ 0x8914A2C32D5E8B50, 0x21);
        if (!visual_settings)
            return;

        uint64_t properties = *reinterpret_cast<uint64_t*>(visual_settings + 0xB0);
        if (!properties)
            return;

        if ((properties & 0xFFFFFFFF) != 0x20748000)
            *reinterpret_cast<uint32_t*>(visual_settings + 0xB0) = 0x20748000;

        Sleep(200);
        LOG("properties -> 0x%llx", properties);

    }

    inline int controller_count() {

        int c = static_cast<int>(_rotl64(*reinterpret_cast<uint64_t*>(globals::game.game_manager + 0x140) - 0x19, 0x12) & 0x3FFFFFFF);
        LOG("controllers -> %d", c);
        return c;

    }

    inline uint64_t controller_list() {

        return _rotl64(*reinterpret_cast<uint64_t*>(globals::game.game_manager + 0x138) - 0x19, 0x12);

    }

    inline uint64_t profile_manager() {

        auto v10 = _rotl64((*reinterpret_cast<uint64_t*>(globals::game.base + 0x7550348) ^ 0x23) - 0x3D65795183DD42A9i64, 36);
        auto v11 = _rotl64(*reinterpret_cast<uint64_t*>(v10 + 24) - 34i64, 8);
        auto v12 = *reinterpret_cast<uint64_t*>(v11);
        return v12;

    }

    inline player_controller_c::pawn_component_c::actor_c localplayer()  {

        auto v13 = _rotl64(*reinterpret_cast<uint64_t*>(profile_manager() + 24), 37) ^ 0x77i64;
        v13 -= 0x630A5EF86C409DFCi64;

        const auto pawn_component = player_controller_c::pawn_component_c{ _rotl64(*reinterpret_cast<uint64_t*>(v13 + 0x38) - 0x211C0F86ED634100i64, 0x3B) - 0x2F };
        if (!pawn_component.address)
            return {};

        const auto actor = player_controller_c::pawn_component_c::actor_c{ (_rotl64(*reinterpret_cast<uint64_t*>(pawn_component.address + 0x18), 0x1A) ^ 0xBCC79864C12C2B1Fui64) - 0x5C };
        if (!actor.address)
            return {};

        return actor;

    }

    inline uint64_t current_weapon(player_controller_c::pawn_component_c::actor_c actor) {

        uintptr_t component = *reinterpret_cast<uint64_t*>(actor.address + 0xD8);
        BYTE index = *reinterpret_cast<BYTE*>(actor.address + 0x228);

        uintptr_t weaponArray = *reinterpret_cast<uint64_t*>(component + (index * sizeof(uintptr_t)));

        uintptr_t entry = _rotl64(_rotl64(*reinterpret_cast<uint64_t*>(weaponArray + 0x608), 4) - 0x6A, 0x2C);
        if (!entry) entry = _rotl64(*reinterpret_cast<uint64_t*>(weaponArray + 0x580) + 0x1FDC8465C49F95B, 0x19) - 0x192C98AA3ECEA41D;

        entry = *reinterpret_cast<uint64_t*>(entry);

        uintptr_t weaponEntry = *reinterpret_cast<uint64_t*>(entry + 0x1B0);
        uintptr_t currentWeapon = ((*reinterpret_cast<uint64_t*>(weaponEntry + 0x218) - 0x754F07C2B92B0D3E) ^ 0xCE9B301A9687670B) - 0x37;

        return currentWeapon;

    }

}