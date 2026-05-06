#include <iostream>
#include <string>
#include <cstdlib> 
#include <iomanip>
#include <vector>
#include <ctime>
#include <memory>
#include <map>

#include "Battle.h"
#include "Monster.h"
#include "Player.h"

using namespace std;

// [1단계: map 기반 아이템 도감]
std::map<std::string, int> itemDB = {
    {"루비", 1},
    {"애비게일의 목걸이", 1},
    {"강철 검", 2},
    {"전설의 방패", 5}
};

int main()
{
    srand((unsigned int)time(NULL));
    system("cls");

    string uName, cClass;
    int cChoice;
    char hcIn;
    bool isHC = false;

    cout << "================================================\n";
    cout << "       [ 텍스트 에디션 : 심연의 광산 ]          \n";
    cout << "================================================\n";
    cout << " >> 이름을 입력하세요 : ";
    cin >> uName;

    system("cls");
    cout << "------------------------------------------------\n";
    cout << "           시작 도구를 선택하세요               \n";
    cout << "------------------------------------------------\n";
    cout << "  1. 전사  2. 마법사  3. 야만인  4. 성기사      \n";
    cout << "------------------------------------------------\n";
    cout << " >> 선택: ";
    cin >> cChoice;

    if (cChoice == 1) cClass = "전사";
    else if (cChoice == 2) cClass = "마법사";
    else if (cChoice == 3) cClass = "야만인";
    else if (cChoice == 4) cClass = "성기사";
    else cClass = "농부";

    cout << "\n >> 하드코어 모드? (1:예 / 0:아니오) : ";
    cin >> hcIn;
    isHC = (hcIn == '1');

    system("cls");
    Player player(uName, cClass, isHC);
    
    vector<Monster> forestMonsters;
    forestMonsters.push_back(Monster("초록 슬라임", 40, 10, 15, 10, 50));
    forestMonsters.push_back(Monster("먼지 요정", 50, 15, 20, 10, 80));

    vector<Monster> mineMonsters;
    mineMonsters.push_back(Monster("바위 게", 30, 20, 15, 10, 120));
    mineMonsters.push_back(Monster("그림자 브루트", 40, 40, 20, 20, 300));

    // stageName을 while문 밖으로 꺼내어 Scope 문제 해결
    string stageName = "";

    while (player.isAlive())
    {
        cout << "\n어디로 이동하시겠습니까? (0번 누르면 게임 종료)\n";
        cout << "1. 평화로운 숲 (쉬움)\n";
        cout << "2. 어두운 광산 (어려움)\n";
        cout << "선택 : ";
        int mapChoice;
        cin >> mapChoice;
        
        if (mapChoice == 0) break;

        // 변수 할당
        vector<Monster>* targetStage = (mapChoice == 1) ? &forestMonsters : &mineMonsters;
        stageName = (mapChoice == 1) ? "숲" : "광산";

        for (int i = 0; i < 3; i++) {
            if (!player.isAlive()) break;

            system("cls");
        
            int randomIndex = rand() % targetStage->size();
            Monster currentMonster = (*targetStage)[randomIndex];

            cout << "------------------------------------------\n";
            cout << " [" << stageName << " 탐험 중] " << currentMonster.GetName() << " 등장!\n";
            cout << "------------------------------------------\n\n";
            system("pause");

            Battle battle(player, currentMonster);
            if (!battle.Run()) {
                cout << "\n당신은 쓰러졌습니다...\n";
                break;
            } else {
                cout << "\n승리했습니다!\n";
                player.GainExp(currentMonster.GetExpReward());
                
                // 통합 로직
                std::string findname = "루비"; 
                auto it = itemDB.find(findname);

                if (it != itemDB.end())
                {
                    // 1. 이름과 등급(it->second)을 모두 전달하여 생성
                    auto newItem = std::make_unique<Item>(it->first, it->second);
                    
                    // 2. 소유권 이전 및 가방 추가
                    player.PickUpItem(std::move(newItem));
    
                    // 3. 람다 검색 기반 아이템 사용
                    player.UseItem(findname);
    
                    // 4. Erase-Remove 기반 가방 정리
                    player.ClearLowGradeItems();
    
                    // 5. 가방 상태 출력
                    player.Loot();
                }
            } // Battle 승리 영역 닫기
            
            system("pause");
        } // for문(전투 3회) 닫기

        if (player.isAlive())
        {
            // 위에서 선언한 stageName을 안전하게 인식함
            cout << "\n" << stageName << " 탐험을 마치고 마을로 돌아왔습니다!\n";
            system("pause");
        }
    } // while문 닫기
    
    system("pause");
    return 0;
} // main 함수 닫기