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
#include <QMediaMetaData>
#include <QImage>
#include <QStringList>
#include <QUrl>

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
    playlist = new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    QStringList filenames = { "/home/tlepage/test.mp3", "/home/tlepage/test2.mp3" };
    for(const QString & filename: filenames){
        playlist->addMedia(QMediaContent(QUrl::fromLocalFile(filename)));
    }

    player->setPlaylist(playlist);
    player->setVolume(50);

    connect(player, &QMediaPlayer::durationChanged, this, &MusicWindow::durationChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &MusicWindow::positionChanged);
    connect(player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &MusicWindow::metaDataChanged);
    connect(ui_->nextButton, &QPushButton::clicked, playlist, &QMediaPlaylist::next);
    connect(ui_->previousButton, &QPushButton::clicked, this, &MusicWindow::previousClicked);
    connect(ui_->playPauseButton, &QPushButton::clicked, this, &MusicWindow::playPause);

    metaDataChanged();
}

MusicWindow::~MusicWindow()
{
    delete ui_;
    delete player;
    delete playlist;
}

void MusicWindow::playPause()
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

void MusicWindow::metaDataChanged()
{
    if (player->isMetaDataAvailable()) {
        ui_->lblSongName->setText(player->metaData(QMediaMetaData::Title).toString());
        ui_->lblSongArtist->setText(player->metaData(QMediaMetaData::AlbumArtist).toString());
        if (ui_->imgArtwork) {
            QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();
            if (url.isEmpty()) {
                QImage image = player->metaData(QMediaMetaData::CoverArtImage).value<QImage>();
                QPixmap pMap = QPixmap::fromImage(image).scaled(ui_->imgArtwork->size(),Qt::KeepAspectRatio);
                ui_->imgArtwork->setPixmap(pMap);

            } else {
                ui_->imgArtwork->setPixmap(QPixmap(url.toString()));
            }

        }
    }
}

void MusicWindow::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
    if(player->position() <= 5000) {
        playlist->previous();
    }
    else {
        player->setPosition(0);
    }
}

}
}
}
}




