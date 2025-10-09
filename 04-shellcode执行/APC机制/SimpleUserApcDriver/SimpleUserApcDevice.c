#include "SimpleUserApcDevice.h"
#include "SimpleUserApcControl.h"
#include "SimpleUserApc.h"


NTSTATUS
SimpleUserApcDefaultSuccess(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp
	);

NTSTATUS
SimpleUserApcIoControlDispatch(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp
	);

static UNICODE_STRING gDeviceName = RTL_CONSTANT_STRING(L"\\Device\\" SIMPLE_USER_APC_DEVICE_NAME_W);
static UNICODE_STRING gDeviceSymbolicLink = RTL_CONSTANT_STRING(L"\\??\\" SIMPLE_USER_APC_DEVICE_NAME_W);
static PDEVICE_OBJECT gDeviceObject = NULL;

NTSTATUS
SimpleUserApcInitializeDevice(
	PDRIVER_OBJECT DriverObject
	)
{
	struct {
		BOOLEAN InitializedDevice;
	} CleanupState = {0};

	NTSTATUS Status;

	Status = IoCreateDevice(
			DriverObject,
			0,
			&gDeviceName,
			FILE_DEVICE_UNKNOWN,
			0,
			TRUE,
			&gDeviceObject
		);

	if (!NT_SUCCESS(Status)) {
		goto Cleanup;
	}
	
	CleanupState.InitializedDevice = TRUE;

	Status = IoCreateSymbolicLink(&gDeviceSymbolicLink, &gDeviceName);

	if (!NT_SUCCESS(Status)) {
		goto Cleanup;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE] = SimpleUserApcDefaultSuccess;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = SimpleUserApcDefaultSuccess;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = SimpleUserApcIoControlDispatch;
	
	Status = STATUS_SUCCESS;

Cleanup:
	if (!NT_SUCCESS(Status)) {
		if (CleanupState.InitializedDevice) {
			IoDeleteDevice(gDeviceObject);
		}
	}

	return Status;
}

VOID
SimpleUserApcDeleteDevice(
	VOID
	)
{
	IoDeleteSymbolicLink(&gDeviceSymbolicLink);
	IoDeleteDevice(gDeviceObject);
}

NTSTATUS
SimpleUserApcDefaultSuccess(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp
	)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	UNREFERENCED_PARAMETER(Irp);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS
SimpleUserApcIoControlDispatch(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp
	)
{
	UNREFERENCED_PARAMETER(DeviceObject);


	NTSTATUS Status = STATUS_SUCCESS;
	PIO_STACK_LOCATION IoStackLocation = IoGetCurrentIrpStackLocation(Irp);
	

	switch (IoStackLocation->Parameters.DeviceIoControl.IoControlCode) {
	case IOCTL_SIMPLE_USER_APC_QUEUE: {
		if (IoStackLocation->Parameters.DeviceIoControl.InputBufferLength != sizeof(SIMPLE_QUEUE_APC_THREAD)) {
			Status = STATUS_INFO_LENGTH_MISMATCH;
			goto Cleanup;
		}

		PSIMPLE_QUEUE_APC_THREAD QueueApcArguments = (PSIMPLE_QUEUE_APC_THREAD)Irp->AssociatedIrp.SystemBuffer;
		
		Status = SimpleNtQueueApcThread(
			QueueApcArguments->ThreadHandle,
			QueueApcArguments->ApcRoutine,
			QueueApcArguments->SystemArgument1,
			QueueApcArguments->SystemArgument2,
			QueueApcArguments->SystemArgument3
		);
	}
	break;
	case IOCTL_SIMPLE_USER_APC_WAIT: {
		if (IoStackLocation->Parameters.DeviceIoControl.InputBufferLength != sizeof(SIMPLE_USER_APC_WAIT)) {
			Status = STATUS_INFO_LENGTH_MISMATCH;
			goto Cleanup;
		}

		PSIMPLE_USER_APC_WAIT Wait = (PSIMPLE_USER_APC_WAIT)Irp->AssociatedIrp.SystemBuffer;

		Status = SimpleNtWaitForSingleObject(
			Wait->Event,
			Wait->Alertable,
			&Wait->Timeout
		);
	}
	break;
	default:
	break;
	}

Cleanup:
	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = 0;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return Status;
}