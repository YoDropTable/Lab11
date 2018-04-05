#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	
	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms724381(v=vs.85).aspx
	//Get Page Size
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	MEMORY_BASIC_INFORMATION buffer;

	//Print Page Size
	printf("Page Size is %u\n", systemInfo.dwPageSize);
	printf("-------------------------------------------\n");
	int *allocatedMemory;

	//allocating memory 2^20 = 1048576
	allocatedMemory = (int *)malloc(1048576);
	printf("Allocating Memory\n");

	/* from https://msdn.microsoft.com/en-us/library/windows/desktop/aa366775(v=vs.85).aspx
	State	Meaning
	MEM_COMMIT
	0x1000
	Indicates committed pages for which physical storage has been allocated, 
	either in memory or in the paging file on disk.

	MEM_FREE
	0x10000
	Indicates free pages not accessible to the calling process and available to be allocated. 
	For free pages, the information in the AllocationBase, AllocationProtect, Protect, and Type members is undefined.

	MEM_RESERVE
	0x2000
	Indicates reserved pages where a range of the process's virtual address space is 
	reserved without any physical storage being allocated. For reserved pages, the information in the Protect member is undefined.
	*/
	//fill buffer structure
	if (VirtualQuery(allocatedMemory, &buffer, sizeof(buffer)) == 0) {
		printf("Error on Virtual Query\n");
	}

	//Switch on Buffer State
	switch (buffer.State) {
	case 0x1000: //4096
		printf("----> Memory Commited\n");
		break;
	case 0x10000: //65536
		printf("----> Memory Free\n");
		break;
	case 0x2000: //8192
		printf("----> Memory Reserved\n");
		break;
	}
	
	//Free up memory
	free(allocatedMemory);
	printf("Freeing Memory\n");

	//fill buffer structure
	if (VirtualQuery(allocatedMemory, &buffer, sizeof(buffer)) == 0) {
		printf("Error on Virtual Query 2");
	}

	//Switch on buffer State
	switch (buffer.State) {
	case 0x1000: //4096
		printf("----> Memory Commited\n");
		break;
	case 0x10000: //65536
		printf("----> Memory Free\n");
		break;
	case 0x2000: //8192
		printf("----> Memory Reserved\n");
		break;
	}

	//Needed a line to break on for visual studio
	printf("Program Complete");
}
