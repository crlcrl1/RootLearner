/**
 * @date 2023.10.24
 * @brief The Word class
 * @author crl
 */

#include <QString>

#ifndef WORD_H
#define WORD_H

class Root;

class Word
{
private:
    
    QString word;
    Root* root;
    QString meaning;
public:
    Word();
    Word(QString word, Root* root, QString meaning);
    ~Word();
    QString getWord();
    Root* getRoot();
    QString getMeaning();
    void setWord(QString word);
    void setRoot(Root* root);
    void setMeaning(QString meaning);
};

#endif // WORD_H
