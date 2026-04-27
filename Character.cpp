#include "Character.h"

// 생성자
Character::Character(int str, int dex, int vit, int en, int lv)
    : strength(str), dexterity(dex), vitality(vit), energy(en), level(lv),
      fireResist(0), coldResist(0), lightningResist(0), poisonResist(0)
{
    // maxHp 계산
    maxHp = vitality * 2; 
    hp = maxHp;

    // (int)
    maxMp = (int)(energy * 1.5f);
    mp = maxMp;

    attackDamage = strength * 0.2f;
    attackSpeed = dexterity / 10.0f;
    
    movingSpeed = (double)dexterity / 30.0; 
}

// 데미지 처리 함수
void Character::TakeDamage(int damage)
{
    hp -= damage;
    if (hp < 0) hp = 0; // 체력이 음수가 되지 않도록 방지
}

// 기본 공격 데미지 반환
int Character::Attack() const
{
    return (int)attackDamage; 
}