#include <iostream>
#include <string>
#include <cstdlib> 
#include <iomanip>
#include <vector>
#include <ctime>

#include "Battle.h"
#include "Monster.h"
#include "Player.h"

using namespace std;

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
    
    // 사냥터별 몬스터 목록(벡터) 만들기
    vector<Monster> forestMonsters;
    forestMonsters.push_back(Monster("초록 슬라임", 40, 10, 15, 10, 50));
    forestMonsters.push_back(Monster("먼지 요정", 50, 15, 20, 10, 80));

    vector<Monster> mineMonsters;
    mineMonsters.push_back(Monster("바위 게", 30, 20, 15, 10, 120));
    mineMonsters.push_back(Monster("그림자 브루트", 40, 40, 20, 20, 300));

    while (player.isAlive())
    {
        // 사냥터 선택 (웨이포인트 구현)
        cout << "\n어디로 이동하시겠습니까? (0번 누르면 게임 종료)\n";
        cout << "1. 평화로운 숲 (쉬움)\n";
        cout << "2. 어두운 광산 (어려움)\n";
        cout << "선택 : ";
        int mapChoice;
        cin >> mapChoice;
        
        if (mapChoice == 0) break;

        // 선택된 사냥터 벡터 결정
        vector<Monster>* targetStage = (mapChoice == 1) ? &forestMonsters : &mineMonsters;
        string stageName = (mapChoice == 1) ? "숲" : "광산";

        // 전투 루프 (선택한 사냥터에서 3마리 랜덤 스폰)
        for (int i = 0; i < 3; i++) {
            if (!player.isAlive()) break;

            system("cls");
        
            // 해당 사냥터 벡터 내에서 무작위 몬스터 한 마리 선택
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
                player.Loot(2); // 벡터 루팅 함수 실행
                system("pause");
            }
        }

        if (player.isAlive())
        {
            cout << "\n" << stageName << "탐험을 마치고 마을로 돌아왔습니다!\n";
            system("pause");
        }
    }
    
    
    system("pause");
    return 0;
}