#include "impl.h"

#include <boost/unordered_map.hpp>

#include "../head/utility_new.h"//������ڰ������



BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}
#include "../head/M_interface.h"


M_IMPL(ns_base::h_logger, ns_base::impl_logger);//2. �ӿ�ʵ��
M_OPEN();//3. ģ�齨��
