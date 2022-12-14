#include <iostream>
#include "CasualLibrary.hpp"
#include "Utils.h"

using namespace std;

int main()
{
    int choice;

	#pragma region Message box
    const wstring name(L"EtG.exe");
    const wchar_t* etg_process_name = name.c_str();

    if (is_process_running(etg_process_name) == false)
    {
        MessageBox(0, _T("Enter the Gungeon isn't open! Please open Enter the Gungeon and then restart the program!"), _T("Error"), 0);
        return 0;
    }
    #pragma endregion

    Memory::External memory = Memory::External("EtG.exe", true);

	#pragma region Address variables
    Address health_base_addr = memory.getModule("UnityPlayer.dll");
    Address health_addr = memory.getAddress(health_base_addr + 0x0146FCC8, { 0x120, 0x10, 0x30, 0x30, 0x38, 0x28, 0x118 });

    Address shells_base_addr = memory.getModule("mono.dll");
    Address shells_addr = memory.getAddress(shells_base_addr + 0x00264A68, { 0xC0, 0xE90, 0xA8, 0x198, 0x1C });
    // shells are the currency used in EtG runs if you didn't know

    Address blanks_base_addr = memory.getModule("UnityPlayer.dll");
    Address blanks_addr = memory.getAddress(blanks_base_addr + 0x0144EBB8, { 0x8, 0x98, 0x28, 0x30, 0x568 });

    float current_health = memory.read<float>(health_addr);
    int current_shells = memory.read<int>(shells_addr);
    int current_blanks = memory.read<int>(blanks_addr);
	#pragma endregion

    while (true) {
        cout << "Current health: " << current_health << endl;
        cout << "Current shells: " << current_shells << endl;
        cout << "Current blanks: " << current_blanks << endl;

        cout << "\nEtG Essentials\n";
        cout << " 1 - Infinite Health\n";
        cout << " 2 - Infinite Shells\n";
        cout << " 3 - Infinite Blanks\n";
        cout << " 4 - Auto Blank Spam\n";
        cout << " 5 - Exit.\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nGiving Player infinite health! Press the ESCAPE key to exit EtGEssentials\n\n";
            infinite_health(memory, health_addr);
            break;
        case 2:
            memory.write<int>(shells_addr, 100000000, true);
            cout << "\nGave Player 100 million shells!\n\n";
            break;
        case 3:
            cout << "\nGiving Player infinite blanks! Press the ESCAPE key to exit EtGEssentials\n\n";
            infinite_blanks(memory, blanks_addr);
        case 4:
            cout << "\nStarted auto blank spam cheat! Press the ESCAPE key to exit EtGEssentials\n\n";
            auto_blank_spam(memory, blanks_addr);
        case 5:
            cout << "\nExiting..";
            Sleep(2000);
            return 0;
        default:
            cout << "Not a valid choice, choose again.\n";
            break;
        }
    }
}