//------------------------------------------------------------
//ӵ����	�Ὥ �汾0.3 ����2010.1.12
//����		���ڼ��memorylink��������ڴ�й¶��������ļ�+�������Ա㶨λ
//ʹ��		����cpp��#include "utility_new.h" Ϊ����һ��ͷ�ļ�
//------------------------------------------------------------

#ifndef QIN_HEADERS_UTILITY_NEW_H_
#define QIN_HEADERS_UTILITY_NEW_H_

#include <stdlib.h>
#include <crtdbg.h>

#define BOOST_MS_CRT_BASED_DEBUG
static void detect_memory_leaks( bool on_off, bool out_put_debug = true)
{

#ifdef BOOST_MS_CRT_BASED_DEBUG
	int flags = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

	if(!on_off)
		flags &= ~_CRTDBG_LEAK_CHECK_DF;
	else {
		flags |= _CRTDBG_LEAK_CHECK_DF;
		if(!out_put_debug)
		{
			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
			_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
		}
	}

	_CrtSetDbgFlag( flags );
#endif // BOOST_MS_CRT_BASED_DEBUG
}

#ifdef _DEBUG

	#ifndef _NORMAL_BLOCK    
	#define _NORMAL_BLOCK 1
	#endif

	#include <crtdbg.h> 
	#define BOOST_TEST_DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
	#define new BOOST_TEST_DEBUG_NEW

#else

	#define BOOST_TEST_DEBUG_NEW

#endif

#endif
