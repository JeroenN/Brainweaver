#include "qtbrainweaveroverviewwidget_test.h"
#include "qtbrainweaveroverviewwidget.h"

void ribi::braw::qtbrainweaveroverviewwidget_test::default_construction()
{
  ribi::braw::QtOverviewWidget d;
  d.show();
  QTest::keyClick(&d, Qt::Key_X);
  QTest::keyClick(&d, Qt::Key_Escape);
}

