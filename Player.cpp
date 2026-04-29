#include "Player.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib> // rand() 사용을 위해 필요

using namespace std;

// 생성자
Player::Player(const string& name, const string& characterClass, bool isHardcore)
    : Character(50, 50, 50, 50, 1),
      name(name), characterClass(characterClass), isHardcore(isHardcore),
      exp(0), expToNextLevel(100)
{
    inventory.reserve(20); // 가방 크기 미리 20칸 예약 (성능 최적화)
    
    // 부모에게 물려받은 변수들을 사용하여 수치 계산 (오류 방지용 괄호 추가)
    maxHp = vitality * 2; 
    hp = maxHp;
    
    maxMp = (int)(energy * 1.5f);
    mp = maxMp;
    
    attackDamage = strength * 0.2f;
    attackSpeed = dexterity / 10.0f;
    movingSpeed = (double)dexterity / 30.0;
}

void Player::LevelUp() {
    level++;
    cout << "\n [!] 레벨 업! 당신의 농사 기술이 숙련되었습니다. \n";
}

void Player::PreviewCritical() const {
    float preview = attackDamage * 2.0f;
    cout << " * 예상 치명타 데미지: " << preview << " *\n";
}

int Player::CriticalAttack() const {
    return (int)(attackDamage * 2);
}

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

void Player::Loot(int count) {
    
    // 아이템 풀
    vector<string> itemPool = { "돌멩이", "금광석", "새먼베리", "낡은 검", "단단한 나무" };

    cout << "\n [알림] 광산 바닥에서 무언가를 발견했습니다! \n";

    for (int i = 0; i < count; i++) {
        
        // 랜덤하게 아이템 이름을 선택
        int randomIndex = rand() % itemPool.size();
        string pickedItem = itemPool[randomIndex];
        
    }

    // 가방 출력 로직
    cout << "------------------------------------------\n";
    cout << "   [ 가 방 안 소 지 품 ] \n";
    cout << "------------------------------------------\n";

    for (size_t j = 0; j < inventory.size(); j++) {
        string itemName = inventory[j]->GetName(); 

        cout << "  슬롯 " << j << " .......... [" << itemName << "]\n";
    }
    cout << "------------------------------------------\n";
}

// 새로운 아이템 습득 함수 추가
void Player::PickUpItem(unique_ptr<Item> item) {
    if (!item) return;

    cout << "▶ [아이템 획득] 가방에 " << item->GetName() << "을 담았습니다." << endl;

    // std::move를 사용해 소유권을 인벤토리 벡터로 이전
    inventory.push_back(std::move(item)); 
    
    cout << "[상태] 현재 인벤토리 아이템 개수: " << inventory.size() << "개\n";
}

// 반복자 삭제 로직 추가
void Player::UseItem(string itemName)
{
    // 고전 반복자 순회 방식
    for (auto it = inventory.begin(); it != inventory.end(); )
    {
        // it가 가리키는 스마트 포인터의 이름 확인
        if ((*it)->GetName() == itemName)
        {
            std::cout << "[사용] " << itemName << "을(를) 사용하여 가방에서 제거합니다.\n";
            
            // it = erase(it) 패턴 (반복자 무효화 방지)
            it = inventory.erase(it);
            
            return; // 하나만 지우고 종료
        }
        else
        {
            ++it; // 지우지 않았을 때만 반복자 증가
        }
    }
    std::cout << "[실패] " << itemName << "이 가방에 없습니다.\n";
}