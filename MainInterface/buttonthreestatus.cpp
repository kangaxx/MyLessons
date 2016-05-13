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


#include "buttonthreestatus.h"


ButtonThreeStatus::ButtonThreeStatus(QWidget *parent):QPushButton(parent)
{
    setDown(false);
    setFocusPolicy(Qt::NoFocus);

}

ButtonThreeStatus::~ButtonThreeStatus()
{

}


/********************************************
    Function:void enterEvent(QEvent *event)
    Description:重载“进入”事件，当鼠标进入按钮区域时显示FocusIcon
    Input:
    Output:
    Return:
    Calls:
    Called By:
********************************************/
void ButtonThreeStatus::enterEvent(QEvent *event)
{
    if(isEnabled() && !m_focusIcon.isNull()){
        setIcon(m_focusIcon);
    }else{
        QMessageBox::warning(this, "Waring", "FocusIcon may be null");
    }
}


/********************************************
    Function:
    Description:重载“离开”事件，当鼠标离开按钮区域时显示NormalIcon
    Input:
    Output:
    Return:
    Calls:
    Called By:
********************************************/
void ButtonThreeStatus::leaveEvent(QEvent *event)
{

    if(isEnabled() && !m_normalIcon.isNull()){
        setIcon(m_normalIcon);
    }else{
        QMessageBox::warning(this, "Waring", "NormalIcon may be null");
    }
}


/********************************************
    Function:void mousePressEvent(QMouseEvent *event)
    Description:重载鼠标“点击”事件，当鼠标点击按钮区域时显示ClickedIcon
    Input:
    Output:
    Return:
    Calls:
    Called By:
********************************************/
void ButtonThreeStatus::mousePressEvent(QMouseEvent *event)
{
    if(isEnabled() && !m_clickIcon.isNull()){
        setIcon(m_clickIcon);
    }else{
        QMessageBox::warning(this, "Waring", "ClickedIcon may be null");
    }

    QPushButton::mousePressEvent(event);
}


/********************************************
    Function:void mouseReleaseEvent(QMouseEvent *event)
    Description: 重载鼠标“释放”事件，当鼠标释放按钮区域时显示FocusIcon
    Input:
    Output:
    Return:
    Calls:
    Called By:
********************************************/
void ButtonThreeStatus::mouseReleaseEvent(QMouseEvent *event)
{
    if(isEnabled() && !m_focusIcon.isNull()){
        setIcon(m_clickIcon);
    }else{
        QMessageBox::warning(this, "Waring", "FocusIcon may be null");
    }

    QPushButton::mouseReleaseEvent(event);
}


/********************************************
    Function: void SetButtonIncons(const QIcon &normal, const QIcon &focus, const QIcon &clicked)
    Description: 设置按钮控件图标
    Input:
    Output:
    Return:
    Calls: setIcon(m_normalIcon)
    Called By:
********************************************/
void ButtonThreeStatus::SetButtonIncons(const QIcon &normal, const QIcon &focus, const QIcon &clicked)
{
    m_normalIcon = normal;
    m_focusIcon = focus;
    m_clickIcon = clicked;

    setIcon(m_normalIcon);  //默认为NormalIcon
}

