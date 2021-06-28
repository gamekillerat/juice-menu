#pragma once

namespace rage
{
	struct scrNativeRegistration;
}
struct twoBytes
{
	BYTE	byte[2];

	bool	empty();
};
namespace Big
{
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;
		bool* is_session_started{};
		void PostInit();
		
    	std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		PVOID ModelBypass;
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
		rage::scrNativeRegistration** m_NativeRegistrations;

		std::uint64_t** m_GlobalBase;
		char m_OriginalNativeRetn[2];
		char* m_NativeRetn;
		char* m_juicesaybye;
		char* m_gtatime;
		char* NOTIFICATION;
		char* m_GameBuild;
		uint64_t m_WorldPtr;
		char* m_JoinPattern;
		__int64** m_globalPtr;
		uint64_t PlayerListPtr;
		uint32_t activeThreadTlsOffset;
		uint64_t M_cWorld;
		std::vector<void*> m_EventPtr;
		twoBytes* m_ownedExplosionBypass;
		
	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;

		using IsDlcPresent = bool(std::uint32_t hash);
		IsDlcPresent* m_IsDlcPresent;
		PVOID object_spawn_bypass;
		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetEventData* m_GetEventData;

		using GetLabelText = const char* (void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using tFileRegister = unsigned int* (int* a1, const char* a2, bool a3, const char* a4, bool a5);
		tFileRegister* pFileRegister;

		using SessionTime = void(int hour, int min);
		SessionTime* m_SessionTime;

		using ChatMessage = void(void* thisptr, __int64 unk1, __int64 unk2, const char* message);
		ChatMessage* m_ChatMessage;

		using pJoinPattern = int(__int64 a1, int a2, __int64* a3, int a4);
		pJoinPattern* m_JoinPattern;

		using RandomPat = char(int a1, __int64 a2, unsigned int a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7);
		RandomPat* m_Pattern;

		using GiveWantedLevel = void(int64_t wantedLevel, int a3, char a4);
		GiveWantedLevel* m_GiveWantedLevel;

		/*using TriggerScriptEvent = int(bool unk0, uint64_t* args, int argCount, int bitFlags);
		TriggerScriptEvent* m_TriggerScriptEvent;*/

		using GetNumOfEvents = int(int eventgroup);
		GetNumOfEvents* m_GetNumOfEvents;

		using NetworkMgr = void(__int64 a3, unsigned __int16 a4, int a5, int a6, __int64 a7, __int64 a8);
		NetworkMgr* m_NetworkEvents;

		using pDenyDrops = bool();
		pDenyDrops* m_DenyDrops; 

		using JuiceChange = bool();
		JuiceChange* m_JuiceChange;

		using GetPlayerNetworkIds = int;
		GetPlayerNetworkIds* m_GetPlayerNetworkIds;

		using EventMgr = bool();
		EventMgr* m_EventManager;

		using DisableErrorScreen = void(char* entryHeader);
		DisableErrorScreen* m_DisableErrorScreen;

		using ScriptVM = int(void* stack, signed __int64** globals, void* program);
		ScriptVM* m_ScriptVM;

		using ChatSensor = int(__int64 chat_menu, const char* user_text, const char** output_text);
		ChatSensor* m_ChatSensor;

		using pReportMyselfEvent = bool(void* targetPlayer);
		pReportMyselfEvent* m_ReportMyselfEvent;

		using pNetworkInfoChange = bool(void* thisptr);
		pNetworkInfoChange* m_NetworkInfoChange;

		using pNetworkCanBail = bool();
		pNetworkCanBail* m_pNetworkCanBail;

		
	

			void TransformPattern(const std::string& pattern, std::string& data, std::string& mask);

			class executable_meta {
			private:

				uintptr_t	m_begin;
				uintptr_t	m_end;
				DWORD		m_size;
			public:

				executable_meta()
					: m_begin(0), m_end(0) {
				}

				void EnsureInit();

				inline uintptr_t begin() { return m_begin; }
				inline uintptr_t end() { return m_end; }
				inline DWORD size() { return m_size; }
			};

	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
