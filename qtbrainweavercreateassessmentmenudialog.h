//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#ifndef QTBRAINWEAVERCREATEASSESSMENTMENUDIALOG_H
#define QTBRAINWEAVERCREATEASSESSMENTMENUDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "qthideandshowdialog.h"
#include "brainweaverfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtCreateAssessmentMenuDialog; }

namespace ribi {
namespace pvdb {

class QtCreateAssessmentMenuDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
public:
  explicit QtCreateAssessmentMenuDialog(QWidget* parent = 0);
  QtCreateAssessmentMenuDialog(const QtCreateAssessmentMenuDialog&) = delete;
  QtCreateAssessmentMenuDialog& operator=(const QtCreateAssessmentMenuDialog&) = delete;
  ~QtCreateAssessmentMenuDialog() noexcept;

  ///Must the parent go back to the menu?
  bool GoBackToMenu() const noexcept { return m_back_to_menu; }

  protected:
  void keyPressEvent(QKeyEvent *);

private slots:

  void on_button_create_assessment_complete_clicked();

signals:

private:
  Ui::QtCreateAssessmentMenuDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;

  ///The focal concept map question
  std::string m_question;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTMENUDIALOG_H
