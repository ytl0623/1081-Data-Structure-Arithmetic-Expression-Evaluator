// 10727139 蘇崇傑 10727124 劉宇廷

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

typedef char str20[20];

struct node{
  string  ch;
  int type;
  node *next;
  
};

bool Error1( char temp ){
  int x = 0;
  
  if( temp == '+' ){
    x= 1;
  }
  else if ( temp == '-' ){
    x = 1;
  }
  else if ( temp == '*' ){
    x = 1;
  }
  else if ( temp == '/' ){
    x = 1;
  }
  else if ( temp == '('){
    x = 1;
  }
  else if ( temp == ')'){
    x = 1;
  }
  else if ( temp >= '0' && temp <= '9' ){
    x = 1;
  }
  else if ( temp == ' '){
    x = 1;
  }

  if ( x == 0 ){
    return true;
  }
  else {
    return false;
  }
  
}

void Error2( char temp, int & Nerror2 ){
  if ( temp == '(' ){
    Nerror2++;
  }
  else if ( temp == ')' ){
    Nerror2--;
  }
  
}

int Priority( string A ){     // 順序 
  if ( A == "+" || A == "-" ){
    return 1;
  }
  else if ( A == "*" || A == "/" ){
    return 2;
  }
  else {
    return 0;
  }
  
}

bool AllisNum( string str ){
  for ( int i = 0; i < str.size(); i++ ){
    int tmp = (int)str[i];
    if ( tmp >= 48 && tmp <= 57 ){
      continue;
    }
    else{
      return false;
	}
  }
  return true;
  
}

void Intopostfix( node * head ){
  string stacks[20];     // 堆疊 
  node *postfix = new node;
  postfix -> next = NULL;
  node* temp = postfix;
  int top = 0;
  
  while ( head != NULL ){
    if ( head -> ch == "(" ){
      top++;
      stacks[top] = head -> ch;
    }
    else if ( head -> ch == "+" || head -> ch == "-" || head -> ch == "*" || head -> ch == "/" ){
      while( Priority( stacks[top] ) >= Priority( head -> ch ) ) {
        postfix -> next = new node;
        postfix = postfix -> next;
        postfix -> next = NULL;
        postfix -> ch = stacks[top];
        top --;
      }
      
      top++;
      stacks[top] = head -> ch;
    }
    else if ( head -> ch == ")" ){
      while( stacks[top] != "(" ) {     // 遇')'輸出至'('
        postfix -> next = new node;
        postfix = postfix -> next;
        postfix -> next = NULL;
        postfix -> ch = stacks[top];
        top--;
      }
      
      stacks[top] = "\0";
      top--;
    }
    else if ( AllisNum( head -> ch ) ){
      postfix -> next = new node;
      postfix = postfix -> next;
      postfix -> next = NULL;
      postfix -> ch = head -> ch;
    }

    head = head -> next;

  }

  while( top > 0 ) {     // 堆疊槽有剩的通通印出來 
    postfix -> ch = stacks[top];
    top--;
    postfix -> next = new node;
    postfix = postfix -> next;
    postfix -> next = NULL;
  }

  cout << "Postfix expression: ";
  temp = temp -> next;

  cout << temp -> ch;
  temp = temp -> next;
  
  while ( temp -> next  != NULL ){
    cout  << " , " << temp -> ch;
    temp = temp -> next;
  }
  
  cout << endl << endl ;

}


int main(){
    cout << "* Arithmetic Expression Evaluator *" << endl;
    cout << "* 0. QUIT                         *" << endl;
    cout << "* 1. Infix2postfix Transformation *" << endl;
    cout << "***********************************" << endl;
    cout << "Input a choice(0, 1):";
    
    str20 command;
    cin >> command;
    string temp;
    char a;
    
    while ( strcmp( command, "0" ) != 0 ){
      if ( strcmp( command, "1" ) == 0 ){
        cout << "Input an infix expression:";
        cin >> a;
		getline( cin ,temp,'\n' );
		temp = a + temp;

        node *head = new node;
        head -> next = NULL;
        node *current = head;
        int i = 0;
        int  longt = temp.size();
        bool errors = false;
        int Nerror2 = 0;
        
        while ( i < longt && !errors ){
          if ( Error1( temp[i] ) ){
            cout << i;
            cout <<"Error 1:" << temp[i] <<"is not a legitimate character." << endl;
            delete head;
            errors = true;
          }
          
          if ( temp[i] == ' ' ){     // skip space
            while ( temp[i] == ' ' && i < longt){
              i++;
            }
          }
          
		  Error2( temp[i], Nerror2 );

          if ( Nerror2 < 0 ) {
            cout << "Error 2 :there is one extra close parenthesis." << endl;
            delete head;
            errors = true;
          }
          
          current -> ch = current -> ch + temp[i];
          
          if ( temp[i] == '+' ||temp[i] == '-' ||temp[i] == '*' ||temp[i] == '/' ){     // set type
            current -> type = 1;
          }
          else if ( temp[i] == '('){
            current -> type = 3;
          }
          else if ( temp[i] == ')'){
            current -> type = 4;
          }

          if ( temp[i] >= '0' && temp[i] <= '9' ){
            current -> type = 2;
            i++;
            while ( temp[i] >='0' && temp[i] <= '9' && i < longt ){
              current -> ch = current -> ch + temp[i];
              i++;
            }
          }
          else {
            i++;
          }

          current -> next = new node;
          current = current -> next;
          current -> next = NULL;
        }

        //Error2( temp[i], Nerror2 );
        
        if ( Nerror2 > 0 ) {
          cout << "Error 2 :there is one extra open parenthesis.";
          delete head;
          errors = true;
        }

        node *error3 = head;     // check infix

        if ( head -> type == 1 || head -> type == 4 ){     // head 
          cout << "Error 3: it is not infix in the parentheses." << endl ;
          errors = true;
          delete head;
        }

        while ( error3 != NULL && !errors ){
          if ( error3 -> type == 1 ){
            if ( error3 -> next -> type == 1 ){     // "+*"
              cout <<"Error 3: there is one extra operator." << endl ;
              errors = true;
            }
            else if ( error3 -> next -> type == 4 ){     // ""
              cout << "Error 3: it is not infix in the parentheses." << endl;
              errors = true;
            }
          }
          else if ( error3 -> type == 2 ){
            if ( error3 -> next -> type == 2 ){     // 數字間沒有運算子 
              cout << "Error 3: it is not infix in the parentheses." << endl;
              errors = true;
            }
            else if ( error3 -> next -> type == 3 ){     // "123(" 
              cout << "Error 3: it is not infix in the parentheses." << endl;
              errors = true;
            }
          }
          else if ( error3 -> type == 3 ){
            if  ( error3 -> next -> type == 1 ){     // "(+"
              cout << "Error 3: it is not infix in the parentheses." << endl;
              errors = true;
            }
          }
          else if ( error3 -> type == 4 ){     // ")123"
            if  ( error3 -> next -> type == 2  ){
              cout << "Error 3: there is one extra operand." << endl;
              errors = true;
            }
          }

          error3 = error3 -> next;
          
          if ( errors ){
            delete head;     // 清不乾淨 
          }
        }

        node *A = head;

        if ( !errors ){
          cout << "It is a legitimate infix expression."<< endl;
          Intopostfix( head );
        }
      } // if
      else {
        cout << "Command does not exist!" << endl;
      }
      
      cout << endl << "* Arithmetic Expression Evaluator *" << endl;
      cout << "* 0. QUIT                         *" << endl;
      cout << "* 1. Infix2postfix Transformation *" << endl;
      cout << "***********************************" << endl;
      cout << "Input a choice(0, 1):";
      cin >> command;
    }
    return 0;
}
