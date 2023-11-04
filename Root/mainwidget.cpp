#include "mainwidget.h"
#include "./ui_mainwidget.h"
#include "rootwidget.h"
#include "wordwidget.h"

#include <QInputDialog>
#include <QMessageBox>

int chosenPages = 0;
int chosenLetters = 0;
bool mode; // 0: page, 1: letter

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowTitle("Roots Learner");
    mode = false;
    connect(ui->rootsButton_Letter, &QPushButton::clicked, this, &MainWidget::startOnlyRoots);
    connect(ui->rootsButton_Page, &QPushButton::clicked, this, &MainWidget::startOnlyRoots);
    connect(ui->wordsAndRootsButton_Letter, &QPushButton::clicked, this, &MainWidget::startWithWord);
    connect(ui->wordsAndRootsButton_Page, &QPushButton::clicked, this, &MainWidget::startWithWord);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_PageCheckBox_1_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 1);
}

void MainWidget::on_PageCheckBox_2_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 2);
}

void MainWidget::on_PageCheckBox_3_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 3);
}

void MainWidget::on_PageCheckBox_4_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 4);
}

void MainWidget::on_PageCheckBox_5_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 5);
}

void MainWidget::on_PageCheckBox_6_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 6);
}

void MainWidget::on_PageCheckBox_7_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 7);
}

void MainWidget::on_PageCheckBox_8_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 8);
}

void MainWidget::on_PageCheckBox_9_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 9);
}

void MainWidget::on_PageCheckBox_10_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 10);
}

void MainWidget::on_PageCheckBox_11_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 11);
}

void MainWidget::on_PageCheckBox_12_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 12);
}

void MainWidget::on_PageCheckBox_13_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 13);
}

void MainWidget::on_PageCheckBox_14_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 14);
}

void MainWidget::on_PageCheckBox_15_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 15);
}

void MainWidget::on_PageCheckBox_16_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 16);
}

void MainWidget::on_PageCheckBox_17_stateChanged(int arg1) {
    chosenPages = chosenPages ^ (1 << 17);
}

void MainWidget::on_PageCheckBox_18_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 18);
}

void MainWidget::on_PageCheckBox_19_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 19);
}

void MainWidget::on_PageCheckBox_20_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 20);
}

void MainWidget::on_PageCheckBox_21_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 21);
}

void MainWidget::on_PageCheckBox_22_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 22);
}

void MainWidget::on_PageCheckBox_23_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 23);
}

void MainWidget::on_PageCheckBox_24_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 24);
}

void MainWidget::on_PageCheckBox_25_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 25);
}

void MainWidget::on_PageCheckBox_26_stateChanged(int arg1)
{
    chosenPages = chosenPages ^ (1 << 26);
}

void MainWidget::on_PageCheckBox_27_stateChanged(int arg1) {
    chosenPages = chosenPages ^ (1 << 27);
}

void MainWidget::on_letterCheckBox_A_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 1);
}

void MainWidget::on_letterCheckBox_B_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 2);
}

void MainWidget::on_letterCheckBox_C_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 3);
}

void MainWidget::on_letterCheckBox_D_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 4);
}

void MainWidget::on_letterCheckBox_E_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 5);
}

void MainWidget::on_letterCheckBox_F_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 6);
}

void MainWidget::on_letterCheckBox_G_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 7);
}

void MainWidget::on_letterCheckBox_H_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 8);
}

void MainWidget::on_letterCheckBox_I_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 9);
}

void MainWidget::on_letterCheckBox_J_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 10);
}

void MainWidget::on_letterCheckBox_K_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 11);
}

void MainWidget::on_letterCheckBox_L_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 12);
}

void MainWidget::on_letterCheckBox_M_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 13);
}

void MainWidget::on_letterCheckBox_N_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 14);
}

void MainWidget::on_letterCheckBox_O_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 15);
}

void MainWidget::on_letterCheckBox_P_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 16);
}

void MainWidget::on_letterCheckBox_Q_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 17);
}

void MainWidget::on_letterCheckBox_R_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 18);
}

void MainWidget::on_letterCheckBox_S_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 19);
}

void MainWidget::on_letterCheckBox_T_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 20);
}

void MainWidget::on_letterCheckBox_U_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 21);
}

void MainWidget::on_letterCheckBox_V_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 22);
}

void MainWidget::on_letterCheckBox_W_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 23);
}

void MainWidget::on_letterCheckBox_X_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 24);
}

void MainWidget::on_letterCheckBox_Y_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 25);
}

void MainWidget::on_letterCheckBox_Z_stateChanged(int arg1) {
    chosenLetters = chosenLetters ^ (1 << 26);
}

void MainWidget::startOnlyRoots() {
    QObject* senderObj = sender();
    if (senderObj->objectName() == "rootsButton_Letter") {
	mode = true;
	if (chosenLetters == 0) {
	    QMessageBox::warning(NULL, "WARNING!", "Please choose at least one letter!");
	    return;
	}
    } else {
	mode = false;
	if (chosenPages == 0) {
	    QMessageBox::warning(NULL, "WARNING!", "Please choose at least one page!");
	    return;
	}
    }

    bool ok;
    QString strNumber = QInputDialog::getText(this, tr("Roots Learner"),
	tr("How many roots do you want to learn?"), QLineEdit::Normal,
	"1", &ok);
    bool isNum;
    if (ok && !strNumber.isEmpty()) {
	int number = strNumber.toInt(&isNum);
	if (!isNum) {
	    QMessageBox::warning(NULL, "WARNING!", "Please input a number!");
	    return;
	}
	if (number <= 0) {
	    QMessageBox::warning(NULL, "WARNING!", "You need to learn at lease one root!");
	    return;
	}
	RootWidget* w = new RootWidget(NULL, this, number);
	w->show();
	this->hide();
    }
}

void MainWidget::startWithWord() {
    QObject* senderObj = sender();
    if (senderObj->objectName() == "wordsAndRootsButton_Letter") {
	mode = true;
	if (chosenLetters == 0) {
	    QMessageBox::warning(NULL, "WARNING!", "Please choose at least one letter!");
	    return;
	}
    } else {
	mode = false;
	if (chosenPages == 0) {
	    QMessageBox::warning(NULL, "WARNING!", "Please choose at least one page!");
	    return;
	}
    }

    bool ok;
    QString strNumber = QInputDialog::getText(this, tr("Roots Learner"),
	tr("How many roots do you want to learn?"), QLineEdit::Normal,
	"1", &ok);
    bool isNum;
    if (ok && !strNumber.isEmpty()) {
	int number = strNumber.toInt(&isNum);
	if (!isNum) {
	    QMessageBox::warning(NULL, "WARNING!", "Please input a number!");
	    return;
	}
	if (number <= 0) {
	    QMessageBox::warning(NULL, "WARNING!", "You need to learn at lease one word!");
	    return;
	}
	WordWidget* w = new WordWidget(NULL, this, number);
	w->show();
	this->hide();
    }
}
