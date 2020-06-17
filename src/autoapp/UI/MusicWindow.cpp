/*
*  This file is part of openauto project.
*  Copyright (C) 2018 f1x.studio (Michal Szwaj)
*
*  openauto is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.

*  openauto is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with openauto. If not, see <http://www.gnu.org/licenses/>.
*/

#include <f1x/openauto/autoapp/UI/MusicWindow.hpp>
#include "ui_musicwindow.h"
#include <fstream>
#include <QStyle>
#include <QTimer>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{

MusicWindow::MusicWindow(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::MusicWindow)
{
    ui_->setupUi(this);
    connect(ui_->pushHomeButton, &QPushButton::clicked, this, &MusicWindow::home);

    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/home/tlepage/test.mp3"));
    player->setVolume(50);

    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
}

MusicWindow::~MusicWindow()
{
    delete ui_;
}

void MusicWindow::load()
{
    ui_->lblSongName->setText("Ceci est un test");
    QPixmap mypix ("/home/tlepage/Pictures/ecole.png");
    ui_->imgArtwork->setPixmap(mypix);
}

void MusicWindow::on_playPauseButton_clicked()
{
    if (player->state() == QMediaPlayer::PlayingState) {
        QPixmap pix(":/play.png");
        QIcon icon(pix);
        player->pause();
        ui_->playPauseButton->setIcon(icon);
    } else {
        QPixmap pix(":/pause.png");
        QIcon icon(pix);
        player->play();
        ui_->playPauseButton->setIcon(icon);
    }
}

void MusicWindow::durationChanged(qint64 duration)
{
    //this->duration = duration/1000;
    ui_->sliderDuration->setMaximum(duration / 1000);
}

void MusicWindow::positionChanged(qint64 progress)
{
    if (!ui_->sliderDuration->isSliderDown()) {
        ui_->sliderDuration->setValue(progress / 1000);
    }
    //updateDurationInfo(progress / 1000);
}

}
}
}
}




