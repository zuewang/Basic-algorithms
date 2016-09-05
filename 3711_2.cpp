#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
struct trie{
	int weight;
	string codes;
	trie* left;
	trie* right;
};
void encode (trie* op, int& length){

	if(op->left!=NULL){
		trie *temp_left = new trie;
		temp_left = op->left;
		temp_left->codes = op->codes + "0";
		encode(temp_left, length);
	}
	if(op->right!=NULL){
		trie *temp_right = new trie;
		temp_right = op->right;
		temp_right -> codes = op->codes +"1";
		encode(temp_right, length);
	}
	else{
		//display the code
		cout<<"code: "<<op->codes<<endl;
		length += op->codes.length()*op->weight;
	}
}
int main(){
	string line;
	ifstream infile;
	//change the file name either "non-uniform_distribution.txt" or
	// "uniform_distribution.txt"
	infile.open("uniform_distribution.txt");
	if (infile.good()){
		cout<<"There's no problem opening the file"<<endl;
	}else{cerr<<"There's problem opening the file"<<endl;}
	getline(infile,line);
	vector<char>vec_file;
	for (int i=0; i<line.length(); i++){
		vec_file.push_back(line[i]);
	}
	sort(vec_file.begin(),vec_file.end());
	string line_2;
	for (int i=0; i<vec_file.size(); i++){
		line_2 += vec_file.at(i);
	}
	vector<int> vec_freq;
	int freq=0;
	char temp_char = line_2[0];
	for (int i=0; i<line_2.length(); i++){
		if(line_2[i] == temp_char){freq++;}
		else{
			temp_char = line_2[i];
			vec_freq.push_back(freq);
			freq=1;
		}
		if(i == line_2.length()-1){
			vec_freq.push_back(freq);
		}
	}
	sort(vec_freq.begin(),vec_freq.end());
	vector <trie*> chars;
	for (int i=0; i<vec_freq.size(); i++){
		trie *temp = new trie;
		temp->weight = vec_freq.at(i);
		temp->left = NULL;
		temp->right = NULL;
		chars.push_back(temp);
	}
	trie *root = new trie;
	while (chars.size()>1){
		trie *node = new trie;
		node->left = chars.at(0);
		node->right = chars.at(1);
		node->weight = chars.at(0)->weight + chars.at(1)->weight;
		chars.erase(chars.begin());
		chars.erase(chars.begin());
		bool if_find = false; int k=0;
		for(int i=0; i< chars.size(); i++){
			if((node->weight)<(chars.at(i)->weight)){
				chars.insert(chars.begin()+i,node);
				if_find = true;
				break;
			}
		}
		if(if_find == false){chars.push_back(node);}
		if_find=false;
	}
	root = chars.at(0);
	root->codes = "";
	int message_length = 0;
	encode(root, message_length);
	cout<<"the message length is: "<<message_length<<endl;
	return 0;
}
