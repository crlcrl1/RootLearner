#ifndef ROOTWIDGET_H
#define ROOTWIDGET_H

#include <QCloseEvent>
#include <QVector>
#include <QWidget>

#include "root.h"
// #include "word.h"

namespace Ui {
class RootWidget;
}

/**
 * @brief The RootWidget class
 * @var roots Roots in selected area
 * @var rootNumber Number of roots in selected area
 * @var allRoots All roots in database
 * @var allRootNumber Number of all roots in database
 */
class RootWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RootWidget(QWidget *parent = nullptr, QWidget *rootWidget = nullptr, int learnNumber = 10000);
    ~RootWidget();
    
private:
    Ui::RootWidget *ui;
    QWidget *fatherWidget;
    QVector<Root *> roots;
    int rootNumber;
    QVector<Root *> allRoots;
    int allRootNumber;
    bool *learnedRoots;
    int learnedNumber;
    int numberToLearn;

    Root *currentRoot;
    QString currentRootMeaning;
    QString rootExample;
    int answer;

    void next();

    void closeEvent(QCloseEvent *event);
    void readData();

private slots:
    void do_chose_answer();
    void on_skipButton_clicked();
    void do_nextButton_clicked();
};

#endif // ROOTWIDGET_H
