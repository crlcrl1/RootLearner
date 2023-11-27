#ifndef WORDWIDGET_H
#define WORDWIDGET_H

#include "root.h"
#include "word.h"

#include <QVector>
#include <QWidget>

enum Status {
    ROOT,
    ROOT_MEANING,
    WORD_MEANING
};

namespace Ui {
class WordWidget;
}

class WordWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WordWidget(QWidget *parent = nullptr, QWidget *wordWidget = nullptr, int learnNumber = 10000);
    ~WordWidget();
    
private:
    Ui::WordWidget *ui;
    QWidget *fatherWidget;
    int numberToLearn;
    QVector<Word *> words;
    int wordNumber;
    QVector<Word *> allWords;
    int allWordNumber;
    QVector<Root *> roots;
    int rootNumber;
    QVector<Root *> allRoots;
    int allRootNumber;
    bool *learnedWords;
    int learnedNumber;
    Word *currentWord;
    int answer;
    Status status;

    void initChoice(int answer, QString ans, QString choice1, QString choice2, QString choice3);
    int generateRandomNumber();

    void closeEvent(QCloseEvent *event);
    void readData();
    void nextRoot();
    void nextRootMeaning();
    void nextWordMeaning();

private slots:
    void do_skipButton_clicked();
    void do_nextButton_clicked();
    void do_chose_answer();
};

#endif // WORDWIDGET_H
