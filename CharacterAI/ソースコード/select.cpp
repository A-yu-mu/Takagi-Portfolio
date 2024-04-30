#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "select.h"

#include "game.h"
#include "game01.h"
#include "game02.h"
#include "Polygon2D.h"
#include "fade.h"


void Select::Init()
{
	m_SelectNumber = 1;
	m_SelectNumberMax = 3;
	m_Fade = AddGameObject<Fade>(2);
}

void Select::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger('D'))	//Dキーで
	{
		m_SelectNumber++;
	}
	if (Input::GetKeyTrigger('A'))	//Aキーで
	{
		m_SelectNumber--;
	}

	if (m_SelectNumber > m_SelectNumberMax)
	{
		m_SelectNumber = m_SelectNumberMax;
	}
	else if (m_SelectNumber <= 0)
	{
		m_SelectNumber = 1;
	}
	


	switch (m_SelectNumber)
	{
	case 1:
		// ステージ１の画像

		AddGameObject<Polygon2D>(2)->SelectStage(1);
		break;
	case 2:
		// ステージ２の画像

		AddGameObject<Polygon2D>(2)->SelectStage(2);
		break;
	case 3:
		// ステージ3の画像

		AddGameObject<Polygon2D>(2)->SelectStage(3);
		break;
	default:
		break;
	}


	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}
	if (m_SelectNumber == 1)
	{
		if (m_Fade->GetFadeFinish())
		{
			Manager::SetScene<Game>();
		}
	}
	else if (m_SelectNumber == 2)
	{
		if (m_Fade->GetFadeFinish())
		{
			Manager::SetScene<Game01>();
		}
	}
	else if (m_SelectNumber == 3)
	{
		if (m_Fade->GetFadeFinish())
		{
			Manager::SetScene<Game02>();
		}
	}
}