#ifndef QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H
#define QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H

#include "qtbrainweaverdialog.h"
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui {
  class QtPrintConceptMapDialog;
}

namespace ribi {
namespace braw {

///View the current work, optimized for humans
///This dialog will not be visible for humans at all in release
///QtPrintConceptMapDialog is optimized for printers
class QtPrintConceptMapDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  explicit QtPrintConceptMapDialog(
    const File& file,
    QWidget *parent = 0
  );
  QtPrintConceptMapDialog(const QtPrintConceptMapDialog&) = delete;
  QtPrintConceptMapDialog& operator=(const QtPrintConceptMapDialog&) = delete;
  ~QtPrintConceptMapDialog() noexcept;
  void Print();
  void Print(const std::string& filename);

protected:
  void keyPressEvent(QKeyEvent * event);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();
private:
  Ui::QtPrintConceptMapDialog *ui;

  const File m_file;

  ConceptMap * const m_widget;

  std::vector<QWidget *> CollectWidgets() const;

  friend class qtbrainweaverprintconceptmapdialog_test;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H
