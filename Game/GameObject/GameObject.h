#pragma once
class GameObjectManager;
typedef unsigned char	GameObjectPrio;
class GameObject :Noncopyable
{
public:
	GameObject() :
		m_priority(0),
		m_isStart(false),
		m_isDead(false),
		m_isNewFromGameObjectManager(false)
	{
	}
	virtual bool Start() { return true; }
	/*!
	*@brief	更新
	*/
	virtual void Update() {}
	/*!
	*@brief	描画
	*/
	virtual void Draw()
	{
	}
	/*!
	*@brief	Render関数が実行された後で呼ばれる描画処理
	*@details
	* ポストエフェクトの後で実行されます。HUDなどポストエフェクトの影響を受けたくない描画物はここでレンダリングしてください。
	*/
	virtual void PostDraw() {
	}
	/*!
	*@brief	インスタンスが生成された直後に呼ばれる関数。
	*@details	コンストラクタが呼ばれた後で即呼ばれます。
	*/
	virtual void Awake() {}
	/*!
	*@brief	削除されるときに呼ばれる。
	*@details	CGameManager::DeleteGameObjectを呼んだときに実行されます。
	* デストラクタより前に実行されます。
	*/
	virtual void OnDestroy() {}

	/*!
	*@brief	実行優先度を取得。
	*/
	GameObjectPrio GetPriority() const
	{
		return m_priority;
	}
	/*!
	*@brief	死亡フラグを立てる。
	*@details
	*/
	void SetDeadMark()
	{
		m_isDead = true;
	}


	void SetMarkNewFromGameObjectManager()
	{
		m_isNewFromGameObjectManager = true;
	}
	bool IsNewFromGameObjectManager() const
	{
		return m_isNewFromGameObjectManager;
	}
	//Start関数
	void StartWrapper()
	{
		if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
			if (Start()) {
				//初期化処理完了。
				m_isStart = true;
			}
		}
	}
	//Update関数を呼ぶ
	void UpdateWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
			Update();
		}
	}
	//Draw関数を呼ぶ
	void DrawWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
			Draw();
		}
	}
	void PostDrawWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
			PostDraw();
		}
	}
	friend class GameObjectManager;
protected:
	GameObjectPrio	m_priority;			//!<実行優先度。
	bool m_isStart;						//!<Startの開始フラグ。
	bool m_isDead;						//!<死亡フラグ。
	bool m_isRegistDeadList = false;	//!<死亡リストに積まれている。
	bool m_isNewFromGameObjectManager;	//!<GameObjectManagerでnewされた。
	bool m_isRegist = false;			//!<GameObjectManagerに登録されている？
	bool m_isActive = true;				//!<Activeフラグ。
	unsigned int m_tags = 0;			//!<タグ。
	unsigned int m_nameKey = 0;			//!<名前キー。
};

