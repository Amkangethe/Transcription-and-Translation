// Name: Strand.cpp
// Author: Allan Kangethe
// Date: 4/3/2023
// Desc: The Strand is the one linked list class for this project.


#include "Strand.h"
#include <iostream>
using namespace std;
 
// Default Constructor
Strand::Strand()
{
  m_name = "Empty Strand";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Overloaded Constructor
Strand::Strand(string name)
{
  m_name = name;
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Destructor
Strand::~Strand()
{
  // Makes new node.
  Node *curr = m_head;

  // While current node isn't null.
  while(curr != nullptr)
    {
      // Current node iterates linked list
      m_head = curr;
      curr = curr -> m_next;

      // Node head is continually pointing to next node and is delete. Effectively deleting node tail.
      delete m_head;
    }

  // Set all variables to null or default values.
  m_name = "Empty Strand";
  m_head = nullptr;
  m_tail = nullptr;
  m_size = 0;
}

// Takes in a char. Creates a new node. Inserts node at the end of strand. Inreases size.
void Strand::InsertEnd(char data)
{
  // Creates new node
  Node *newNode = new Node();
  newNode -> m_next = nullptr;
  newNode -> m_data = data;

  //If linked list is empty
  if(m_head == nullptr)
    {
      //First node is new node
      m_head = newNode;
      m_size++;
    }
  //Else list is not empty
  else
    {
      // Temp Node
      Node *temp = m_head;

      //Tranverses till last node
      while(temp -> m_next != nullptr)
	{
	  temp = temp -> m_next;
	}
      //Adds new node at end
      temp -> m_next = newNode;
      m_size++;
      //cout << "Added new element, data is " << temp -> m_next -> m_data << endl;
    }
  
}

// Returns name of strand.
string Strand::GetName()
{
  return m_name;
}

// Returns size of strand.
int Strand::GetSize()
{
  return m_size;
}

// Reverses the strand. Strand sequence is reversed in place.
void Strand::ReverseSequence()
{

  //variables
  Node *curr = m_head;
  Node *prev = nullptr;
  Node *next = nullptr;

  // Makes sure current doesn't equal nullptr
  while(curr != nullptr)
    {
      //Strore value current node is pointing to.
      next = curr -> m_next;
      //Reverses the current node's pointer.
      curr -> m_next = prev;
      // Moves the pointers one posistion up.
      prev = curr;
      curr = next;
    }
  m_head = prev;
  
}

// Returns data at node index of strand.
char Strand::GetData(int nodeNum)
{
  // Creates temp node.
  Node *curr = m_head;

  for(int i = 0; i < nodeNum; i++)
    {

    
      if(curr -> m_next != nullptr)
	{
	  curr = curr -> m_next;
	}
    }

  return curr -> m_data;
}

ostream &operator<< (ostream &output, Strand &myStrand)
{
  Node *temp = myStrand.m_head;
  for(int i = 0; i < myStrand.m_size; i++)
    {
      // Create output.
      output << temp -> m_data << ",";

      // Iterates to next node and runs loop again.
      temp = temp -> m_next;
    }

  return output;
  
}
