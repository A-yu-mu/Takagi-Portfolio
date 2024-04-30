#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "game01.h"

#include "result.h"
#include "gameOver.h"
#include "camera.h"
#include "field.h"
#include "Polygon2D.h"
#include "sky.h"
#include "player.h"
#include "enemy.h"
#include "cylinder.h"
#include "box.h"
#include "score.h"
#include "goal.h"
#include "audio.h"
#include "fade.h"
#include "distance.h"
#include "death.h"


void Game01::Init()
{
	AddGameObject<Camera>(1);
	AddGameObject<Sky>(1);
	AddGameObject<Field>(1);
	AddGameObject<Player>(1)->SetPosition(D3DXVECTOR3(7.0f, 0.0f, -1.0f));
	AddGameObject<Goal>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 30.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(11.0f, 0.0f, 20.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-12.0f, 0.0f, 20.0f));

	Cylinder* cylinder = AddGameObject<Cylinder>(1);
	cylinder->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 15.0f));
	cylinder->SetScale(D3DXVECTOR3(6.0f, 4.0f, 6.0f));

	{
		Box* box0 = AddGameObject<Box>(1);
		box0->SetPosition(D3DXVECTOR3(-20.0f, -1.0f, 0.0f));
		box0->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box1 = AddGameObject<Box>(1);
		box1->SetPosition(D3DXVECTOR3(-20.0f, -1.0f, 10.0f));
		box1->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box2 = AddGameObject<Box>(1);
		box2->SetPosition(D3DXVECTOR3(-20.0f, -1.0f, 20.0f));
		box2->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box3 = AddGameObject<Box>(1);
		box3->SetPosition(D3DXVECTOR3(-30.0f, -1.0f, 20.0f));
		box3->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box4 = AddGameObject<Box>(1);
		box4->SetPosition(D3DXVECTOR3(-30.0f, -1.0f, 30.0f));
		box4->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box5 = AddGameObject<Box>(1);
		box5->SetPosition(D3DXVECTOR3(-20.0f, -1.0f, 40.0f));
		box5->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box6 = AddGameObject<Box>(1);
		box6->SetPosition(D3DXVECTOR3(-20.0f, -1.0f, 30.0f));
		box6->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box7 = AddGameObject<Box>(1);
		box7->SetPosition(D3DXVECTOR3(-10.0f, -1.0f, 30.0f));
		box7->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box8 = AddGameObject<Box>(1);
		box8->SetPosition(D3DXVECTOR3(0.0f, -1.0f, 40.0f));
		box8->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box9 = AddGameObject<Box>(1);
		box9->SetPosition(D3DXVECTOR3(10.0f, -1.0f, 30.0f));
		box9->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box10 = AddGameObject<Box>(1);
		box10->SetPosition(D3DXVECTOR3(-10.0f, -1.0f, 40.0f));
		box10->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box11 = AddGameObject<Box>(1);
		box11->SetPosition(D3DXVECTOR3(20.0f, -1.0f, 20.0f));
		box11->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box12 = AddGameObject<Box>(1);
		box12->SetPosition(D3DXVECTOR3(10.0f, -1.0f, 30.0f));
		box12->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box13 = AddGameObject<Box>(1);
		box13->SetPosition(D3DXVECTOR3(20.0f, -1.0f, 30.0f));
		box13->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box14 = AddGameObject<Box>(1);
		box14->SetPosition(D3DXVECTOR3(20.0f, -1.0f, 20.0f));
		box14->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box15 = AddGameObject<Box>(1);
		box15->SetPosition(D3DXVECTOR3(20.0f, -1.0f, 10.0f));
		box15->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box16 = AddGameObject<Box>(1);
		box16->SetPosition(D3DXVECTOR3(20.0f, -1.0f, 0.0f));
		box16->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box17 = AddGameObject<Box>(1);
		box17->SetPosition(D3DXVECTOR3(20.0f, -1.0f, 0.0f));
		box17->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box18 = AddGameObject<Box>(1);
		box18->SetPosition(D3DXVECTOR3(10.0f, -1.0f, -10.0f));
		box18->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box19 = AddGameObject<Box>(1);
		box19->SetPosition(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		box19->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box20 = AddGameObject<Box>(1);
		box20->SetPosition(D3DXVECTOR3(-10.0f, -1.0f, 0.0f));
		box20->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box21 = AddGameObject<Box>(1);
		box21->SetPosition(D3DXVECTOR3(-20.0f, -1.0f, 0.0f));
		box21->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));

		Box* box22 = AddGameObject<Box>(1);
		box10->SetPosition(D3DXVECTOR3(10.0f, -1.0f, 40.0f));
		box10->SetScale(D3DXVECTOR3(5.0f, 2.0f, 5.0f));
	}

	Polygon2D* polygon2D = AddGameObject<Polygon2D>(2);
	polygon2D->MiniMap();
	Distance* distance = AddGameObject<Distance>(2);
	Death* death = AddGameObject<Death>(2);

	AddGameObject<Score>(2);
	m_Fade = AddGameObject<Fade>(2);

	// BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("audio\\bgm01.wav");
	bgm->Play(true);
}

void Game01::Update()
{
	Scene::Update();

	// âÊñ ëJà⁄ÉRÅ[ÉhÇÇ±Ç±Ç…èëÇ≠

	Scene* scene = Manager::GetScene();
	Goal* goal = scene->GetGameObject<Goal>();
	Death* death = scene->GetGameObject<Death>();

	if (goal->GetGoal() == true)
	{
		m_Fade->FadeOut();
		SetMoveScene(0);
	}
	else if (death->GetDeath() == true)
	{
		m_Fade->FadeOut();
		SetMoveScene(1);
	}
	if (m_Fade->GetFadeFinish())
	{
		if (GetMoveScene() == 0)
		{
			Manager::SetScene<Result>();
		}
		else if (GetMoveScene() == 1)
		{
			Manager::SetScene<GameOver>();
		}
	}

}