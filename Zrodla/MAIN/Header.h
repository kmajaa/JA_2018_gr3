#pragma once
#include <string>

bool isAlphaOnly(std::string text);
std::string retrieveKey();
std::string retrievePlaintext();
void vigenere_param(std::string kword, std::string plaintext);
void vigenere_no_param();
void greetUser();