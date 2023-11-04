#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private slots:
    void on_PageCheckBox_1_stateChanged(int arg1);
    void on_PageCheckBox_2_stateChanged(int arg1);
    void on_PageCheckBox_3_stateChanged(int arg1);
    void on_PageCheckBox_4_stateChanged(int arg1);
    void on_PageCheckBox_5_stateChanged(int arg1);
    void on_PageCheckBox_6_stateChanged(int arg1);
    void on_PageCheckBox_7_stateChanged(int arg1);
    void on_PageCheckBox_8_stateChanged(int arg1);
    void on_PageCheckBox_9_stateChanged(int arg1);
    void on_PageCheckBox_10_stateChanged(int arg1);
    void on_PageCheckBox_11_stateChanged(int arg1);
    void on_PageCheckBox_12_stateChanged(int arg1);
    void on_PageCheckBox_13_stateChanged(int arg1);
    void on_PageCheckBox_14_stateChanged(int arg1);
    void on_PageCheckBox_15_stateChanged(int arg1);
    void on_PageCheckBox_16_stateChanged(int arg1);
    void on_PageCheckBox_17_stateChanged(int arg1);
    void on_PageCheckBox_18_stateChanged(int arg1);
    void on_PageCheckBox_19_stateChanged(int arg1);
    void on_PageCheckBox_20_stateChanged(int arg1);
    void on_PageCheckBox_21_stateChanged(int arg1);
    void on_PageCheckBox_22_stateChanged(int arg1);
    void on_PageCheckBox_23_stateChanged(int arg1);
    void on_PageCheckBox_24_stateChanged(int arg1);
    void on_PageCheckBox_25_stateChanged(int arg1);
    void on_PageCheckBox_26_stateChanged(int arg1);
    void on_PageCheckBox_27_stateChanged(int arg1);

    void on_letterCheckBox_A_stateChanged(int arg1);
    void on_letterCheckBox_B_stateChanged(int arg1);
    void on_letterCheckBox_C_stateChanged(int arg1);
    void on_letterCheckBox_D_stateChanged(int arg1);
    void on_letterCheckBox_E_stateChanged(int arg1);
    void on_letterCheckBox_F_stateChanged(int arg1);
    void on_letterCheckBox_G_stateChanged(int arg1);
    void on_letterCheckBox_H_stateChanged(int arg1);
    void on_letterCheckBox_I_stateChanged(int arg1);
    void on_letterCheckBox_J_stateChanged(int arg1);
    void on_letterCheckBox_K_stateChanged(int arg1);
    void on_letterCheckBox_L_stateChanged(int arg1);
    void on_letterCheckBox_M_stateChanged(int arg1);
    void on_letterCheckBox_N_stateChanged(int arg1);
    void on_letterCheckBox_O_stateChanged(int arg1);
    void on_letterCheckBox_P_stateChanged(int arg1);
    void on_letterCheckBox_Q_stateChanged(int arg1);
    void on_letterCheckBox_R_stateChanged(int arg1);
    void on_letterCheckBox_S_stateChanged(int arg1);
    void on_letterCheckBox_T_stateChanged(int arg1);
    void on_letterCheckBox_U_stateChanged(int arg1);
    void on_letterCheckBox_V_stateChanged(int arg1);
    void on_letterCheckBox_W_stateChanged(int arg1);
    void on_letterCheckBox_X_stateChanged(int arg1);
    void on_letterCheckBox_Y_stateChanged(int arg1);
    void on_letterCheckBox_Z_stateChanged(int arg1);

    void startOnlyRoots();
    void startWithWord();

private:
    Ui::MainWidget *ui;
    // TODO we need to clean learning widget when it closes
};
#endif // MAINWIDGET_H
