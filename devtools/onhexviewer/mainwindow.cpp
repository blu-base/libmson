#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QSplitter>
#include <qhexview.h>

#include "documentitem.h"
#include "documentmodel.h"
#include "documentmodelfactory.h"



MainWindow::MainWindow(QCommandLineParser* parser,
                       const QCommandLineOption &file,
                       QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      splitter(new QSplitter(this)), hexView(new QHexView(splitter)),
      treeView(new QTreeView(splitter)),
      selectionModel(nullptr),
      m_model(new DocumentModel(this)),
      m_hexDoc(nullptr),
      m_cli_parser(parser),
      m_cli_file(file)

{



  ui->setupUi(this);

  ui->centralwidget->layout()->addWidget(splitter);
  splitter->addWidget(treeView);
  splitter->addWidget(hexView);


  treeView->setFont(QFont("Monospace"));


   hexView->setReadOnly(true);

  connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);
  connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
  connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);


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
  const QModelIndex index = treeView->selectionModel()->currentIndex();

  QHexMetadata* hexmetadata = m_hexDoc->metadata();
  hexmetadata->clear();


  for (auto item : newSelection.indexes()) {

    quint64 begin =
        item.sibling(item.row(), 3).data().toString().toUInt(nullptr, 16);
    quint64 offset = item.sibling(item.row(), 4).data().toString().toUInt(nullptr,16);

    hexmetadata->metadata(begin, begin+offset, Qt::white, Qt::darkBlue, QString());

  }

  hexView->document()->cursor()->moveTo(newSelection.indexes().first().sibling(newSelection.indexes().first().row(),3).data().toString().toUInt(nullptr,16));

}

void MainWindow::createDocumentModel(const QString& fileName)
{
  QFileInfo fileInfo(fileName);

  if (!fileInfo.exists()) {
    return;
  }

    DocumentModelFactory(fileName).createModel(m_model);
}



void MainWindow::markSelection(const QModelIndex& item)
{

}

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
  m_model = new DocumentModel(this);
  createDocumentModel(fileName);

  treeView->setModel(m_model);


  if (selectionModel != nullptr) {
    disconnect(
        selectionModel, &QItemSelectionModel::selectionChanged, this,
        &MainWindow::selectionChangedSlot);
  }

  selectionModel = treeView->selectionModel();
  connect(
      selectionModel, &QItemSelectionModel::selectionChanged, this,
      &MainWindow::selectionChangedSlot);
}
