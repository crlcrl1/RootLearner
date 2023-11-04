/**
 * @date 2023.10.24
 * @brief The Root class
 * @author crl
 */


#include <QString>
#include <QVector>
#include "word.h"

#ifndef ROOT_H
#define ROOT_H


class Root
{
private:
    QString root;
    QString meaning;
    QVector<Word*> words;
    int currentWord;
public:
    Root();
    Root(QString root);
    ~Root();
    QString getRoot();
    void setRoot(QString root);
    QString getMeaning();
    void setMeaning(QString meaning);
    void addWord(Word* word);
    void removeWord(int index);
    void removeWord(QString word);
    Word* nextWord();
    Word* prevWord();
    QVector<Word*> getAllWords();
};

#endif // ROOT_H
