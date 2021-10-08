/* keep project in x86 and debug */
#include <Windows.h>
#include <iostream>
#include <vector>

uintptr_t base_address = (uintptr_t)GetModuleHandleA(0);

bool is_enabled = true; 
bool WriteMemory(uintptr_t const ss, std::vector<uint8_t> const& bytes)
{
	return WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<LPVOID>(base_address + ss), bytes.data(), bytes.size(), nullptr);
}

DWORD WINAPI noclip_thread(LPVOID param)
{
	for (;;)
	{
		if (is_enabled)
		{
			WriteMemory(0x20A23C, { 0xE9, 0x79, 0x06, 0x00, 0x00 });
		}
		else
		{
			WriteMemory(0x20A23C, { 0x6A, 0x14, 0x8B, 0xCB, 0xFF });
		}
	}
}

bool __stdcall DllMain(void* one, unsigned long two, void* three)
{
	if (two == 1)
	{
		CreateThread(NULL, 0x1000, &noclip_thread, NULL, 0, NULL);
		return TRUE;
	}
	return 1;
}