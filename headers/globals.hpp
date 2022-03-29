#pragma once
#include "memory/memory.hpp"
#include <psapi.h>
#define LOG_SIG "[ye]"
#define LOG( ... )                                                                                                     \
    {                                                                                                                  \
        char buff[ 256 ];                                                                                              \
        snprintf( buff, sizeof buff, LOG_SIG##__VA_ARGS__ );                                                           \
        OutputDebugStringA( buff );                                                                                    \
    }

struct game_info {

	uint32_t pid;
	uint64_t 
		base,
		game_manager;
	

	void get() {

		this->pid = GetCurrentProcessId();
		this->base = memory::get_module_baseaddr(this->pid, "RainbowSix.exe");
		this->game_manager = (_rotl64(*reinterpret_cast<uint64_t*>(this->base + 0x82F6288), 52) + 0x7B6DEAF5F516B71Ci64) ^ 0x1745AC3A02EE9E46i64;

		LOG("pid  -> %d\n", this->pid);
		LOG("base -> 0x%llx", this->base);
		LOG("game_manager -> 0x%llx", this->game_manager);
	}

};

namespace globals {

	game_info game;

}