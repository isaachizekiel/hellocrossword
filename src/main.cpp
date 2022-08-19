#include <cstring>
#include <iostream>
#include <cstdio>
#include <list>
#include <string>


int fact(int num) {
  if (num > 1)  return num * fact(num - 1);
  else return 1;
  
}

struct PuzzleNode {
  const char *str;
  bool isFound = false;
  PuzzleNode *next;
};


PuzzleNode* creatrePuzzleNode(const char *str) {
  PuzzleNode *p = new PuzzleNode;
  p->str = str;
  p->next = nullptr;
  return p;
}

void insertPuzzleNode(PuzzleNode *head, PuzzleNode *p) {
  if (head == nullptr) {
    p->next = nullptr;
  }

  while(head->next != nullptr) head = head->next;

  head->next = p;
  p->next = nullptr; 
    
}

void displayPuzzleNodes(PuzzleNode *head) {  
  while (head != nullptr) {
    printf("%s is found: %d\n", head->str, head->isFound);
    head = head->next;
  }  
}



bool checkPuzzleAnswer(PuzzleNode *head, const char *answer) {  
  while (head != nullptr) {
    printf("checking %s with %s\n", answer, head->str);
    if (0 == strcmp(head->str, answer) && !head->isFound) {
      head->isFound = true;
      return true;
    }
    
    head = head->next;
  }

  return false;
}


PuzzleNode* init() {
  const char *data[4] = {"fruit0", "fruit1", "fruit2", "fruit3"};  
  PuzzleNode *head = creatrePuzzleNode("seed"), *element;

  for (int i = 0; i < 4; i++) {
    element = creatrePuzzleNode(data[i]);
    insertPuzzleNode(head, element);
  }
    
  return head;
}

int main()
{
  auto p = init();
  displayPuzzleNodes(p);
  
  bool quit = false;
  std::string ans;
  bool correct;
  
  while (!quit) {
    std::cin >> ans;

    if (ans == "e" || ans == "exit") {
      quit = true;
      break;      
    }
    
    correct = checkPuzzleAnswer(p, ans.c_str());
    
    if (correct) {
      displayPuzzleNodes(p);
    }
    
  }
  
  return 0;
}





































