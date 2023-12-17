#pragma once

uintptr_t oldAddress;

namespace Papyrus
{
	class DisableLevelUpMenu
	{
	public:

		void forceLvlUp()
		{
			RE::PlayerCharacter::GetSingleton()->skills->AdvanceLevel(false);
		}

		static inline bool disableLevelUpMenu(RE::StaticFunctionTag*)
		{
			//oldAddress = SKSE::GetTrampoline().write_call<5>(REL::ID(52510).address() + 0x1012, &forceLvlUp);  //AE
			oldAddress = SKSE::GetTrampoline().write_call<5>(REL::ID(51638).address() + 0xf8e, &forceLvlUp);  //SSE  
			return true;
		}

		static inline bool enableLevelUpMenu(RE::StaticFunctionTag*)
		{
			if (oldAddress) {
				//SKSE::GetTrampoline().write_call<5>(REL::ID(52510).address() + 0x1012, oldAddress);  //AE
				SKSE::GetTrampoline().write_call<5>(REL::ID(51638).address() + 0xf8e, oldAddress);  //SSE
				return true;
			}
		}

		static inline bool RegisterFuncs(RE::BSScript::IVirtualMachine* a_vm)
		{
			a_vm->RegisterFunction("disableLevelUpMenu", "NoLevelUpMenu", disableLevelUpMenu);
			a_vm->RegisterFunction("enableLevelUpMenu", "NoLevelUpMenu", enableLevelUpMenu);
			logger::info("Registered funcs for NoLevelUpMenu.");

			return true;
		}
	};

	inline bool Register(RE::BSScript::IVirtualMachine* a_vm)
	{
		DisableLevelUpMenu::RegisterFuncs(a_vm);
		return true;
	}
}
