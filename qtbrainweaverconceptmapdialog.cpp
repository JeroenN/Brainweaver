#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweaverconceptmapdialog.h"

#include <cassert>
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QTimer>

#include "add_bundled_edge_between_vertices.h"
#include "add_bundled_vertex.h"
#include "brainweavercluster.h"
#include "brainweaverfile.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedge.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmap.h"
#include "qtconceptmap.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtscopeddisable.h"

#include "ui_qtbrainweaverconceptmapdialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtConceptMapDialog::QtConceptMapDialog(
  const File& file,
  QWidget *parent)
  : QtDialog(parent),
    ui(new Ui::QtConceptMapDialog),
    m_back_to_menu(false),
    m_file(file),
    m_widget{new ribi::cmap::QtConceptMap(this)}
{
  if (!m_file.GetCluster().Empty() && boost::num_vertices(m_file.GetConceptMap()) == 0)
  {
    m_file.SetConceptMap(
      CreateFromCluster(m_file.GetQuestion(), m_file.GetCluster())
    );
  }
  if (boost::num_vertices(m_file.GetConceptMap()) == 0)
  {
    //Add the first central node
    using ribi::cmap::CenterNodeFactory;
    using ribi::cmap::Concept;
    const auto cn = CenterNodeFactory().Create(Concept(m_file.GetQuestion()));
    add_bundled_vertex(cn, m_file.GetConceptMap());
    assert(boost::num_vertices(m_file.GetConceptMap()) > 0);
  }
  assert(boost::num_vertices(m_file.GetConceptMap()) > 0);
  assert(m_widget);

  ui->setupUi(this);
  m_widget->SetConceptMap(m_file.GetConceptMap());
  m_widget->SetMode(ribi::cmap::Mode::edit);

  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  assert(this->layout());
  this->layout()->addWidget(m_widget);

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }

  //Start autosave
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(OnAutosave()));
    timer->setInterval(10000);
    timer->start();
  }
}

ribi::braw::QtConceptMapDialog::~QtConceptMapDialog() noexcept
{
  this->m_widget->StopTimer();
  delete ui;
}

ribi::cmap::ConceptMap ribi::braw::CreateFromCluster(
  const std::string& question,
  const Cluster& cluster)
{
  ribi::cmap::ConceptMap p;

  //Add center node
  const auto vd_center = add_bundled_vertex(
    ribi::cmap::Node{
      ribi::cmap::Concept(question),
      ribi::cmap::NodeType::center,
      0.0,
      0.0
    },
    p
  );


  const std::vector<ribi::cmap::Concept> v = cluster.Get();
  const int n = boost::numeric_cast<int>(v.size());
  const double delta_angle{2.0 * boost::math::constants::pi<double>() / static_cast<double>(n)};
  for (int i=0; i!=n; ++i)
  {
    const double angle{(static_cast<double>(i) * delta_angle) + 0.00001}; //Add noise
    const int x =  std::sin(angle) * 200.0;
    const int y = -std::cos(angle) * 200.0;
    ribi::cmap::Node node(v[i], ribi::cmap::NodeType::normal, x, y);
    const auto vd_here = add_bundled_vertex(node, p);
    add_bundled_edge_between_vertices(
      ribi::cmap::Edge(ribi::cmap::Node()),
      vd_center,
      vd_here,
      p
    );
  }
  assert(v.size() + 1 == boost::num_vertices(p)
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
  return p;
}

const ribi::cmap::QtConceptMap * ribi::braw::QtConceptMapDialog::GetQtConceptMap() const
{
  assert(m_widget);
  return m_widget;
}

ribi::cmap::QtConceptMap * ribi::braw::QtConceptMapDialog::GetQtConceptMap()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<cmap::QtConceptMap*>(
    const_cast<const QtConceptMapDialog*>(this)->GetQtConceptMap()); //?Why Dialog

}

bool ribi::braw::QtConceptMapDialog::GoBackToMenu() const noexcept
{
  return m_back_to_menu;
}

void ribi::braw::QtConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape)
  {
    emit remove_me(this);
    return;
  }
  if (e->key() == Qt::Key_F4 && (e->modifiers() & Qt::AltModifier))
  {
    emit remove_me(this);
    return;
  }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    on_button_save_clicked(); return;
  }
  m_widget->keyPressEvent(e);
  if (!e->isAccepted())
  {
    QDialog::keyPressEvent(e);
  }
}

void ribi::braw::QtConceptMapDialog::on_button_print_clicked()
{
  qDebug() << __func__ << (__LINE__);
  UpdateFileWithConceptMapFromWidget();
  qDebug() << __func__ << (__LINE__);
  this->m_widget->setEnabled(false); //Prevents #101
  m_widget->StopTimer();
  QtPrintConceptMapDialog * const d = new QtPrintConceptMapDialog(m_file);
  emit add_me(d);

  //this->m_widget->setEnabled(true);
}

void ribi::braw::QtConceptMapDialog::OnAutosave()
{
  if (!isVisible()) return;
  try
  {
    UpdateFileWithConceptMapFromWidget();
    m_file.AutoSave();
    qDebug() << __func__ << ": successfull autosave";
  }
  catch (std::exception& e)
  {
    qCritical() << __func__ << ": exception thrown with description " << e.what();
  }
}

void ribi::braw::QtConceptMapDialog::on_button_save_clicked()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  UpdateFileWithConceptMapFromWidget();
  Save(filename);
  //this->m_back_to_menu = true; //2013-04-19 Request by client
  //emit remove_me(this); //2013-04-19 Request by client
}

void ribi::braw::QtConceptMapDialog::showEvent(QShowEvent *)
{
  m_widget->setFocus();
}

void ribi::braw::QtConceptMapDialog::UpdateFileWithConceptMapFromWidget()
{
  CheckInvariants(*GetQtConceptMap());

  m_file.SetConceptMap(GetQtConceptMap()->ToConceptMap());
  assert(m_file.GetConceptMap() == GetQtConceptMap()->ToConceptMap());

  CheckInvariants(*GetQtConceptMap());
}

void ribi::braw::QtConceptMapDialog::Save(const std::string& filename) const
{
  if (m_file.GetConceptMap() != GetQtConceptMap()->ToConceptMap())
  {
    std::clog << __func__ << ": warning: you should have called "
      << "'UpdateFileWithConceptMapFromWidget' before saving, doing so now\n"
    ;
    const_cast<QtConceptMapDialog*>(this)->UpdateFileWithConceptMapFromWidget();
  }
  m_file.Save(filename);
}
