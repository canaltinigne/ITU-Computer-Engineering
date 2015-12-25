#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main(){
	FILE * myfile = fopen("stopwords.txt", "r");

	if (!myfile){
		return 0;
	}
		

	char word[25];
	set <string> stopwords;

	while (!feof(myfile)){
		fscanf(myfile, "%s", word);
		stopwords.insert(word);
	}

	fclose(myfile);

	myfile = fopen("input.txt", "r");

	if (!myfile)
		return 0;

	int counter = 0;

	set<string>::iterator its;
	map <string, int> freq;

	while (!feof(myfile)){
		
		fscanf(myfile, "%s", word);
		char str[25];
		string deneme;
		deneme = word;

		int a = 0;

		for (int i = 0; i < deneme.length(); i++){
			if (isalpha(deneme[i])){
				str[a] = tolower(deneme[i]);
				a++;
			}
		}

		str[a] = '\0';

		its = stopwords.find(str);

		if (its != stopwords.end()){
			freq[str]++;
			counter++;
		}
			
	}

	fclose(myfile);

	multimap <int, string> freq_rev;
	map<string, int>::iterator it;

	for (it = freq.begin(); it != freq.end(); it++)
		freq_rev.insert(make_pair(it->second, it->first));

	multimap<int, string>::reverse_iterator myit;
	int count = 0;

	for (myit = freq_rev.rbegin(); count < freq_rev.size(); myit++, count++)
		cout << (*myit).second << " " << (*myit).first << " % " << 100.0*(*myit).first / counter << endl;

	return 0;
}