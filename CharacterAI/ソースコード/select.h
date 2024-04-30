#pragma once

#include "scene.h"

class Select :public Scene
{
private:
	int m_SelectNumber;
	int m_SelectNumberMax;

	class Fade* m_Fade{};

public:
	void Init()override;
	void Update()override;


};