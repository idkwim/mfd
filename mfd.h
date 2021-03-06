#ifndef __MFD_H__
#define __MFD_H__

#pragma warning(push)
#pragma warning(disable:4510)
#pragma warning(disable:4512)
#pragma warning(disable:4610)
#include <fltKernel.h>
#pragma warning(pop)
#pragma optimize("", off)

#include "mfd_pre_handler.h"
#include "mfd_post_handler.h"

#define FLT_FILTER_NAME L"\\mfd"
// DbgPrintEx(DPFLTR_DEFAULT_ID, DPFLTR_ERROR_LEVEL, "DbgPrintEx\n");

#ifdef __cplusplus
extern "C" {
#endif

	NTSTATUS
	FLTAPI MFDPortMessage(
		_In_ PVOID pvConnectionCookie,
		_In_ PVOID pvInputBuffer,
		_In_ ULONG ulInputBufferSize,
		_Out_ PVOID pvOutputBuffer,
		_Out_ ULONG ulOutputBufferSize,
		_Out_ PULONG pulRetOutputBufferSize
	);

	NTSTATUS
	FLTAPI MFDPortConnect(
		_In_ PFLT_PORT pClientPort,
		_In_ PVOID pvServerPortCookie,
		_In_ PVOID pvConnectionContext,
		_In_ ULONG ulSizeOfContext,
		_In_ PVOID *pvConnectionCookie
	);

	VOID
	FLTAPI MFDPortDisconnect(
		_In_ PVOID pvConnectionCookie
	);

	NTSTATUS
	FLTAPI MFDInstanceSetup(
		_In_ PCFLT_RELATED_OBJECTS pFltObjects,
		_In_ FLT_INSTANCE_SETUP_FLAGS Flags,
		_In_ DEVICE_TYPE VolumeDeviceType,
		_In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
	);

	VOID
	FLTAPI MFDInstanceTeardown(
		_In_ PCFLT_RELATED_OBJECTS pFltObjects,
		_In_ FLT_INSTANCE_TEARDOWN_FLAGS Reason
	);

	NTSTATUS
	FLTAPI DriverUnload(
		_In_ FLT_FILTER_UNLOAD_FLAGS Flags
	);

	NTSTATUS
	DriverEntry(
		_In_ PDRIVER_OBJECT pDriverObject,
		_In_ PUNICODE_STRING puniRegistryPath
	);

#ifdef __cplusplus
}
#endif

CONST FLT_OPERATION_REGISTRATION Callbacks[] =
{
	{
		IRP_MJ_CREATE,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_READ,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_WRITE,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_QUERY_INFORMATION,
		0,
		MFDPreHandler, 
		MFDPostHandler
	},
	{
		IRP_MJ_SET_INFORMATION,
		0,
		MFDPreHandler,
		MFDPostHandler
	},	
	{
		IRP_MJ_QUERY_VOLUME_INFORMATION,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_SET_VOLUME_INFORMATION,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_DIRECTORY_CONTROL,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_FILE_SYSTEM_CONTROL,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_DEVICE_CONTROL,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_INTERNAL_DEVICE_CONTROL,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{
		IRP_MJ_CLEANUP,
		0,
		MFDPreHandler,
		MFDPostHandler
	},
	{ IRP_MJ_OPERATION_END }
};

typedef struct _MFD_VOLUME_CONTEXT
{
	PVOID pvReserved;
}MFD_VOLUME_CONTEXT, *PMFD_VOLUME_CONTEXT;

typedef struct _PMFD_INSTANCE_CONTEXT
{
	PVOID pvReserved;
}MFD_INSTANCE_CONTEXT, *PMFD_INSTANCE_CONTEXT;

typedef struct _MFD_FILE_CONTEXT
{
	PVOID pvReserved;
}MFD_FILE_CONTEXT, *PMFD_FILE_CONTEXT;

typedef struct _MFD_STREAM_CONTEXT
{
	PVOID pvReserved;
}MFD_STREAM_CONTEXT, *PMFD_STREAM_CONTEXT;

typedef struct _MFD_STREAMHANDLE_CONTEXT
{
	PVOID pvReserved;
}MFD_STREAMHANDLE_CONTEXT, *PMFD_STREAMHANDLE_CONTEXT;

typedef struct _MFD_TRANSACTION_CONTEXT
{
	PVOID pvReserved;
}MFD_TRANSACTION_CONTEXT, *PMFD_TRANSACTION_CONTEXT;

FLT_CONTEXT_REGISTRATION FilterContextRegistration[] =
{
	{
		FLT_VOLUME_CONTEXT,
		0,
		NULL,
		sizeof(MFD_VOLUME_CONTEXT),
		'MFDV',
		NULL,
		NULL,
		NULL
	},
	{
		FLT_INSTANCE_CONTEXT,
		0,
		NULL,
		sizeof(MFD_INSTANCE_CONTEXT),
		'MFDI',
		NULL,
		NULL,
		NULL
	},
	{
		FLT_FILE_CONTEXT,
		0,
		NULL,
		sizeof(MFD_FILE_CONTEXT),
		'MFDF',
		NULL,
		NULL,
		NULL
	},
	{
		FLT_STREAM_CONTEXT,
		0,
		NULL,
		sizeof(MFD_STREAM_CONTEXT),
		'MFDS',
		NULL,
		NULL,
		NULL
	},
	{
		FLT_STREAMHANDLE_CONTEXT,
		0,
		NULL,
		sizeof(MFD_STREAMHANDLE_CONTEXT),
		'MFDH',
		NULL,
		NULL,
		NULL
	},
	{
		FLT_TRANSACTION_CONTEXT,
		0,
		NULL,
		sizeof(MFD_TRANSACTION_CONTEXT),
		'MFDT',
		NULL,
		NULL,
		NULL
	},
	{ FLT_CONTEXT_END }
};

FLT_REGISTRATION FilterRegistration =
{
	sizeof(FLT_REGISTRATION),
	FLT_REGISTRATION_VERSION,
	0, // FLTFL_REGISTRATION_DO_NOT_SUPPORT_SERVICE_STOP
	FilterContextRegistration,
	Callbacks,
	DriverUnload,
	MFDInstanceSetup,
	NULL,
	MFDInstanceTeardown,
	NULL,
	NULL
};

typedef struct _MFD_CONTEXT
{
	PFLT_FILTER pMFDFilter;
	PFLT_PORT pServerPort;
	PFLT_PORT pClientPort;
}MFD_CONTEXT, *PMFD_CONTEXT;

#endif