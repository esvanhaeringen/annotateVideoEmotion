#include "ExampleDialog.h"
#include <string>
#include <sstream>
#include <filesystem>
#include <QComboBox>

using namespace std;
namespace fs = filesystem;

ExampleDialog::ExampleDialog(int valence, int arousal, int maxExamples, QWidget* parent)
    :ui(new Ui::exampleDialog)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->setupUi(this);
    const char* valLabels[] = { "Very negative", "Slightly negative", "Neutral", "Slightly positive", "Very positive" };
    const char* aroLabels[] = { "Very passive", "Slightly passive", "Neutral", "Slightly active", "Very active" };
    setWindowTitle(QStringLiteral("Example clips of Valence: %1 | Arousal: %2").arg(valLabels[valence]).arg(aroLabels[arousal]));  
    ui->arousalCB->setCurrentIndex(arousal);
    ui->valenceCB->setCurrentIndex(valence);

    connect(ui->arousalCB, &QComboBox::currentTextChanged, this, &ExampleDialog::loadVideos);
    connect(ui->valenceCB, &QComboBox::currentTextChanged, this, &ExampleDialog::loadVideos);

    makePlayers(maxExamples);
    loadVideos();
    QApplication::restoreOverrideCursor();
}

ExampleDialog::~ExampleDialog()
{
    delete ui;
    deleteVideos();
}

void ExampleDialog::deleteVideos()
{
    for (int idx = 0; idx < vw.size(); ++idx)
    {
        vw[idx]->~QVideoWidget();
        pl[idx]->~QMediaPlaylist();
        mp[idx]->~QMediaPlayer();
    }
    vw.clear();
    pl.clear();
    mp.clear();
}

void ExampleDialog::makePlayers(int numberOfPlayers)
{
    for (int idx = 0; idx < numberOfPlayers; ++idx)
    {
        vw.push_back(new QVideoWidget(this));
        ui->gridLayout->addWidget(vw[idx], int(idx / 3), idx % 3);
        pl.push_back(new QMediaPlaylist(this));
        pl[idx]->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
        mp.push_back(new QMediaPlayer(this));
        mp[idx]->setVideoOutput(vw[idx]);
        mp[idx]->setVolume(0);
        mp[idx]->setPlaylist(pl[idx]);
    }
}

void ExampleDialog::loadVideos()
{
    for (int idx = 0; idx < pl.size(); ++idx)
        pl[idx]->clear();

    stringstream folder;
    folder << "A" << ui->arousalCB->currentIndex() << "V" << ui->valenceCB->currentIndex();
    int vidCounter = 0;
    for (const auto& entry : fs::directory_iterator(d_examplesPath / folder.str()))
    {
        if (vidCounter < vw.size() && entry.path().extension() == ".avi")
        {  
            pl[vidCounter]->addMedia(QUrl::fromLocalFile(QString::fromStdString(entry.path().string())));
            mp[vidCounter]->play();
            vidCounter += 1;
        }
    }
}