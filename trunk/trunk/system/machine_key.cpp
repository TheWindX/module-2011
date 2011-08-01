
#include <windows.h>
#include "machine_key.h"

bool GetCpuId(long& id_out)   
{   
	BOOL bException = FALSE;   
	BYTE szCpu[16]  = { 0 };   
	UINT uCpuID     = 0U;   
	__try    
	{   
		_asm    
		{   
			mov eax, 0   
				cpuid   
				mov dword ptr szCpu[0], ebx   
				mov dword ptr szCpu[4], edx   
				mov dword ptr szCpu[8], ecx   
				mov eax, 1   
				cpuid   
				mov uCpuID, edx   
		}   
	}   
	__except( EXCEPTION_EXECUTE_HANDLER )   
	{   
		bException = TRUE;   
		return false;
	}   
	id_out = uCpuID;
	return true;
}


// IOCTL 指令常数
#define DFP_GET_VERSION   0x00074080
#define DFP_RECEIVE_DRIVE_DATA 0x0007c088
// 用于 IDEREGS 结构 bCommandReg 项的有效值
#define IDE_ATAPI_IDENTIFY  0xA1
#define IDE_ATA_IDENTIFY  0xEC
#define IDENTIFY_BUFFER_SIZE 512
// 结构体定义
// 保存磁盘驱动器的信息
typedef struct _GETVERSIONOUTPARAMS
{
	BYTE bVersion;
	BYTE bRevision;
	BYTE bReserved;
	BYTE bIDEDeviceMap;
	DWORD fCapabilities;
	DWORD dwReserved[4];
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;

bool GetDiskPhysicalSN(char pchDiskPhysicalSN[14])
{
	BYTE IdOutCmd[530];
	HANDLE drive=CreateFile ("\\\\.\\PhysicalDrive0", GENERIC_READ | 
		GENERIC_WRITE, 

		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,

		OPEN_EXISTING, 0, NULL);
	if (drive == INVALID_HANDLE_VALUE)
	{
		// 错误处理
		return false;
	}
	GETVERSIONOUTPARAMS VersionParams;
	DWORD cbBytesReturned = 0;
	memset ((void*) &VersionParams, 0, sizeof(VersionParams));
	if (!DeviceIoControl(drive, DFP_GET_VERSION, NULL, 0, 
		&VersionParams,
		sizeof
		(VersionParams), &cbBytesReturned, NULL))
	{
		// 错误处理
		return false;
	}
	if (VersionParams.bIDEDeviceMap<=0)
	{
		// 错误处理
		return false;
	}
	BYTE bIDCmd = 0;
	SENDCMDINPARAMS scip;
	bIDCmd = (VersionParams.bIDEDeviceMap >> 0 & 0x10) ? 
IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;
	memset (&scip, 0, sizeof(scip));
	memset (IdOutCmd, 0, sizeof(IdOutCmd));
	scip.cBufferSize=IDENTIFY_BUFFER_SIZE;
	scip.irDriveRegs.bFeaturesReg=0;
	scip.irDriveRegs.bSectorCountReg=1;
	scip.irDriveRegs.bSectorNumberReg=1;
	scip.irDriveRegs.bCylLowReg=0;
	scip.irDriveRegs.bCylHighReg=0;
	scip.irDriveRegs.bDriveHeadReg=0xA0 | (((BYTE) drive & 1) << 4);
	scip.irDriveRegs.bCommandReg=bIDCmd;
	scip.bDriveNumber=(BYTE) drive;
	scip.cBufferSize=IDENTIFY_BUFFER_SIZE;
	if (!DeviceIoControl(drive, DFP_RECEIVE_DRIVE_DATA, &scip, sizeof
		(SENDCMDINPARAMS) - 1,
		(LPVOID)&IdOutCmd, 
		sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
		&cbBytesReturned, 
		NULL))
	{
		// 错误处理
		return false;
	}
	USHORT *pIdSector = (USHORT *)((PSENDCMDOUTPARAMS) IdOutCmd) -> 
		bBuffer;
	int nIndex=0, nPosition=0;
	for (nIndex=13; nIndex<20; nIndex++)
	{
		pchDiskPhysicalSN[nPosition++]=(unsigned char)(pIdSector
			[nIndex]/256);
		pchDiskPhysicalSN[nPosition++]=(unsigned char)(pIdSector
			[nIndex]%256);
	}
	return true;
}