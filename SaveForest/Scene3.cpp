#include "Scene3.h"


#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTimer>

using namespace std;

Scene3::Scene3() {
	_Kill = unique_ptr<Kill>(new Kill(this));
	_monster = unique_ptr<monster>(new monster(this));
	_background = unique_ptr<background>(new background(this));
	_buttons = unique_ptr<buttons>(new buttons(this));
	_battle = unique_ptr<Battle>(new Battle());


	_attackTimer = shared_ptr<QTimer>(new QTimer);

	//�������� ���� ������������
	connectButtons();


	// �������� ������� ��� ����������� ���������� �����
	const auto timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Scene3::updateScene);
	timer->start(_timerInterval);

	connect(_Kill.get(), &Kill::attackComplete, this, &Scene3::monster_Attacks);

	connect(_monster.get(), &monster::attackComplete, this, &Scene3::completeAttack);
}

void Scene3::updateScene() {
	_background->updateClouds(_timerInterval);
}


void Scene3::connectButtons() {
	connect(_buttons->_buttons[0], &QPushButton::clicked, this, &Scene3::setKill_Attack1);
	if (_battle->can_Attack2())
		connect(_buttons->_buttons[1], &QPushButton::clicked, this, &Scene3::setKill_Attack2);
	if (_battle->can_Attack3())
		connect(_buttons->_buttons[2], &QPushButton::clicked, this, &Scene3::setKill_Attack3);
	if (_battle->can_Heal())
		connect(_buttons->_buttons[3], &QPushButton::clicked, this, &Scene3::setKill_Heal);
	if (_battle->can_SpecialAttack())
		connect(_buttons->_buttons[4], &QPushButton::clicked, this, &Scene3::setKill_SpecialAttack);
}

void Scene3::disconnectButtons() {
	disconnect(_buttons->_buttons[0], &QPushButton::clicked, this, &Scene3::setKill_Attack1);
	disconnect(_buttons->_buttons[1], &QPushButton::clicked, this, &Scene3::setKill_Attack2);
	disconnect(_buttons->_buttons[2], &QPushButton::clicked, this, &Scene3::setKill_Attack3);
	disconnect(_buttons->_buttons[3], &QPushButton::clicked, this, &Scene3::setKill_Heal);
	disconnect(_buttons->_buttons[4], &QPushButton::clicked, this, &Scene3::setKill_SpecialAttack);
}



void Scene3::monster_Attacks() {
	//disconnect(&*_attackTimer.get(), &QTimer::timeout, this, &Scene3::monster_Attacks);
	//_attackTimer->stop();

	//disconnect(_Kill.get(), &Kill::attackComplete, this, &Scene3::monster_Attacks);

	//_Kill->setNormal(); //��� ������ ���� � ����� ������ ����� � �����

	if (_battle->win()) {
		emit win();
		return;
	}
	int attack = 0;
	_Kill->setPose("down");
	switch (_random() % 3)
	{
	case 0:
		attack = _battle->monsterAttack1();
		_buttons->updateKillHP(-((float)attack/ (float)Battle::KILL_HP * 500));
		_monster->Attack1();
		break;
	case 1:
		attack = _battle->monsterAttack2();
		_buttons->updateKillHP(-((float)attack / (float)Battle::KILL_HP * 500));
		_monster->Attack2();
		break;
	case 2:
		attack = _battle->monsterAttack3();
		_buttons->updateKillHP(-((float)attack / (float)Battle::KILL_HP * 500));
		_monster->Attack3();
		break;
	}

	//connect(&*_attackTimer.get(), &QTimer::timeout, this, &Scene3::completeAttack);
	//_attackTimer->start(500);

	//_Kill->setNormal();
	////��� ����������� �����
	//int KillHP = _battle->getKillHP();

	//
}


void Scene3::completeAttack() {
	//disconnect(&*_attackTimer.get(), &QTimer::timeout, this, &Scene3::completeAttack);
	//_attackTimer->stop();
	if (_battle->gameOver()) {
		emit game_over();
		return;
	}

	_Kill->setNormal("down");
	connectButtons();
}



//�������� ��� �� �� ����� � ��� ������ �������� ������ �������, ���������
//������ ����� �� �����, ��� �����
//� ����� ������������� ���� 0!!!
void Scene3::setKill_Attack1() {
	//���������� ������
	disconnectButtons();

	int attack = _battle->killAttack1(); //�������� ����� ������� �����
	_buttons->updateMonsterHP((float)attack / (float)Battle::MONSTER_HP * 500);
	_Kill->Attack1();

}


//�� �� �����, ��� � ����
void Scene3::setKill_Attack2() {

	disconnectButtons();

	int attack = _battle->killAttack2(); //�������� ����� ������� �����
	_buttons->updateMonsterHP((float)attack / (float)Battle::MONSTER_HP * 500);
	_buttons->updateKillMana((float)Battle::KILL_MANA_ATTACK_2 / (float)Battle::KILL_MANA * 400);
	_Kill->Attack2();

}

void Scene3::setKill_Attack3() {
	//���������� ������
	disconnectButtons();

	int attack = _battle->killAttack3(); //�������� ����� ������� �����
	_buttons->updateMonsterHP((float)attack / (float)Battle::MONSTER_HP * 500);
	_buttons->updateKillMana((float)Battle::KILL_MANA_ATTACK_3 / (float)Battle::KILL_MANA * 400);
	_Kill->Attack3();

}

void Scene3::setKill_Heal() {
	//���������� ������
	disconnectButtons();

	int attack = _battle->killHeal(); //�������� ����� ������� �����
	_buttons->updateKillHP((float)attack / (float)Battle::KILL_HP * 500);
	_buttons->updateKillMana(Battle::KILL_MANA_HEAL / (float)Battle::KILL_MANA * 400);
	_Kill->Heal();

}

void Scene3::setKill_SpecialAttack() {
	//���������� ������
	disconnectButtons();

	int attack = _battle->killSpecial(); //�������� ����� ������� �����
	_buttons->updateMonsterHP((float)attack / (float)Battle::MONSTER_HP * 500);


	//!!!!!! ��� ������� ��������� ��!!!!!
	_buttons->updateSP();

	_Kill->SpecialAttack();

}
