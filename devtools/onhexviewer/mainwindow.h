#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QSplitter>
#include <QTreeView>
#include <QUndoStack>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QHexView;
class QHexDocument;
class DocumentModel;
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(
      QCommandLineParser* parser, const QCommandLineOption& file,
      QWidget* parent = nullptr);
  ~MainWindow();


private slots:

  void open();

  void exit();

  void about();

  void selectionChangedSlot(
      const QItemSelection& newSelection, const QItemSelection& oldSelection);

  void treeViewClicked(const QModelIndex& index);

  void onCustomContextMenu(const QPoint& point);


private:
  void openFile(QString fileName);
  void createDocumentModel(const QString& fileName);


  void markSelection(const QModelIndex& item);


private:
  Ui::MainWindow* ui;

  QSplitter* splitter = nullptr;

  QHexView* hexView                   = nullptr;
  QTreeView* treeView                 = nullptr;
  QItemSelectionModel* selectionModel = nullptr;
  QMenu* contextMenu                  = nullptr;

  DocumentModel* m_model = nullptr;
  QHexDocument* m_hexDoc = nullptr;

  QString m_currentFile;

  // command line settings
  QCommandLineParser* m_cli_parser = nullptr;
  QCommandLineOption m_cli_file;


  // stream positions
  QAction* undoAction      = nullptr;
  QAction* redoAction      = nullptr;
  QUndoStack* posUndoStack = nullptr;
};
#endif // MAINWINDOW_H
