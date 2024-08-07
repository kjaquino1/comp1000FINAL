#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();
    void on_searchButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    QStringList lines; // Member variable to store lines of the file

    QString performSearch(const QString& searchTerm, int& matchCount);
    void displayWordCounts(const QStringList &lines);
    int countSyllables(const QString &word);
    int countSentences(const QString &text);
    double calculateFleschReadingEase(int totalWords, int totalSentences, int totalSyllables);
    double calculateFleschKincaidGradeLevel(int totalWords, int totalSentences, int totalSyllables);
};

#endif // MAINWINDOW_H
