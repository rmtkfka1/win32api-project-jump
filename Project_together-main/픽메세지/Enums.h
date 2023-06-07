#pragma once


enum class KeyType
{
	LeftMouse = VK_LBUTTON,
	RightMouse = VK_RBUTTON,
	SpaceBar = VK_SPACE,

	//�÷��̾�1
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	F = 'F',
	G = 'G',

	//�÷��̾�2
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	J = 'J',
	K = 'K',
	Z = 'Z',
	X = 'X',
	I = '1',
	O='2',
	P='3',
	Q='Q',

	on ='O'

};

enum class KeyState
{
	NONE,//�ƹ��͵� �ƴѻ���
	PRESS, //�������ִ»���
	DOWN, //�ѹ�����
	UP, //Ű���� ���Ƕ�
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KeyState::END)
};

enum class SceneType
{
	NONE,
	LOBBY,
	STAGE1,
	STAGE2,
	STAGE3,
	EDITSCENE,
	ENDING,
	END,
};


enum class ObjectType
{
	NONE,
	PLAYER,
	PLAYER1,
	PLAYER2,
	PLAYERSUM,
	MONSTER,
	MISSILE,
	TILE,
	ENV,

};

enum class Motion
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

enum class Bullet_Dir
{
	LEFT,
	RIGHT,
	DOWN,
	UP,
};