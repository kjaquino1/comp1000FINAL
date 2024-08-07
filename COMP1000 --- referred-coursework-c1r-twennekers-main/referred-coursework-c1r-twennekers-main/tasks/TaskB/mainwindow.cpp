#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect signals to slots
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::on_openButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::on_saveButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->statsLabel->setText("Failed to open file.");
        return;
    }

    QTextStream in(&file);
    QString textContent = in.readAll();
    ui->resultsTextEdit->setPlainText(textContent);
    ui->statsLabel->clear();

    lines = textContent.split('\n');
    displayWordCounts(lines);

    int totalWords = 0, totalSyllables = 0;
    static QRegularExpression wordRegex("\\W+");
    foreach (const QString &line, lines) {
        QStringList words = line.split(wordRegex, Qt::SkipEmptyParts);
        totalWords += words.count();
        foreach (const QString &word, words) {
            totalSyllables += countSyllables(word);
        }
    }
    int totalSentences = countSentences(textContent);

    double fleschReadingEase = calculateFleschReadingEase(totalWords, totalSentences, totalSyllables);
    double fleschKincaidGradeLevel = calculateFleschKincaidGradeLevel(totalWords, totalSentences, totalSyllables);

    ui->statsLabel->setText(QString("Flesch Reading Ease: %1\nFlesch-Kincaid Grade Level: %2")
                                .arg(fleschReadingEase).arg(fleschKincaidGradeLevel));
}

void MainWindow::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text();
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    int matchCount = 0;
    QString results = performSearch(searchTerm, matchCount);

    ui->resultsTextEdit->setPlainText(results);

    if (matchCount > 0) {
        ui->statsLabel->setText(QString("The term '%1' was found %2 times.").arg(searchTerm).arg(matchCount));
    } else {
        ui->statsLabel->setText(QString("No matches found for '%1'.").arg(searchTerm));
    }
}

QString MainWindow::performSearch(const QString& searchTerm, int& matchCount)
{
    QString results;
    matchCount = 0;
    for (int i = 0; i < lines.size(); ++i) {
        if (lines[i].contains(searchTerm, Qt::CaseInsensitive)) {
            results += QString("Match found at line %1: %2\n").arg(i + 1).arg(lines[i]);
            matchCount++;
        }
    }
    return results;
}

void MainWindow::displayWordCounts(const QStringList &lines)
{
    QMap<QString, int> wordCounts;
    static QRegularExpression regex("\\W+");
    for (const QString &line : lines) {
        QStringList words = line.split(regex, Qt::SkipEmptyParts);
        for (const QString &word : words) {
            QString lowerWord = word.toLower();
            wordCounts[lowerWord]++;
        }
    }

    QString wordCountResults;
    QMapIterator<QString, int> i(wordCounts);
    while (i.hasNext()) {
        i.next();
        wordCountResults += i.key() + ": " + QString::number(i.value()) + "\n";
    }

    ui->resultsTextEdit->append(wordCountResults);
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Results", "", "CSV Files (*.csv)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        ui->statsLabel->setText("Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "Filename,Search Term,Frequency (%)\n";

    QString searchTerm = ui->searchLineEdit->text();
    int totalWords = 0, matchCount = 0;
    static QRegularExpression wordRegex("\\W+");
    foreach (const QString &line, lines) {
        QStringList words = line.split(wordRegex, Qt::SkipEmptyParts);
        totalWords += words.count();
        foreach (const QString &word, words) {
            if (word.contains(searchTerm, Qt::CaseInsensitive)) {
                matchCount++;
            }
        }
    }
    double frequency = (totalWords > 0) ? (static_cast<double>(matchCount) / totalWords * 100) : 0.0;
    out << QFileInfo(fileName).fileName() << "," << searchTerm << "," << frequency << "%" << "\n";

    ui->statsLabel->setText("Results saved to " + fileName);
}

int MainWindow::countSyllables(const QString &word)
{
    int count = 0;
    bool lastWasVowel = false;
    QString vowels = "aeiouy";

    for (int i = 0; i < word.length(); ++i) {
        if (vowels.contains(word[i], Qt::CaseInsensitive)) {
            if (!lastWasVowel) {
                count++;
                lastWasVowel = true;
            }
        } else {
            lastWasVowel = false;
        }
    }

    if (word.endsWith('e', Qt::CaseInsensitive) && count > 1) {
        count--;
    }

    return count > 0 ? count : 1;
}

int MainWindow::countSentences(const QString &text)
{
    int count = 0;
    static QRegularExpression sentenceEnd("[.!?]");
    QRegularExpressionMatchIterator i = sentenceEnd.globalMatch(text);
    while (i.hasNext()) {
        i.next();
        count++;
    }
    return count;
}

double MainWindow::calculateFleschReadingEase(int totalWords, int totalSentences, int totalSyllables)
{
    double ASL = static_cast<double>(totalWords) / totalSentences;
    double ASW = static_cast<double>(totalSyllables) / totalWords;
    return 206.835 - (1.015 * ASL) - (84.6 * ASW);
}

double MainWindow::calculateFleschKincaidGradeLevel(int totalWords, int totalSentences, int totalSyllables)
{
    double ASL = static_cast<double>(totalWords) / totalSentences;
    double ASW = static_cast<double>(totalSyllables) / totalWords;
    return (0.39 * ASL) + (11.8 * ASW) - 15.59;
}
