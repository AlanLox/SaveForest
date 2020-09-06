#include "GameWindow.h"

#include <QApplication>

#include <QAction>
#include <QDir>
#include <QIcon>
#include <QMenuBar>
#include <QTimer>

using namespace std;


void GameWindow::scene2() {
    _scene2 = unique_ptr<Scene2>(new Scene2);

    _view->setScene(_scene2.get());
    disconnect(_scene1->getNextScene(), &QPushButton::clicked, this, &GameWindow::scene2);

    //коннект кнопки из сцены 2
    connect(_scene2->getNextScene(), &QPushButton::clicked, this, &GameWindow::scene3);
}

//тут не кнопка!
void GameWindow::scene3() {
    _scene3 = unique_ptr<Scene3>(new Scene3);

    _view->setScene(_scene3.get());
    disconnect(_scene2->getNextScene(), &QPushButton::clicked, this, &GameWindow::scene3);

    //коннект сигнала из сцены 3 (нет)
    connect(_scene3.get(), &Scene3::win, this, &GameWindow::scene4w);
    connect(_scene3.get(), &Scene3::game_over, this, &GameWindow::scene4o);

}



void GameWindow::scene4w() {
    _scene4 = unique_ptr<Scene4>(new Scene4(true));
    _view->setScene(_scene4.get());
    //коннект кнопки из сцены 4
    connect(_scene4->endScene(), &QPushButton::clicked, qApp, &QApplication::quit);
}

void GameWindow::scene4o() {
    _scene4 = unique_ptr<Scene4>(new Scene4(false));
    _view->setScene(_scene4.get());
    //коннект кнопки из сцены 4
    connect(_scene4->endScene(), &QPushButton::clicked, qApp, &QApplication::quit);
}

GameWindow::GameWindow() {
	// Настройка заголовка окна и меню
	setWindowTitle(u8"Save Forest!");
	this->setFixedSize(_windowSize);

	//создание вьюхи
	_view = unique_ptr<QGraphicsView>(new QGraphicsView);

	_view->setFixedSize(_windowSize);
	_view->setFrameShape(QFrame::Shape::NoFrame);
	_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(_view.get());


	//создание сцен (потом)
	_scene1 = unique_ptr<Scene1>(new Scene1);
    _scene2 = nullptr;
    _scene3 = nullptr;
    _scene4 = nullptr;

	_view->setScene(_scene1.get());

    //коннект кнопки из сцены 1
    connect(_scene1->getNextScene(), &QPushButton::clicked, this, &GameWindow::scene2);

}
