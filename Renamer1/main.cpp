//Renamer1 02.19.15
#include "dirent.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string dirseparator = "/";

int main(int argc, char *argv[])
{
	//The string we have and the string we want
	string oldStr;
	string newStr;
	//Vector of names in the directory.
	vector<string> strVec;		//All the files.
	vector<string> oldVec;		//The ones slated for renaming.
	vector<string> newVec;		//The renamed files.

	//Fancy title.
	cout << "\n----Renamer1----\n";

	//Now we set the directory.
	char *directory;
	if (argv[1] == NULL)
	{
		cout << "No argv given. Define a directory here: ";
		char inputdir[256];
		cin >> inputdir;
		directory = inputdir;
	}
	else
	{
		directory = argv[1];
		cout << "Directory: " << directory << "\n";
	}
	string dirStr(directory);			//Save the directory as a string for later use.

	//Define the strings we have and want.
	cout << "\nRename: ";
	cin >> oldStr;
	cout << "To: ";
	cin >> newStr;

	//Search the directory and add the file names to our vector.
	cout << "\nSearching directory.\n\nFiles Found: \n";
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directory)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_REG)
			{
				string fileString(ent->d_name);
				cout << fileString << "\n";
				strVec.push_back(fileString);
			}
		}
		closedir(dir);
	}
	else {
		perror("");
		return EXIT_FAILURE;
	}

	//Find the files slated for renaming.
	cout << "\nFiles to be renamed: \n";
	for (int i = 0; i < (int)strVec.size(); i++)
	{
		if (strVec[i].find(oldStr) != -1)
		{
			//strVec[i].replace(strVec[i].find(oldStr), oldStr.length(), newStr);
			cout << strVec[i] << "\n";
			oldVec.push_back(strVec[i]);
		}
		
	}
	
	//Generate the vector of the renamed files.
	cout << "\nThe renamed files: \n";
	newVec = oldVec;
	for (int i = 0; i < (int)newVec.size(); i++)
	{
		if (newVec[i].find(oldStr) != -1)
		{
			newVec[i].replace(newVec[i].find(oldStr), oldStr.length(), newStr);
		}
	}
	for (int i = 0; i < (int)newVec.size(); i++)
	{
		cout << newVec[i] << "\n";
	}

	//Now rename the files.
	cout << "\nRenaming:\n";
	for (int i = 0; i < (int)newVec.size(); i++)
	{
		cout << oldVec[i] << " to " << newVec[i] << "\n";
		int result = rename((directory + dirseparator + oldVec[i]).c_str(), (directory + dirseparator + newVec[i]).c_str());
		if (result == 0)
		{
			cout << "Success.\n";
		}
		else
		{
			perror("Error renaming file");
		}
	}

	return 0;
}
