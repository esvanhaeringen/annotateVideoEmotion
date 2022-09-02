#pragma once
#include <QDialog>
#include <QCoreApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <ui_exampleDialog.h>
#include <filesystem>
#include <QtGui>
#include <QtWidgets>
#include <vector>
#include <QVideoWidget>

namespace Ui {
	class exampleDialog;
}

class Overlay;

class ExampleDialog : public QDialog
{
	Q_OBJECT
	std::filesystem::path d_examplesPath = std::filesystem::current_path() / "examples";
    Ui::exampleDialog* ui;
    std::vector<QVideoWidget*> vw;
    std::vector<QMediaPlaylist*> pl;
    std::vector<QMediaPlayer*> mp;
public:
    ExampleDialog(int valence, int arousal, int maxExamples, QWidget* parent = 0);
	~ExampleDialog();

private:
    void makePlayers(int numberOfPlayers);
    void deleteVideos();
    void loadVideos();
};