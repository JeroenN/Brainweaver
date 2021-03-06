#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtbrainweaveroverviewdialog.h"

#include <cassert>
#include <QKeyEvent>
#include <QVBoxLayout>

#include "qtbrainweaveroverviewwidget.h"

#pragma GCC diagnostic pop

ribi::braw::QtOverviewDialog::QtOverviewDialog(QWidget* parent)
  : QDialog(parent)
{
  
  QLayout * const layout = new QVBoxLayout(this);
  this->setLayout(layout);
  QtOverviewWidget * const widget = new QtOverviewWidget;
  layout->addWidget(widget);
}

void ribi::braw::QtOverviewDialog::keyPressEvent(QKeyEvent* e)
{
  assert(e);
  if (e->key() == Qt::Key_Escape)
  {
    close();
    //emit remove_me(this);
    return;
  }
  QDialog::keyPressEvent(e);
}
