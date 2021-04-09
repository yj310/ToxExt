#pragma once
#include "page.h"

class PageManager
{
public:
	PageManager();

	Page* currentPage;



	void CreateTitlePage();
	void CreateFirstGamePage();
	void CreateSecondGamePage();
	void CreateIntroPage();
	void CreateManualPage();
	void CreateRankingPage();
	void CreateInputPage();

	void Update();
	void Render();
	void DeleteCurrentPage();




};