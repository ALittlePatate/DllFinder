#include <Windows.h>
#include <Psapi.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

#define HEADER_SIZE 0x1000 

bool address_in_vector(LPVOID addr, std::vector<std::pair<std::string, LPVOID>> modules, std::string &name) {
    // Check if the target_address is present in the vector
    for (const auto& module : modules) {
        if (module.second == addr) {
            name = module.first;
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: DllFinder.exe [PID]\n");
		return 1;
	}

	int pid;
	sscanf_s(argv[1], "%d", &pid);

	if (pid < 0) {
		printf("Bad PID value\n");
		return 1;
	}

	printf("PID : %d\n", pid);

	HANDLE proc_handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, TRUE, pid);
	if (proc_handle == nullptr) {
		printf("Could not open the process\n");
		return 1;
	}
	
	std::vector<std::pair<std::string, LPVOID>> modules = {};

    int mod_count = 0;
	HMODULE module_handles[1024];
    DWORD needed;
    if (EnumProcessModulesEx(proc_handle, module_handles, sizeof(module_handles), &needed, LIST_MODULES_ALL)) {
        int module_count = needed / sizeof(HMODULE);

        for (int i = 0; i < module_count; i++) {
            TCHAR module_name[MAX_PATH];
            MODULEINFO module_info;

            if (GetModuleBaseName(proc_handle, module_handles[i], module_name, sizeof(module_name) / sizeof(TCHAR))) {
                if (GetModuleInformation(proc_handle, module_handles[i], &module_info, sizeof(module_info))) {
                    // module_name now contains the name of the DLL
                    std::wstring wide_module_name(module_name);
                    std::string module_name_str(wide_module_name.begin(), wide_module_name.end());

					modules.push_back(std::make_pair(module_name_str, module_info.lpBaseOfDll));
                    // module_name_str now contains the name as a std::string
                    std::cout << module_name_str;
                    std::cout << " --> 0x" << std::hex << module_info.lpBaseOfDll << "\n";
                    ++mod_count;
                }
            }
        }
    }

    printf("Found %d modules.\n", mod_count);
	printf("Finding manual mapped dlls..\n\n");

	MEMORY_BASIC_INFORMATION mem_info;
    LPVOID current_address = 0;
    int m_mod_count = 0;
    while (VirtualQueryEx(proc_handle, current_address, &mem_info, sizeof(mem_info))) {
        if (mem_info.RegionSize == HEADER_SIZE) { //sizeof(header)
            short mz = 0;
            ReadProcessMemory(proc_handle, mem_info.BaseAddress, &mz, sizeof(mz), NULL);

            if (mz == 0x5a4d) { //'ZM'
                std::string mod_name;
                if (address_in_vector(current_address, modules, mod_name)) {
                }
                else {
                    std::string out_name;
                    std::cout << "Module found --> 0x" << std::hex << current_address << std::endl;
                    ++m_mod_count;
                }
            }
        }

        // Move to the next memory region
        current_address = (LPVOID)((DWORD_PTR)mem_info.BaseAddress + mem_info.RegionSize);
    }

    printf("Found %d modules.\n", m_mod_count);

	CloseHandle(proc_handle);
	return 0;
}