#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include <QTreeView>
#include <QSplitter>
#include <QCommandLineParser>
#include <QCommandLineOption>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QHexView;
class QHexDocument;
class DocumentModel;
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QCommandLineParser* parser,
             const QCommandLineOption &file,
             QWidget *parent = nullptr);
  ~MainWindow();




private slots:

  void open();

  void exit();

  void about();

  void selectionChangedSlot(
      const QItemSelection& newSelection, const QItemSelection& oldSelection);


private:
  void openFile(QString fileName);
  void createDocumentModel(const QString& fileName);


  void markSelection(const QModelIndex& item);




private:
  Ui::MainWindow* ui;

  QSplitter* splitter;

  QHexView* hexView;
  QTreeView* treeView;
  QItemSelectionModel* selectionModel;

  DocumentModel* m_model;
  QHexDocument* m_hexDoc;

  QString m_currentFile;

  // command line settings
  QCommandLineParser* m_cli_parser;
  QCommandLineOption m_cli_file;

};
#endif // MAINWINDOW_H
