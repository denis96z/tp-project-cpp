#include "Tokenizer.hpp"
#include <iostream>


void Tokenizer::sentence_token(){ // разделение на предложения
	boost::char_separator<char> sep("!?."); // разделители
	boost::tokenizer<boost::char_separator<char>> tokens(text, sep);
	for (boost::tokenizer<boost::char_separator<char>>::iterator it = tokens.begin(); it != tokens.end(); ++it){
		sentences.push_back(*it);
		// std::cout << *it<< "\n";
	}
}


void Tokenizer::sentence_to_words(){ // разделение предложений на слова
	std::vector<std::string> sep_sentence;
	std::vector<std::string> normalized_sent;
	
	// std::vector<std::string> none_sep_sent = sentence_token(); // получаем вектор предложений из текста
	
	/*
	если до разбиения предложений на слова текст не был разбит на предложения,
	то есть переменная sentences класс DataHub пуста, вызвать функцию разбиения текста на предложения
	*/
	if (sentences.size() == 0) 
		sentence_token();
	
	normalized_sent = normalize(sentences); // получаем вектор нормализированных предложений (создаем нормализированную копию sentenes)

	boost::char_separator<char> sep(" ");
	for (int i = 0; i < normalized_sent.size(); ++i){ // идем по векторы нормализованных предложений
		boost::tokenizer<boost::char_separator<char>> words(normalized_sent[i], sep);
		for (boost::tokenizer<boost::char_separator<char>>::iterator it = words.begin(); it != words.end(); ++it){ // идем по одному предлодению
			sep_sentence.push_back(*it);
			std::cout << *it << "\n";
		}
		tokens.push_back(sep_sentence);
		// std::cout << sep_sentence << "\n";
	}
}


/*
Нормализация - очищение предложений от знаков
*/
std::vector<std::string> Tokenizer::normalize(std::vector<std::string>& array){ 
	std::string signes ("()-<>/[]{}|*");
	for (int i = 0; i < array.size(); ++i){
		for (int j = 0; j < array[i].size(); ++j){
			if (signes.find(array[i][j]) != std::string::npos){
				array[i].erase(array[i].begin()+j);
			}
		}
	}
	return array;	
}
