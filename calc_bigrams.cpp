#include <iostream>
#include <fstream>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

//This program is used to read words from a document, count the occurrences of each word, and count the occurrences of each word pair.
//After getting these counts, the user is then prompted to enter two words and the program will find a bigram probability of it,
//As long as the words occur in the document and the wordPair exists in the document as well.	-R. Cisneros


//Takes in string, sets to lower case, and removes punctuation. I did not write this, this was written by my Data Structures professor Rivka Levitan, Brooklyn College
std::string normalizeString(const std::string& str) {
	std::string res = str;																						//1. Assigns string input to res
	std::cout << str << " ";																					//2. prints string with space in front of it
	std::transform(res.begin(), res.end(), res.begin(), ::tolower);												//3. sets string to lower case
	res.erase(std::remove_if(res.begin(), res.end(), std::ptr_fun<int,int>(ispunct)), res.end());				//4. Removes punctuation
	std:: cout << res << "\n";																					//5. Inserts newline
	return res;
}

int main(int argc, char* argv[]){
	if (argc < 2) {
		throw std::underflow_error("File not given");
		return 1;
	}
	ifstream infile(argv[1]);

	std::map<std::pair<std::string, std::string>, int> wordPairMap;	//Maps word pair count
	std::map<std::string, int> wordMap;								//Maps word count
	
	std::string word1, word2;
	std::pair<std::string, std::string> wordPair;
	
	infile >> word1;										//this is the initial reading. we have to start this off before we enter the loop
	infile >> word2;										//because after this word 1 is going to be based off of word 2

	 wordPair.first = normalizeString(word1);				//Adds the normalized strings to wordPair
	 wordPair.second = normalizeString(word2);
	 
	 wordPairMap[wordPair]=1;						//Sets the count		
	 wordMap[word1] = 1;							//Also sets the count for the first word
	 
	while(!infile.eof()){
	
		word1 = word2;								//Move to the next word; it must still take word2
		infile >> word2;							//Then read in word2
		
		wordPair.first = normalizeString(word1);		//Normalize and assign to wordPair
		wordPair.second = normalizeString(word2);
		
		wordMap[word1]++;								//By default the count is at 0, so from here we can just increment
		wordPairMap[wordPair]++;						//the word and wordPair counts, and move forward through the file
	 }
	
	std::string a, b;
	double singleFreq, pairFreq;
	double ratio;
	std::pair<std::string, std::string> inputPair;
	
	while (a != "q" || b!= "q"){					//This portion allows the user to give input and see the frequency
		cout << "Enter a pair of words: " << endl;
		cin >> a;
		cin >> b;
		
		if(wordMap.count(a))						//Gets the count of the word if it is in the file
			singleFreq = wordMap[a];
		else
			cout << "\nFirst word not found" << endl;
			
		if(wordMap.count(b)){															//This checks if the second word is in the file.			
			inputPair = std::make_pair(a, b);											//If it is, we assign the two words to a pair
			if(wordPairMap.count(inputPair)){											//And check if the wordPair is in the map.
				pairFreq = wordPairMap[inputPair];										//If it is, we get frequency of the pair
				ratio = pairFreq / singleFreq;											//We then divide the pair frequency by the first-word frequency to get the bigram probability
				cout << "\nThe bigram probability is: " << ratio << endl;
			}
			else
				cout << "\nPair not found" << endl;
		}
		else
			cout << "\nSecond word not found" << endl;
			
		
	}
	
	return 0;
}
