#include "stdafx.h"
#include "Player.h"
#include"Enemy.h"
#include"BackGround.h"
Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start() {
	m_position = { 0.0f,1000.0f,0.0f };
	m_charaCon.Init(
		2.0,		//半径
		1.0f,		//高さ
		m_position//初期位置
	);
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	//ddsファイルの読み込み
	m_spritetex.CreateFromDDSTextureFromFile(L"Assets/sprite/hpd.dds");
	//テクスチャの初期化
	m_sprite.Init(m_spritetex, 1, 1);
	//アニメーション読み込み初期化
	InitAnimation();
	m_animation.Play(enAnimationClip_idle);
	m_enemy = FindGO<Enemy>("Enemy");
	m_background = FindGO<BackGround>("background");
	return true;
}
void Player::InitAnimation() {
	//アニメーション読み込み
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	//アニメーションループ
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	//アニメーション初期化
	m_animation.Init(m_model, m_animClips, enAnimationClip_Num);
}
void Player::AnimataionControl(){
	if (!m_charaCon.IsJump()) {
		if (m_moveSpeed.LengthSq() > 20.0f * 20.0f) {
			//走りアニメーション
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (m_moveSpeed.LengthSq() > 2.5f * 2.5f) {
			//歩きアニメーション
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//待機アニメーション
			m_animation.Play(enAnimationClip_idle, 0.2f);
		}
	}
	m_animation.Update(GameTime().GetFrameDeltaTime());
}
void Player::Move() {
	//重力
	const float gravity = 9.8f;
	//速度
	const float Speed = 90.0f;
	//ジャンプ時の高さ
	const float jump = 120.0f;
	//摩擦力
	m_friction = -3.0f;
	//左スティックの入力量を受け取る。
	float lStick_x = g_pad->GetLStickXF();
	float lStick_y = g_pad->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	cameraForward *= lStick_y *Speed *GameTime().GetFrameDeltaTime();	//奥方向への移動速度を代入。	
	cameraRight *= lStick_x * Speed*GameTime().GetFrameDeltaTime();	//右方向への移動速度を加算。
	
	//ジャンプ
	if (g_pad->IsTrigger(enButtonA) && m_charaCon.IsOnGround() == true) {
		m_moveSpeed.y += jump;
	}
	//二段ジャンプ
	if (g_pad->IsTrigger(enButtonA) && m_charaCon.IsJump()&&!m_charaCon.Is2ndJump()) {
		m_moveSpeed.y += jump;
		m_charaCon.Set2ndJump();
	}
	//摩擦
	CVector3 masa = m_moveSpeed;
	if (m_charaCon.IsJump()) {
		//ジャンプ中、摩擦力を下げる
		m_friction = -1.0f;
		masa *= m_friction;
	}
	else {
		//その他
		masa *= m_friction;
	}
	//移動速度に摩擦を与える
	m_moveSpeed.x += masa.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += masa.z * GameTime().GetFrameDeltaTime();
	m_moveSpeed += cameraForward;
	m_moveSpeed += cameraRight;
	//ジャンプ時
	if (g_pad->IsPress(enButtonB) 
		&& m_charaCon.IsJump()) {
		//速く落ちる(重力の5倍)に設定
		m_moveSpeed.y -= gravity*5.0f;
	}
	else {
		m_moveSpeed.y -= gravity;
	}
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	if (m_position.y<= -400.0f) {
		m_position = { 0.0f,30.0f,0.0f };
	}
}
void Player::Rotation() {

	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);

	m_rot.MakeRotationFromQuaternion(m_rotation);
	m_tarpos.x = m_rot.m[2][0] * 5.0f + m_position.x;
	m_tarpos.y = m_rot.m[2][1] * 5.0f + m_position.y;
	m_tarpos.z = m_rot.m[2][2] * 5.0f + m_position.z;
}
void Player::Avoid() {
	//エネミーからプレイヤーのベクトル
	CVector3 EtoPpos;
	EtoPpos = m_enemy->GetPosition() - m_position;
	//エネミーからプレイヤーの長さ
	float EtoPlen;
	EtoPlen =EtoPpos.Length();
	//テクスチャ表示フラグ
	if (EtoPlen < 10.0f && !m_Avoidf) {
		m_Avoidf = true;
	}
	else if((EtoPlen > 10.0f && m_Avoidf)) {
		m_Avoidf = false;
	}

	//まだ試作段階　　/エネミーの後ろに移動する処理
	if (m_Avoidf&&g_pad->IsTrigger(enButtonB))
	{
		m_rot.MakeRotationFromQuaternion(m_enemy->GetRotation());
		m_position.x = -m_rot.m[2][0] * 40.0f + m_enemy->GetPosition().x;
		m_position.z = -m_rot.m[2][2] * 40.0f + m_enemy->GetPosition().z;
		m_charaCon.SetPosition(m_position);

	}

}
void Player::Action() {
	CVector3 SpriteToPos = m_position - m_background->GetSpritePos();
	float StoPLen=SpriteToPos.Length();
	if (StoPLen<=10.0f&&g_pad->IsTrigger(enButtonB))
	{ 

	}
}
void Player::Update()
{
	AnimataionControl();
	Move();
	Rotation();
	Avoid();

	CQuaternion qRot=CQuaternion::Identity();
	qRot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	qRot.Multiply(m_rotation, qRot);
	//ワールド行列の更新。
	if (g_pad->IsTrigger(enButtonDown))
	{
		m_model.SetSpecPow(0.0f);
	}
	m_model.UpdateWorldMatrix(m_position, qRot,CVector3 { 0.1f,0.1f,0.1f });
	m_sppos.y = 1.0f;
	m_sprite.Update(m_sppos, CQuaternion::Identity(), CVector3::One());
}

void Player::Draw()
{
	m_renderModel = 1;
	m_model.Draw(
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		m_renderModel
	);
	m_renderModel = 0;
	m_model.Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_renderModel
	);
}
void Player::PostDraw() {
	if (g_pad->IsPress(enButtonLB2)) {
		m_sprite.Draw(
			MainCamera2D().GetViewMatrix(),
			MainCamera2D().GetProjectionMatrix()
		);
	}
}