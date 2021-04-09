#include "DXUT.h"
#include "file_manager.h"
#include "global.h"

void FileManager::Save(char name[128])
{
	FILE* fp = nullptr;

	fopen_s(&fp, "ranking.txt", "wt");

	char cname[128];
	//strcpy_s<128>(cname, name);
	strcpy_s(playerInfo[5].name, name);
	playerInfo[5].score = score;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (playerInfo[i].score < playerInfo[j].score)
			{
				PlayerInfo temp = playerInfo[i];
				playerInfo[i] = playerInfo[j]; 
				playerInfo[j] = temp;
			}
			
		}
	}
	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%s %d\n", playerInfo[i].name, playerInfo[i].score);
	}

	fclose(fp);
}

void FileManager::Load()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "ranking.txt", "rt");
	char name[128];
	int score;
	if (fp != nullptr)
	{
		for (int i = 0; i < 5; i++)
		{
			int score;
			char name[128];
			fscanf_s(fp, "%s %d", playerInfo[i].name, 128, &playerInfo[i].score);
		}
		
	}


	fclose(fp);
}
