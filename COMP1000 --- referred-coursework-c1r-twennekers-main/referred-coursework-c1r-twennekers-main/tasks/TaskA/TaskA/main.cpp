#include "TaskA.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

void saveResultsToCSV(const string& fileName, const string& searchTerm, double frequency);

int main(int argc, char* argv[])
{
    cout << "Number of arguments: " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << "Argument " << i << ": " << argv[i] << endl;
    }

    if (argc == 2 || argc == 3 || argc == 4 || argc == 5) {
        cout << "TaskA (c)2024" << endl;

        string fileName(argv[1]);
        string searchString = "";
        bool isRegex = false;
        int topN = 0;

        if (argc >= 3) {
            searchString = argv[2];
        }

        if (argc == 4) {
            if (string(argv[3]) == "-regex") {
                isRegex = true;
            }
            else {
                topN = stoi(argv[3]);
            }
        }
        else if (argc == 5) {
            if (string(argv[3]) == "-regex") {
                isRegex = true;
                topN = stoi(argv[4]);
            }
            else {
                cerr << "Usage: TaskA <filename> <search term> [-regex] [topN]" << endl;
                return EXIT_FAILURE;
            }
        }

        cout << "TaskA " << fileName << " " << searchString << (isRegex ? " -regex" : "") << endl;

        TextFile textFile;
        if (!textFile.load(fileName)) {
            return EXIT_FAILURE;
        }
        vector<string> lines = textFile.getLines();

        if (searchString.empty()) {
            textFile.displayContent();
            return EXIT_SUCCESS;
        }

        Search search(searchString, isRegex);
        search.execute(lines);
        search.displayResults();

        cout << endl;

        // Display the number of search hits
        int matchCount = search.getMatchCount();
        cout << "Number of search hits: " << matchCount << endl;

        Statistics stats(lines);

        // Calculate and display the average word length
        double averageWordLength = stats.calculateAverageWordLength();
        cout << "Average Word Length: " << averageWordLength << endl;

        // Calculate and display the total number of words
        int totalWords = 0;
        for (const auto& entry : stats.getWordCounts()) {
            totalWords += entry.second;
        }
        cout << "Total Words: " << totalWords << endl;

        // Calculate and display the frequency of the search hits
        double frequency = (totalWords > 0) ? (static_cast<double>(matchCount) / totalWords * 100) : 0.0;
        cout << "Search hit frequency: " << frequency << "%" << endl;

        cout << endl;

        // Display word counts
        stats.displayWordCounts();

        cout << endl;

        // Display top N words if specified
        if (topN > 0) {
            vector<pair<string, int>> topWords = stats.getTopNWords(topN);
            cout << "Top " << topN << " Words:" << endl;
            for (const auto& entry : topWords) {
                cout << entry.first << ": " << entry.second << endl;
            }
        }

        cout << endl;

        // Calculate total sentences and syllables
        int totalSentences = Readability::countSentences(lines);
        int totalSyllables = 0;
        for (const auto& entry : stats.getWordCounts()) {
            totalSyllables += Readability::countSyllables(entry.first) * entry.second;
        }

        cout << "Total Sentences: " << totalSentences << endl;
        cout << "Total Syllables: " << totalSyllables << endl;

        cout << endl;

        // Calculate and display readability scores
        double fleschReadingEase = Readability::calculateFleschReadingEase(totalWords, totalSentences, totalSyllables);
        double fleschKincaidGradeLevel = Readability::calculateFleschKincaidGradeLevel(totalWords, totalSentences, totalSyllables);

        cout << "Flesch Reading Ease: " << fleschReadingEase << endl;
        cout << "Flesch-Kincaid Grade Level: " << fleschKincaidGradeLevel << endl;


        // Save results to CSV
        saveResultsToCSV(fileName, searchString, frequency);

        return EXIT_SUCCESS;
    }
    cerr << "Usage: TaskA <filename> <search term> [-regex] [topN]" << endl;
    return EXIT_FAILURE;
}
