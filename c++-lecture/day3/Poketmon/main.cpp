#include "Poketmon.h"
#include <typeinfo>

int main() {

    // 1. 캐릭터 선택
    int select;
    cout << "Select your Poketmon\n";
    cout << "1. Pikachu  2. Squirtle  3. Bulbasaur\n> ";
    cin >> select;

    // 2. 선택한 객체 생성 (부모 포인터로 자식 객체를 가리킴)
    Poketmon* p = nullptr;
    switch(select) {
        case 1: p = new Pikachu();   break;
        case 2: p = new Squirtle();  break;
        case 3: p = new Bulbasaur(); break;
        default:
            cout << "Wrong choice\n";
            return 0;
    }

    // 3. 객체로 메뉴를 돌림
    int menu;
    while(true) {
        cout << "\n1.eat 2.sleep 3.play 4.exercise 5.state 6.skill 7.exit\n> ";
        cin >> menu;

        if(menu == 7) break;

        switch(menu) {
            case 1: p->eat();        break;
            case 2: p->sleep();      break;
            case 3: p->play();       break;
            case 4: p->exercize();   break;
            case 5: p->checkState(); break;
            case 6: // 실제 객체 타입을 확인해서 자식 클래스 전용 함수 호출
                    if(typeid(*p) == typeid(Pikachu)) ((Pikachu*)p)->skill();
                    else if(typeid(*p) == typeid(Squirtle)) ((Squirtle*)p)->skill();
                    else ((Bulbasaur*)p)->skill();
                    break;
            default: cout << "Wrong menu\n";
        }

        if(p->isDead()) {
            cout << "Game Over\n";
            break;
        }
    }

    delete p;

    return 0;
}

/*
캐릭터 선택 => 선택한 객체 생성 => 객체로 메뉴를 돌림
메뉴 1.밥 2.잠 3.놀 4.운동 5.상태 6.스킬 7.종료
*/
