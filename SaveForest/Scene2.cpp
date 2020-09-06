#include "Scene2.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFrame>

using namespace std;


Scene2::Scene2() {
	QPixmap background("resources/scene2/background.png");
	auto b = new QGraphicsPixmapItem(background);
	b->setZValue(-0.5);
	addItem(b);

	QPixmap m("resources/scene2/monster.png");

	_items.insert(pair<string, QGraphicsPixmapItem*>("Kill1", new QGraphicsPixmapItem(QPixmap("resources/scene2/Kill1.png"))));
	_items.insert(pair<string, QGraphicsPixmapItem*>("Kill2", new QGraphicsPixmapItem(QPixmap("resources/scene2/Kill2.png"))));
	_items.insert(pair<string, QGraphicsPixmapItem*>("Kill3", new QGraphicsPixmapItem(QPixmap("resources/scene2/Kill3.png"))));
	_items.insert(pair<string, QGraphicsPixmapItem*>("monster1", new QGraphicsPixmapItem(m)));
	_items.insert(pair<string, QGraphicsPixmapItem*>("monster2", new QGraphicsPixmapItem(m)));

	QFrame* dialog = new QFrame();
	//пофиксь
	dialog->setFixedSize(1140, 190);
	dialog->setFrameStyle(QFrame::Panel + QFrame::Raised);
	dialog->setLineWidth(4);
	dialog->move(5, 485);
	dialog->setStyleSheet("QFrame{" "background-color: #669e85;" "}");

	_nextScene = unique_ptr<QPushButton>(new QPushButton(u8"В бой!"));
	//настрой норм
	_nextScene->setGeometry(1010, 600, 100, 50);
	_nextScene->setFont(QFont("Times", 20, QFont::Bold));
	_nextScene->setStyleSheet("QPushButton{" "color: #001f1a;"
		"background-color: #669e85;"
		"border: 4px solid #3e6151;"
		"}");

	_next = unique_ptr<QPushButton>(new QPushButton(u8"Далее"));
	//настрой норм
	_next->setGeometry(1010, 600, 100, 50);
	_next->setFont(QFont("Times", 20, QFont::Bold));
	_next->setStyleSheet("QPushButton{" "color: #001f1a;"
		"background-color: #669e85;"
		"border: 4px solid #3e6151;"
		"}");


	_texts.insert(pair<string, QGraphicsTextItem*>("k1", new QGraphicsTextItem(u8"Что ты такое?")));
	_texts.insert(pair<string, QGraphicsTextItem*>("m1", new QGraphicsTextItem(u8"Аааррггггррррхххрр!!!")));
	_texts.insert(pair<string, QGraphicsTextItem*>("k2", new QGraphicsTextItem(u8"Демон пустоши? Что ж, зачем ты пришёл к моему лесу?")));
	_texts.insert(pair<string, QGraphicsTextItem*>("m2", new QGraphicsTextItem(u8"Роооааааррркккхххррр!!!")));
	_texts.insert(pair<string, QGraphicsTextItem*>("k3", new QGraphicsTextItem(u8"Что?! Ты хочешь уничтожить лес, чтобы забрать себе его энергию?! \n Я не позволю тебе сделать это!")));
	//настроить текст!!!

	for (auto it = _texts.begin(); it != _texts.end(); ++it)
		setFont(it->second);


	addItem(_items.find("Kill1")->second);

	

	//мб заменить на пиксмап? а то говно
	addWidget(dialog);

	addWidget(_next.get());

	addItem(_texts.find("k1")->second);
	connect(_next.get(), &QPushButton::clicked, this, &Scene2::next2);

	//ещё добавляем картинку, на которой будет что-то типа "победи монстра!" (нет)
}


void Scene2::setFont(QGraphicsTextItem* text) {
	text->setFont(QFont("Times", 20));
	text->setPos(80, 540);
}


void Scene2::next2() {
	disconnect(_next.get(), &QPushButton::clicked, this, &Scene2::next2);
	removeItem(_texts.find("k1")->second);
	removeItem(_items.find("Kill1")->second);


	_items.find("monster1")->second->setZValue(-0.1);
	addItem(_items.find("monster1")->second);
	addItem(_texts.find("m1")->second);
	connect(_next.get(), &QPushButton::clicked, this, &Scene2::next3);
}

void Scene2::next3() {
	disconnect(_next.get(), &QPushButton::clicked, this, &Scene2::next3);
	removeItem(_texts.find("m1")->second);
	removeItem(_items.find("monster1")->second);

	_items.find("Kill2")->second->setZValue(-0.1);
	addItem(_items.find("Kill2")->second);
	addItem(_texts.find("k2")->second);
	connect(_next.get(), &QPushButton::clicked, this, &Scene2::next4);
}

void Scene2::next4() {
	disconnect(_next.get(), &QPushButton::clicked, this, &Scene2::next4);
	removeItem(_texts.find("k2")->second);
	removeItem(_items.find("Kill2")->second);

	_items.find("monster2")->second->setZValue(-0.1);
	addItem(_items.find("monster2")->second);
	addItem(_texts.find("m2")->second);
	connect(_next.get(), &QPushButton::clicked, this, &Scene2::next5);
}

void Scene2::next5() {
	disconnect(_next.get(), &QPushButton::clicked, this, &Scene2::next5);
	removeItem(_texts.find("m2")->second);
	removeItem(_items.find("monster2")->second);

	_items.find("Kill3")->second->setZValue(-0.1);
	addItem(_items.find("Kill3")->second);
	addItem(_texts.find("k3")->second);
	
	addWidget(_nextScene.get());
}





QPushButton* Scene2::getNextScene() const {
	return _nextScene.get();
}