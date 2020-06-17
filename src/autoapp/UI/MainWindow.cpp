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

#include <QApplication>
#include <QDateTime>
#include <QTimer>
#include <f1x/openauto/autoapp/UI/MainWindow.hpp>
#include "ui_mainwindow.h"
#include <f1x/openauto/Common/Log.hpp>
#include <fstream>

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    connect(ui_->pushButtonAndroidAuto, &QPushButton::clicked, this, &MainWindow::openAndroidAuto);
    connect(ui_->pushButtonExit, &QPushButton::clicked, this, &MainWindow::exit);
    connect(ui_->pushButtonToggleCursor, &QPushButton::clicked, this, &MainWindow::toggleCursor);
    connect(ui_->pushButtonWirelessConnection, &QPushButton::clicked, this, &MainWindow::openConnectDialog);

    // Start the clock
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    timer->start(1000);
    showTime();

    // File watcher
    watcher_tmp = new QFileSystemWatcher(this);
    watcher_tmp->addPath("/tmp");
    connect(watcher_tmp, &QFileSystemWatcher::directoryChanged, this, &MainWindow::tmpChanged);

    // Music App
    autoapp::ui::MusicWindow *musicWindow = new MusicWindow();
    ui_->stackedWidget->insertWidget(1, musicWindow);
    connect(musicWindow, &MusicWindow::home, this, &MainWindow::moveHome);

    // Settings App
    auto configuration = std::make_shared<autoapp::configuration::Configuration>();
    autoapp::ui::SettingsWindow *settingsWindow = new SettingsWindow(configuration);
    ui_->stackedWidget->insertWidget(2, settingsWindow);
    connect(settingsWindow, &SettingsWindow::home, this, &MainWindow::moveHome);

}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::showTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui_->lblTime->setText(currentDateTime.toString("hh:mm"));
    ui_->lblDate->setText(currentDateTime.toString("d MMMM yyyy"));
}

void MainWindow::tmpChanged()
{
    try {
        if (std::ifstream("/tmp/entityexit")) {
            MainWindow::TriggerAppStop();
            std::remove("/tmp/entityexit");
        }
    } catch (...) {
        OPENAUTO_LOG(error) << "[OpenAuto] Error in entityexit";
    }
}

void MainWindow::on_pushMusicPlayer_clicked()
{
    ui_->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButtonSettings_clicked()
{
    ui_->stackedWidget->setCurrentIndex(2);
}

void MainWindow::moveHome() {
    ui_->stackedWidget->setCurrentIndex(0);
}

}
}
}
}

