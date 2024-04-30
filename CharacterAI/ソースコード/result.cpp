#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "result.h"

#include "title.h"
#include "Polygon2D.h"
#include "ResultLogo.h"
#include "fade.h"


void Result::Init()
{
	AddGameObject<ResultLogo>(2);
	m_Fade = AddGameObject<Fade>(2);
}

void Result::Update()
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