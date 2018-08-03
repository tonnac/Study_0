char* FindFile(void)
{
	struct _finddata_t file;
	struct _finddata_t next;
	// 핸들  ↓
	intptr_t hFile = _findfirst("*.txt", &file);
	if (hFile == -1L)
	{
		return NULL;
	}
	else
	{
		next = file;
		//printf("nor rdo hid arc sub sys name time size\n");
		do
		{
			FileSort(&next);

			//				111111
			//				100000

			/*printf((next.attrib & _A_NORMAL) ? " Y " : " N ");
			printf((next.attrib & _A_RDONLY) ? " Y " : " N ");
			printf((next.attrib & _A_HIDDEN) ? " Y " : " N ");
			printf((next.attrib & _A_ARCH) ? " Y " : " N ");
			printf((next.attrib & _A_SUBDIR) ? " Y " : " N ");
			printf((next.attrib & _A_SYSTEM) ? " Y " : " N ");
			printf("%-12s %.24s %9ld\n",
			next.name,
			ctime(&(next.time_write)),
			next.size
			);*/

		} while (_findnext(hFile, &next) == 0);
	}
	//1) 폴더의 모든파일 검색.
	//2) 검색된 파일중에 최근파일 반환.
	//3) 검색된 파일중에 원하는 파일 로드.
	return g_file[0].name;
}
void FileSort(struct _finddata_t * pFile)
{
	if (g_iNumFiles >= MAX_COUNT)
	{
		return;
	}
	struct _finddata_t file;
	int iCnt;
	for (iCnt = 0; iCnt < g_iNumFiles; iCnt++)
	{
		memcpy(&file, &g_file[iCnt], sizeof(struct _finddata_t));
		if (file.time_create < pFile->time_create)
		{
			break;
		}
	}

	for (int iIndex = g_iNumFiles;
		iIndex > iCnt
		; iIndex--)
	{
		memcpy(&g_file[iIndex], &g_file[iIndex - 1], sizeof(struct _finddata_t));
	}
	memcpy(&g_file[iCnt], pFile, sizeof(struct _finddata_t));
	g_iNumFiles++;
}