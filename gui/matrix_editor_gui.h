#ifndef MATRIX_GUI_H
#define MATRIX_GUI_H

#include <QWidget>
#include <QTableWidget>
#include "calculator/matrix.h"

namespace Ui {
class Matrix_editor_gui;
}

class Matrix_editor_gui : public QWidget
{
    Q_OBJECT

public:
    explicit Matrix_editor_gui(QWidget *parent = 0);
    ~Matrix_editor_gui();

    Matrix *mat1;
    Matrix *mat2;
    Matrix *mat3;
    Matrix *mat;
    Matrix *mat_copy_paste;
    QTableWidget *tableWidget_mat;

protected:
    void showEvent(QShowEvent *event);

private slots:

    void on_spinBox_rows1_valueChanged(int arg1);
    void on_spinBox_cols1_valueChanged(int arg1);
    void on_spinBox_rows2_valueChanged(int arg1);
    void on_spinBox_cols2_valueChanged(int arg1);
    void updateSpinBoxes();

    void on_tableWidget_matrix1_customContextMenuRequested(const QPoint &pos);
    void on_tableWidget_matrix2_customContextMenuRequested(const QPoint &pos);
    void on_tableWidget_matrix3_customContextMenuRequested(const QPoint &pos);

    void matrixRandom();
    void matrixZeros();
    void matrixOnes();
    void matrixDiagonal();
    void matrixInverse();
    void matrixTranspose();
    void matrixDeterminant();
    void matrixCopy();
    void matrixPaste();
    void showMatrix();//for debug porpuse

    void ContextMenu(QPoint pos);

    void on_pushButton_calculate_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::Matrix_editor_gui *ui;

    QAction *matrixRandomAct;
    QAction *matrixZerosAct;
    QAction *matrixOnesAct;
    QAction *matrixDiagonalAct;
    QAction *matrixInverseAct;
    QAction *matrixTransposeAct;
    QAction *matrixDeterminantAct;
    QAction *matrixCopyAct;
    QAction *matrixPasteAct;
    QAction *matrixShowAct;//for debugging porpuse

    void createActions();
};

#endif // MATRIX_GUI_H
