//
// Created by Eric on 6/4/2024.
//

#pragma once
#include "service.h"
#include <QDialog>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPaintEvent>

class Painting : public QDialog, public Observer {
private:
    Service& service;
    QLabel* label;

public:
    explicit Painting(Service& serv, QWidget *parent = nullptr) : QDialog(parent), service(serv) {
        service.adauga_listener(this);
        label = new QLabel("Număr de cercuri: 0");
        auto layout = new QVBoxLayout(this);
        layout->addWidget(label);
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        auto const& reteta = service.cos_getAll();

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distributionX(0, width());
        std::uniform_int_distribution<int> distributionY(0, height());

        int numar = 0;
        for (const auto& medicament : reteta) {
            painter.setPen(QPen(Qt:: green, 10));
            painter.setBrush(QBrush{Qt::green,Qt :: SolidPattern});
            int x = distributionX(generator);
            int y = distributionY(generator);
            painter.drawEllipse(x, y, 30, 30);

            numar++;
        }
        label->setText("Numar de cercuri: " + QString::number(numar));
    }

    void update() override {
        repaint();
    }

    ~Painting() override {
        service.sterge_listener(this);
    }
};

