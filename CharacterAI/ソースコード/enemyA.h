#pragma once
#include "animationModel.h"
#include "gameObject.h"

class EnemyB;	// EnemyB�N���X�̑O���錾

enum ENEMY_A_STATE
{
	ENEMY_A_STATE_ROUND,	// ����X�e�[�g
	ENEMY_A_STATE_CAUTION,	// �x���X�e�[�g
	ENEMY_A_STATE_BATTLE	// �퓬�X�e�[�g
};

class EnemyA : public GameObject
{
private:
	ENEMY_A_STATE m_EnemyAState = ENEMY_A_STATE_ROUND;	// ���݂̃X�e�[�g
	int m_KillCount = 0;	// �|������
	bool m_Alive;		// �����Ă��邩
	bool m_HandednessR;	// ������͉E�� (�ړ����ɐG�ꂽ�I�u�W�F�N�g����������)

	float m_HP;				// �q�b�g�|�C���g
	float m_MaxHP;			// Max�q�b�g�|�C���g
	float m_RandomHP;		// �q�b�g�|�C���g +�����_���l
	float m_MP;				// �}�W�b�N�|�C���g		// ��
	float m_MaxMP;			// Max�}�W�b�N�|�C���g	// ��
	float m_RandomMP;		// �}�W�b�N�|�C���g +�����_���l
	float m_AutoRecoveryAmount;	// �����񕜗�
	float m_RecoveryPoint;	// �񕜗�	// ��

	float m_MeleeRange;		// �ߐڍU���\�͈�
	float m_LongAttackRange;	// �������U���\�͈�
	float m_AttackRate;		// �U�����[�g	// �l�b�Ԋu�ōU������
	float m_RandomAttackRate;		// �U�����[�g +�����_���l
	float m_AttackPoint;	// �U����
	float m_RandomAttackPoint;	// �U���� +�����_���l
	int m_AttackRateCount = 0;		// �U�����[�g�J�E���g
	// int m_LongAttackRateCount = 0;		// �������U�����[�g�J�E���g
	int m_AttackAnimationCount = 0;	// �U���A�j���[�V�����𐳏�ɕ\��������ׂ̃J�E���g

	// bool m_Discovery;		// �����������ǂ����̃t���O		// �G�l�~�[B�ł͎g��Ȃ�

	float m_DiscoveryAreaA;	// ���F�͈�
	float m_DiscoveryAreaB;	// ���F�͈�
	float m_UnDiscoveryArea;// �� ���F�͈�	// ����������
	float m_SearchCircle;	// �T���T�[�N��		// ��������̍��G�͈͂Ƃ��Ďg������
	int m_ThinkingTime;		// �v�l�d��
	int m_RandomThinkingTime;	// �v�l�d���� +�����_���l
	int m_ThinkingTimeCount;	// �v�l�d���J�E���g
	int m_SurveyCount = 0;	// ���F�m�F �b���J�E���g

	int kakunin = 0;

	EnemyB* m_NearestEnemy;
	D3DXVECTOR3 m_MinDistance;	// ��ԋ߂��G���W
	D3DXVECTOR3 m_ObjectivePoint;	// �ڕW�n�_


	D3DXVECTOR3 m_Move;		// �ړ���
	float m_WalkSp;	// ���s ���x
	float m_RandomWalkSp;	// ���s ���x +�����_���l
	float m_RunSp;	// ���s ���x
	float m_RandomRunSp;	// ���s ���x +�����_���l
	bool m_EndMovement;	// �ړ������t���O

	// ���f���E�A�j���[�V����
	AnimationModel* m_Model{};
	int m_time{};
	float m_BlendRate{};
	std::string m_NextAnimationName;
	std::string m_AnimationName;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	bool m_Virgin = false;	// �ŏ��݂̂ɓ���

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �X�e�[�g�̑J��
	void SetChangeState(ENEMY_A_STATE ChangeState)
	{
		m_ThinkingTimeCount = 0;
		m_EnemyAState = ChangeState;
	}

	// �v���C���[�̏󋵂ɍ��킹�čX�V���s��
	void UpdateRound();			// ����X�e�[�g
	void UpdateCaution();		// �x���X�e�[�g
	void UpdateBattle();		// �퓬�X�e�[�g

	void AddDamage(float Damage);	// �_���[�W

	// �r�w�C�r�A�Ŏg�p����֐�
	void Move(D3DXVECTOR3 ObjectivePoint, bool Run);	// �ړ�
	void Attack();	// �ߐڍU��
	void LongAttack();	// �������U��
	void Approach();// �߂Â�
	void Round();	// ����
	void Survey(int VigilantTime/*���n������*/);	// ���n��
	void AutoRecovery();	// ������
	void VisualSearch(float DiscoveryArea);	// ���F����
	void ThinkingTime();	// �v�l�d������
	// void Pathfinding();		// �o�H�T��
	bool AttackAllowed();	// �ߐڍU���s�� ��
	bool LongAttackAllowed();	// �������U���s�� ��
	bool GetAlive();		// �����Ă��邩�ǂ���
	EnemyB* GetNearestEnemy();	// ��ԋ߂��G�����擾
	void SetKillCount() { m_KillCount++; };
	int GetKillCount() { return m_KillCount; };

};