#include "Scene1_4.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace std;

Scene1::Scene1() {
	QPixmap start("resources/start.png");
	addItem(new QGraphicsPixmapItem(start));

	_nextScene = unique_ptr<QPushButton>(new QPushButton(u8"Start"));
	//настрой норм
	_nextScene->setGeometry(500, 145, 150, 80);

	_nextScene->setFont(QFont("Times", 40, QFont::Bold));
	_nextScene->setStyleSheet("QPushButton{" "color: #1a3ca3;"
		"background-color: #afdafc;"
		"border: 8px solid #906bff;"
		"}");
	this->addWidget(_nextScene.get());
}


QPushButton* Scene1::getNextScene() const {
	return _nextScene.get();
}





Scene4::Scene4(bool end) {
	

	_end = unique_ptr<QPushButton>(new QPushButton(u8"Exit"));
	//настрой норм
	_end->setFont(QFont("Times", 20));
	_end->setGeometry(980, 590, 100, 50);
	

if (!end) {
		QPixmap game_over("resources/gameover.png");
		addItem(new QGraphicsPixmapItem(game_over));
		_end->setStyleSheet("QPushButton{" "color: #1f0e0f;"
			"background-color: #bc5d58;"
			"border: 3px solid #1f0e0f;"
			"}");
	}
	else {
		QPixmap win("resources/win.png");
		addItem(new QGraphicsPixmapItem(win));
		_end->setStyleSheet("QPushButton{" "color: #003d33;"
			"background-color: #078c64;"
			"border: 3px solid #003d33;"
			"}");
	}

	this->addWidget(_end.get());
	//добавить кнопочки играть заново или выход?
}


QPushButton* Scene4::endScene() const {
	return _end.get();
}