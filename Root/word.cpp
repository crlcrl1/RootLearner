#include "word.h"

Word::Word()
{
    
}

void Word::setMeaning(QString meaning)
{
    this->meaning = meaning;
}

void Word::setRoot(Root* root)
{
    this->root = root;
}

void Word::setWord(QString word)
{
    this->word = word;
}

QString Word::getMeaning()
{
    return meaning;
}

Root* Word::getRoot() {
    return root;
}

QString Word::getWord()
{
    return word;
}

Word::Word(QString word, Root* root, QString meaning)
    : word(word)
    , root(root)
    , meaning(meaning) {
}

Word::~Word()
{
    
}
