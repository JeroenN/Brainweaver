#ifndef QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
#define QTBRAINWEAVERRATECONCEPTMAPDIALOG_H

#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"
#include "qtbrainweaverdialog.h"

namespace Ui { class QtRateConceptMapDialog; }

namespace ribi {
namespace braw {

struct qtbrainweaverrateconceptmapdialog_test;

class QtRateConceptMapDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  explicit QtRateConceptMapDialog(
    const File& file,
    QWidget* parent = 0);
  QtRateConceptMapDialog(const QtRateConceptMapDialog&) = delete;
  QtRateConceptMapDialog& operator=(const QtRateConceptMapDialog&) = delete;
  ~QtRateConceptMapDialog() noexcept;

  const File& GetFile() const noexcept;
  cmap::QtConceptMap * GetWidget();

  ///Respond to key press
  void keyPressEvent(QKeyEvent *);

  void Save();
  void Save(const std::string& filename);

private slots:
  void changeEvent(QEvent *) override;
  void on_button_next_clicked();
  void on_button_save_clicked();
  void showEvent(QShowEvent *) override;

private:
  Ui::QtRateConceptMapDialog *ui;
  File m_file;
  ConceptMap * const m_concept_map;

  friend class qtbrainweaverrateconceptmapdialog_test;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
