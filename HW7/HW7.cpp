#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/******************************************************************************


Date = 5/5/2020
CS204 Seventh Homework
Purpose = Implement a program that encrypts given data

******************************************************************************/


string XOR_encryption(const string & encryption_key, string & plain_text);
unsigned char permutation_part( const char & gonna_be_permuted);

int main()
{
	string encryption_key, plain_text;

	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: " ;
	getline(cin, encryption_key);

	cout << "Please enter the plaintext to be encrypted: ";
	
	while(getline(cin, plain_text))
	{
		cout << "Ciphertext: " << XOR_encryption(encryption_key, plain_text) << endl << endl;
		cout << "Please enter the plaintext to be encrypted: ";
	}


	return 0;
}

string XOR_encryption(const string & encryption_key, string & plain_text)
{
	ostringstream os;    
	// I am using ostringstream to output every char with hex then I will return string version of the ostringstream

	unsigned int key_length = encryption_key.length();
	unsigned int i = 0;
	for(; i < plain_text.length(); i++)
	{
		unsigned char c = (permutation_part(plain_text[i]) ^ encryption_key[i % key_length]);
		os << hex << (int) c;
	}
	return os.str();

}

unsigned char permutation_part(const char & gonna_be_permuted)
{
	unsigned char ciphered_char = 0x00;
	
	for(unsigned int i = 0; i < 8; i++)
	{
		unsigned char bit_order_change = gonna_be_permuted;
		// The main concept of this part.
		// So, first we are using a left shift to make the corresponding bit the most significant one
		//Then, I am making a right shift to make it the less significant one since I am using unsigned char the other bits will be zero
		// In if else statement I will add it to ciphered char with a respective coefficient so that I will get my finalized permutated char

		bit_order_change= bit_order_change <<(7-i);
		bit_order_change = bit_order_change >> 7;

		
		if(i == 0)
		{
			ciphered_char = ciphered_char + 4*bit_order_change; // Since it is going to be the second bit
		}
		
		else if(i == 1)
		{
			ciphered_char = ciphered_char + bit_order_change; // Since it is going to be the zeroth bit
		}
		else if(i == 2)								
		{
			ciphered_char = ciphered_char + 8*bit_order_change;	// Since it is going to be the third bit
		}
		else if(i == 3)
		{
			ciphered_char = ciphered_char + 2*bit_order_change; // Since it is going to be the first bit
		}
		else if(i == 4)
		{
			ciphered_char = ciphered_char + 64*bit_order_change; // Since it is going tobe the sixth bit
		} 
		else if(i == 5)
		{
			ciphered_char = ciphered_char + 16*bit_order_change; // Since it is going to be the fourth bit
		}		
		else if(i == 6)
		{
			ciphered_char = ciphered_char + 128*bit_order_change; // Since it is going to be the seventh bit
		}
		else if(i == 7)
		{
			ciphered_char = ciphered_char + 32*bit_order_change; // Since it is going to be the fifth bit
		}
		
		                                                        
	}

	return ciphered_char;
}

// End of Homework 7
// Yours sincerely
// Ilker Gul
