#include "Header.h"
#include <iostream>
#include <stdlib.h>

#define ALPH 26

bool isAlphaOnly(std::string text)
{
	for (char letter : text)
	{
		if (!isalpha(letter))
		{
			std::cout << "Invalid key!" << std::endl;
			return false;
		}
	}
	return true;
}

std::string retrieveKey()
{
	std::string kword = "";
	do
	{
		std::cout << "Enter keyword (letters only): ";
		std::getline(std::cin, kword);
		// Check that the key contains only letters
		for (int i = 0; i < kword.length(); i++)
		{
			if (!isalpha(kword[i]))
			{
				// if invalid, complain and try again
				std::cout << "Invalid key!\n";
				kword = "";
			}
		}
	} while (kword == "");

	return kword;
}

std::string retrievePlaintext()
{
	std::string plaintext = "";
	do
	{
		std::cout << "Enter plaintext to encode: ";
		std::getline(std::cin, plaintext);
	} while (plaintext == "");

	return plaintext;
}

void vigenere_param(std::string kword, std::string plaintext)
{
	// set keyword length
	int key_length = kword.length();

	// Encrypt plaintext with the key letter by letter
	for (int i = 0, j = 0, ptxt_length = plaintext.length(), newchar; i < ptxt_length; i++)
	{
		// set the key
		char key;
		if (isupper(kword[j%key_length]))
			key = ((kword[j%key_length] - 'A') % ALPH);
		else
			key = ((kword[j%key_length] - 'a') % ALPH);

		// shift letters only
		if (isalpha(plaintext[i]))
		{
			// preserve capitalisation; refer to the alphabetical
			// index to calculate and revert to ascii
			if (isupper(plaintext[i]))
				newchar = ('A' + ((plaintext[i] - 'A' + key) % ALPH));
			else
				newchar = ('a' + ((plaintext[i] - 'a' + key) % ALPH));

			j++;
		}
		else
		{
			newchar = plaintext[i];
		}

		//print the encoded character
		printf("%c", newchar);
	}

	std::cout << std::endl;
}

void vigenere_no_param()
{
	// Retrieve keyword
	std::string kword = retrieveKey();

	// Get the plaintext
	std::string plaintext = retrievePlaintext();

	vigenere_param(kword, plaintext);
}

void greetUser()
{
	std::cout << "HELLO!" << std::endl;
}