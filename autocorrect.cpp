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

	ifstream words;
	ifstream input;
	FILE *fp = NULL;
	fp = fopen("D:\\wordlist.txt", "r");
	words.open(filename.c_str());

	if (!words.is_open())
	{
		cout << "Dictionary file Not Open" << endl;
		return false;
	}

	while (!words.eof())
	{
		char s[100];
		words >> s;
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
		cout << "Check for word correctness and and suggest corrections" << endl;
				{ //word correction and suggestions
			string s;
			cin >> s;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			int count = 0;
			set<string> suggestions;
			vector<string> edit_list;
			if (trie->searchWord(s)){
				//	output<<s<<" Correct word "<<endl;
				cout << s << "found in Dictionary" << endl;
				
			}
			else
			{
				edits(s, edit_list);

				for (unsigned int i = 0; i<edit_list.size(); i++)
				{
					if (trie->searchWord(edit_list[i]))
					{
						suggestions.insert(edit_list[i]);
						count++;
						if (count>10)
							break;
					}
				}
				if (count == 0){
					cout << "No suggestions" << endl;
				}
				else
				{
					cout << "Did you mean" << endl;
					set<string>::iterator itr;
					for (itr = suggestions.begin(); itr != suggestions.end(); itr++)
						cout << *itr << endl;
				}

			}

		}


	}
}

