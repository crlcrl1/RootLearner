#include "root.h"

Root::Root()
{
    currentWord = 0;
}

Root::Root(QString root) : root(root)
{
    currentWord = 0;
}
    
QString Root::getRoot()
{
    return root;
}

void Root::setRoot(QString root)
{
    this->root = root;
}

QString Root::getMeaning() {
    return meaning;
}

void Root::setMeaning(QString meaning) {
    this->meaning = meaning;
}

void Root::addWord(Word* word) {
    words.push_back(word);
}

void Root::removeWord(int index)
{
    Word* toDelete = words[index];
    words.remove(index);
    delete toDelete;
}

void Root::removeWord(QString word)
{
    int index = 0;
    size_t size = words.size();
    for (; index < size; index++)
	if (words[index]->getWord() == word)
	    break;
    Word* toDelete = words[index];
    words.remove(index);
    delete toDelete;
}

Word* Root::nextWord() {
    if (currentWord == words.size() - 1)
        currentWord = 0;
    else
        currentWord++;
    return words[currentWord];
}

Word* Root::prevWord() {
    if (currentWord == 0)
        currentWord = words.size() - 1;
    else
        currentWord--;
    return words[currentWord];
}

QVector<Word*> Root::getAllWords() {
    return words;
}

Root::~Root()
{
    int len = words.size();
    for (int i = 0; i < len; i++)
	delete words[i];
}
