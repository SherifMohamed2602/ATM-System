#include <iostream>
#include <string.h>
#include <cmath>
#include <assert.h>

using namespace std;

class ATM {

private :
    char account_name[200] ;
    char Card_number[20] ;
    double Amount = 0 ;

public :

 void create_new_acc();
 void Deposit();
 void Withdrawal();
 void Transfer (ATM* );
 void Print_acc_data();
 char GetCard(int i) { return Card_number[i] ;}


};

ATM *A[200] ;
int Num_accounts = 0 ;

void trials(int &n)       // function to check the number of trials made by the user to enter his card number
{
n++ ;
if (n > 10 )
    {
        cout  << " you have exceeded the maximum number of trials  "<< endl; assert(n<=10) ;
    }                                                                                        /* if the number of trials exceeds 10 trials ,
                                                                                                the program will terminate */
}

void checkname(char name[], int n)                //function to check the validity of the account name
{
     if (strlen(name)> 100 || strlen(name)== 0)        /* to check if the name exceeds the 100 character
                                                         limit or if there are no characters entered */
     goto label0 ;
    for(int q = 0 ; q < strlen(name) ; q ++)           //checks each character individually , to make sure all the characters are letters only
if (!(122 >= int (name[q]) && int (name[q]) >= 97 || 90 >= int (name[q]) && int (name[q]) >= 65 || int(name[q]) == 32))
     goto label0 ;

  return ;

  label0 : trials(n) ;        //increase number of wrong entries made by the user
    cout << "not valid input. the name must consist of letters only and at least one character up to 100 , please enter a valid name: " ;
    gets(name) ;   //gets the name again after sending the error message

    return checkname(name , n) ;
}


void checkcard(char card[], int & n)    // checks the validity of the card number
 { int counter = 0 ;

    if (strlen(card) == 10 )     // checks whether the card number is 10 digits or not
 {
   for (int i = 0 ; i < 10 ; i++)
    {
     if ( !(57 >= int (card[i]) && int (card[i]) >= 48)  )  //the number must be digits from 0 to 9
        goto label1;
     if (card[i] == card[i+1]) counter ++ ;
     if (counter == 9 ) goto label1;
    }
     return;
 }
 label1 : trials(n) ;  //increase number of wrong entries made by the user
 cout << "invalid number. Please enter the 10 digits account number" << endl ;
 gets(card) ; return checkcard(card , n) ;    // takes the number again after sending the error message
 }


 int Get( char card[], int i ) // this is the function that finds the account in the array by searching using the card number
 {
     int x ;char Cards[10] ;
   for ( x = 0 ; x < i ; x++ ) {
  for (int z = 0 ; z < 10 ; z++ )
    Cards[z] = A[x]->GetCard(z) ;

    for (int k = 0 ; k < 10 ; k ++)
    { if (card[k] != Cards [k])  goto label2 ;
       }   return x ;
   label2 :
       continue ;
    }

 return -1 ;   // if the card is not found in the array it returns -1
 }


 int checkNum(char number[20], int &n) //checks the validation of the number of operation
 {
    if ( strlen(number) == 1 )   //checks whether the input number is one digit or not
if (number[0] > 48 && number[0] < 54 ) return 1 ;
                                                 /*checks whether the input character is a number between 1 and 5 by
                                                 checking their ASCII code as the numbers are treated as characters*/

   trials(n) ; //increase number of wrong entries made by the user
   cout << "not valid"<<endl ;
   return 0 ;

 }


int checkmoney(char a[])               // the function "Check money" checks whether all the entered data are numbers
 {                                     // and checks for any other errors as multiple decimal dots
  int N=strlen(a);
  int dotnum = 0;
  for (int i = 0 ; i <N ; i++)
   {  if (int(a[i])== 46)
   dotnum ++ ;
     if (!(57 >= int (a[i]) &&  int(a[i]) >= 48 || int(a[i])== 46 ) || dotnum > 1 )   // the characters must be numbers from 0 to 9

          return 0;
   }
   return 1;
 }


void value(char a[], double &Value )    // function to transform the numbers entered as an array of characters into a double value
 {                                     // the numbers are entered as an array of characters, so that we could check them individually
   int N=strlen(a);
   double j=1;
   int dotpos=N;
   Value=0;

      for (int i = 0 ; i <N ; i++)
     {
     if (int(a[i])== 46)
        dotpos=i;}

     for (int i=0; i<  dotpos ;i++)
        Value= Value+ (int (a[i])-48) * pow(10,dotpos-i-1);

     for (int i = dotpos+1 ; i<N;i++)
     { Value= Value+ double(int (a[i])-48) * pow(10,-1*j);
         j++;
     }
 }



int main()
{ char number[20] ;              // The number of operation
int location1 , location2  ;     //Locations of the accounts in the array
char Card_number0[20] , Card_number1[20];
 /* The account card number
 There are two card numbers as they are needed if there's a transfer operation being held. */

int n = 0 ;  // for initializing the number of trials
do { cout <<"1----Create new account"<<endl              // the main interface of the ATM
          <<"2----Deposit"<<endl
          <<"3----transfer to another account"<<endl
          <<"4----withdrawal"<<endl
          <<"5----exit"<<endl;
     cout << "please enter the number of operation: ";
      gets(number);     //gets operation number from user
     int Check = checkNum(number, n) ; // To check whether the number is valid or not
     if (Check == 0 )
        continue ;
      /* if the check is over and the numbers are not valid,
     it returns to the main interface with an error message "invalid" */
 n = 0 ;
     if ( Num_accounts == 0 && number[0] != 49 && number[0] != 53 )
                                                                            /* To check if the user tries to deposit or withdraw or transfer money
                                                                            when there are no accounts in the system, and the system can only
                                                                            work to add new accounts or to exit */
        {
        cout << "there is no accounts in the system, yet. please create your account first " << endl ;
         continue ;
         }
 if ( Num_accounts < 2 && number[0] == 51  )
                                                                            /* To check if the user tries to transfer money
                                                                            when there are less than 2 accounts in the system*/
        {
        cout << "there is no enough accounts in the system to transfer , yet. please create enough accounts first " << endl ;
         continue ;
         }

     if      (number[0] == 49 )    // if the selected operation is 1 i.e create new account
        {
           if (Num_accounts >= 100 )
            {cout << " maximum number of accounts"<< endl ; continue ;}    /* check the number of accounts
                                                                                                   to make sure it is not the maximum number */
      A[Num_accounts] = new ATM ; A[Num_accounts]->create_new_acc() ;
      A[Num_accounts]->Print_acc_data();
      Num_accounts++ ;}

         // a new account is created and the user enters its data , and the data is printed , and the number of accounts increases by one

     else if (number[0] == 50 )    // if the selected operation is 2 i.e deposit

        { n = 0 ;
            label3 :
                cout<< "please enter the account number(10 numbers): " ;      // gets the card number from the user
                             gets(Card_number0) ;
                             checkcard(Card_number0, n) ;     // checks the validity of the number
                             location1 = Get(Card_number0,Num_accounts) ;        /* searches for the account of the user by using the number
                                                                                   and gets the location of the account in the accounts array */
                   if(location1>=0)
                        {
                             A[location1]->Deposit();   //after checking and finding the location of the account the user then deposits the money
                   A[location1]->Print_acc_data();
                        }                              //and the new account data is printed
                   else
                        {
                            trials(n) ;      //increase number of wrong entries made by the user
                            cout << " card number is not in the system"<< endl ;
                            cin.clear();
                            goto label3;
                        }
                    /* if the account number doesn't exist the
                   user enters a new number after the error message appears */
                                                                                                     }

     else if (number[0] == 51 )    // if the selected operation is 3 i.e transfer
        { n = 0 ;
            label4 :
                cout<< "please enter the number of the sending account (10 numbers): " ;
                             gets(Card_number0) ;
                             checkcard(Card_number0, n) ;    /* the user enters the card number of the sender and then the card is checked
                                                                                   then the system gets the location of the card number*/
                             location1 = Get(Card_number0,Num_accounts ) ;
                             if(!(location1>=0))
                             {
                                  trials(n) ;  //increase number of wrong entries made by the user
                                  cout << " card number is not in the system"<< endl ;
                                  goto label4;
                             }

                             n = 0 ;
                             label5:
                                 cout<< "please enter the number of the receiving account (10 numbers): " ;  /* the user enters the card number of
                                                                                                                 the receiver  and is also checked */
                             gets(Card_number1) ;
                             checkcard(Card_number1, n) ;
                             location2 = Get(Card_number1,Num_accounts ) ;                // gets the location of the second card
                             if(!(location2>=0))
                              {
                                  trials(n) ;      //increase number of wrong entries made by the user
                                  cout << " card number is not in the system"<< endl ;
                                  goto label5;
                              }
                             if ( location1 == location2)                                 // if the same card number is both the sender and the receiver
                              {
                                cout << "Not Valid, the sending account is the receiving account " << endl ;
                                goto label4 ;
                              }
                             A[location1]->Transfer(A[location2]);      //then the transfer operation takes place
                              cout << "sending account:"<< endl ;
                             A[location1]->Print_acc_data();
                             cout << "receiving account:"<< endl ;
                              A[location2]->Print_acc_data();

                              // the data of two accounts is printed after the transfer

       }


     else if (number[0] == 52 )    // if the selected operation is 4 i.e withdrawal
        { n = 0 ;
            label6 :
                cout<< "please enter the account number(10 numbers): " ;
                             gets(Card_number0) ;
                             checkcard(Card_number0 , n) ;   // gets the card number and checks it
                             location1 = Get(Card_number0,Num_accounts ) ;      /* searches for the account of the user by using the number
                                                                                   and gets the location of the account in the accounts array */
                             if(location1>=0)
                                {A[location1]->Withdrawal();      /*after checking and finding the location of the account the user
                                                                                   then withdraws the money*/
                                A[location1]->Print_acc_data(); }
                                else
                                    {
                                        trials(n) ;   //increase number of wrong entries made by the user
                                cout << " card number is not in the system"<< endl ;
                                 goto label6 ;
                                    }                                              /*if the card is not in the system it
                                                                                     gets another number from the user */

        }
    else if(number[0]== 53) break; // if the selected operation is 5 terminate the program


} while (1);

    return 0;
}

void ATM::create_new_acc (){ int check , n = 0;              // The function that creates new account
    cout << "please enter the account name: ";

    gets (account_name) ;                             //gets account name from the user
     checkname(account_name, n);                         /* checks the validity of the name*/
    n = 0 ;
    cout<< "please enter the account number(10 numbers): " ;
    label7 :
    gets(Card_number) ;
    checkcard(Card_number, n) ;   // gets the card number from the user
    check = Get(Card_number,Num_accounts) ;         // checks its validity
    if (check > -1 )
        {
         trials(n) ;    //increase number of wrong entries made by the user
         cout << " already exists , please enter a valid card number"<< endl ;
    goto label7 ;
        }
}


void ATM::Deposit()    //The function for depositing in the class ATM
    { int n = 0 ;
    double DepValue ;
    char Dep[100] ;
    label8 :
    cout << "please enter the amount to be deposited: " << endl;
    gets(Dep) ;                           //gets the amount to be deposited from the user
    if  (!checkmoney(Dep) || strlen(Dep)== 0)    //checks the validity of the entered data
      { trials(n) ;      //increase number of wrong entries made by the user
          cout<<"not valid amount"<<endl;
    goto label8;
      }
    value(Dep,DepValue);      // transforms the entered characters into their real double value
Amount += (DepValue*1.01) ;    // then increases the amount of money in the account with a 1% bonus
}


void ATM::Withdrawal()          //The function for withdrawing in the class ATM
{ int n1 = 0 , n2 = 0 ;
    if (Amount == 0 )
        {cout << "this account is empty, You can not withdraw from it "<< endl  ; return ; }
    double WithdrawVal ;
    char Withdraw[100] ;
    label9 :
    cout << "please enter the amount to be withdrawn: " << endl;
    gets (Withdraw) ;                                                  // gets the amount from the user to be withdrawn
    if  (!checkmoney(Withdraw) || strlen(Withdraw)== 0)    // checks the amount's validity
      { trials(n1) ;  //increase number of wrong entries made by the user
          cout<<"not valid amount"<<endl;
    goto label9;
      }
    value(Withdraw,WithdrawVal);    // transforms the entered characters into their real double value
    if (WithdrawVal*1.03 > Amount)
     {trials(n2) ;  //increase number of wrong entries made by the user
         cout << "the amount in your account is not enough, you only have "<< Amount << " in your account " << endl;
         goto label9;} // checks if the amount in the account is sufficient
    else Amount -=  (WithdrawVal*1.03) ;
}


void ATM::Transfer(ATM* A)     //the function in the class ATM that transfers an amount of money between two accounts
{ int n1 = 0 , n2 = 0 ;
    if (Amount == 0 )
        {cout << "the sending account is empty, You can not transfer from it "<< endl  ; return ; }
    char Trans[100] ;
    double TransVal ;
    label10 :
    cout << "please enter the amount to be transferred: " << endl;
    gets(Trans) ;          // gets the amount of money to be transferred as an array of characters
    if  (!checkmoney(Trans) || strlen(Trans)==0)  //checks the validity of the data
      {
          trials(n1) ;     //increase number of wrong entries made by the user
          cout<<"not valid amount"<<endl;
          goto label10;
      }
    value(Trans,TransVal);             // transforms the entered characters into their real double value
    if ( TransVal*1.015 > Amount)  /* checks whether the amount in the sender account is enough to be sent to the receiver*/
       {
        trials(n2) ;     //increase number of wrong entries made by the user
        cout << " the amount in the sending account is not enough, you only have "<< Amount << " in the sending account "<< endl ;
        goto label10;
       }

else {Amount -= (TransVal *1.015 );
A->Amount += (TransVal *.985 ); }
                                   // then the amount of money is transferred between the two accounts with a deduced amount of 3% from both accounts
}


void ATM::Print_acc_data()     // prints acc data LOL XD
{
    cout << "name:"<< account_name<< endl;
    cout <<"Card number: " << Card_number << endl;
    cout <<"amount:"<< Amount << endl;
}
