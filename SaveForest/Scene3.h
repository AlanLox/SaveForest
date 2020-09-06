#pragma once

#include <QGraphicsScene>
#include <memory>

#include "Characters.h"
#include "GameLogic.h"

class Scene3 : public QGraphicsScene {
	std::unique_ptr<Kill> _Kill;
	std::unique_ptr<monster> _monster;
	std::unique_ptr<background> _background;
	std::unique_ptr<buttons> _buttons;
	std::unique_ptr<Battle> _battle;

	std::shared_ptr<QTimer> _attackTimer;

	const int _timerInterval = 50;

	std::mt19937 _random;





	Q_OBJECT
private slots:

	void connectButtons();
	void disconnectButtons();

	void updateScene();

	void completeAttack();

	void setKill_Attack1();
	void setKill_Attack2();
	void setKill_Attack3();
	void setKill_Heal();
	void setKill_SpecialAttack();


	void monster_Attacks();


signals:

	void game_over();
	void win();

public:
	Scene3();

};