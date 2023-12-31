#include "wordwidget.h"
#include "ui_wordwidget.h"

#include <QCloseEvent>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QPalette>
#include <QRandomGenerator>

extern int chosenPages;
extern int chosenLetters;
extern bool mode; // 0: page, 1: letter

WordWidget::WordWidget(QWidget *parent, QWidget *wordWidget, int learnNumber)
    : QWidget(parent)
    , ui(new Ui::WordWidget)
    , fatherWidget(wordWidget)
    , status(ROOT) {
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setWindowTitle("Root Leaner");
    readData();
    learnedWords = new bool[wordNumber + 1] {};
    learnedNumber = 0;
    numberToLearn = std::min(learnNumber, wordNumber);

    connect(ui->skipButton, &QPushButton::clicked, this, &WordWidget::do_skipButton_clicked);
    connect(ui->AChoiceButton, &QPushButton::clicked, this, &WordWidget::do_chose_answer);
    connect(ui->BChoiceButton, &QPushButton::clicked, this, &WordWidget::do_chose_answer);
    connect(ui->CChoiceButton, &QPushButton::clicked, this, &WordWidget::do_chose_answer);
    connect(ui->DChoiceButton, &QPushButton::clicked, this, &WordWidget::do_chose_answer);
    connect(ui->nextButton, &QPushButton::clicked, this, &WordWidget::do_nextButton_clicked);
    QString proc = QString::number(learnedNumber) + "/" + QString::number(numberToLearn);
    ui->progerssLabel->setText(proc);
    nextRoot();
}

WordWidget::~WordWidget() {
    int len = roots.length();
    for (int i = 0; i < len; ++i) {
	delete roots[i];
    }
    len = allRoots.length();
    for (int i = 0; i < len; ++i) {
	delete allRoots[i];
    }
    delete learnedWords;
    delete ui;
}

void WordWidget::initChoice(int answer, QString ans, QString choice1, QString choice2, QString choice3) {
    QPalette pal = ui->skipButton->palette();
    ui->AChoiceButton->setPalette(pal);
    ui->BChoiceButton->setPalette(pal);
    ui->CChoiceButton->setPalette(pal);
    ui->DChoiceButton->setPalette(pal);
    ui->AChoiceButton->setEnabled(true);
    ui->BChoiceButton->setEnabled(true);
    ui->CChoiceButton->setEnabled(true);
    ui->DChoiceButton->setEnabled(true);
    switch (answer) {
    case 0:
	ui->AChoiceButton->setText(ans);
	ui->BChoiceButton->setText(choice1);
	ui->CChoiceButton->setText(choice2);
	ui->DChoiceButton->setText(choice3);
	break;
    case 1:
	ui->AChoiceButton->setText(choice1);
	ui->BChoiceButton->setText(ans);
	ui->CChoiceButton->setText(choice2);
	ui->DChoiceButton->setText(choice3);
	break;
    case 2:
	ui->AChoiceButton->setText(choice1);
	ui->BChoiceButton->setText(choice2);
	ui->CChoiceButton->setText(ans);
	ui->DChoiceButton->setText(choice3);
	break;
    case 3:
	ui->AChoiceButton->setText(choice1);
	ui->BChoiceButton->setText(choice2);
	ui->CChoiceButton->setText(choice3);
	ui->DChoiceButton->setText(ans);
	break;
    }
}

int WordWidget::generateRandomNumber() {
    return QRandomGenerator::global()->bounded(allRootNumber);
}

void WordWidget::closeEvent(QCloseEvent *event) {
    fatherWidget->show();
    event->accept();
}

void WordWidget::readData() {
    if (!mode) { // page
	QFile file(":/root/res/res_page.json");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	    QMessageBox::warning(this, "Error", "Cannot read data");
	    this->close();
	    return;
	}
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
	file.close();
	if (error.error != QJsonParseError::NoError) {
	    QMessageBox::warning(this, "Error", "Fail to read json");
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
			Word *newWord = new Word(example, currentRoot, examples.value(example).toString());
			currentRoot->addWord(newWord);
			words.append(newWord);
		    }
		    ++number;
		}
	    }
	}
	rootNumber = number;
	wordNumber = words.length();

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
		    Word *newWord = new Word(example, currentRoot, examples.value(example).toString());
		    currentRoot->addWord(newWord);
		    allWords.append(newWord);
		}
		++number;
	    }
	}
	allRootNumber = number;
	allWordNumber = allWords.length();
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
			Word *newWord = new Word(example, currentRoot, meaning);
			currentRoot->addWord(newWord);
			words.append(newWord);
		    }
		    ++number;
		}
	    }
	}
	rootNumber = number;
	wordNumber = words.length();
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
		    Word *newWord = new Word(example, currentRoot, meaning);
		    currentRoot->addWord(newWord);
		    allWords.append(newWord);
		}
		++number;
	    }
	}
	allRootNumber = number;
	allWordNumber = allWords.length();
    }
}

void WordWidget::nextRoot() {
    status = ROOT;
    ui->descriptionLabel->setText("Please choose the root of the word");
    ui->nextButton->hide();
    ui->skipButton->setEnabled(true);
    QString proc = QString::number(learnedNumber) + "/" + QString::number(numberToLearn);
    ui->progerssLabel->setText(proc);
    if (learnedNumber == numberToLearn) {
	QMessageBox::information(this, "Congratulations", "You have learned all roots!");
	this->close();
	return;
    }
    int temp = QRandomGenerator::global()->bounded(wordNumber - learnedNumber);
    int index = 0, i = -1;
    while (true) {
	if (!learnedWords[index]) {
	    ++i;
	    if (i == temp)
		break;
	}
	++index;
    }
    learnedWords[index] = true;
    currentWord = words[index];
    QString root = currentWord->getRoot()->getRoot();
    answer = QRandomGenerator::global()->bounded(4);
    ui->label->setText(currentWord->getWord());
    QString alter1, alter2, alter3;
    int tempAlter1, tempAlter2, tempAlter3;
    while (allRoots[tempAlter1 = generateRandomNumber()]->getRoot() == root)
	continue;
    while (allRoots[tempAlter2 = generateRandomNumber()]->getRoot() == root || tempAlter2 == tempAlter1)
	continue;
    while (allRoots[tempAlter3 = generateRandomNumber()]->getRoot() == root || tempAlter3 == tempAlter1 || tempAlter3 == tempAlter2)
	continue;
    alter1 = allRoots[tempAlter1]->getRoot();
    alter2 = allRoots[tempAlter2]->getRoot();
    alter3 = allRoots[tempAlter3]->getRoot();
    initChoice(answer, root, alter1, alter2, alter3);
}

void WordWidget::nextRootMeaning() {
    status = ROOT_MEANING;
    ui->descriptionLabel->setText("Please choose the root's meaning");
    QString rootMeaning = currentWord->getRoot()->getMeaning();
    answer = QRandomGenerator::global()->bounded(4);
    QString alter1, alter2, alter3;
    int tempAlter1, tempAlter2, tempAlter3;
    while (allRoots[tempAlter1 = generateRandomNumber()]->getMeaning() == rootMeaning)
	continue;
    while (allRoots[tempAlter2 = generateRandomNumber()]->getMeaning() == rootMeaning || tempAlter2 == tempAlter1)
	continue;
    while (allRoots[tempAlter3 = generateRandomNumber()]->getMeaning() == rootMeaning || tempAlter3 == tempAlter1 || tempAlter3 == tempAlter2)
	continue;
    alter1 = allRoots[tempAlter1]->getMeaning();
    alter2 = allRoots[tempAlter2]->getMeaning();
    alter3 = allRoots[tempAlter3]->getMeaning();
    initChoice(answer, rootMeaning, alter1, alter2, alter3);
}

void WordWidget::nextWordMeaning() {
    status = WORD_MEANING;
    ui->descriptionLabel->setText("Please choose the word's meaning");
    QString wordMeaning = currentWord->getMeaning();
    answer = QRandomGenerator::global()->bounded(4);
    QString alter1, alter2, alter3;
    int tempAlter1, tempAlter2, tempAlter3;
    while (allWords[tempAlter1 = generateRandomNumber()]->getMeaning() == wordMeaning)
	continue;
    while (allWords[tempAlter2 = generateRandomNumber()]->getMeaning() == wordMeaning || tempAlter2 == tempAlter1)
	continue;
    while (allWords[tempAlter3 = generateRandomNumber()]->getMeaning() == wordMeaning || tempAlter3 == tempAlter1 || tempAlter3 == tempAlter2)
	continue;
    alter1 = allWords[tempAlter1]->getMeaning();
    alter2 = allWords[tempAlter2]->getMeaning();
    alter3 = allWords[tempAlter3]->getMeaning();
    initChoice(answer, wordMeaning, alter1, alter2, alter3);
}

void WordWidget::do_skipButton_clicked() {
    ++learnedNumber;
    QString proc = QString::number(learnedNumber) + "/" + QString::number(numberToLearn);
    ui->progerssLabel->setText(proc);
    nextRoot();
}

void WordWidget::do_nextButton_clicked() {
    nextRoot();
}

void WordWidget::do_chose_answer() {
    if (status == ROOT) {
	QObject *senderObj = sender();
	QString senderName = senderObj->objectName();
	if (senderName[0].unicode() - 'A' == answer) {
	    ui->nextButton->setEnabled(true);
	    QString display = ui->label->text();
	    display += "\nRoot: " + currentWord->getRoot()->getRoot();
	    ui->label->setText(display);
	    nextRootMeaning();
	} else {
	    QPushButton *pushedButton = qobject_cast<QPushButton *>(senderObj);
	    QPalette pal = pushedButton->palette();
	    QColor tempColor(170, 0, 0);
	    pal.setColor(QPalette::Button, tempColor);
	    pushedButton->setPalette(pal);
	}
    } else if (status == ROOT_MEANING) {
	QObject *senderObj = sender();
	QString senderName = senderObj->objectName();
	if (senderName[0].unicode() - 'A' == answer) {
	    ui->nextButton->setEnabled(true);
	    QString display = ui->label->text();
	    display += "\nRoot's meaning: " + currentWord->getRoot()->getMeaning();
	    ui->label->setText(display);
	    nextWordMeaning();
	} else {
	    QPushButton *pushedButton = qobject_cast<QPushButton *>(senderObj);
	    QPalette pal = pushedButton->palette();
	    QColor tempColor(170, 0, 0);
	    pal.setColor(QPalette::Button, tempColor);
	    pushedButton->setPalette(pal);
	}
    } else {
	QObject *senderObj = sender();
	QString senderName = senderObj->objectName();
	if (senderName[0].unicode() - 'A' == answer) {
	    ui->nextButton->setEnabled(true);
	    QString display = ui->label->text();
	    display += "\nWord's meaning: " + currentWord->getMeaning();
	    ui->label->setText(display);
	    QPushButton *pushedButton = qobject_cast<QPushButton *>(senderObj);
	    QPalette pal = pushedButton->palette();
	    QColor tempColor(0, 170, 0);
	    pal.setColor(QPalette::Button, tempColor);
	    pushedButton->setPalette(pal);
	    ui->AChoiceButton->setEnabled(false);
	    ui->BChoiceButton->setEnabled(false);
	    ui->CChoiceButton->setEnabled(false);
	    ui->DChoiceButton->setEnabled(false);
	    ui->nextButton->show();
	    ui->skipButton->setEnabled(false);
	    ++learnedNumber;
	    QString proc = QString::number(learnedNumber) + "/" + QString::number(numberToLearn);
	    ui->progerssLabel->setText(proc);
	} else {
	    QPushButton *pushedButton = qobject_cast<QPushButton *>(senderObj);
	    QPalette pal = pushedButton->palette();
	    QColor tempColor(170, 0, 0);
	    pal.setColor(QPalette::Button, tempColor);
	    pushedButton->setPalette(pal);
	}
    }
}
