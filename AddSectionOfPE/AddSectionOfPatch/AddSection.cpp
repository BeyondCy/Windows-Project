//
//   ���ɵĳ���  ԭ����ûʲô����   ��Win7ֻ�ܵ���Box XP�޷�ִ��   ��PE Tool ִ��Rebuild PE֮��Ϳ�����������  ������(��_��)
//
//Wipe relocation...No relocation found��
//Rebuilding...Done!
//Validate PE Image...Done!
//
//
#include "StdAfx.h"
#include "AddSection.h"
#include "AddSectionOfPatchDlg.h"


extern CAddSectionOfPatchDlg* g_Dlg;




void Main()
{
	//���ļ�
	FILEDATA PatchFile = {0};
	FILEDATA DestFile = {0};
	BOOL bOk = GetFileMess(&PatchFile,L"Patch.exe");
	if(bOk==TRUE)
	{
		CString mz;
		mz.Format(L"���������СΪ:%d",PatchFile.ulFileSize);
		g_Dlg->AddListInfo(mz);
	}
	else
	{
		return;
	}
	bOk = GetFileMess(&DestFile,L"Notepad.exe");
	if(bOk==TRUE)
	{
		CString mz;
		mz.Format(L"Ŀ������СΪ:%d",DestFile.ulFileSize);
		g_Dlg->AddListInfo(mz);
	}
	else
	{
		return;
	}


	//��ȡԭ�ļ�PEͷ��PE����
	DWORD	dwValidHeaderSize	=	GetValidHeadSize(DestFile.lpFileData);

	if (dwValidHeaderSize==0)
	{
		return;
	}

	//������ļ�ͷ���ļ�����
	DWORD dwFileAlign	=	0;
	DWORD dwNewFileHeaderSize	=	0;
	dwFileAlign	=	GetFileAlign(DestFile.lpFileData);
	dwNewFileHeaderSize	=	((dwValidHeaderSize+2*sizeof(IMAGE_SECTION_HEADER)+dwFileAlign)/dwFileAlign)*dwFileAlign; //�����Ժ���ļ�ͷ��С

	CString str;
	str.Format(L"�����Ժ��New�ļ�ͷ��С �� 0x%p",dwNewFileHeaderSize);
	g_Dlg->AddListInfo(str);


	//���Ŀ�겹����С  196h   �����200h
	DWORD dwPatchCodeSize = GetCodeSize(PatchFile.lpFileData);
	//������½ڴ�С
	DWORD dwNewSectionSize
		=	((dwPatchCodeSize+dwFileAlign)/dwFileAlign)*dwFileAlign; 


	str.Format(L"�����PatchCodeSize �� 0x%p",dwNewSectionSize);
	g_Dlg->AddListInfo(str);



	//�����ļ��Ĵ�С
	DWORD	dwNewFileSize	=	0;
	DWORD	dwOff			=	0;
	PIMAGE_SECTION_HEADER DestSectionHeader;
	PIMAGE_DOS_HEADER	DestDosHeader	=	(PIMAGE_DOS_HEADER)DestFile.lpFileData;
	PIMAGE_NT_HEADERS	DestNtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DestDosHeader+(ULONG_PTR)DestDosHeader->e_lfanew);

	DestSectionHeader	=	(PIMAGE_SECTION_HEADER)((ULONG_PTR)DestNtHeader+sizeof(IMAGE_NT_HEADERS));
	//�ļ�����Ĳ��� dwOff = 0
	dwOff	=		dwNewFileHeaderSize - DestSectionHeader[0].PointerToRawData;
	//���ļ���С = ԭ�ļ���С + ��ӽڱ�����Ĳ��� + �½ڶ����Ĳ���
	dwNewFileSize	=	DestFile.ulFileSize	+	dwOff + dwNewSectionSize;     //����200
	
	str.Format(L"New�ļ���С �� 0x%p",dwNewFileSize);
	g_Dlg->AddListInfo(str);


	//�����ڴ�
	FILEDATA	NewFile	=	{0};
	wcscpy(NewFile.wzFilePath,L"NewFile.exe");

	NewFile.ulFileSize	=	dwNewFileSize;
	NewFile.lpFileData	=	(BYTE*)malloc(dwNewFileSize);

	if (NewFile.lpFileData==NULL)
	{
		return;
	}
	memset(NewFile.lpFileData,0,NewFile.ulFileSize);



	//��ʼ����
	DWORD  dwCopySize	=	0;
	memcpy(NewFile.lpFileData,DestFile.lpFileData,dwValidHeaderSize);  //����ԭʼDos Nt �ڱ�
	dwCopySize	+=	dwNewFileHeaderSize;   //�ӹ�������ļ�ͷ��С  Խ���ļ�ͷ
	str.Format(L"��Ŀ���ļ��ļ���DOSͷ���ָ��Ƶ��ڴ����� Size�� 0x%p",dwValidHeaderSize);
	g_Dlg->AddListInfo(str);

	//���ƽڵ���ϸ����
	DWORD dwFirstSectionRaw	=	DestSectionHeader[0].PointerToRawData;  //�ӵ�һ���ڿ�ʼ��֮�����ж�������
	DWORD dwNeedCopy			=	DestFile.ulFileSize - dwFirstSectionRaw;

	memcpy((PVOID)((DWORD)(NewFile.lpFileData)+dwNewFileHeaderSize),(PVOID)((DWORD)DestFile.lpFileData+dwFirstSectionRaw),dwNeedCopy);
	dwCopySize	+=	dwNeedCopy;
	str.Format(L"���ƽڵ���ϸ���� Size�� 0x%p",dwNeedCopy);
	g_Dlg->AddListInfo(str);





	DWORD dwOldEntryPoint = DestNtHeader->OptionalHeader.AddressOfEntryPoint;   //�ɵ�EntryPoint
	DWORD OldSectionNum = DestNtHeader->FileHeader.NumberOfSections;

	PIMAGE_SECTION_HEADER FirstSection = (PIMAGE_SECTION_HEADER)((ULONG_PTR)DestNtHeader+sizeof(IMAGE_NT_HEADERS));
//���һ���ڱ�
	PIMAGE_SECTION_HEADER LastSection = (PIMAGE_SECTION_HEADER)((ULONG_PTR)FirstSection+(OldSectionNum-1)*sizeof(IMAGE_SECTION_HEADER));

//Խ�����һ���ڱ����õĵ�ַ 10600
	DWORD LastSectionPointRaw = 
		((LastSection->PointerToRawData+LastSection->SizeOfRawData)/dwFileAlign)*dwFileAlign; //�����Ժ���ļ�ͷ��С
	               //8400                       8000

	//������
	DWORD dwPatchCodeSegStart	=	0;
	dwPatchCodeSegStart	=	GetPatchCodeSegStart(PatchFile.lpFileData);		//���Code����ʼ��ַ

	memcpy((PVOID)(LastSectionPointRaw+(ULONG_PTR)NewFile.lpFileData),(PVOID)((DWORD)PatchFile.lpFileData+dwPatchCodeSegStart),dwPatchCodeSize);
	dwCopySize	+= dwPatchCodeSize;


	str.Format(L"���Ʋ������� Size�� 0x%p",dwPatchCodeSize);
	g_Dlg->AddListInfo(str);

	//������ϣ��޸��¼ӱ�ͷ




	IMAGE_SECTION_HEADER SectionNew = {0};
	strcpy((char*)SectionNew.Name,".mz");             //������
	SectionNew.Misc.VirtualSize = dwPatchCodeSize;    //ʵ�ʴ�С
	SectionNew.SizeOfRawData =dwNewSectionSize; // 0x19A;      //�ļ�������С   dwNewSectionSize
	SectionNew.PointerToRawData = LastSectionPointRaw;//�ڵ��ļ�ƫ��
	SectionNew.Characteristics = (DWORD)0x60000020  ; //��ҳ�������  �ɶ���д��ִ��   
	SectionNew.VirtualAddress = DestNtHeader->OptionalHeader.SizeOfImage;   //�����ڴ��м��ص�ַ  
	
	

	
	
	PIMAGE_DOS_HEADER	NewDosHeader	=	(PIMAGE_DOS_HEADER)(NewFile.lpFileData);
	PIMAGE_NT_HEADERS	NewNtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)NewDosHeader+(ULONG_PTR)NewDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER NewSection = (PIMAGE_SECTION_HEADER)((ULONG_PTR)NewNtHeader+sizeof(IMAGE_NT_HEADERS));


	//�������  RVA
	NewNtHeader->OptionalHeader.AddressOfEntryPoint = DestNtHeader->OptionalHeader.SizeOfImage;
	//������
	NewNtHeader->FileHeader.NumberOfSections++;
	//�ļ�ͷ��С
	NewNtHeader->OptionalHeader.SizeOfHeaders = dwNewFileHeaderSize;
	//�ļ����ڴ��д�С
	NewNtHeader->OptionalHeader.SizeOfImage = DestNtHeader->OptionalHeader.SizeOfImage+ dwPatchCodeSize; //DestNtHeader->OptionalHeader.SectionAlignment;

	PIMAGE_SECTION_HEADER NewFirstSection = (PIMAGE_SECTION_HEADER)((ULONG_PTR)NewNtHeader+sizeof(IMAGE_NT_HEADERS));
	PIMAGE_SECTION_HEADER NewLastSection = (PIMAGE_SECTION_HEADER)((ULONG_PTR)NewFirstSection+(OldSectionNum)*sizeof(IMAGE_SECTION_HEADER));


	//����ͷ��Ϣ����
	memcpy(NewLastSection,&SectionNew,sizeof(IMAGE_SECTION_HEADER));


	//��������OEP
	DWORD dwJmpAddr	=	(DWORD)NewFile.lpFileData+LastSectionPointRaw+dwPatchCodeSize -5;
	DWORD dwJmpOff	=	dwOldEntryPoint	-	(DestNtHeader->OptionalHeader.SizeOfImage+dwPatchCodeSize -5 +4);
	*(DWORD*)dwJmpAddr		=	dwJmpOff;

	str.Format(L"������������E9֮��Ĳ�����   �� 0x%p",dwJmpOff);
	g_Dlg->AddListInfo(str);


	
	RemoveIatDirectory((ULONG_PTR)NewFile.lpFileData);
	str.Format(L"�Ƴ������ɹ���");
	g_Dlg->AddListInfo(str);

	if (IcWriteFile(&NewFile))
	{
		str	=	L"�����ļ� :  ";
		str	+=	NewFile.wzFilePath;
		g_Dlg->AddListInfo(str);
	}


	if (PatchFile.lpFileData!=NULL)
	{
		free(PatchFile.lpFileData);
		PatchFile.lpFileData	=	NULL;
	}
	if (DestFile.lpFileData!=NULL)
	{
		free(DestFile.lpFileData);
		DestFile.lpFileData	=	NULL;
	}
	if (NewFile.lpFileData!=NULL)
	{
		free(NewFile.lpFileData);
		NewFile.lpFileData	=	NULL;

	}

}
void RemoveIatDirectory(ULONG_PTR lpData)
{
		DWORD SearchAddress = 0;


		PIMAGE_DOS_HEADER DosHeader = (PIMAGE_DOS_HEADER)lpData;
		PIMAGE_NT_HEADERS NtHeader = (PIMAGE_NT_HEADERS)((ULONG_PTR)lpData + DosHeader->e_lfanew);

		SearchAddress = NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;

		NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

	//	NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress =0;
	//	NtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	
		PIMAGE_SECTION_HEADER SectionHeader = (PIMAGE_SECTION_HEADER)((ULONG_PTR)NtHeader  + sizeof(IMAGE_NT_HEADERS)) ;
		DWORD	dwNumberOfSection				=	NtHeader->FileHeader.NumberOfSections;

	
	if (SearchAddress)
	{
		for (WORD i = 0; i < dwNumberOfSection; i++)
		{
			if (SectionHeader[i].VirtualAddress <= SearchAddress && (SectionHeader[i].VirtualAddress + SectionHeader[i].Misc.VirtualSize) > SearchAddress)
			{
				//section must be read and writable
				SectionHeader[i].Characteristics |= IMAGE_SCN_MEM_READ|IMAGE_SCN_MEM_WRITE;
			}
		}
	}
}


BOOL IcWriteFile(PFILEDATA FileData)
{
	HANDLE		hFile		=	NULL;

	hFile = CreateFile(FileData->wzFilePath,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile==INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}


	if (WriteFile(hFile,FileData->lpFileData,FileData->ulFileSize,&FileData->ulFileSize,NULL))
	{
		CloseHandle(hFile);


		return TRUE;

	}
	return FALSE;

}
//����ļ�FileAlign
DWORD GetFileAlign(PVOID lpData)
{
	DWORD dwRet	=	0;
	PIMAGE_DOS_HEADER	DosHeader	=	(PIMAGE_DOS_HEADER)lpData;
	PIMAGE_NT_HEADERS	NtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader+(ULONG_PTR)DosHeader->e_lfanew);


	dwRet	=	NtHeader->OptionalHeader.FileAlignment;



	return dwRet;
}

//���patchcodestart��ַ
DWORD GetPatchCodeSegStart(PVOID lpData)
{
	DWORD dwRet	=	0;

	PIMAGE_DOS_HEADER	DosHeader	=	(PIMAGE_DOS_HEADER)lpData;
	PIMAGE_NT_HEADERS	NtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader+(ULONG_PTR)DosHeader->e_lfanew);


	dwRet	=	NtHeader->OptionalHeader.AddressOfEntryPoint;
	dwRet	=	GetRVASectionStart(lpData,dwRet);




	return dwRet;
}
//��ȡRVA���ڽڵ��ļ���ʼ��ַ
DWORD GetRVASectionStart(PVOID lpData,ULONG_PTR ulAddressofEntryPoint)
{
	DWORD dwStart =	0;
	DWORD i		 =	0;

	PIMAGE_DOS_HEADER	DosHeader	=	(PIMAGE_DOS_HEADER)lpData;
	PIMAGE_NT_HEADERS	NtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader+(ULONG_PTR)DosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER	SectionHeader	=	(PIMAGE_SECTION_HEADER)((ULONG_PTR)NtHeader+sizeof(IMAGE_NT_HEADERS));
	DWORD	dwNumberOfSection				=	NtHeader->FileHeader.NumberOfSections;


	//�����ڱ� 


	for (i=0;i<dwNumberOfSection;i++)
	{

		if (ulAddressofEntryPoint>=SectionHeader[i].VirtualAddress
			&&ulAddressofEntryPoint<SectionHeader[i].VirtualAddress+SectionHeader[i].SizeOfRawData)
		{
			//Found
			dwStart	=	SectionHeader[i].PointerToRawData;

			break;

		}


	}

	return dwStart;
}

WORD GetCodeSize(PVOID BaseAddress)
{
	DWORD dwSize	=	0;


	PIMAGE_DOS_HEADER	DosHeader	=	(PIMAGE_DOS_HEADER)BaseAddress;
	PIMAGE_NT_HEADERS	NtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader+(ULONG_PTR)DosHeader->e_lfanew);


	ULONG_PTR	ulAddressOfEntryPoint	=	NtHeader->OptionalHeader.AddressOfEntryPoint;


	dwSize	=	GetRVASectionSize(BaseAddress,ulAddressOfEntryPoint);

	return	dwSize;
}
//��ȡRVA���ڽڵ�ԭʼ��С
DWORD GetRVASectionSize(PVOID BaseAddress,ULONG_PTR ulAddressofEntryPoint)
{
	DWORD dwSize =	0;
	DWORD i		 =	0;

	PIMAGE_DOS_HEADER	DosHeader	=	(PIMAGE_DOS_HEADER)BaseAddress;
	PIMAGE_NT_HEADERS	NtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader+(ULONG_PTR)DosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER	SectionHeader	=	(PIMAGE_SECTION_HEADER)((ULONG_PTR)NtHeader+sizeof(IMAGE_NT_HEADERS));
	DWORD	dwNumberOfSection				=	NtHeader->FileHeader.NumberOfSections;


	//�����ڱ� 


	for (i=0;i<dwNumberOfSection;i++)
	{

		if (ulAddressofEntryPoint>=SectionHeader[i].VirtualAddress
			&&ulAddressofEntryPoint<SectionHeader[i].VirtualAddress+SectionHeader[i].SizeOfRawData)
		{
			//Found
			dwSize	=	SectionHeader[i].Misc.VirtualSize;

			break;

		}


	}

	return dwSize;
}


DWORD GetValidHeadSize(PVOID BaseAddress)
{
	DWORD	dwRet	=	0;
	PIMAGE_DOS_HEADER	DosHeader	=	(PIMAGE_DOS_HEADER)BaseAddress;
	PIMAGE_NT_HEADERS	NtHeader	=	(PIMAGE_NT_HEADERS)((ULONG_PTR)DosHeader+(ULONG_PTR)DosHeader->e_lfanew);

	PIMAGE_SECTION_HEADER	SectionHeader	=	(PIMAGE_SECTION_HEADER)((ULONG_PTR)NtHeader+sizeof(IMAGE_NT_HEADERS));

	DWORD	dwFirstSectionRaw	=	SectionHeader[0].PointerToRawData;

	DWORD	dwTemp	=dwFirstSectionRaw	-	1;                                                                                                                                                             
	DWORD	i	=	0;


	for(i=0;i<dwFirstSectionRaw;i++)
	{
		if (((PBYTE)BaseAddress)[dwTemp-i]!=0)
		{

			dwRet	=	dwFirstSectionRaw - i + 2;		//Ϊ��Ч���ֱ��������ַ���
			return dwRet;	
		}

	}
	return 0;


}

BOOL GetFileMess(PFILEDATA FileData,CString FileName)
{
	//����ļ����
	HANDLE hFile =
	CreateFile(FileName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	
	if(hFile==INVALID_HANDLE_VALUE)
	{
		g_Dlg->AddListInfo(L"���ļ���ʼ��ʧ��...");
		return FALSE;
	}

	//����ļ���С
	DWORD dwHight  =0;
	DWORD   dwLow = GetFileSize(hFile,&dwHight);
	if(dwLow==0)
	{
		CloseHandle(hFile);
		g_Dlg->AddListInfo(L"��ȡ�ļ���Сʧ��...");
		return FALSE;
	}


	wsprintf(FileData->wzFilePath,L"s",FileName);
	FileData->ulFileSize	=	dwLow;
	//��ȡ�ļ�
	FileData->lpFileData	=	(BYTE*)malloc(dwLow);
	if (FileData->lpFileData==NULL)
	{
		return FALSE;

	}
	memset(FileData->lpFileData,0,dwLow);

	DWORD dwReadReturn = 0;
	BOOL bOk = ReadFile(hFile,FileData->lpFileData,dwLow,&dwLow,NULL);

	if (bOk==FALSE)
	{
		CloseHandle(hFile);
		return FALSE;
	}


	return TRUE;
	
}

ULONG_PTR RVAToOffset(PIMAGE_NT_HEADERS NTHeader, ULONG_PTR ulRVA)   
{
    PIMAGE_SECTION_HEADER SectionHeader =
        (PIMAGE_SECTION_HEADER)((ULONG_PTR)NTHeader + sizeof(IMAGE_NT_HEADERS));  //��ýڱ�  
    
    for(int i = 0; i < NTHeader->FileHeader.NumberOfSections; i++)
    {
        //��ѯ�������������ĸ��ڵ� 
        /***********************************************************************
            SectionHeader[i].VirtualAddress    ����ʼ��RVA  0x1000
            SectionHeader[i].SizeOfRawData     �����ļ��ϵĴ�С
            SectionHeader[i].PointerToRawData  ���ǽڻ����ļ���ƫ������PE װ����ͨ������ֵ�ҵ����������ļ��е�λ��
            ���絼������.txt����
            SectionHeader[i].PointerToRawData == 0x200       SectionHeader[i].VirtualAddress == 0x1000    
                                                             ulRVA = 0x1030
                                                             
            ��ô���������ļ��е�ƫ�ƾ���0x230  ����
        ***********************************************************************/
        if(ulRVA >= SectionHeader[i].VirtualAddress && ulRVA < 
            (SectionHeader[i].VirtualAddress 
            + SectionHeader[i].SizeOfRawData))
        {
            //�ļ�ƫ��
            return SectionHeader[i].PointerToRawData + 
                (ulRVA - SectionHeader[i].VirtualAddress);
        }
    }
    
    return 0;
}
