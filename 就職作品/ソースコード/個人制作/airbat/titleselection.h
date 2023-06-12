//=============================================================================
//
// �^�C�g����ʏ��� [titleselection.h]
// Author : Imai
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_START_LOGO		("data/TEXTURE/start001.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_RANKING_LOGO	("data/TEXTURE/ranking001.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_CHOICEARROW		("data/TEXTURE/arrow001.png")		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TITLELOGO_POS_X		(200)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_POS_Y		(350)							// �^�C�g�����S�̕\���ʒu
#define	TITLELOGO_SIZE_X	(250)							// �^�C�g�����S�̕�
#define	TITLELOGO_SIZE_Y	(100)							// �^�C�g�����S�̍���
#define STARTLOGO_POS_X		(250)							// �X�^�[�g���S�̕\���ʒu
#define STARTLOGO_POS_Y		(250)							// ����
#define STARTLOGO_SIZE_X	(250/2)							// �X�^�[�g���S�̃T�C�Y
#define STARTLOGO_SIZE_Y	(125/2)							// ����

#define RANKINGLOGO_POS_X	(250)							// �����L���O���S�̕\���ʒu
#define RANKINGLOGO_POS_Y	(350)							// ����
#define RANKINGLOGO_SIZE_X	(250/2)							// �����L���O���S�̃T�C�Y
#define RANKINGLOGO_SIZE_Y	(125/2)							// ����

#define CHOICEARROW_POS_X	(150)							// �I��p���̕\���ʒu
#define CHOICEARROW_HIGHT	(30)							// ���̍��������p
#define CHOICEARROW_SIZE_X	(125/2)							// �I��p���̃T�C�Y
#define CHOICEARROW_SIZE_Y	(250/2)							// ����
#define ARROW_ANIM_DEVIDE_X		(10)							// �A�j���[�V�����̃e�N�X�`��������
#define ARROW_ANIM_DEVIDE_Y		(1)							// ����
#define ARROW_ANIM_NUM		(ARROW_ANIM_DEVIDE_X * ARROW_ANIM_DEVIDE_Y)	// �A�j���[�V�����̃p�^�[����
#define ARROW_ANIM_TIME		(3)


typedef struct
{
	D3DXVECTOR3				pos;				// ���̕\���ʒu
	D3DXVECTOR3				rot;				// ��]��

	LPDIRECT3DTEXTURE9		pD3DTexture;			// �e�N�X�`���̃|�C���^
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N

	int						nCountAnim;			// �A�j���[�V�����p�̃J�E���g
	int						nPatternAnim;		// �A�j���[�V�����̃p�^�[��

	float					radius;				// ���a
	float					baseAngle;			// �p�x

	bool					isRanked;			// �����L���O�\�����邩�ۂ��i�Q�Ɨp�j
}ARROW;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitleSelection(int type);
void UninitTitleSelection(void);
void UpdateTitleSelection(void);
void DrawTitleSelection(void);
ARROW *GetArrow(void);

