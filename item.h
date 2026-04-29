#pragma once
#include <iostream>
#include <string>

class Player; // 전방 선언

class Item {
public:
    // 생성자: 아이템 생성 시 로그 출력
    Item(std::string name) : name(name) {
        std::cout << "[생성] " << name << " 아이템이 월드에 생겨났습니다.\n";
    }

    // 소멸자: 아이템 삭제(메모리 해제) 시 로그 출력
    ~Item() {
        std::cout << "[소멸] " << name << " 아이템이 메모리에서 해제되었습니다.\n";
    }

    std::string GetName() const { return name; }

private:
    std::string name;
    std::weak_ptr<Player> owner; // 주인을 가리키는 약한 참조 (순환 참조 방지)
};