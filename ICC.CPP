#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>
void welcome()
{
cout<<"\n\n\n\n\t\t  PROJECT ON ICC WORLD CUP TEAM MANAGEMENT"<<endl;
cout<<        "\t\t   ====================================="<<endl;
cout<<"\n\t\t       DELHI TECHNOLOGICAL UNIVERSITY"<<endl;
cout<<        "\t\t   ====================================="<<endl;
cout<<"\n\n\t\t\tMADE BY :- ARPIT GARG ";
cout<<"\n\n\t\t\tROLL NO :- 2K20/B17/08";
cout<<"\n\n\n\n\n\t\t\t\tpress any key to continue";
}
class Teams
{
      int tid;
      int matchwin;
      int matchplay;
      float winper;
      char tname[50];
      char owners[100];
      void calcwinper()
{
    winper=((float)matchwin/(float)matchplay)*100;
}
public:
	      void setTeams();
	      void editteam();
	      void displayTeams();
	      void edittid();
	      int gettid();
	      char* gettname();
};
void Teams::edittid()
{
     tid+=1;
}


int Teams::gettid()
{
     return tid;
}



char* Teams::gettname()
{
return tname;
}


int getteamid()
{
     Teams t;
      fstream file("teams.dat",ios::in|ios::binary);
      file.seekg(0,ios::end);
      int pos=(file.tellg()/sizeof(t))+1;
      file.close();
      return pos;
}
void Teams::setTeams()
{
clrscr();
tid=getteamid();
cout<<"\nTeam ID : "<<tid<<endl;
cout<<"-------------";
cout<<"\n Enter Team Name (max. size to 6)"<<endl;
cout<<":";
gets(tname);
cout<<"Enter Owners details(max. size to 6 ):";
gets(owners);
cout<<"Enter No. of Matches Played :";
cin>>matchplay;
cout<<"Enter No. of Macthes Win :";
cin>>matchwin;
calcwinper();
}


void Teams::editteam()
{ clrscr();
cout<<"\nTeam ID :";
cout<<"\nEnter New Team Name (Blank, if no change) :";
char t[100];
gets(t);
if(strcmpi(t,"")!=0)
		strcpy(tname,t);
cout<<"Enter Owners Details(Blank, if no change) :";
gets(t);
if(strcmpi(t,"")!=0)
	     strcpy(owners,t);


cout<<"Enter New No. of Match Played : ";
cin>>matchplay;
cout<<"Enter New No. of Matches Win : ";
cin>>matchwin;

calcwinper();
}


void Teams::displayTeams()
{
     calcwinper();
     cout<<tid<<"          "<<tname<<"        "<<owners<<"     "<<matchplay<<"               "<<matchwin<<"             "<<winper<<endl;
}


void addteam()
{  clrscr();
	 Teams t;
	  char ch;
	  fstream file("Teams.dat",ios::app|ios::binary);
	  t.setTeams();
	  file.write((char*)&t,sizeof(t));
	  t.edittid();


	  file.close();
}


void displayallteams()
{    clrscr();
     Teams t;
     cout<<"\n\n\n\n\n\t\t\tDISPLAY OF ALL TEAMS INFO"<<endl;
     cout<<                        "\t\t\t================================"<<endl;
     cout<<"TEAM ID  TEAM NAME      OWNER     TOTAL MATCH   MATCH WIN  WIN PERCENTAGE"<<endl;


     fstream file("Teams.dat",ios::in|ios::binary);
     while(file.read((char*)&t,sizeof(t)))
{
	      t.displayTeams();
}
file.close();
}

void searchteam()
{
	   clrscr();
	   Teams t;
	   fstream file("Teams.dat",ios::in|ios::binary);
	   char tname[50];
	   cout<<"\nEnter Team Name to Search : ";
	   gets(tname);
	     cout<<"\n\n\n\n\n\t\t\tDISPLAY OF CURRENT TEAMS INFO"<<endl;
	     cout<<                      "\t\t\t=================================="<<endl;
     cout<<"TEAM ID  TEAM NAME      OWNER     TOTAL MATCH   MATCH WIN  WIN PERCENTAGE"<<endl;




	   while(file.read((char*)&t,sizeof(t)))
	    {
			if(strcmpi(tname,t.gettname())==0)
			{
				     t.displayTeams();
				     file.close();
				     return;
			}
	   }
	   file.close();
	   cout<<"\n\nTeam not found .......";
	   getch();


}


void editteam()
{          clrscr();
	   Teams t;
	   fstream file("Teams.dat",ios::in|ios::out|ios::binary);
	   char tname[50];
	   cout<<"\nEnter Team Name to Edit : ";
	   gets(tname);
	   file.seekg(0);
	   while(file.read((char*)&t,sizeof(t)))
	    {
			    if(strcmpi(tname,t.gettname())==0)
			    {
				     t.editteam();
				     file.seekp(file.tellg()-sizeof(t));
				     file.write((char*)&t,sizeof(t));
				     file.close();
				     return;
			    }
	    }
	    file.close();
	   cout<<"\n\nTeam not found ......";
	   getch();


}


void deleteteam()
{  clrscr();

	       Teams t;
		fstream file("Teams.dat",ios::in|ios::binary);
		fstream tfile("tTeams.dat",ios::out|ios::binary);
		char tname[50];
		cout<<"\n To delete all the members of the particular team (TEAM NAME) ";
		gets(tname);
		int f=0;

	       while(file.read((char*)&t,sizeof(t)))
	       {
			      if(strcmpi(tname,t.gettname())!=0)
			      {
					tfile.write((char*)&t,sizeof(t));
			       }
			     else
					 f=1;
	       }
	       file.close();
	       tfile.close();
	       if(f==0)
		    cout<<"\n\n Team not found .......";
	      else
	      {
			    remove("Teams.dat");
			    rename("tTeams.dat","Teams.dat");
	      }
}


void deleteallteam()
{  clrscr();

	       Teams t;
		fstream file("Teams.dat",ios::in|ios::binary);
		fstream tfile("tTeams.dat",ios::out|ios::binary);
			    remove("Teams.dat");
			    rename("tTeams.dat","Teams.dat");

}



void teammenu()
{
	      int ch=1;
	      while(ch!=0)
	     {
			   clrscr();
			      cout<<"\n\n";
			      cout<<"\t\t       TEAM MENU"<<endl;
			   cout<<"\t\t       =========="<<endl;


			   cout<<"\n\n\t\t\t 1. Add Team Details\n\t\t\t 2. Search Team Details\n";
			   cout<<"\t\t\t 3. Modify Team Details\n\t\t\t 4. Delete Team\n\t\t\t 5. Delete All Teams\n\t\t\t 6.Display All Teams";
			   cout<<"\n\t\t\t 0. Exit \n\t\t\t Enter your choice{0 to 6} : ";
			   cin>>ch;
	   if(ch!=0)
	     {
		switch(ch)
	     {
			case 1:                addteam();
						     break;
			case 2:                searchteam();
						     break;
		       case 3:                 editteam();
						     break;
		       case 4:                 deleteteam();
						     break;
		       case 6:                 displayallteams();
						     break;
		       case 5:                 deleteallteam();
						     break;
		       default:
		       cout<<"wrong choice";
	     }
	     }
	     cout<<"\n\n press a key to continue ....";
	     getch();
     }

}


class Player
{
	     int pid;
	     int runs;
	     int rung;
	     int wkt;
	     int match;
	     int inns;
	     int batavg,bowlavg;
	    char tname[50],pname[50],type;
	    void calcavg();
	     public:
			void setPlayer();
			void editPlayer();
			void displayPlayer();
			int getpid();
			char* getpname();
			char* gettname();



};


int Player::getpid()
{
	 return pid;
}
char* Player::getpname()
{
	return pname;
}

char* Player::gettname()
{
		return tname;
}
void Player::calcavg()
{ if(runs!=0)
batavg=((float)runs/(float)inns);
else
batavg=0.0;
if(wkt!=0&&rung!=0)
bowlavg=((float)rung/(float)wkt);
else
bowlavg=0.0;
}
int getplayerid()
{
		 Player t;
		 fstream file("Players.dat",ios::in|ios::binary);
		 file.seekg(0,ios::end);
		 int pos=(file.tellg()/sizeof(t))+1;
		 file.close();
		 return pos;
}

void Player::setPlayer()
{         clrscr();
	  pid= getplayerid();
	  cout<<"\nPlayer ID : "<<pid<<endl;
	  cout<<"----------------";
	  cout<<"\nEnter Player Name :(max. size 7) ";
	  gets(pname);
	  cout<<"Enter Team Name :(max. size 6)";
	  gets(tname);
	  cout<<"Enter No. of Matches Played : ";
	  cin>>match;
	  cout<<"Enter No. of Innings Played : ";
	  cin>>inns;
	  cout<<"Enter Speciality((B)atsman/Bo(w)ler) : ";
	  type=getche();
	  cout<<"\n Enter Runs Scored : ";
	  cin>>runs;
	  cout<<"Enter Runs Given(0, if a batsman) : ";
	  cin>>rung;
	  cout<<"Enter Wickets Taken(0, if a batsman) : ";
	  cin>>wkt;
	  calcavg();

}

void Player::editPlayer()
{           clrscr();
	    cout<<"\nPlayer ID : "<<pid;
	    cout<<"\nEnter New Team Name(Blank, if no change) : ";
	    char t[100];
	    gets(t);
	    if(strcmpi(t,"")!=0)
			   strcpy(tname,t);
	   cout<<"Enter New No. of Mathes Played : ";
	   cin>>match;

	  cout<<"Enter New No. of Innings Played : ";
	  cin>>inns;
	  cout<<"Enter New Runs Scored : ";
	  cin>>runs;
	  cout<<"Enter New Wickets Taken(0, if a batsman) : ";
	  cin>>wkt;


}


void Player::displayPlayer()
{   calcavg();
    cout<<"\n"<<pid<<"    "<<pname<<"\t  "<<tname<<"\t  "<<match<<"\t  "<<inns<<"\t  "<<runs<<"\t  "<<rung<<"\t  "<<wkt<<"\t  "<<batavg<<"\t  "<<bowlavg;
}

void addplayer()
{             clrscr();
	      Player t;
	      char ch;
	      fstream file("Players.dat",ios::app|ios::binary);
	  t.setPlayer();
	  file.write((char*)&t,sizeof(t));




	      file.close();
}


void displayallplayer()
{            clrscr();
	     Player t;
	      cout<<"\n\n\n\n";
	      cout<<"\t\t\t DISPLAY INFO OF ALL TEAMS"<<endl;
	      cout<<"\t\t\t==========================="<<endl;
	      cout<<"P.ID  P.NAME     TEAM\t  M.PLAY   I.PLAY  RUNS   RUNG   WKTS   BATAVG   BOWLAVG\n";
	      fstream file("Players.dat",ios::in|ios::binary);
	     while(file.read((char*)&t,sizeof(t)))
	     {
		    t.displayPlayer();
	     }
	     file.close();
}

void searchplayer()
{        clrscr();
	 Player t;
	 fstream file("Players.dat",ios::in|ios::binary);
	 char tname[50];
	 cout<<"\n Enter Player Name to Search : ";
	 gets(tname);
	 cout<<"\n\n\n\t\t\tDISPLAY SPECIFIC PLAYER SEARCHED"<<endl;
	   cout<<"\t\t\t==========================="<<endl;
	      cout<<"P.ID  P.NAME     TEAM\t  M.PLAY   I.PLAY  RUNS   RUNG   WKTS   BATAVG   BOWLAVG\n";


	 while(file.read((char*)&t,sizeof(t)))
	 {
		  if(strcmpi(tname,t.getpname())==0)
		  {
				t.displayPlayer();
				file.close();

		  }
		  else
			  cout<<"\n\nPlayer not found .......";
	  }
	  file.close();

	  getch();
}


void searchplayerinteam()
{          clrscr();
	   Player t;
	   fstream file("Players.dat",ios::in|ios::binary);
	   char tname[50];
	   cout<<"\nEnter Team Name to List Players : ";
	   gets(tname);
		 cout<<"\n\n\n\t\t\t DISPLAY PLAYERS SEARCHED IN SPECIFIC TEAM"<<endl;
		 cout<<"\t\t\t============================================"<<endl;
	       cout<<"P.ID  P.NAME     TEAM\t  M.PLAY   I.PLAY  RUNS   RUNG   WKTS   BATAVG   BOWLAVG\n";
	       while(!file.eof())
	       {
	   while(file.read((char*)&t,sizeof(t)))
	   {
			if(strcmpi(tname,t.gettname())==0)
			{
					       t.displayPlayer();
			}
			 else
			   cout<<"\n\nTeam not found ......";
	    }
	    }
	    file.close();

	    getch();
}


void editplayer()
{          clrscr();
	   Player t;
	   fstream file("Players.dat",ios::in|ios::out|ios::binary);
	   char tname[50];
	   cout<<"\nEnter Player Name to Edit : ";
	   gets(tname);
	   file.seekg(0);
	   while(file.read((char*)&t,sizeof(t)))
	   {
			if(strcmpi(tname,t.getpname())==0)
			{
					       t.editPlayer();
					       file.seekg(file.tellg()-sizeof(t));
					       file.write((char*)&t,sizeof(t));
					       file.close();
					       return;
			 }
	    }
	    file.close();
	    cout<<"\n\nPlayer not found ......";
	    getch();
}

void deleteplayer()
{           clrscr();
	    Player t;
		fstream file("Players.dat.dat",ios::in|ios::binary);
		fstream tfile("tPlayers.dat",ios::out|ios::binary);
		char kname[50];
		cout<<"\nEnter Player Name to Delete : ";
		gets(kname);
		int f=0;

	       while(file.read((char*)&t,sizeof(t)))
	       {
			      if(strcmpi(kname,t.getpname())!=0)
			      {
					tfile.write((char*)&t,sizeof(t));
			       }
			     else
					 f=1;
	       }
	       file.close();
	       tfile.close();
	       if(f==0)
		    cout<<"\n\n Player not found .......";

	      else
	      {
			    remove("Players.dat.dat");
			    rename("tPlayers.dat","Players.dat");
	      }


 }
 void deleteallplayer()
{           clrscr();
	    Player t;
		fstream file("Players.dat",ios::in|ios::binary);
		fstream tfile("tPlayers.dat",ios::out|ios::binary);

			    remove("Players.dat");
			    rename("tPlayers.dat","Players.dat");



 }


void playermenu()
{
	      int ch=1;
	     while(ch!=0)
	     {
			   clrscr();
			      cout<<"\n\n";
			      cout<<"\t\t PLAYER MENU"<<endl;
			   cout<<"\t\t================ "<<endl;


			   cout<<"\n\n\t\t\t1. Add Player Details\n";
			   cout<<"\t\t\t2. Search Player Details\n";
			   cout<<"\t\t\t3. Modify Player Details\n";
			   cout<<"\t\t\t4. Delete Specific Players\n";
			   cout<<"\t\t\t5. Delete All Players\n";
			   cout<<"\t\t\t6. Display Players in a Specific Team\n";
			   cout<<"\t\t\t7. Display all Players\n";
			   cout<<"\n\n\t\t\t0. Exit \n";

			   cout<<"\t\t\tEnter your choice{0 to 6} : ";
			   cin>>ch;
	     if(ch!=0)
	     {
		switch(ch)
	     {
			case 1:                addplayer();
						     break;
			case 2:                searchplayer();
						     break;
			case 3:                 editplayer();
						     break;
			case 4:                 deleteplayer();
						     break;
			case 5:                 deleteallplayer();
						     break;
			case 6:                 searchplayerinteam();
						     break;
			case 7:                 displayallplayer();
						     break;
			default:
			{
		cout<<"wrong choice";
            }    
	     }
	     }
	     cout<<"\n\n press a key to continue ....";
	     getch();
     }
}

class Venue
{
	    int vid;
	    int matchplay;
	    long capacity;
	    char tname[50];
	    char vname[50];
public:
	     void setvenue();
	     void editvenue();
	     void displayvenue();
	     int getvid();
	     char* gettname();
	     char* getvname();
};

int Venue::getvid()
{
	       return vid;
}

char* Venue::gettname()
{
	     return tname;
}


char* Venue::getvname()
{
	     return vname;
}

int getvenueid()
{
      Venue t;
      fstream file("Venues.dat",ios::in|ios::binary);
      file.seekg(0,ios::end);
      int pos=(file.tellg()/sizeof(t))+1;
      file.close();
      return pos;
}
void Venue::setvenue()
{
      vid=getvenueid();
      cout<<"\nVenue ID : "<<vid<<endl;
      cout<<"---------------";
      cout<<"\n Enter Name of Stadium :(max.size 11)";
      gets(vname);
      cout<<"Enter Home Team :(max. size 6)";
      gets(tname);
      cout<<"Enter No. of Matches Played :";
      cin>>matchplay;
      cout<<"Enter Total capacity of Ground :";
      cin>>capacity;
}
void Venue::editvenue()
{
      cout<<"\nVenue ID :"<<vid;
      cout<<"\nEnter New Name for Stadium(Blank, if no change) :";
      char t[100];
      gets(t);
      if(strcmpi(t,"")!=0)
      strcpy(vname,t);
      cout<<"Enter New Home Team(Blank, if no change) :";
      gets(t);
      if(strcmpi(t,"")!=0)
      strcpy(tname,t);
      cout<<"Enter New No. of Matches Played : ";
      cin>>matchplay;
      cout<<"Enter New Capacity of Ground : ";
      cin>>capacity;
}
void Venue::displayvenue()
{
	  cout<<"\n"<<vid<<"\t  "<<vname<<"\t "<<tname<<"\t  "<<matchplay<<"\t  "<<capacity;
}

void addvenue()
{        clrscr();
	 Venue t;
	 char ch;
	  fstream file("Venues.dat",ios::app|ios::binary);
	  t.setvenue();
	   file.write((char*)&t,sizeof(t));

	  file.close();
}
void displayallvenue()
{    clrscr();
     Venue t;
     cout<<"\n\n\n"<<endl;
     cout<<"\t\t\t DISPLAY DETAILS OF ALL VENUE"<<endl;
     cout<<"\t\t\t==============================="<<endl;
      cout<<"V.ID \t  V.NAME    \t   T.NAME\t M.PLAY\t CAPACITY\n"<<endl;
     fstream file("Venues.dat",ios::in|ios::binary);
     while(file.read((char*)&t,sizeof(t)))
{
	      t.displayvenue();
}
file.close();
}
void searchvenue()
{          clrscr();
	   Venue t;
	   fstream file("Venues.dat",ios::in|ios::binary);
	   char tname[50];
	   cout<<"\nEnter Stadium Name to Search : ";
	   gets(tname);
	    cout<<"\n\n\n"<<endl;
	    cout<<"\t\t\t DISPLAY DETAILS OF SEARCHED VENUE"<<endl;
	    cout<<"\t\t\t==============================="<<endl;
	    cout<<"V.ID \t  V.NAME    \t   T.NAME\t M.PLAY\t CAPACITY\n"<<endl;

	   while(file.read((char*)&t,sizeof(t)))
	    {
			if(strcmpi(tname,t.getvname())==0)
			{
				     t.displayvenue();
				     file.close();

			}
	   }
	   file.close();
	   cout<<"\n\nStadium not found .......";
	   getch();
}
void editvenue()
{          clrscr();
	   Venue t;
	   fstream file("Venues.dat",ios::in|ios::out|ios::binary);
	   char tname[50];
	   cout<<"\nEnter Stadium Name to Edit : ";
	   gets(tname);
	   file.seekg(0);
	   while(file.read((char*)&t,sizeof(t)))
	    {
			    if(strcmpi(tname,t.getvname())==0)
			    {
				     t.editvenue();
				     file.seekp(file.tellg()-sizeof(t));
				     file.write((char*)&t,sizeof(t));
				     file.close();
				     return;
			    }
	    }
	    file.close();
	   cout<<"\n\nStadium not found ......";
	   getch();
}


void deletevenue()
{
		clrscr();
		Venue t;
		fstream file("Venues.dat",ios::in|ios::binary);
		fstream tf("tv.dat",ios::out|ios::binary);
		char tname[50];
		cout<<"\nEnter Stadium Name to Delete : ";
		gets(tname);
		int f=0;
		while(file.read((char*)&t,sizeof(t)))
	       {
		 if(strcmpi(tname,t.getvname())!=0)
		    {
		      tf.write((char*)&t,sizeof(t));
		      }
		 else
		 f=1;
	       }
	       file.close();
	       tf.close();
	       if(f==0)
		    cout<<"\n\n Venue not found .......";
	       else
	      {
			    remove("Venue.dat");
			    rename("tv.dat","Venues.dat");
	      }
}
 void deleteallvenue()
{
	     clrscr();
	    Venue t;
		fstream file("Venues.dat",ios::in|ios::binary);
		fstream apf("apv.dat",ios::out|ios::binary);

			    remove("Venues.dat");
			    rename("apv.dat","Venues.dat");



 }



void venuemenu()
{
	      int ch=1;
	     while(ch!=0)
	     {
			   clrscr();
			   cout<<"\n\n";
			   cout<<"\t\t VENUE MENU"<<endl;
			   cout<<"\t\t================ "<<endl;
			   cout<<"\n\n\n\t\t1. Add Venue Details\n";
			   cout<<"\t\t2. Search Venue Details\n";
			   cout<<"\t\t3. Modify Venue Details\n";
			   cout<<"\t\t4. Delete Venue\n";
			   cout<<"\t\t5. Delete All Venue\n";
			   cout<<"\t\t6. Display all Venues\n"<<endl;
			   cout<<"\n\t\t0. Exit \n";
			   cout<<"\n\n\t\tEnter your choice{0 to 5} : ";
			   cin>>ch;
	    if(ch!=0)
	    {
		switch(ch)
	     {
			case 1:                addvenue();
						     break;
			case 2:                searchvenue();
						     break;
		       case 3:                 editvenue();
						     break;
		       case 4:                 deletevenue();
						     break;
		       case 5:                 deleteallvenue();
						     break;
		       case 6:                 displayallvenue();
						     break;
		       default:
					       cout<<"wrong choice";

	     }
	     }
	     cout<<"\n\n press a key to continue ....";
	     getch();
     }
}

void main()
{            clrscr();
	     welcome();
	     getch();
	     int ch=1;
	     while(ch!=0)
	     {
		 clrscr();
		 cout<<"\n\n\n\n\n\n";
		 cout<<"\t\t\tMAIN MENU"<<endl;
		 cout<<"\t\t\t===========";
		 cout<<"\n";
		 cout<<"\t\t\t1. Team Menu\n";
		 cout<<"\t\t\t2. Player Menu\n";
		 cout<<"\t\t\t3. Venue Menu\n";
		 cout<<"\t\t\t0. Exit\n";
		 cout<<"\n\n\n\n\n\n\n\n\n";
		 cout<<"\t\t\t\t\t\tEnter your choice {0 to 3} : ";
		 cin>>ch;
	     if(ch!=0)
	     {
	     switch(ch)
	     {
			case 1:           teammenu();
						break;
			case 2:           playermenu();
						break;
			case 3:           venuemenu();
						break;
		       default:
		       cout<<"wrong choice";
	      }
	      }
  }

}


