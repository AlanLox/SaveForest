#include <QApplication>
#include <QWidget>
#include <iostream>

using namespace std;

//#include "Utils.h"
#include "GameWindow.h"

// Справка по аргументам QObject::connect:
// 1) объект A, в котором необходимо отслеживать какой-либо сигнал;
// 2) сигнал (с точки зрения кода - обычный метод, объявленный в секции signals) объекта A, который необходимо обслеживать;
// 3) объект B, который будет обрабатывать сигнал;
// 4) слот (с точки зрения кода - обычный метод, объявленный в секции slots) объекта B, который будет обрабатывать сигнал.




int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	GameWindow Window;
	//Window.setFixedSize(Window.sizeHint());
	Window.show();

	return QApplication::exec();
}




Battle battle;

int monster() {
	int HP = 0;
	switch (rand() % 3) {
	case 0:
		HP = battle.monsterAttack1();
		break;
	case 1:
		HP = battle.monsterAttack2();
		break;
	case 2:
		HP = battle.monsterAttack3();
		break;
	}
	return HP;
}

bool can_attack(int attack) {
	bool go = false;
	switch (attack)
	{
	case 0:
		go = true;
		break;
	case 1:
		if (battle.can_Attack2()) go = true;
		break;
	case 2:
		if (battle.can_Attack3()) go = true;
		break;
	case 3:
		if (battle.can_Heal()) go = true;
		break;
	case 4:
		if (battle.can_SpecialAttack()) go = true;
		break;
	}
	return go;
}

int Kill(int attack) {
	int HP = 0;
	switch (attack)
	{
	case 0:
		HP = battle.killAttack1();
		break;
	case 1:
		HP = battle.killAttack2();
		break;
	case 2:
		HP = battle.killAttack3();
		break;
	case 3:
		HP = battle.killHeal();
		break;
	case 4:
		HP = battle.killSpecial();
		break;
	}
	return HP;
}

void stats() {
	cout << "\n Stats: \n";
	cout << "Kill HP: " << battle.getKillHP() << endl;
	cout << "Kill Mana: " << battle.getKillMana() << endl << endl;
	cout << "Monster HP: " << battle.getMonsterHP() << endl << endl;
}


/*int main() {

	cout << "Start game!" << endl;
	while (!battle.gameOver() && !battle.win()) {
		int attack;
		bool go = false;
		do {
			cout << "Select attack: \n 0) attack 1 \n 1) attack 2 \n 2) attack 3 \n 3) heal \n 4) special attack \n ";
			cin >> attack;
			go = can_attack(attack);
		} while (go == false);
		auto tmp = Kill(attack);
		if (attack == 0 || attack == 1 || attack == 2 || attack == 4)
			cout << "\n Kill's attack: -" << tmp << endl;
		else if (attack == 3)
			cout << "\n Kill's heals: +" << tmp << endl;
		stats();
		if (!battle.win()) { 
			cout << "\n Monster's attack: -" << monster() << endl;
			stats();
		}

	}

	if (battle.gameOver())
		cout << "Game over!" << endl;
	else cout << "You win!" << endl;
}*/











/*int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	QWidget widget;

	// Для отслеживания момента вызова деструктора можете использовать функцию trackDestructor из Utils.h:
	trackDestructor(&widget, "QWidget destroyed!");

	widget.show();

	return QApplication::exec();
}*/


