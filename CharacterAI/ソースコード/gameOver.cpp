#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "gameOver.h"

#include "title.h"
#include "Polygon2D.h"
#include "gameOverLogo.h"
#include "fade.h"


void GameOver::Init()
{
	AddGameObject<GameOverLogo>(2);
	m_Fade = AddGameObject<Fade>(2);
}

void GameOver::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Title>();
	}
}