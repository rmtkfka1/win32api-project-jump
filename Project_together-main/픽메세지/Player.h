#pragma once
#include "Object.h"

class BackGround;

class Player :public Object
{

public:


	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC mdc) override;
	virtual void BoundingBox(HDC mdc) override;


	void Init(BackGround*);

	////void CRender(HDC mdc);
	Pos	GetDiffP1() { return _DiffP1; }		// player1�� ���̰�
	Pos	GetDiffP2() { return _DiffP2; }		// player2�� ���̰�
	ObjectType& GetTurn() { return _turn; }
	void GapUpdate(KeyType);
	bool& GetDivide() { return _divide; }


	void jump1();
	void jump2();

	/// ī�޶� �̵� ��ȯ ó��
	void CameraGap();
	void CollisionGap();

	// �˹� �߰�
	void KnocBackP1();
	void KnocBackP2();

	// player2�� �б�

public:

	// Player1
	////////////////////////////////////////////////////////////////////


	Pos				_posP1{};			// player1�� ���� ��ġ
	Pos				_RenderPosP1{};		// player1�� ������ â ��ġ
	Pos				_CenterPosP1{};		// �߽���ġ
	Pos				_DiffP1{};			// ���� ��ġ�� ������ â ��ġ�� ���� ��
	float			_motion_cntP1{ };

	CImage			player1_img_left;
	CImage			player1_img_right;

	CImage          fire_img;

	Motion			_motionP1;

	HDC				mdcP1;
	HBITMAP			hBitmapP1;

	// ����
	CImage			player1_img_jump;
	Motion			JumpMotionP1;
	float			JumpTime1 = 0.f;
	float			JumpHeight1 = 0;
	float			jumpPower1 = 45.f;
	float			temp1 = 0;
	bool			fallP1{ false };

	
    BOOL            landing1;
    BOOL	    Gravity1;
	BOOL			g_bJumpkeyPressed1 = FALSE;	//	���� Ű Space bar�� ������ TRUE�� ����

	// �˹� �κ� �߰� �κ�
	CImage          player1_img_hurt_left;
	CImage          player1_img_hurt_right;
	BOOL			_KnocBackP1{ false };
	Pos				_KnockPosP1{};

	// ��ٸ� �߰� �κ�
	CImage			player1_img_Climb;
	BOOL			intersect_sadari1;

	// Player2
	////////////////////////////////////////////////////////////////////

	Pos				_posP2{};			// player2�� ���� ��ġ
	Pos				_RenderPosP2{};		// player2�� ������ â ��ġ
	Pos				_CenterPosP2{};		// �߽���ġ
	Pos				_DiffP2{};			// ���� ��ġ�� ������ â ��ġ�� ���� ��
	float				_motion_cntP2{ };

	CImage			player2_img_left;
	CImage			player2_img_right;

	Motion			_motionP2;

	HDC				mdcP2;
	HBITMAP			hBitmapP2;

	// �˹� �κ� �߰� �κ�
	CImage          player2_img_hurt_left;
	CImage          player2_img_hurt_right;
	BOOL			_KnocBackP2{ false };
	Pos				_KnockPosP2{};

	//����
	CImage			player2_img_jump;
	Motion			JumpMotionP2;
	float			JumpTime2 = 0.f;
	float			JumpHeight2 = 0;
	float			jumpPower2 = 45.f;
	float			temp2 = 0;
	bool			fallP2{ false };

	BOOL			Gravity2;
	BOOL			g_bJumpkeyPressed2 = FALSE;	//	���� Ű Space bar�� ������ TRUE�� ����
	BOOL            landing2;
	// ��ٸ� �߰� �κ�
	CImage			player2_img_Climb;
	BOOL            intersect_sadari2;

	// player2 �б�
	CImage			player2_img_push;
	bool			pushBool{};
	bool			realpushBool{};

	// ����
	////////////////////////////////////////////////////////////////////
	BOOL			FIRE;
	int				fire_count = 0;
	WCHAR			test[100];

	bool			_divide{ false };
	ObjectType		_turn{ ObjectType::PLAYER1 };
	BackGround* _background{ nullptr };
	bool			boundingOnOff{ false };


	// ī�޶� �߰� �κ�
	float			_collisionLeftP1{};
	float			_collisionLeftP2{};

};
