/*
 *Copyright@2013 上海青凤致远地球物理地质勘探科技有限公司IT部
 *All Right Reserved
 *
 *简    介：控制图幅菜单栏按钮显示三态效果，即根据鼠标焦点是否在按钮控件上
 *          分为三种显示状态，1.不在按钮上,显示正常色  2 .在按钮上,显示亮色
 *          3.鼠标按压按钮,显示高亮
 *作    者：刘 爽
 *完成日期：
 *版 本 号：
 *功 能 类：ButtonThreeStatus
 *
 */


#ifndef BUTTONTHREESTATUS_H
#define BUTTONTHREESTATUS_H

#include <QPushButton>
#include <QIcon>
#include <QMouseEvent>
#include <QEvent>
#include <QMessageBox>

class ButtonThreeStatus : public QPushButton
{
    Q_OBJECT

public:
    ButtonThreeStatus(QWidget *parent=0);
    ~ButtonThreeStatus();
    void SetButtonIncons(const QIcon &normal, const QIcon &focus, const QIcon &clicked);            //设置按钮控件图标

private:
    QIcon m_clickIcon;                                          //点击时图标
    QIcon m_focusIcon;                                          //聚焦时图标
    QIcon m_normalIcon;                                         //正常时图标

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);                             //重载“离开”事件，当鼠标离开按钮区域时显示NormalIcon
    void mousePressEvent(QMouseEvent *event);                   //重载鼠标“点击”事件，当鼠标点击按钮区域时显示ClickedIcon
    void mouseReleaseEvent(QMouseEvent *event);                 //重载鼠标“释放”事件，当鼠标释放按钮区域时显示FocusIcon

};

#endif // BUTTONTHREESTATUS_H
