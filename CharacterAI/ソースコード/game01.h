#pragma once

#include "scene.h"

class Game01 :public Scene
{
private:
	class Fade* m_Fade{};
	int m_MoveScene;

public:
	void Init()override;
	void Update()override;

	void SetMoveScene(int MoveScene) { m_MoveScene = MoveScene; }
	int GetMoveScene() { return m_MoveScene; }
};