#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<set>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include"trie.h"

using namespace std;


void edits(std::string word, std::vector<string> &result)
{
	cout << word << endl;
	for (string::size_type i = 0; i < word.length(); i++) result.push_back(word.substr(0, i) + word.substr(i + 1)); //deletions
	for (string::size_type i = 0; i < word.size() - 1; i++) result.push_back(word.substr(0, i) + word[i + 1] + word.substr(i + 2)); //transposition

	for (char j = 'a'; j <= 'z'; ++j)
	{
		for (string::size_type i = 0; i < word.size(); i++) result.push_back(word.substr(0, i) + j + word.substr(i + 1)); //alterations
		for (string::size_type i = 0; i < word.size() + 1; i++) result.push_back(word.substr(0, i) + j + word.substr(i)); //insertion
	}
}


bool loadDictionary(Trie* trie, string filename)
{

	ifstream w;
	ifstream i;
	FILE *fp = NULL;
	fp = fopen("D:\\wordlist.txt", "r");
	w.open(filename.c_str());

	if (!w.is_open())
	{
		cout << "Dictionary file Not Open" << endl;
		return false;
	}

	while (!w.eof())
	{
		char s[100];
		w >> s;
		trie->addWord(s);
	}
	return true;
}

int main()
{
	Trie* trie = new Trie();
	int mode;

	cout << "Loading dictionary" << endl;

	loadDictionary(trie, "D:\\wordlist.txt");

	while (1)
	{
		cout << endl << endl;
		cout << " Auto Complete Feature to give suggestions" << endl;
		
		{ //autocomplete

			string s;
			cin >> s;
			transform(s.begin(), s.end(), s.begin(), ::tolower);

			vector<string> autoCompleteList;
			trie->autoComplete(s, autoCompleteList);

			if (autoCompleteList.size() == 0)
			{
				cout << "No suggestions" << endl;
			}
			else
			{
				cout << "Autocomplete reply :" << endl;
				for (int i = 0; i<autoCompleteList.size(); i++)
				{
					cout << autoCompleteList[i] << endl;
				}
			}
		}
		

	}
}

