#pragma once
#include "Duba.h"

/*��Դ��*/
signed int _InitializeResourceLite(); //In Entry
BOOLEAN __stdcall _AcquireResourceSharedLiteByEresource(PERESOURCE Resource);  //1EF1E
void __stdcall _ReleaseResourceLiteByEresource(PERESOURCE Resource);//1EF48
int  Asm_3A1E7();
/*
In KiFastCallEntry
*/
NTSTATUS _InitializResourceLite409BA();
BOOLEAN __stdcall _AcquireResourceExclusiveLiteByResource(PERESOURCE Resource);//sub_1EF33


PDEVICE_OBJECT _OpenPhysicalDrive0();
/*
�Ƿ�ҳ�ڴ�
*/
int _AllocMemoryWithLength(SIZE_T NumberOfBytes);
void _ReleaseMemoryWithLength(PVOID p);



/*
LookasideList
*/
signed int _InitializePagedLookasideList();   // sub_1E0EB();
void   _InitializeNPagedLookasideList(); //sub_34D86()

