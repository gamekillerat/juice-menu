#include "Game.hpp"
#include "Invoker.hpp"
#include "Nm.h"

namespace Big
{	
	GameVariables::GameVariables() :
		
		m_GameState(Signature("48 85 C9 74 4B 83 3D", "Found 'SCRP'->Hooked").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
		m_FrameCount(Signature("F3 0F 10 0D ? ? ? ? 44 89 6B 08", "Found 'GHOS'").Scan().Add(4).Rip().Sub(8).As<decltype(m_GameState)>()),
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
		m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01", "Found 'CMI'").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),
		ModelBypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48","Found 'SPWN'->Hooked").Scan().Add(8).As<decltype(ModelBypass)>()),
		m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF", "Found 'SST").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
		m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0", "Found 'GBB").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>()),
		is_session_started(Signature("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE", "Found 'SPTR'").Scan().Add(3).Rip().As<bool*>()),
		m_NativeRetn(Signature("44 89 75 9F 49 8D 0C C1", "Found 'GLT'->Hooked").Scan().Add(8).As<char*>()),
		NOTIFICATION(Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 83 3D ? ? ? ? ? 41 8A D8", "Found 'NARRM'").Scan().Add(9).As<char*>()),
		m_gtatime(Signature("83 79 18 00 48 8B D1 74 4A FF 4A 18", "Found 'TME'").Scan().Add(9).As<char*>()),
		m_juicesaybye(Signature("48 89 5C 24 ? 57 48 83 EC 20 48 8B FA 48 8B D9 E8 ? ? ? ? 48 8B 47 38 4C 8B C7 48 8D 4B 5C", "Found 'JUIC'->Hooked").Scan().Add(59).As<char*>())

	{
		
	}
	void GameVariables::PostInit()
	{
	}
	GameFunctions::GameFunctions() : //i had gife you my last money for this mouth :(
		//m_TriggerScriptEvent(Signature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC ? ? ? ? 45 8B F0 41 8B F9", "Found 'TSE'->Hooked").Scan().As<decltype(m_TriggerScriptEvent)>()),
		m_JuiceChange(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9", "Found 'JC'").Scan().As<decltype(m_JuiceChange)>()),
		m_DenyDrops(Signature("49 8B 80 ? ? ? ? 48 85 C0 74 0C F6 80 ? ? ? ? ? 75 03 32 C0 C3", "Found 'NERBB'").Scan().As<decltype(m_DenyDrops)>()),
		m_SessionTime(Signature("48 89 5C 24 08 57 48 83 EC 20 8B F9 48 8B 0D ? ? ? ? 48 8B DA 33 D2 E9 ? ? ? ?", "Found 'HKH'").Scan().As<decltype(m_SessionTime)>()),
		m_ScriptVM(Signature("4D 8B F9 4D 8B F0 4C 8B C2 4D 63 57 0C 49 63 47 14 4D 8B 6E 10 48 FF C8 49 8B D2", "Found 'OIFH'").Scan().Sub(0x26).As<decltype(m_ScriptVM)>()),
		m_NetworkEvents(Signature("66 41 83 F9 ? 0F 83 ? ? ? ?", "Found 'OIFH'").Scan().As<decltype(m_NetworkEvents)>()),
		object_spawn_bypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48", "Found 'OSBP'->Hooked").Scan().Add(8).As<PVOID>()),
		m_IsDlcPresent(Signature("84 C0 74 0D 8D 53 0C", "Found 'DN'").Scan().Sub(63).As<decltype(m_IsDlcPresent)>()),
		m_WndProc(Signature("48 8B 0D ? ? ? ? 48 8D 55 EF FF 15", "Found 'PTFXEH'").Scan().Sub(853).As<decltype(m_WndProc)>()),
		m_pNetworkCanBail(Signature("48 8B 0D ? ? ? ? 33 C0 48 85 C9 74 25", "Found 'EEH'").Scan().As<decltype(m_pNetworkCanBail)>()),
		m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10", "Found 'IDP'").Scan().Sub(28).As<decltype(m_GetEventData)>()),
		m_ChatSensor(Signature("E8 ? ? ? ? 83 F8 FF 75 B9", "Found 'PSYNT'").Scan().Add(1).Rip().As<decltype(m_ChatSensor)>()),
		m_ReportMyselfEvent(Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 40 48 8B D9 48 8B 0D ? ? ? ? 48 8B F2", "Found 'SCP'").Scan().As<decltype(m_ReportMyselfEvent)>()),
		m_GetNumOfEvents(Signature("48 83 EC 28 33 D2 85 C9", "Found 'SCP'").Scan().As<decltype(m_GetNumOfEvents)>()),
		m_EventManager(Signature("40 53 48 81 EC ? ? ? ? 44 8B 81 ? ? ? ? 4C 8B CA 41 8D 40 FF 3D ? ? ? ? 77 42", "Found 'OEXBP1'").Scan().As<decltype(m_EventManager)>()),
		m_GetPlayerNetworkIds(Signature("74 0A 83 F9 1F 77 05 E8 ? ? ? ? 48", "Found 'OEXBP2'").Scan().Sub(12).As<decltype(m_GetPlayerNetworkIds)>()),
		m_DisableErrorScreen(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 60 4C 8B F2 48 8B 94 24 ? ? ? ? 33 DB", "Found 'SWM'").Scan().As<decltype(m_DisableErrorScreen)>()),
		m_ChatMessage(Signature("40 88 B3 ? ? ? ? 89 73 08 48 39 B3 ? ? ? ? 75 24 48 8D 05 ? ? ? ? 48 8B CB 48 89 B3", "Found 'SWSF'").Scan().Add(0x16).Rip().As<decltype(m_ChatMessage)>()),
		m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9", "Found 'GCE'").Scan().Sub(19).As<decltype(m_GetLabelText)>()),
		m_NetworkInfoChange(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 30 48 8B F1 48 8B 0D ? ? ? ? 48 8B FA", "Found 'GSSCE'").Scan().As<decltype(m_NetworkInfoChange)>()),
		m_JoinPattern(Signature("48 8B C4 48 89 58 10 48 89 70 18 48 89 78 20 48 89 48 08 55 41 54 41 55 41 56 41 57 48 8D 68 A8", "Found 'ARRCSD'").Scan().As<decltype(m_JoinPattern)>()),
		pFileRegister(Signature("84 C0 74 0D 4C 8B 07", "Found 'N2H'").Scan().Sub(0x6C).As<decltype(pFileRegister)>()),
		m_Pattern(Signature("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC 40 44 8B F9 B9 ? ? ? ? 49 8B F1 41 8B E8 4C 8B F2 33 DB E8 ? ? ? ? 48 8B F8 48 85 C0 74 56 48 8B C8 E8 ? ? ? ? 48 8B 84 24 ? ? ? ? 44 8B CD 48 89 47 40 48 8B 84 24 ? ? ? ? 4D 8B C6 48 89 44 24 ? 8B 84 24 ? ? ? ? 41 8B D7 89 44 24 28 48 8B CF 48 89 74 24 ? E8 ? ? ? ? 84 C0 74 10 48 8B CF E8 ? ? ? ? 84 C0 74 04 B3 01 EB 08 48 8B CF E8", "Found 'GHOS'->Hooked").Scan().As<decltype(m_Pattern)>()),
		m_GiveWantedLevel(Signature("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 44 88 48 20 57 41 54 41 55 41 56 41 57 48 83 EC 30 4C 8B F1 48 8B 0D ? ? ? ? 44 8B E2 B2 01 41 8A D9 45 8B E8 E8 ? ? ? ? 48 8B 0D ? ? ? ?", "Found 'P2H'").Scan().As<decltype(m_GiveWantedLevel)>())

	{
	}
}
