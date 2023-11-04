#include "rootwidget.h"
#include "ui_rootwidget.h"

#include <QColor>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QPalette>
#include <QRandomGenerator>

#include <QDebug>

extern int chosenPages;
extern int chosenLetters;
extern bool mode; // 0: page, 1: letter

RootWidget::RootWidget(QWidget *parent, QWidget *rootWidget, int learnNumber)
    : QWidget(parent)
    , ui(new Ui::RootWidget)
    , fatherWidget(rootWidget) {
    ui->setupUi(this);
    setWindowTitle("Roots Leaner");
    setAttribute(Qt::WA_DeleteOnClose, true);

    readData();
    numberToLearn = std::min(learnNumber, rootNumber);
    learnedRoots = new bool[rootNumber + 1] {};
    learnedNumber = 0;
    connect(ui->AChoiceButton, &QPushButton::clicked, this, &RootWidget::do_chose_answer);
    connect(ui->BChoiceButton, &QPushButton::clicked, this, &RootWidget::do_chose_answer);
    connect(ui->CChoiceButton, &QPushButton::clicked, this, &RootWidget::do_chose_answer);
    connect(ui->DChoiceButton, &QPushButton::clicked, this, &RootWidget::do_chose_answer);
    connect(ui->nextButton, &QPushButton::clicked, this, &RootWidget::do_nextButton_clicked);
    next();
}

RootWidget::~RootWidget() {
    int len = roots.length();
    for (int i = 0; i < len; ++i) {
	delete roots[i];
    }
    len = allRoots.length();
    for (int i = 0; i < len; ++i) {
	delete allRoots[i];
    }
    delete learnedRoots;
    delete ui;
}

void RootWidget::next() {
    ui->nextButton->setEnabled(false);
    QString proc = QString::number(learnedNumber) + "/" + QString::number(numberToLearn);
    ui->procressLable->setText(proc);
    if (learnedNumber == numberToLearn) {
	QMessageBox::information(this, "Congratulations", "You have learned all roots!");
	this->close();
	return;
    }
    int temp = QRandomGenerator::global()->bounded(rootNumber - learnedNumber);
    int index = 0, i = -1;
    while (true) {
	if (!learnedRoots[index]) {
	    ++i;
	    if (i == temp)
		break;
	}
	++index;
    }
    learnedRoots[index] = true;
    currentRoot = roots[index];
    QString root = currentRoot->getRoot();
    currentRootMeaning = currentRoot->getMeaning();
    QVector<Word *> words = currentRoot->getAllWords();
    rootExample.clear();
    for (Word *&word : words) {
	rootExample += "\n";
	rootExample += word->getWord();
	rootExample += "   ";
	rootExample += word->getMeaning();
    }
    answer = QRandomGenerator::global()->bounded(4);
    ui->label->setText(root);
    QString alter1, alter2, alter3;
    int tempAlter1, tempAlter2, tempAlter3;
    while (allRoots[tempAlter1 = QRandomGenerator::global()->bounded(allRootNumber)]->getRoot() == root)
	continue;
    while (allRoots[tempAlter2 = QRandomGenerator::global()->bounded(allRootNumber)]->getRoot() == root || tempAlter2 == tempAlter1)
	continue;
    while (allRoots[tempAlter3 = QRandomGenerator::global()->bounded(allRootNumber)]->getRoot() == root || tempAlter3 == tempAlter1 || tempAlter3 == tempAlter2)
	continue;
    alter1 = allRoots[tempAlter1]->getMeaning();
    alter2 = allRoots[tempAlter2]->getMeaning();
    alter3 = allRoots[tempAlter3]->getMeaning();
    switch (answer) {
    case 0:
	ui->AChoiceButton->setText(currentRootMeaning);
	ui->BChoiceButton->setText(alter1);
	ui->CChoiceButton->setText(alter2);
	ui->DChoiceButton->setText(alter3);
	break;
    case 1:
	ui->AChoiceButton->setText(alter1);
	ui->BChoiceButton->setText(currentRootMeaning);
	ui->CChoiceButton->setText(alter2);
	ui->DChoiceButton->setText(alter3);
	break;
    case 2:
	ui->AChoiceButton->setText(alter1);
	ui->BChoiceButton->setText(alter2);
	ui->CChoiceButton->setText(currentRootMeaning);
	ui->DChoiceButton->setText(alter3);
	break;
    case 3:
	ui->AChoiceButton->setText(alter1);
	ui->BChoiceButton->setText(alter2);
	ui->CChoiceButton->setText(alter3);
	ui->DChoiceButton->setText(currentRootMeaning);
	break;
    }
}

void RootWidget::closeEvent(QCloseEvent *event) {
    fatherWidget->show();
    event->accept();
}

void RootWidget::readData() {
    if (!mode) { // page
	QFile file(":/root/res/res_page.json");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	    QMessageBox::critical(this, "Error", "Cannot read data");
	    this->close();
	    return;
	}
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
	file.close();
	if (error.error != QJsonParseError::NoError) {
	    QMessageBox::critical(this, "Error", "Fail to read json");
	    this->close();
	    return;
	}
	QJsonObject pageObj = doc.object();
	int number = 0;
	for (int i = 1; i <= 27; ++i) {
	    if (chosenPages & (1 << i)) {
		QJsonObject page = pageObj.value(QString::number(i)).toObject();
		for (const QString &root : page.keys()) {
		    QJsonObject rootObj = page.value(root).toObject();
		    roots.append(new Root(root));
		    Root *currentRoot = roots[number];
		    currentRoot->setMeaning(rootObj.value("meaning").toString());
		    QJsonObject examples = rootObj.value("examples").toObject();
		    for (const QString &example : examples.keys()) {
			currentRoot->addWord(new Word(example, currentRoot, examples.value(example).toString()));
		    }
		    ++number;
		}
	    }
	}
	rootNumber = number;

	number = 0;
	for (int i = 1; i <= 27; ++i) {
	    QJsonObject page = pageObj.value(QString::number(i)).toObject();
	    for (const QString &root : page.keys()) {
		QJsonObject rootObj = page.value(root).toObject();
		allRoots.append(new Root(root));
		Root *currentRoot = allRoots[number];
		currentRoot->setMeaning(rootObj.value("meaning").toString());
		QJsonObject examples = rootObj.value("examples").toObject();
		for (const QString &example : examples.keys()) {
		    currentRoot->addWord(new Word(example, currentRoot, examples.value(example).toString()));
		}
		++number;
	    }
	}
	allRootNumber = number;
    } else { // letter
	QFile file(":/root/res/res_letter.json");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	    QMessageBox::critical(this, "Error", "Cannot read data");
	    this->close();
	    return;
	}
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
	file.close();
	if (error.error != QJsonParseError::NoError) {
	    QMessageBox::critical(this, "Error", "Fail to read json");
	    this->close();
	    return;
	}

	QJsonObject letterObj = doc.object();
	int number = 0;
	for (int i = 1; i <= 26; ++i) {
	    if (chosenLetters & (1 << i)) {
		QJsonObject letter = letterObj.value(QString(QChar('A' - 1 + i))).toObject();
		for (const QString &root : letter.keys()) {
		    QJsonObject rootObj = letter.value(root).toObject();
		    roots.append(new Root(root));
		    Root *currentRoot = roots[number];
		    currentRoot->setMeaning(rootObj.value("meaning").toString());
		    QJsonObject examples = rootObj.value("examples").toObject();
		    for (const QString &example : examples.keys()) {
			QJsonObject exampleObj = examples.value(example).toObject();
			QString meaning = exampleObj.value("property").toString() + " " + exampleObj.value("meaning").toString();
			currentRoot->addWord(new Word(example, currentRoot, meaning));
		    }
		    ++number;
		}
	    }
	}
	rootNumber = number;
	number = 0;
	for (int i = 1; i <= 26; ++i) {
	    QJsonObject letter = letterObj.value(QString(QChar('A' - 1 + i))).toObject();
	    for (const QString &root : letter.keys()) {
		QJsonObject rootObj = letter.value(root).toObject();
		allRoots.append(new Root(root));
		Root *currentRoot = allRoots[number];
		currentRoot->setMeaning(rootObj.value("meaning").toString());
		QJsonObject examples = rootObj.value("examples").toObject();
		for (const QString &example : examples.keys()) {
		    QJsonObject exampleObj = examples.value(example).toObject();
		    QString meaning = exampleObj.value("property").toString() + " " + exampleObj.value("meaning").toString();
		    currentRoot->addWord(new Word(example, currentRoot, meaning));
		}
		++number;
	    }
	}
	allRootNumber = number;
    }
}

void RootWidget::do_chose_answer() {
    QObject *senderObj = sender();
    QString senderName = senderObj->objectName();
    if (senderName[0].unicode() - 'A' == answer) {
	ui->nextButton->setEnabled(true);
	ui->label->setText(currentRoot->getRoot() + " = " + currentRootMeaning + rootExample);
	QPushButton *pushedButton = qobject_cast<QPushButton *>(senderObj);
	QPalette pal = pushedButton->palette();
	QColor tempColor(0, 170, 0);
	pal.setColor(QPalette::Button, tempColor);
	pushedButton->setPalette(pal);
	ui->AChoiceButton->setEnabled(false);
	ui->BChoiceButton->setEnabled(false);
	ui->CChoiceButton->setEnabled(false);
	ui->DChoiceButton->setEnabled(false);
    } else {
	QPushButton *pushedButton = qobject_cast<QPushButton *>(senderObj);
	QPalette pal = pushedButton->palette();
	QColor tempColor(170, 0, 0);
	pal.setColor(QPalette::Button, tempColor);
	pushedButton->setPalette(pal);
    }
}

void RootWidget::on_skipButton_clicked() {
    QPalette pal = ui->skipButton->palette();
    ui->AChoiceButton->setPalette(pal);
    ui->BChoiceButton->setPalette(pal);
    ui->CChoiceButton->setPalette(pal);
    ui->DChoiceButton->setPalette(pal);
    ui->AChoiceButton->setEnabled(true);
    ui->BChoiceButton->setEnabled(true);
    ui->CChoiceButton->setEnabled(true);
    ui->DChoiceButton->setEnabled(true);
    ++learnedNumber;
    next();
}

void RootWidget::do_nextButton_clicked() {
    QPalette pal = ui->skipButton->palette();
    ui->AChoiceButton->setPalette(pal);
    ui->BChoiceButton->setPalette(pal);
    ui->CChoiceButton->setPalette(pal);
    ui->DChoiceButton->setPalette(pal);
    ui->AChoiceButton->setEnabled(true);
    ui->BChoiceButton->setEnabled(true);
    ui->CChoiceButton->setEnabled(true);
    ui->DChoiceButton->setEnabled(true);
    ++learnedNumber;
    next();
}
