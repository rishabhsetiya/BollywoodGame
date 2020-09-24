//Class XII Project - Bollywood Game
#include<fstream.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>
#include<dos.h>

/************************************************************************
	       User Accounts class and related functions here
 ************************************************************************/

class User
{char username[20],password[20];
 int score;
public:
User()
{score=0;}
int get_info();
void display();
void show()
{cout<<"Username : "<<username<<'\n'<<"Password : "<<password<<'\n';}
char* get_username()
{return username;}
char* get_password()
{return password;}
void update_score()
{ score+=50;}
int get_score()
{return score;}

 };

void User::display()
 {int f=0;
  for(int i=0;i<strlen(username);i++)
  if(username[i]==' ')
  f=1;
  if(f==1)
  cout<<"\t\t"<<username<<"\t\t\t"<<score;
  else
  cout<<"\t\t"<<username<<"\t\t\t\t"<<score;}

int User::get_info()
{
 char passcode[20],a=100;  //For confirming password twice;
 int i=0;
 clrscr();
 gotoxy(28,10);
 cout<<"B  O  L  L  Y  W  O  O  D";
 gotoxy(25,15);
 cout<<"Enter username : ";
 gets(username);

 gotoxy(25,17);
 cout<<"Enter password : ";
 while(a>32&&a<127&&i<20)
 {a=getch();
 if(a<=32||a>=127)
 break;
 password[i]=a;
 cout<<'*';
 i++;}
 password[i]='\0';

 a=100;i=0;
 gotoxy(25,19);
 cout<<"Enter password again to confirm : ";
 while(a>31&&a<126&&i<20)
 {a=getch();
 if(a<=32||a>=127)
 break;
 passcode[i]=a;
 cout<<'*';
 i++;}
 passcode[i]='\0';

 gotoxy(25,21);
 if(strcmp(passcode,password)!=0)
 {cout<<"Password does not match";
 return 1;}
 else
 {cout<<"Success \t";
  delay(500);
  return 0;}}

void addaccount()                //To add records in database
{ofstream mf("accounts.dat",ios::binary|ios::app);
 User u;

 if(!mf)
  {cout<<"Error in stream"; getch(); exit(0);}

  if(u.get_info()==0)
 {mf.write((char*)&u,sizeof(User));
  cout<<"Account created";}
  mf.close();
  getch();}

void accounts_menu()
{clrscr();
 gotoxy(28,10);
 cout<<"B  O  L  L  Y  W  O  O  D";
 gotoxy(1,15);
 cout<<"Press 1 : Display all accounts info"<<'\t'
     <<"Press 2 : Change admin details";
 gotoxy(1,17);
 cout<<"Press 3 : Exit to previous menu";
 char a;
 a=getch();
 switch(a)
 {case '1':
 {ifstream mf;
 mf.open("accounts.dat",ios::binary);
 if(!mf)
 {cout<<"error"; getch(); exit(0);}

 User u;clrscr();int i=1;char ch='y';

 mf.read((char*)&u,sizeof(User));
 while(mf&&(ch=='y'||ch=='Y'))
{cout<<'\n'<<'\n'<<i<<'.'<<'\n';
 u.show();i++;
 mf.read((char*)&u,sizeof(User));
 cout<<'\n'<<"Show next record ?(Press Y for 'yes')"; ch=getch();}

 mf.close();
  }
 break;

 case '2':
 {fstream mf;
 mf.open("accounts.dat",ios::binary|ios::in|ios::out);
 User u;
 u.get_info();
 getch();
 mf.write((char*)&u,sizeof(User));
 mf.close();}
 break;
 case '3':break;
 default:"Choice mismatch";}
 }

 void menu(User player);

 void login(User player)
{ clrscr();
  User u;
  char username[20],password[20],a=100,i=0;

  ifstream mf("accounts.dat",ios::binary);
  mf.read((char*)&u,sizeof(User));
  gotoxy(28,10);
  cout<<"B  O  L  L  Y  W  O  O  D";
  gotoxy(25,15);
  cout<<"Enter username : ";
  gets(username);

 gotoxy(25,17);
 cout<<"Enter password : ";
 while(a>32&&a<127&&i<20)
 {a=getch();
  if(a<=32||a>=127)
  break;
  password[i]=a;
  cout<<'*';
  i++;}
  password[i]='\0';
  gotoxy(25,19);
  mf.read((char*)&u,sizeof(User));
  while(mf && strcmpi(username,u.get_username())!=0)
  mf.read((char*)&u,sizeof(User));
  if(strcmpi(username,u.get_username())==0)
   if(strcmpi(password,u.get_password())==0)
    {player=u;
     cout<<"Logged in";}
    else cout<<"Password does not match";
  else cout<<"Account does not exist";
  getch();
  menu(player);}

 void show_useraccounts()
 {clrscr();
  gotoxy(18,10);
  cout<<"NAME"<<'\t'<<'\t'<<'\t'<<'\t'<<"SCORE"<<'\n'<<'\n';
  User p;
  ifstream mf("Accounts.dat",ios::binary);
  if(!mf)
  cout<<"User accounts file not found";

  mf.read((char*)&p,sizeof(User));
  while(mf)
  {p.display();cout<<'\n';
   mf.read((char*)&p,sizeof(User));
   }
   }

/*********************************************************************
	    Movie class declaration and member functions
 *********************************************************************/

int countrecords(); //To count the number of movies in database

class Movie
{static int count;  //number of movies in database
 char title[50],
      actor[50],actress[50],  //for giving hints
      question[50]; //movie title with blanks

 public:

 void show()            // To show the details of a movie
 {cout<<"Title       : "<<title<<'\n'
      <<"Lead Actor  : "<<actor<<'\n'
      <<"Lead Actress: "<<actress<<'\n';}

 void make_question();           //Fill data member 'question' of class Movie

 void get_info()                 //To modify or add to movie database
 {cout<<"Enter title";
  gets(title);
  cout<<"Enter lead actor's name";
  gets(actor);
  cout<<"Enter lead actress's name";
  gets(actress);

  make_question();
  count++;
  }

 void hint();                     //To give hint to player

 void show_question();           // Display movie title with blanks

 void guess(char ch);                  //To fill in the blanks

 char* give_question()
 {return question;}

 char* give_title()
 {return title;}

 int movie_count()
 {return count;}

 void autofillup();
 };

 int Movie::count=countrecords();

 void Movie::hint()         //Give hint to player
 {cout<<"Which hint will you take ?"<<'\n'
      <<"1. Lead Actor"<<'\n'
      <<"2. Lead Actress"<<'\n';
  char a;
  a=getch();
  switch(a)
  {case '1':gotoxy(40,22);
	    cout<<actor;
	    break;
   case '2':gotoxy(40,23);
	    cout<<actress;
	    break;
   default:gotoxy(40,22);
	   cout<<"Hint expired due to choice mismatch";
   }
 }
 void Movie::make_question()   // Fill data member 'question' of class Movie
 {for(int i=0;i<strlen(title);i++)
 if(title[i]=='A'||title[i]=='a'
  ||title[i]=='E'||title[i]=='e'
  ||title[i]=='I'||title[i]=='i'
  ||title[i]=='O'||title[i]=='o'
  ||title[i]=='U'||title[i]=='u')
  question[i]=title[i];
  else if(title[i]==' ')
  question[i]='/';
  else question[i]='_';
  question[i]='\0';
 }

void Movie::show_question()  //Display movie title with blanks
{gotoxy(15,15);
 for(int i=0;i<strlen(question);i++)
 cout<<question[i]<<' ';}

void Movie::guess(char ch)           //To fill in the blanks
{for(int i=0;i<strlen(title);i++)
 if(ch==toupper(title[i])||ch==tolower(title[i]))
 question[i]=title[i];}


void Movie::autofillup()
{for(int i=0;i<strlen(title);i++)
 if(question[i]!='/')
 question[i]=title[i];}

/*******************************************************************
		class Movie declarations end here
 ********************************************************************/
/********************************************************************
	     movie database file functions begin
 *******************************************************************/

void create()                 //To create the movie database
{ofstream mf("movie.dat",ios::binary);
 if(!mf)
 {cout<<"error"; getch(); exit(0);}

 Movie m;clrscr();char ch;

 do{m.get_info();
 mf.write((char*)&m,sizeof(m));
   cout<<"Do you want to add more movies ?";
   cin>>ch;}while(ch=='Y'||ch=='y');

 mf.close();}

void display()              //To view the records in database
{ifstream mf("movie.dat",ios::binary);
 if(!mf)
 {cout<<"error"; getch(); exit(0);}

 Movie m;clrscr();int i=1;char ch='y';

 mf.read((char*)&m,sizeof(Movie));
 while(mf&&(ch=='y'||ch=='Y'))
{cout<<'\n'<<'\n'<<i<<'.'<<'\n';
 m.show();i++;
 mf.read((char*)&m,sizeof(Movie));
 cout<<'\n'<<"Show next record ?(Press Y for 'yes')"; ch=getch();}

 mf.close();}


void append()                //To add records in database
{ofstream mf("movie.dat",ios::binary|ios::app);
 Movie m;

 if(!mf)
  {cout<<"Error in stream"; getch(); exit(0);}

  m.get_info();
  mf.write((char*)&m,sizeof(Movie));

  cout<<"Added";
  mf.close();
  getch();}

void overwrite()    //To overwrite previous record in database
{display();
 fstream mfile("movie.dat",ios::binary|ios::in|ios::out);
 if(!mfile)
 {cout<<"Database missing !";getch(); exit(0);}
  Movie m; int num;
  cout<<"Enter record number to overwrite.";
  cin>>num;
  mfile.seekg((num-1)*sizeof(m),ios::beg);
  mfile.read((char*)&m,sizeof(m));
  m.show();
  cout<<"Are you sure you want to overwrite this record ?";
  char ch;
  cin>>ch;
  if(ch=='Y'||ch=='y')
  {m.get_info();m.show();
   mfile.seekg((num-1)*sizeof(m),ios::beg);
   mfile.write((char*)&m,sizeof(Movie));}
   mfile.close();}

int countrecords()           //To count the number of movies in database
{ifstream mf("movie.dat",ios::binary);
 if(!mf)
 {cout<<"File Not Found... Create file? Y for Yes /any other to exit";
  char ch; ch=getch();
  if(ch=='Y'||ch=='y')
  create();
  else exit(0);}

 mf.seekg(0,ios::end);
 int t=mf.tellg()/sizeof(Movie);
 mf.close();
 return t;
  }

/*********************************************************************
		  movie database file functions end
**********************************************************************/

/*********************************************************************
		   Game Play Functions begin here
 ********************************************************************/
void menu(User player);

void instructions(User player)
{clrscr();
 gotoxy(33,1);
 cout<<"+--------------+";
 gotoxy(33,2);        ;
 cout<<"| INSTRUCTIONS |";
 gotoxy(33,3);
 cout<<"+--------------+";
 cout<<"\n\n";
 cout<<"1. This is a movie guessing game.\n\n"
     <<"2. When you start playing, the vowels in the "
     <<"movie title will be displayed\n"
     <<"   and consonants will be replaced by underscores(_) "
     <<"to represent blank spaces.\n"
     <<"   Separation between words will be indicated by slashes(/).\n\n"
     <<"3. Your objective is to guess all the consonants in the movie title.\n\n"
     <<"4. A track of chances available to you will be kept by the"
     <<" letters of the \n   word 'BOLLYWOOD' being flashed on the screen.\n"
     <<"5. Missing letters indicate incorrect attempts made.\n\n"
     <<"6. If you guess the next letter to disappear, even if it"
     <<" turns out to be wrong,\n   it will not disappear.\n\n"
     <<"7. The names of one actor and one actress who worked in the film can be provided   as hint.\n\n"
     <<"8. You win if you guess all the letters before you are out of chances.\n\n"
     <<"9. You lose if all the letters of the word 'BOLLYWOOD' disappear.";
 getch();
 menu(player);
 }

Movie random_movie()  //Randomly select and return a movie from database
{ifstream mfile;
 mfile.open("movie.dat",ios::binary);
 if(!mfile)
 {cout<<"error"; getch(); exit(0);}
 Movie m; int mno;         //mno stores the number of movie that will be asked
 time_t t;
 srand((unsigned) time(&t));
 mno=rand()%m.movie_count();
 mfile.seekg(mno*sizeof(m),ios::beg);
 mfile.read((char*)&m,sizeof(Movie));
 mfile.close();
 return m;
 }



void round(User player)       //To play one round of this game (how the game works)
{clrscr();
 char score[10]={'B','O','L','L','Y','W','O','O','D'};
 int scorenum=0,i;
 gotoxy(28,10);
 cout<<"B  O  L  L  Y  W  O  O  D";
 char prev[50],now[50],guesschar;
 Movie m=random_movie();
 int flag=1;
 while(flag==1&&scorenum<=9)
 {strcpy(prev,m.give_question());
  m.show_question();
  gotoxy(1,19);
  cout<<"Enter letter or digit to guess"<<'\n'<<'\n';
  gotoxy(1,25);
  cout<<"Press '?/' for hint"<<'\t'<<"Press Space Bar for Main Menu";
  gotoxy(1,21);
  guesschar=getch();

  if(isalnum(guesschar))
 { m.guess(guesschar);
  m.show_question();
  strcpy(now,m.give_question());
  if(strcmp(now,prev)==0&&score[scorenum]!=toupper(guesschar))
  scorenum++;
  }



  if(guesschar=='/')
  m.hint();
  else if(guesschar==' ')
  menu(player);


  gotoxy(28,10);
  for(i=0;i<scorenum;i++)
  cout<<"   ";
  for(i=scorenum;i<=9;i++)
  cout<<score[i]<<' '<<' ';
  cout<<'\n'<<'\n';


  if(scorenum==9)
  {gotoxy(1,19);
   clreol();

  delay(5000);
  break;}
  flag=0;
  for(i=0;i<strlen(m.give_question());i++)
  if(now[i]=='_')
  flag=1;}
  clrscr();
  if(scorenum==9)
  {m.autofillup();
  gotoxy(28,10);

  textcolor(RED);
  cprintf("B  O  L  L  Y  W  O  O  D \n \n");
  m.show_question();
  cout<<'\n'<<'\n';
  cprintf("You lose! :( \n \n");}

  else
  {gotoxy(28,10);

  textcolor(GREEN);
  cprintf("B  O  L  L  Y  W  O  O  D \n \n");
  m.show_question();
  cout<<'\n'<<'\n';
  cprintf("Congratulations! You Win. :) \n");
  player.update_score();}
  delay(5000);
  textcolor(WHITE);
  menu(player);

}

void developer_mode(User player)        //For developer to edit the database
{clrscr();

 char c;
 gotoxy(28,10);
 cout<<"B  O  L  L  Y  W  O  O  D";
 gotoxy(1,15);
 cout<<"Press 1 : Display database contents"<<'\t'
     <<"Press 2 : Overwrite entire database";
 gotoxy(1,17);
 cout<<"Press 3 : Add more movies to database"<<'\t'
     <<"Press 4 : Overwrite on a previous record";
 gotoxy(1,19);
 cout<<"Press 5 : Accounts settings"<<'\t'<<'\t'
     <<"Press 6 : Exit to main menu";
 c=getch();
 switch(c)
 {case '1':display();       break;
  case '2':create();        break;
  case '3':append();        break;
  case '4':overwrite();     break;
  case '5':accounts_menu(); break;
  case '6':menu(player);          break;
  default:cout<<"Choice invalid";}
  developer_mode(player);
}


void select(char a,User player)      //Menu functions
{switch(a)
 {case '1':round(player);
  break;
  case '2':
  break;
  case '3':instructions(player);
  break;
  case '4':
  clrscr();
  User u;
 char name[20],p[20],a=100,i=0;
 ifstream mf("accounts.dat",ios::binary);
 mf.read((char*)&u,sizeof(User));
 gotoxy(28,10);
 cout<<"B  O  L  L  Y  W  O  O  D";
 gotoxy(25,15);
 cout<<"Enter username : ";
 gets(name);

 gotoxy(25,17);
 cout<<"Enter password : ";
 while(a>32&&a<127&&i<20)
 {a=getch();
 if(a<=32||a>=127)
 break;
 p[i]=a;
 cout<<'*';
 i++;}
 p[i]='\0';

 if((strcmp(name,u.get_username())==0 && strcmp(p,u.get_password())==0 )|| (!mf && strcmp(name,"admin")==0&&strcmp(p,"admin")==0))
  developer_mode(player);
  else {gotoxy(25,19);
  cout<<"Access is Denied!\n";
  getch(); menu(player);}
  break;
  case '5':login(player);
	   menu(player);
	   break;
  case '6':addaccount();
	   menu(player);
	   break;
  case '7':show_useraccounts();
	   getch();
	   menu(player);
	   break;
  case '8':exit(0);
 }
 clrscr();}


void menu(User player)
{clrscr();
 gotoxy(28,10);
 cout<<"B  O  L  L  Y  W  O  O  D";
 gotoxy(9,15);
 cout<<"Press 1 : Start new game"<<'\t'
     <<"Press 2 : Continue previous game";
 gotoxy(9,17);
 cout<<"Press 3 : For instructions"<<'\t'
     <<"Press 4 : Enter developer mode"<<'\n';
 gotoxy(9,19);
  cout<<"Press 5 : Login"<<'\t'<<'\t'<<'\t'
      <<"Press 6 : Create new account" <<'\n';
 gotoxy(9,21);
  cout<<"Press 7 : View Scores"<<'\t'<<'\t'
      <<"Press 8 : Exit";
  char a;
  a=getch();
  select(a,player);
  }

/***********************************************************************
		      Gameplay functions end here
 ***********************************************************************/

 void main()
 {User player;
  menu(player); }


