#pragma once

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPixmap>
#include <QSize>


#include <list>
#include <vector>
#include <random>
#include <memory>


#include "Scene1_4.h"
#include "Scene2.h"
#include "Scene3.h"


class GameWindow : public QMainWindow {
	Q_OBJECT
private:

	const QSize _windowSize = QSize(1150, 690);
	std::unique_ptr<QGraphicsView> _view;
	std::unique_ptr<Scene1> _scene1;
	std::unique_ptr<Scene2> _scene2;
	std::unique_ptr<Scene3> _scene3;
	std::unique_ptr<Scene4> _scene4;


private slots:
	void scene2();
	void scene3();
	void scene4w();
	void scene4o();

public:
	GameWindow();
	GameWindow(const GameWindow&) = delete;
	GameWindow& operator=(const GameWindow&) = delete;

};