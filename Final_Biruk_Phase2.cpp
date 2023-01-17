//BK Ela, [12/16/2021 9:12 PM]
/*
*****Final Project Phase 2: Command Execution********
This program is the continuation of the Final program phase 1. It takes command 
from users, checks if they are valid and returns the commands associated with it.

COMP 376:Advanced Unix Programming
C++ Final Project 
Fall 2021
Prof. Dan Kaiser
*/

#include <sys/wait.h>
#include  <sys/types.h>	
#include <cstdio>
#include  <stdio.h>
#include  <sys/types.h>
#include <iostream>
#include <cstring>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <dirent.h> // needed for opendir, readdir and closedir
#include <unistd.h> // needed for chdir and getcwd
//#include <windows.h> // to include system library. Runs executable.
#define PATH_LENGTH 256
using namespace std;

void Parse(char **parseArray, int& sizeofArray); // declaring Parse Function
void help();
void copy(char **parseArray);
void show(char **parseArray);
void listdir(char **argv, int& argc);
void chgdir(char **argv, int& argc);
void runexecutable(char *FileName);

int main() // Main function
{
    // Initializing pointer to pointer array of size 10
    char **parseArray = new char *[10];

    // Creating the storage for the character, size 256, entered where the pointer will be directing to
    for(int i =0; i<10; i++)
    {
       parseArray[i] = new  char [256];
    }

    
    int sizeofArray =0; // Initializing sizeofArray for Parse function
    
    // Do while loop for program to run while condtions of not quit are met.
    do
    {
       // Parse(parseArray, sizeofArray); // Calling Parse function
        if(strcmp(parseArray[0],"quit")!=0) // Call Parse function if user input is not "quit".
            {   
                //condition to check if argument called is help
               if(strcmp(parseArray[0],"help")==0)
                {
                    help();
                
                } 
                //condition to check if argument called is copy to copy files
                else if(strcmp(parseArray[0],"copy")==0 && sizeofArray==3)
                {
                        copy(parseArray);
                        
                }
                //condition to check if argument called is show to show contents of a file
                else if(strcmp(parseArray[0],"show")==0)
                {
                    if (sizeofArray!=2)
                        cout<<"Incorrect number of arguments\n";
                    else
                        show(parseArray);
                }
                //condition to check if argument called is list, to list files in current or specified directory
                else if(strcmp(parseArray[0],"list")==0)
                {
                    listdir(parseArray,sizeofArray);
                }
                //condition to check if argument called is cd, to change current working directory
                else if(strcmp(parseArray[0],"cd")==0)
                {
                    chgdir(parseArray, sizeofArray);
                }
                //condition to check if argument called is run to run an executable file
                else if(strcmp(parseArray[0],"run")==0)
                {
                    runexecutable(parseArray[1]);
                }
                else
                    cout<<"Command is not recognized. Enter 'help' for list of commands.\n";
                //Continue to call Parse function to take arguments
                Parse(parseArray, sizeofArray);

                
            }
       
    }
    while(strcmp(parseArray[0],"quit") != 0);
    
    
    // Quit statement
    std::cout<<"Bye!"<<std::endl;        


    
}

// Defining Parse fuction
void Parse(char **parseArray, int& sizeofArray)


{
    char inCh;
    std::cout<<" Enter your command --> ";  //User input command
    std::cout<<std::endl;
    std::cin.get(inCh);
    sizeofArray = 0;   // Initializing pointer array index for counting

 
    while(inCh !='\n')  // Setting condition till newline is entered
    {   
        while(isspace(inCh))
            std::cin.get(inCh);
            
        int count = 0; // Character counter initialization
        while(!isspace(inCh)){   // Setting condtion while no whitespace is entered
            parseArray[sizeofArray][count] = inCh; // Fill in parseArray with character taken while condtions met.
            std::cin.get(inCh); // keep on getting character from user input.
            count++; //increment count each time a succesfull sharater is read.
        } 
        
        parseArray[sizeofArray][count]='\0'; // End the parsAarray[sizeofArray][count] with a null once a whitespace is incountered
       
        count = 0; // Set count to zero for the next string to be filled from index zero in pasreArray[sizeofArray][count]
        sizeofArray++; // Increment sizeofArray to proceed to th next index in parseArray[sizeofArray]
        
        if(inCh!='\n') // Keep taking character from input stream as long as it is not new line
            std::cin.get(inCh);
        
    }

}
// Function to list the commands for user
void help()
{
    std::cout<<"--------------------------------------\n";
    std::cout<<"Valid Commands\t\t  Commands \n";
    std::cout<<"--------------------------------------\n";
    std::cout<<"- Run excutable file\tRun filename\n";
    std::cout<<"- List\t\t\tlist\n";
    std::cout<<"- List directory\tlist directory\n";
    std::cout<<"- Copy\t\t\tCopy OldFileName NewFileName\n";
    std::cout<<"- cd\t\t\tcd directory\n";
    std::cout<<"- Show\t\t\tshow filename\n";
    std::cout<<"- Quit\t\t\tquit\n";

}
// Function to take argumetns and copy files
void copy(char **parseArray)
    {
    
    string inFileName =parseArray[1];

	ifstream myIn;  // Input filestream variable
	
	// Attempt to open the file
	myIn.open(inFileName.c_str());
	// Check to make sure it opened
	if( myIn.fail() )
	{
		cout << "Error opening input file." << endl;
		exit(EXIT_FAILURE);
	}

    // Attempt to open output file
    string outFileName= parseArray[2];

    ofstream myOut; // Output filestram variable
    // Attempt to open the file
    myOut.open(outFileName.c_str());  // Filename must be a cstring

    // Check to make sure it opened
    if( myOut.fail() )
    {
        cout << "Error opening output file." << endl;
        exit(EXIT_FAILURE);
    }
    
    string line;
    
    if(myIn && myOut){
        cout<<"Do you want to erase contents of the new file?\nYes(y)\nNo(n)\n";
        char option;
        cin>>option;

        if(option=='y'){
            // copy contents of file
            while(getline(myIn,line)){
                myOut << line << "\n";
            }
    
            cout << "Copy Finished \n";
            myIn.close(); // closing input file
            myOut.close(); // closing input file
            cin.ignore(1);
            
        }

        else if(option=='n'){
            cout<<"Copy request terminated.\n";
            myIn.close();
            myOut.close();
            cin.ignore(1);
            
        } 
        
    }
    
     
    else {
        //Something went wrong
        printf("Cannot read File");
    }
    myIn.close(); // closing input file
    myOut.close(); // closing input file
    
}
//Function to show the contents of a given file
void show(char **parseArray)
{
    string inFileName = parseArray[1];

	ifstream myIn;  // Input filestream variable
	
	// Attempt to open the file
	myIn.open(inFileName.c_str());
	// Check to make sure it opened
	if( myIn.fail() )
	{
		cout << "Error opening input file." << endl;
		exit(EXIT_FAILURE);
	}

    string line;
    if(myIn){
        while(getline(myIn,line))
            cout<<line<<"\n";
    }
    myIn.close();
}
// Function to list the files in a given or current directory
void listdir(char **argv, int& argc)
{
    DIR* dir;
	struct dirent* dirEntry;
  if( argc==1)
  {
      dir = opendir(".");
      int i = 0;
	while( (dirEntry = readdir(dir)) != NULL )
	{
		cout << "File " << ++i;
		cout << "\tiNode: " << dirEntry -> d_ino << endl;
		cout << "\tFile Name: " << dirEntry -> d_name << endl;
		cout << endl;
	}
	
	cout << "Listed " << i << " files.\n" << endl;
  }

 else if( argc==2)
 {

  if( (dir = opendir(argv[1])) == NULL )
  {
  	perror("Unable to open directory");
  	//exit(1);
  }
        
  int i = 0;
	while( (dirEntry = readdir(dir)) != NULL )
	{
		cout << "File " << ++i;
		cout << "\tiNode: " << dirEntry -> d_ino << endl;
		cout << "\tFile Name: " << dirEntry -> d_name << endl;
		cout << endl;
	}
	
	cout << "Listed " << i << " files.\n" << endl;
		
 }

 
  else if( argc>=3)
  {
      cerr << "Incorrect number of arguments.\n" << endl;
  }
}
// Function to change working directory
void chgdir(char **argv, int& argc)
{
    char olddir[PATH_LENGTH + 1];
	char newdir[PATH_LENGTH + 1];

	if( getcwd(olddir, PATH_LENGTH) == NULL )  // Error in text
  {
   	perror("Unable to get current directory");
  //	exit(1);
  }
  
  cout << "pwd: " << olddir << endl;
  
  if( argc != 2 )
  {
  	cerr << "No directory specified." << endl;
  //	exit(1);
  }
  
  if( chdir(argv[1]) == -1 )
  {
  	perror("Unable to change directories");
  	//exit(1);
  }
  
  cout << "cd: " << argv[1] << endl;
  
  
  
  if( getcwd(newdir, PATH_LENGTH) == NULL )
  {
   	perror("Unable to get current directory");
  //	exit(1);
  }
  
  cout << "pwd: " << newdir << endl;
}
// Function to run an executable file from a directory
void runexecutable(char *FileName)
{
    
 pid_t p = fork();
 if(p)
 {
  wait(NULL);
 }
 else
 {
  execl(FileName, FileName, NULL);
 }
}

