// Name: Sequencer.cpp
// Author: Allan Kangethe
// Date: 4/3/2023
// Desc: The Sequencer class manages the application and the DNA and mRNA strands from Sequencer.h.


#include "Sequencer.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Default constructor.
// Creates a new sequencer to hold one or more DNA/mRNA strands make of
// multiples of three nucleotides.
Sequencer::Sequencer(string fileName)
{
  // Sets file name
  m_fileName = fileName;
}

// Destructor
Sequencer::~Sequencer()
{
  cout << "Deleting DNA Strands" << endl;
  for(long unsigned i = 0; i < m_DNA.size();i++)
    {
      delete m_DNA.at(i);
    }

  cout << "Deleting mRNA Strands" << endl;
  for(long unsigned i = 0; i < m_mRNA.size();i++)
    {
      delete m_mRNA.at(i);
    }


}

// Name: StartSequencing
// Desc: Calls ReadFile and continually calls mainmenu until the user exits
// Preconditions: m_fileName has been populated
// Postconditions: m_DNA has been populated (after ReadFile concludes)
void Sequencer::StartSequencing()
{
  int choice = 0;
  ReadFile();
  
  while(choice != 5)
    {
      //Gets choice from Main Menu
      choice = MainMenu();
      //Switch statement
      switch(choice)
        {
        case 1:
          //Displays strands
          DisplayStrands();
          break;
        case 2:
          //Reverse Strands
          ReverseSequence();
          break;
        case 3:
          //Transcribes strands
	  Transcribe();
	  break;
        case 4:
          //Translates strands
	  if(m_mRNA.size() == 0)
            {
              cout << "No mRNA to translate; transcribe first" << endl;
            }
	  else
	    {
	      Translate();
	    }
	  break;
        case 5:
          //End Code
	  cout << "Exiting program" << endl;
          return;
        default:
          cout << "Invalid Input! Try Again!" << endl;
        }
    }
  
}

// Name: ReadFile
// Desc: Reads in a file of DNA strands that has the name on one line then
//       the sequence on the next
//       All sequences will be an indeterminate length (always evenly divisible by three though).
//       There are an indeterminate number of sequences in a file.
//       Hint: Read in the entire sequence into a string then go char
//       by char until you hit a new line break. Then insert to the m_DNA vector
// Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
// Postconditions: Populates each DNA strand and puts in m_DNA
void Sequencer::ReadFile()
{
  //Open file
  ifstream infile;
  infile.open(m_fileName);

  //If file is open
  if(infile.is_open())
    {
      cout << "Opened File" << endl;
      //Variables
      string line, strand, strandName;
      int counter = 0;
      
      //Loops through file by line
      while(getline(infile, line))
	{
	  //Loops line
	  while (line[counter] != ',')
            {
	      // Creates string containing name of the source of DNA only
	      strandName += line[counter];
	      counter++;

            }

	  //Loops through rest of line
	  for (long unsigned i = counter+1; i < line.length(); i++)
            {
	      //Creates string containing sequence of characters without commas.
	      if(line[i] != ',')
		{
		  strand += line[i];
		}
            }

	  //Creates strand object, passes name.
	  Strand *s = new Strand(strandName);

	  //Adds sequence of characters to strand list.
	  for(long unsigned i = 0; i < strand.length();i++)
	    {
	      s -> InsertEnd(strand[i]);
	    }

	  
	  //Adds strand to DNA container
	  m_DNA.push_back(s);

	  //Resets values.
	  strandName = "";
	  strand = "";
	  counter = 0;
	}
      cout << m_DNA.size() << " strands loaded." << endl;
      
      
    }

  
}

// Name:  MainMenu
// Desc: Displays the main menu and manages exiting.
//       Returns 5 if the user chooses to quit, else returns 0
// Preconditions: m_DNA populated
// Postconditions: Indicates the user has quit the program
int Sequencer::MainMenu()
{
  //returns choice regardless of quantity
  int choice;
  cout << "What would you like to do?:" << endl;
  cout << "1. Display Strands" << endl;
  cout << "2. Reverse Strand" << endl;
  cout << "3. Transcribe DNA to mRNA" << endl;
  cout << "4. Translate mRNA to Amino Acids" << endl;
  cout << "5. Exit" << endl;
  cin >> choice;

  return choice;

  
}

// Name: DisplayStrands
// Desc: Displays each strand in both mDNA and mRNA
//       Displays numbered type (For example, DNA 1) then the name of the strand.
//       Finally displays the strand with arrows between each nucleotide
// Preconditions: At least one linked list is in mDNA (may have mRNA)
// Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands()
{

  //Prints
  for(long unsigned i = 0; i < m_DNA.size();i++)
    {
      // Get DNA Name
      string dnaName = m_DNA.at(i) -> GetName();
      cout << "DNA #" << i+1 << endl;
      cout << "***" << dnaName << "***" << endl;

      //Get strand size
      int size = m_DNA.at(i) -> GetSize();
      char data;
      for(int j = 0; j < size; j++)
	{
	  
	  data = m_DNA.at(i) -> GetData(j);

	  cout << data << "->";
	}
      cout << "END" <<endl;
      
    }

  //Prints if mRNA is available
  if(m_mRNA.size() != 0)
    {
      for (long unsigned i = 0; i < m_mRNA.size(); i++)
	{
	  string mrnaName = m_mRNA.at(i) -> GetName();
	  cout << "mRNA #" << i + 1 << endl;
	  cout << "***" << mrnaName << "***" << endl;
	  for (int j = 0; j < m_mRNA.at(i)->GetSize(); j++)
	    {
	      cout << m_mRNA.at(i)->GetData(j) << "->";
	    }
	  cout << "END" << endl;
	  
	}
    }
  
  
}

// Name: ReverseSequence
// Desc: User chooses to reverse either DNA or mRNA to reverse
//       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
//       Calls ReverseStrand on chosen location
// Preconditions: Populated m_DNA or m_mRNA
// Postconditions: Reverses a specific strand replacing in place
void Sequencer::ReverseSequence()
{
  //Variables
  int choice, dnaChoice, mrnaChoice;

  //Print options and take choice
  cout << "Which type of strand to reverse?" << endl;
  cout << "1. DNA" << endl;
  cout << "2. mRNA" << endl;
  cin >> choice;

  //Checks input for 1 or 2
  while(choice < 1 || choice > 2)
    {
      cout << "Invalid Input" << endl;
      cout << "Which type of strand to reverse?" << endl;
      cout << "1. DNA" << endl;
      cout << "2. mRNA" << endl;
      cin >> choice;
    }

  //If choice is DNA
  if(choice == 1)
    {
      //Reverse DNA
      dnaChoice = ChooseDNA();

      m_DNA.at(dnaChoice-1) -> ReverseSequence();
 
    }//If choice is 2
  else if(choice == 2)
    {
      //If mRNA is empty
      if(m_mRNA.size() == 0)
	{
	  //Return since empty
	  cout << "No mRNA to reverse; transcribe first" << endl;
	  return;
	}
      //If not empty, reverse
      mrnaChoice = ChooseMRNA();
      m_mRNA.at(mrnaChoice-1) -> ReverseSequence();
    }
  
}

// Name: ChooseDNA
// Desc: Asks the user to choose one strand to use from loaded DNA strands
// Preconditions: Populated m_DNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseDNA()
{
  //Choice
  long unsigned choice;

  //Prints options
  cout << "What strand to work with?" << endl;
  cout << "Choose 1 - " << m_DNA.size() << endl;
  cin >> choice;

  //Checks for valid input
  while(choice < 1 || choice > m_DNA.size())
    {
      cout << "Invalid Input! Try Again" << endl;
      cin >> choice;
    }

  //Return choice
  return choice;
}

// Name: ChooseMRNA
// Desc: Asks the user to choose one strand to use from translated mRNA strands
// Preconditions: Populated m_mRNA
// Postconditions: Returns index of chosen strand
int Sequencer::ChooseMRNA()
{
  //Choice
  long unsigned choice;
  
  //Prints options
  cout << "What strand to work with?" << endl;
  cout << "Choose 1 - " << m_mRNA.size() << endl;
  cin >> choice;

  //Checks for valid input
  while(choice < 1 || choice > m_mRNA.size())
    {
      cout << "Invalid Input! Try Again" << endl;
      cin >> choice;
    }

  //Return choice
  return choice;

}

// Name: Transcribe
// Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
// A->U, T->A, C->G, G->C (DNA to mRNA)
// Can be called multiple times (will result in multiple mRNA strands)
// Puts the transcribed mRNA strand into m_mRNA
// Note: if this function is called more than once on the same strands of DNA,
// it will add duplicate strands into m_mRNA!
// Preconditions: Populated m_DNA
// Postconditions: Transcribes each strand of m_DNA to m_mRNA
void Sequencer::Transcribe()
{

  string name;
  char element = ' ';

 
  for(long unsigned i = 0; i < m_DNA.size(); i++)
    {
      //Make new strand
      Strand *s = new Strand(m_DNA.at(i) -> GetName());
      
      //Make transcribed strand
      for(int j = 0; j < m_DNA.at(i) -> GetSize();j++)
        {
          element = m_DNA.at(i) -> GetData(j);
	  
          switch(element)
            {
            case 'A':
              name += 'U';
              break;
            case 'C':
              name += 'G';
              break;
            case 'T':
              name += 'A';
              break;
            case 'G':
              name += 'C';
              break;
            }
        }

      //Adds elements to list
      for(long unsigned j = 0;j < name.length();j++)
        {
          s -> InsertEnd(name[j]);
        }
      
      
      //Adds list to vector
      m_mRNA.push_back(s);
      name = "";
    }

  cout << m_DNA.size() << " strands of DNA sucessfully transcribed into new mRNA strands" << endl;
  
  
  
  
}

  // Name: Translate
  // Desc: Iterates through a chosen mRNA strand and converts to amino acids
  // For every three nucleotides in strand, passes them three at a time to Convert
  // Displays each amino acid but does not store the amino acids in the class
  // Preconditions: Populated m_mRNA
  // Postconditions: Translates a specific strand of mRNA to amino acids
void Sequencer::Translate()
{
  // Variables
  long unsigned choice;
  string name, convert;

  //Ask user which strand to translate
  cout << "Which strand to work with?" << endl;
  cout << "Choose 1 - " << m_mRNA.size() << ": " << endl;
  cin >> choice;

  //Validate response
  while(choice < 1 || choice > m_mRNA.size())
    {
      cout << "Invalid Input! Try Again:" << endl;
      cin >> choice;
    }

  //Decrease value to match memory in vector
  choice--;

  //Gets strand string for choice
  for(int i = 0; i < m_mRNA.at(choice) -> GetSize(); i++)
    {
      name += m_mRNA.at(choice) -> GetData(i);
    }

  cout << "***" << m_mRNA.at(choice) -> GetName() << "***" << endl;

  //Does the convert
  for(int i = 0; i < m_mRNA.at(choice) -> GetSize()/3; i++)
    {
      convert = Convert(name.substr(0,3));
      cout << name.substr(0,3) << "->" << convert << endl;

      //Erase first 3 elements
      name.erase(0,3);
      
    }

  cout << "Done translating mRNA " << choice+1 << "'s strand." << endl;


}

// Name: Convert
// Author: Jeremy Dixon
// Date: 3/10/2023
// Desc: Paste this into your Sequencer.cpp for project 3.

string Sequencer::Convert(const string trinucleotide){
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
          (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
          (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
          (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
          (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
          (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
          (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
          (trinucleotide=="UCA")||(trinucleotide=="UCG")||
          (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
          (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}

