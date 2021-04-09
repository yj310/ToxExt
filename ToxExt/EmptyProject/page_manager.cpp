#include "DXUT.h"
#include "page_manager.h"
#include "title_page.h"
#include "first_game_page.h"
#include "second_game_page.h"
#include "intro_page.h"
#include "manual_page.h"
#include "ranking_page.h"
#include "input_page.h"

PageManager::PageManager()
{
	currentPage = nullptr;
}

void PageManager::CreateTitlePage()
{
	DeleteCurrentPage();
	currentPage = new TitlePage();
}

void PageManager::CreateFirstGamePage()
{
	DeleteCurrentPage();
	currentPage = new FirstGamePage();
}

void PageManager::CreateSecondGamePage()
{
	DeleteCurrentPage();
	currentPage = new SecondGamePage();
}

void PageManager::CreateIntroPage()
{
	DeleteCurrentPage();
	currentPage = new IntroPage();
}

void PageManager::CreateManualPage()
{
	DeleteCurrentPage();
	currentPage = new ManualPage();
}

void PageManager::CreateRankingPage()
{
	DeleteCurrentPage();
	currentPage = new RankingPage();
}

void PageManager::CreateInputPage()
{
	DeleteCurrentPage();
	currentPage = new InputPage();
}

void PageManager::Update()
{
	if (currentPage != nullptr)
	{
		currentPage->Update();
	}
}

void PageManager::Render()
{
	if (currentPage != nullptr)
	{
		currentPage->Render();
	}
}

void PageManager::DeleteCurrentPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}

}
