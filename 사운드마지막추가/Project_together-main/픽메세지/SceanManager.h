#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager)


public:
	void Init();
	void Update();
	void Render(HDC mdc);
	void Clear();
	void ChangeScene(SceneType sceneType);

private:
	Scene* _scene; //���� �����ϰ��ִ� ��
	SceneType _sceneType = SceneType::NONE; //��Ÿ��(STAGE1,STAGE2,STAGE3)
};

