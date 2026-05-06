#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> 
#include <algorithm>

using namespace std;

// 생성자
Player::Player(const string& name, const string& characterClass, bool isHardcore)
    : Character(50, 50, 50, 50, 1),
      name(name), characterClass(characterClass), isHardcore(isHardcore),
      exp(0), expToNextLevel(100)
{
    inventory.reserve(20); // 가방 크기 미리 20칸 예약 (성능 최적화)
    
    // 능력치 계산
    maxHp = vitality * 2; 
    hp = maxHp;
    
    maxMp = (int)(energy * 1.5f);
    mp = maxMp;
    
    attackDamage = strength * 0.2f;
    attackSpeed = dexterity / 10.0f;
    movingSpeed = (double)dexterity / 30.0;
}

// 레벨업 로직
void Player::LevelUp() {
    level++;
    cout << "\n [!] 레벨 업! 당신의 농사 기술이 숙련되었습니다. \n";
}

// 치명타 예보
void Player::PreviewCritical() const {
    float preview = attackDamage * 2.0f;
    cout << " * 예상 치명타 데미지: " << preview << " *\n";
}

// 치명타 공격력 반환
int Player::CriticalAttack() const {
    return (int)(attackDamage * 2);
}

// 경험치 획득 및 레벨업 체크
void Player::GainExp(int amount) {
    exp += amount;
    cout << " [경험치 +" << amount << " 획득]\n";
    if (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        LevelUp();
        expToNextLevel = level * 100;
        cout << " >>> [레벨 업!] 현재 레벨: " << level << " <<<\n";
    }
}

// 가방 목록 출력 (기존 로직 유지)
void Player::Loot(int count) {
    cout << "------------------------------------------\n";
    cout << "   [ 가 방 안 소 지 품 ] \n";
    cout << "------------------------------------------\n";

    for (size_t j = 0; j < inventory.size(); j++) {
        string itemName = inventory[j]->GetName(); 
        cout << "  슬롯 " << j << " .......... [" << itemName << "]\n";
    }
    cout << "------------------------------------------\n";
}

// 아이템 습득 (소유권 이전)
void Player::PickUpItem(unique_ptr<Item> item) {
    if (!item) return;

    cout << "▶ [아이템 획득] 가방에 " << item->GetName() << "을 담았습니다." << endl;
    inventory.push_back(std::move(item)); 
    cout << "[상태] 현재 인벤토리 아이템 개수: " << inventory.size() << "개\n";
}

// 람다를 이용한 아이템 사용 및 삭제
void Player::UseItem(string itemName)
{
    auto it = std::find_if(inventory.begin(), inventory.end(), 
        [&itemName](const std::unique_ptr<Item>& item) {
            return item->GetName() == itemName;
        });

    if (it != inventory.end())
    {
        std::cout << "[사용] " << (*it)->GetName() << " 아이템을 사용했습니다.\n";
        inventory.erase(it); 
    }
    else
    {
        std::cout << "[실패] " << itemName << "이(가) 가방에 없습니다.\n";
    }
}

// Erase-Remove Idiom 일괄 삭제
void Player::ClearLowGradeItems()
{
    cout << "\n[시스템] 가방 정리를 시작합니다 (1등급 아이템 제거)..." << endl;

    inventory.erase(std::remove_if(inventory.begin(), inventory.end(), 
        [](const std::unique_ptr<Item>& item) { 
            return item->GetGrade() == 1; 
        }), inventory.end());

    cout << "[시스템] 가방 정리가 완료되었습니다.\n" << endl;
}