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

#pragma once

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui
{
class MusicWindow;
}

namespace f1x
{
namespace openauto
{
namespace autoapp
{
namespace ui
{

class MusicWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MusicWindow(QWidget *parent = nullptr);
    ~MusicWindow() override;

signals:
    void home();

private:
    Ui::MusicWindow* ui_;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;

private slots:
    void playPause();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void previousClicked();
    void metaDataChanged();

};

}
}
}
}
