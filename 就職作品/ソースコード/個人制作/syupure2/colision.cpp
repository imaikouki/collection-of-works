//=============================================================================
//
// �����蔻�� [colision.cpp]
// Author : Imai
//
//=============================================================================
#include "main.h"
#include "colision.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemybullet.h"
#include "fade.h"
#include "explosion.h"

//=============================================================================
// BB�ɂ�铖���蔻�菈��
// ��]�͍l�����Ȃ�
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBB(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, D3DXVECTOR3 size1, D3DXVECTOR3 size2)
{
	if ((pos1.x + size1.x > pos2.x - size2.x) && (pos1.x - size1.x < pos2.x + size2.x) &&
		(pos1.y + size1.y > pos2.y - size2.y) && (pos1.y - size1.y < pos2.y + size2.y)&&
		(pos1.z + size1.z > pos2.z - size2.z) && (pos1.z - size1.z < pos2.z + size2.z))

	{
		return true;
	}

	return false;
}

//=============================================================================
// BC�ɂ�铖���蔻�菈��
// �T�C�Y�͔��a
// �߂�l�F�������Ă���true
//=============================================================================
bool CheckHitBC(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	float len = (size1 + size2) * (size1 + size2);	// ���a��2�悵����
	D3DXVECTOR3 temp = pos1 - pos2;
	float fLengthSq = D3DXVec3LengthSq(&temp);		// 2�_�Ԃ̋����i2�悵�����j

	if (len > fLengthSq)
	{
		return true;
	}

	return false;
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CheckHit(void)
{
	ENEMY  *enemy = GetEnemy();			// �G�l�~�[�̃|�C���^�[��������
	PLAYER *player = GetPlayer();		// �v���C���[�̃|�C���^�[��������
	BULLET *bullet = GetBullet();		// �e�̃|�C���^�[��������
	ENEMYBULLET  *enemybullet = GetEnemyBullet();	// �e�̃|�C���^�[��������

	for (int i = 0; i < MAX_ENEMY; i++)		// �v���C���[�̒e�ƓG(BB)
	{
		for (int j = 0; j < MAX_BULLET; j++)
		{
			if (enemy[i].use == true)
			{
				if (bullet[j].bUse == true)
				{
					if (CheckHitBB(bullet[j].pos, enemy[i].pos, D3DXVECTOR3(BULET_SIZE_X, BULET_SIZE_Y, BULET_SIZE_Z),D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z)))
					{
						if (enemy[i].life >= 1)
						{
							enemy[i].life--;
							bullet[j].bUse = false;
							enemy[i].recnt = 60 * 15;
						}
						else
						{
							enemy[i].use = false;
							bullet[j].bUse = false;
							player->killcnt++;
							// �����̐���
							SetExplosion(enemy[i].pos, 100.0f, 100.0f);

							if (player->killcnt == 2)
							{
								SetFade(FADE_OUT);
							}

						}
					}
				}
			}
		}
	}

	
	if (player->use == true)		// ����L�����ƓG�̒e(BB)
	{
		for (int i = 0; i < MAX_ENEMYBULLET; i++)
		{
			if (enemybullet[i].bUse == true)
			{
				if (CheckHitBB(player->pos, enemybullet[i].pos, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), D3DXVECTOR3(ENEMYBULLET_SIZE_X, ENEMYBULLET_SIZE_Y, ENEMYBULLET_SIZE_Z)))
				{
					if (player->life < 60)
					{
						player->life--;
						enemybullet[i].bUse = false;
					}
					else
					{
						player->use = false;
					}
				}
			}
		}
	}

//	for (int i = 0; i < MAX_ENEMY; i++)		//����L�����ƓG�L�����̓����蔻��
//	{
//		if (enemy[i].use == true)
//		{
//			if (CheckHitBB(player->pos, enemy[i].pos, D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z)))
//			{
//				player->life--;
//				enemy[i].use = false;
//			}
//		}
//	}
}
