#pragma once
#include <string>
#include <vector>
#include "Character.h"

using namespace std;

// Character 클래스를 상속받은 Player 클래스
class Player : public Character
{
private:
	// Player 고유 정보
	string name;
	string characterClass;
	bool isHardcore;
    
	// 경험치 시스템
	int exp;
	int expToNextLevel;
    
	// 인벤토리: 정수형(아이템 ID)을 담는 가변 배열
	vector<string> inventory;
    
public:
	
	// 생성자: 이름, 직업, 하드코어 여부를 받아 초기화
	Player(const string& name, const string& characterClass, bool isHardcore);
    
	// Getters: private 변수들을 안전하게 읽어오기 위한 함수들
	string GetName() const { return name; }
	string GetCharacterClass() const { return characterClass; }
	bool GetIsHardcore() const { return isHardcore; }
	int GetExp() const { return exp; }
	int GetExpToNextLevel() const { return expToNextLevel; }
    
	// 플레이어만의 고유 기능들
	int CriticalAttack() const;      // 크리티컬 데미지 계산
	void LevelUp();                  // 레벨업 수치 조정
	void GainExp(int amount);        // 경험치 획득 및 레벨업 체크
	void PreviewCritical() const;    // 크리티컬 데미지 미리보기 출력
	void PrintLevel() const;         // 현재 레벨 출력
	void Loot(int count = 3);        // 아이템 획득 및 인벤토리 출력
};