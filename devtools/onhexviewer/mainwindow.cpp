#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSplitter>
#include <QString>
#include <qhexview.h>

#include "documentitem.h"
#include "documentmodel.h"
#include "documentmodelfactory.h"
#include "selectioncommand.h"


MainWindow::MainWindow(
    QCommandLineParser* parser, const QCommandLineOption& file, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      splitter(new QSplitter(this)), hexView(new QHexView(splitter)),
      treeView(new QTreeView(splitter)), selectionModel(nullptr),
      contextMenu(new QMenu(treeView)), m_model(new DocumentModel(this)),
      m_hexDoc(nullptr), m_cli_parser(parser), m_cli_file(file)

{


  ui->setupUi(this);

  ui->centralwidget->layout()->addWidget(splitter);
  splitter->addWidget(treeView);
  splitter->addWidget(hexView);


  treeView->setFont(QFont("Monospace"));
  treeView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(
      treeView, &QTreeView::customContextMenuRequested, this,
      &MainWindow::onCustomContextMenu);

  connect(treeView, &QTreeView::clicked, this, &MainWindow::treeViewClicked);


  hexView->setReadOnly(true);
//  hexView->setMaximumWidth(
//      hexView->renderer()->documentWidth() +
//      qApp->style()->pixelMetric(QStyle::PM_SliderThickness) + 10);

  connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);
  connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
  connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);


  posUndoStack = new QUndoStack(this);
  undoAction   = posUndoStack->createUndoAction(this, "&Undo");
  undoAction->setShortcuts(QKeySequence::Undo);
  undoAction->setIcon(QIcon::fromTheme("edit-undo"));

  redoAction = posUndoStack->createRedoAction(this, "&Redo");
  redoAction->setShortcuts(QKeySequence::Redo);
  redoAction->setIcon(QIcon::fromTheme("edit-redo"));

  ui->toolBarStp->addAction(undoAction);
  ui->toolBarStp->addAction(redoAction);


  if (m_cli_parser->isSet(m_cli_file)) {

    openFile(m_cli_parser->value(m_cli_file));
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::open()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

  openFile(fileName);
}

void MainWindow::exit() { QApplication::closeAllWindows(); }

void MainWindow::about()
{
  QMessageBox::about(
      this, tr("About Hexviwer"),
      tr("This tool assists in understanding the MS-ONESTORE, and MS-ONE "
         "specificatins"));
}

void MainWindow::selectionChangedSlot(
    const QItemSelection& newSelection, const QItemSelection& oldSelection)
{
  // get the text of the selected item
  const QModelIndex index = treeView->currentIndex();

  posUndoStack->push(new SelectionCommand(treeView, hexView, index));
}

void MainWindow::treeViewClicked(const QModelIndex& index)
{
  posUndoStack->push(new SelectionCommand(treeView, hexView, index));
}

void MainWindow::onCustomContextMenu(const QPoint& point)
{
  QModelIndex index = treeView->indexAt(point).siblingAtColumn(0);
  if (index.isValid()) {

    QString type =
        m_model->data(index.siblingAtColumn(1), Qt::DisplayRole).toString();

    if (type == QStringLiteral("FileNodeChunkReference") ||
        type == QStringLiteral("FileChunkReference64") ||
        type == QStringLiteral("FileChunkReference64x32") ||
        type == QStringLiteral("FileChunkReference32")) {

      QString value =
          m_model->data(index.siblingAtColumn(2), Qt::DisplayRole).toString();

      if (value != "fcrNil" && value != "fcrZero") {


        const auto stpChild = m_model->index(0, 2, index);
        bool valid;

        QString stp = stpChild.data().toString().mid(2);

        int rowCount = treeView->model()->rowCount(treeView->rootIndex());
        for (int row = 0; row < rowCount; ++row) {

          auto current = m_model->index(row, 3, treeView->rootIndex());

          if (current.data() == stp) {
            posUndoStack->push(new SelectionCommand(
                treeView, hexView, current.siblingAtColumn(0)));

            break;
          }
        }




        //    contextMenu->exec(treeView->viewport()->mapToGlobal(point));
      }
    }
  }
}

DocumentModel* MainWindow::createDocumentModel(const QString& fileName)
{
  auto* model = new DocumentModel(this);
  QFileInfo fileInfo(fileName);

  if (!fileInfo.exists()) {
    return model;
  }

  DocumentModelFactory(fileName).createModel(model);

  return model;
}


void MainWindow::markSelection(const QModelIndex& item) {}

void MainWindow::openFile(QString fileName)
{
  QFileInfo fileInfo(fileName);

  if (!fileInfo.exists()) {
    return;
  }

  QFile file(fileName);
  m_currentFile = fileName;

  m_hexDoc = QHexDocument::fromLargeFile(m_currentFile);

  hexView->setDocument(m_hexDoc);


  delete m_model;
  m_model = createDocumentModel(fileName);

  treeView->setModel(m_model);

  selectionModel = treeView->selectionModel();
}
