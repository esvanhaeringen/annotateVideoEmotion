#ifndef annotateVideoEmotion_H_
#define annotateVideoEmotion_H_

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <string>
#include <filesystem>
#include <vector>
#include "About.h"

namespace Ui {
    class annotateVideoEmotion;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class EqualizerDialog;

class annotateVideoEmotion : public QMainWindow
{
    Q_OBJECT
    About* about;
    bool d_ready = false;
    std::string d_annotator;
    std::filesystem::path d_sourcePath = std::filesystem::current_path()/"source";
    std::vector<std::string> d_file;
    std::vector<int> d_dur;
    std::vector<int> d_idc;
    std::vector<std::string> d_clip;
    std::vector<int> d_step;
    std::vector<int> d_nSteps;
    std::vector<int> d_val; 
    std::vector<int> d_aro;
    std::vector<int> d_lab;
    std::vector<QLabel*> d_subSliderLabels;

    int d_total = 0;
    int d_prog = 0;
    int d_current = 0;
    char const* d_descVal[5] = { "Strongly negative", "Slightly negative", "Neutral", "Slightly positive", "Strongly positive" };
    char const* d_descAro[5] = { "Strongly passive", "Slightly passive", "Neutral", "Slightly active", "Strongly active" };
    bool fullWasPlaying = false;
    bool subWasPlaying = false;
    bool sliderWasPressed = false;


public:
    explicit annotateVideoEmotion(QWidget* parent = 0);
    ~annotateVideoEmotion();

private slots:
    void loadVideo(QString url);
    void reference();
    void copyPrevious();
    void previous();
    void next();
    void move(int pos);
    void fullPlayPause();
    void subPlayPause();
    void subPlay();
    void locationResult();
    void changeAnnotator();
    void subDurationChanged(float dur);
    void fullDurationChanged(float dur);
    void subPositionChanged(float pos);
    void fullPositionChanged(float pos);
    void sliderPressed();
    void sliderReleased();
    void sliderValueChanged();
    void subMoveEdit();
    void totalMoveEdit();
    void resizeTable();

private:
    Ui::annotateVideoEmotion* ui;
    QMediaPlayer* mpFull;
    QMediaPlaylist* plFull;
    QMediaPlayer* mpSub;
    QMediaPlaylist* plSub;

    void deletePlayer();
    void reset();
    bool fileExists(const std::filesystem::path name);
    void setState();
    void videoSpeed();
    void saveResult();
    void writeFile();
    void updateStats(); 
    void updateTable();
    void updateTableHeaders(int col, QStringList row);
    void updateSubSliderLabels(int col);
    void setSelection();
};

#endif