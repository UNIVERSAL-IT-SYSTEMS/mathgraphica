#include "graph2d_editor_gui.h"
#include "ui_graph2d_editor_gui.h"
#include "graph2d_addnew_gui.h"

#include <QColorDialog>
#include <QMessageBox>

Graph2D_Editor_gui::Graph2D_Editor_gui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph2D_Editor_gui)
{
    ui->setupUi(this);
    ui->checkBox_automaticGraph3DRotation->hide();

    m_graph2DEditorListPtr = NULL;
    ui->tableWidget_graph2D_list->setColumnCount(1);


    // to used in the derived class, to access the widgets
    tableWidget_graph   = ui->tableWidget_graph2D_list;
    checkBox3DRotation  = ui->checkBox_automaticGraph3DRotation;

}

Graph2D_Editor_gui::~Graph2D_Editor_gui()
{
    delete ui;
}

void Graph2D_Editor_gui::setTimeDelta(const QString t_delta_)
{
    ui->lineEdit_t_delta->setText(t_delta_);
}

QString Graph2D_Editor_gui::getTimeDelta()
{
    return ui->lineEdit_t_delta->text();
}


void Graph2D_Editor_gui::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    if (m_graph2DEditorListPtr == NULL)
        return;


    int size = m_graph2DEditorListPtr->size();
    ui->tableWidget_graph2D_list->setColumnCount(1);
    ui->tableWidget_graph2D_list->setRowCount(size);


    for (int i = 0; i < size; i++)
    {
        QString graphExpressionAux;

        if (m_graph2DEditorListPtr->at(i).isParametricGraph())
        {
            graphExpressionAux = m_graph2DEditorListPtr->at(i).getGraph2DExpression_f1() +
                    "; " + m_graph2DEditorListPtr->at(i).getGraph2DExpression_f2();
        }
        else
        {
            graphExpressionAux = m_graph2DEditorListPtr->at(i).getGraph2DExpression();
        }

        if (ui->tableWidget_graph2D_list->item(i,0) == 0)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem( graphExpressionAux );
            ui->tableWidget_graph2D_list->setItem(i, 0, newItem);

        }
        else
        {
            ui->tableWidget_graph2D_list->item(i,0)->setText( graphExpressionAux );
        }

        ui->tableWidget_graph2D_list->item(i,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }

}


void Graph2D_Editor_gui::on_pushButton_ok_clicked()
{
    qDebug()<<"fecha-me";
    close();
}

void Graph2D_Editor_gui::on_pushButton_cancel_clicked()
{
    close();
}

void Graph2D_Editor_gui::on_pushButton_add_clicked()
{
    if (m_graph2DEditorListPtr == NULL)
        return;


    Graph2D_AddNew_gui newGraph2D_gui;
    newGraph2D_gui.existentGraphs_count = m_graph2DEditorListPtr->size();

    newGraph2D_gui.exec();
    if ( newGraph2D_gui.returnValue == 1 )
    {
        newGraph2D_gui.m_graph2D.setupGraph();
        m_graph2DEditorListPtr->append(newGraph2D_gui.m_graph2D);
        addNewGraph(newGraph2D_gui.m_graph2D.getGraph2DExpression());
        close();
    }    

}

void Graph2D_Editor_gui::addNewGraph(const QString &str)
{
    int size = ui->tableWidget_graph2D_list->rowCount();
    ui->tableWidget_graph2D_list->setRowCount(size+1);

    if (ui->tableWidget_graph2D_list->item(size,0) == 0)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(str);
        newItem->setText(str);
        ui->tableWidget_graph2D_list->setItem(size,0,newItem);
    }
    else
    {
        ui->tableWidget_graph2D_list->item(size,0)->setText(str);
    }

    ui->tableWidget_graph2D_list->item(size,0)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}


void Graph2D_Editor_gui::on_pushButton_edit_clicked()
{

    Graph2D_AddNew_gui graph2D_Edit_gui;
    int index = ui->tableWidget_graph2D_list->currentRow();

    if (index < 0 || index >= m_graph2DEditorListPtr->size())
        return;


    graph2D_Edit_gui.m_graph2D = m_graph2DEditorListPtr->at(index);

    graph2D_Edit_gui.exec();
    if ( graph2D_Edit_gui.returnValue == 1 )
    {
        graph2D_Edit_gui.m_graph2D.setupGraph();

        m_graph2DEditorListPtr->removeAt(index);
        m_graph2DEditorListPtr->insert(index,graph2D_Edit_gui.m_graph2D);
        //m_graph2DEditorListPtr->indexOf( graph2D_Edit_gui.m_graph2D);
       // addNewGraph(graph2D_Edit_gui.m_graph2D.getGraph2DExpression());
        ui->tableWidget_graph2D_list->item(index,0)->setText(graph2D_Edit_gui.m_graph2D.getGraph2DExpression());
        close();
    }

}


void Graph2D_Editor_gui::on_pushButton_backGndColor_clicked()
{
    QColorDialog dlg;
    m_backGroundColor = dlg.getColor();
    close();
}

void Graph2D_Editor_gui::on_pushButton_delete_clicked()
{
    int index = ui->tableWidget_graph2D_list->currentRow();

    //if (index < 0 || index >= m_graph2DEditorListPtr->size())
      //  return;

    if (index >= 0 && index < m_graph2DEditorListPtr->size())
    {
        QString str = "Do you want  to delete the selected 2D graph ?\n" + ui->tableWidget_graph2D_list->item(index, 0)->text();

        if ( QMessageBox::warning(this,tr("2D Graphs"), str, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel)
             == QMessageBox::Yes)
        {
            m_graph2DEditorListPtr->removeAt(index);
            ui->tableWidget_graph2D_list->removeRow(index);
            close();
        }
    }

}

void Graph2D_Editor_gui::on_tableWidget_graph2D_list_cellDoubleClicked(int row, int column)
{
    on_pushButton_edit_clicked();
}
