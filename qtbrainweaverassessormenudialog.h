#ifndef QTBRAINWEAVERASSESSORMENUDIALOG_H
#define QTBRAINWEAVERASSESSORMENUDIALOG_H

#include "qtbrainweaverdialog.h"
#include "brainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui { class QtAssessorMenuDialog; }

namespace ribi {
namespace braw {

class QtAssessorMenuDialog : public QtDialog
{
    Q_OBJECT //!OCLINT
    
public:
  explicit QtAssessorMenuDialog(QWidget* parent = 0);
  QtAssessorMenuDialog(const QtAssessorMenuDialog&) = delete;
  QtAssessorMenuDialog& operator=(const QtAssessorMenuDialog&) = delete;
  ~QtAssessorMenuDialog() noexcept;

public slots:
  void Assess(const std::string& filename);
  void keyPressEvent(QKeyEvent *);
  void on_button_about_clicked();
  void on_button_assess_result_clicked();
  void on_button_create_assessment_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtAssessorMenuDialog *ui;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERASSESSORMENUDIALOG_H
