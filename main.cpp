/* ----------------------------------------------
 * Basic Calculator with + - / % *
 *
 * To Do: To figure out what some encrypted line of text says by trying all possible decryption possibilities
 * ----------------------------------------------
 */


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>     // For the letter checking functions
#include <cctype>
#include <string.h>	  // For file input and output
#include <cassert>   //to check if text file is opened correctly
#include <time.h>
using namespace std;


//struct to store frequency count and character 
struct Freq 
{
	int count;
	char c;
};


//displayIdentifyingInfo displays information about author and program
//the function does not return anything
void displayIdentifyingInfo()
{
	printf("Author: Anusha Pai and  Bushra Baqui\n");
	printf("Program 4: CryptoFile\n");
	printf("Anusha Pai TA: Chenwei Zhang 8am\n");
	printf("Bushra Baqui TA: Chenwei Zhang 9am\n");
	printf("March 11, 2016\n");
	printf("System: Windows 10, DevC++\n\n");
}//end of displayInfo()


//displayUserInstructions displays the options the user could pick from
//this function does not return anything
void displayUserInstructions()
{
	printf ("Choose your option: \n");
	printf ("1. Encrypt a file\n");
	printf ("2. Decrypt a file\n");
	printf ("Your choice: ");
}//end of displayUserInstructions();


//subRandLetter substitutes each letter in array line with a random letter from upperRandLetter or lowerRandLetters(depending on case)
//The index of upperRandLetters and lowerRandLetters determine which letter is substituted with which random letter
//the function does not return anything 
void subRandLetter(char line[],               //char array that needs to be substituted by randome letters    
				   char upperRandLetters[],   //char array of random upper case letters
				   char lowerRandLetters[])   //char array of random lower case letters
{
	//outer for loop goes through each element in array line
	for(int i = 0; i < strlen(line); i++)
	{
		if(isprint(line[i]))
		{
			//checks if letter at index i is upper case
			if(isupper(line[i]))
			{
				//for loop to find the letter that needs to be substituted with (from upperRandLetters)
				for(int u = 65; u <= 90; u++)
				{
					if(line[i] == u)
					{
						line[i] = upperRandLetters[u-65];  //substitutes
						break;
					}
				}
			}
			
			//checks if letter at index i is lower case
			else if(islower(line[i]))
			{
				//for loop to find the letter that needs to be substituted with (from lowerRandLetters)
				for(int l = 97; l <= 122; l++)
				{
					if(line[i] == l)
					{
						line[i] = lowerRandLetters[l-97];  //substitutes
						break;
					}
				}
			}
		}
	}//end of outer loop
}//end of void subRandLetter(char line[], char upperRandLetters[], char lowerRandLetters[]);


//createUpperRandLetters takes in a char array and assigns a random upper case letter to each index (from 0-26)
//there are no repeats in the array (i.e. each index has a unique random letter)
//this function does not return anything
void createUpperRandLetters(char upperRandLetters[])
{
	
	memset(&upperRandLetters[0], 0, sizeof(upperRandLetters));

	//creates random letters everytime program is compiled
	srand((int)time(0));
	
	//outer for loop goes through each element in upperRandLetters from 0-26 
	for(int i = 0; i < 26; i++)
	{
		//assigns first random upper case letter at index i
		upperRandLetters[i] = (rand() % (90-65 + 1)) + 65;
		
		//loops through each element in upperRandLetters to make sure there are no repeats
		for(int j = 0; j < 26; j++)
		{
			//if there is a repeat...
			if((j != i) && (upperRandLetters[j] == upperRandLetters[i]))
			{
				upperRandLetters[i] = (rand() % (90-65 + 1)) + 65;    //assigns a new random character
				j = -1;      //resets the for loop to check all elements again
			}
		}
	}
}//end of void createUpperRandLetters(char upperRandLetters[]);


//createLowerRandLetters takes in a char array and assigns a random lower case letter to each index (from 0-26)
//there are no repeats in the array (i.e. each index has a unique random letter)
//this function does not return anything
void createLowerRandLetters(char lowerRandLetters[])
{
	//clears out result array
	memset(&lowerRandLetters[0], 0, sizeof(lowerRandLetters));
	
	srand((int)time(0));
	
	//outer for loop goes through each element in lowerRandLetters from 0-26 
	for(int i = 0; i < 26; i++)
	{
		//assigns first random lower case letter at index i
		lowerRandLetters[i] = (rand() % (122-97 + 1)) + 97;
		
		for(int j = 0; j < 26; j++) 
		{
			//if there is a repeat...
			if((j != i) && (lowerRandLetters[j] == lowerRandLetters[i]))
			{
				lowerRandLetters[i] = (rand() % (122-97 + 1)) + 97;  //assigns a new random character
				j = -1;   //resets the for loop to check all elements again
			}
		}
	}
}//end of void createLowerRandLetters(char lowerRandLetters[]);


//findCharFreq counts how many times each letter in array line is present
//the frequency of characers is stored in array freq
//this function does not return anything
void findCharFreq(char line[],    //char array to frequency of each letter
			      int freq[])     //in array to store the frequency in
{
	//loops through each character in array line
	for(int i = 0; i < strlen(line); i++)
	{
		//counts how many times each letter is repeated 
		if(isalpha(line[i]))
		{
			freq[line[i]]++;  //frequency of letter is incremented to index(corresponds to ASCII value)
		}
	}
}//end of void findCharFreq(char line[], int freq[]);


void swap(Freq sortArr[], int pass, int sIndex)
{
	int tempI = sortArr[sIndex].count;
	sortArr[sIndex].count = sortArr[pass].count;
	sortArr[pass].count = tempI;
	
	char tempC = sortArr[sIndex].c;
	sortArr[sIndex].c = sortArr[pass].c;
	sortArr[pass].c = tempC;
}//end of void swap(Freq sortArr[], int pass, int sIndex);


//sort from smallest to largest
void sort(Freq sortArr[])
{
	int sIndex = 0;

	for(int pass = 0; pass < 128; pass++)
	{
		sIndex = pass;
		for(int i = pass + 1; i < 128; i++)
		{
			if(sortArr[i].count < sortArr[sIndex].count)
			{
				sIndex = i;	
			}
		}
		swap(sortArr, pass, sIndex);
	}
}//end of void sort(Freq sortArr[]);


//matchFreqCount compares each character frequency and finds two frequency count that are the same
//then the function substitutes the letters in cipherLine with the index of lomFreqCount and stores the characters in result
//this function does not return anything
void matchFreqCount(Freq lomFreqCount[],     
					Freq cFreqCount[],       
					char result[],          //stores the resulting substituted characters in this char array  
					char cipherLine[])      //char array for characters to be substituted and stored in result
{
	int cipherVal = -1;
	bool sub = false;
	
	//clears out result array
	memset(&result[0], 0, sizeof(result));
	
	//sort array from lowest to highest
	sort(lomFreqCount);
	sort(cFreqCount);	
	
	for(int i = 0; i <= strlen(cipherLine); i++)
	{
		cipherVal = -1;
		sub = false;
		if(isalpha(cipherLine[i]))
		{
			for(int j = 0; j < 128; j++)
			{
				if(cipherLine[i] == cFreqCount[j].c)
				{
					result[i] = lomFreqCount[j].c;
				}
			}	
		}
		else
		{
			result[i] = cipherLine[i];
		}
	}
}//end of void matchFreqCount(Freq lomFreqCount[], Freq cFreqCount[], char result[], char cipherLine[]);


/*----------------------------------------------------------------------------------------------------*/
int main()
{
	int userChoice;
	char returnKey;
	
	//variable declarations for case 1
	char upperRandLetters[27];
	char lowerRandLetters[27];
	char sampleLine[100];
	FILE *inFileSample;
	FILE *outFileCipher;
	int count1 = 0;
	
	//variable declarations for case 2
	int lomFreq[128];
	int l;
	int cFreq[128];
	int c;
	char lomLine[100];
	char cLine[100];
	char resultLine[100];
	FILE *inFileCipher;
	FILE *inFileLOM;
	FILE *outFileResult;
	Freq cip [128];
	Freq lom[128];
	int count2 = 0;
	
	displayIdentifyingInfo();
	displayUserInstructions();
	scanf ("%d%c", &userChoice, &returnKey);
	
	int count = 0;
	
	if (userChoice == 1)
	{
	
		printf("You entered option 1 to encrypt file sample.txt\n");
		printf("The first part of that encrypted file looks like:\n\n\n");
		printf("The encrypted file is:\n");
		
		//opening sample.txt
		inFileSample = fopen("sample.txt", "r");
	    
	    //if file can't be opened
		if (!inFileSample)
		{
			printf ("Sample file does not exist!\n");
			exit(-1);
		}
	      
		//opening cipher.txt               	
	    outFileCipher = fopen("cipher.txt", "w");
	    
	    //if file can't be opened
	    if (!outFileCipher)
		{
			printf ("Cipher file does not exist!\n");
			exit(-1);
		}
		createUpperRandLetters(upperRandLetters);
		createLowerRandLetters(lowerRandLetters);

		//reads every line from sample.txt and stores it in sampleLine
		while(fgets(sampleLine, 100, inFileSample) != NULL)
		{
		
			subRandLetter(sampleLine, upperRandLetters, lowerRandLetters);
			
			fprintf(outFileCipher, sampleLine);
			
			count1 += strlen(sampleLine);
			if(count1 < 1500)
			{
				printf("%s", sampleLine);
			}
		}
		
		fclose(outFileCipher);
		fclose(inFileSample);
			
	}
		
	else 
	{
		
		printf("You entered option 2 to decrypt file  cipher.txt  using  lifeonmiss.txt  for frequency counts.\n");
		printf("The first part of that decrypted file looks like:\n\n\n");
		printf("The decrypted file is:\n");
		
		
		//assigns each value in lowFreq to 0
		for(l = 0; l < 128; l++)
		{
			lomFreq[l] = 0;
		}
		
		//assigns each value in cFreq to 0
		for(c = 0; c < 128; c++)
		{
			cFreq[c] = 0;
		}
		
		//opening cipher and lifeonmiss files to read from
		inFileCipher = fopen("cipher.txt", "r");
		
		//if file can't be opened
		if (!inFileCipher)
		{
			printf ("Cipher file does not exist!\n");
			exit(-1);
		}
		
		inFileLOM = fopen("lifeonmiss.txt", "r");
		
		//if file can't be opened
		if (!inFileLOM)
		{
			printf ("Lifeonmiss file does not exist!\n");
			exit(-1);
		}
		
		//opening result file to write on
		outFileResult = fopen("result.txt", "w");
		
		//if file can't be opened
		if (!outFileResult)
		{
			printf ("Result file does not exist!\n");
			exit(-1);
		}
		
		//stores frequent count into cFreq and lomFreq by going through every line
		while(fgets(cLine, 100, inFileCipher) != NULL)
		{
			findCharFreq(cLine, cFreq);		
		}
		while(fgets(lomLine, 100, inFileLOM) != NULL)
		{
			findCharFreq(lomLine, lomFreq);
		}
	
		
		for(l = 0; l < 128; l++)
		{
			cip[l].count = cFreq[l];
			cip[l].c = l;
			lom[l].count = lomFreq[l];
			lom[l].c = l;
		}
		
		
		
		fclose(inFileCipher);
		fclose(inFileLOM);
		inFileCipher = fopen("cipher.txt", "r");

		while(fgets(cLine, 100, inFileCipher) != NULL)
		{
			matchFreqCount(lom, cip, resultLine, cLine);
			
			fprintf(outFileResult, resultLine);
			
			if(count2 <= 1500)
			{
				printf("%s", resultLine);
			}
			count2 += strlen(resultLine);
		}
		fclose(inFileCipher);
		fclose(outFileResult);
	}
	
	return 0;
}




