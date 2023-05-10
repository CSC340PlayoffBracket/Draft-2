#include <iostream> 
#include <vector>
#include <fstream>
#include <string>

/********************************************************************************
 *		TITLE: OOP Bi-Directional Linked List
 *		author(s): Grady Walworth, Nadir Ali, Ethan Torres, Joseph Manahan
 *		adapted from: 
 *		other citations:
 *
 *		goal: Create an OOP Bi-Directional Linked List with several useful functions
 *		overview: 
 *
 *
 *
 ********************************************************************************/

using namespace std;

// abstract object, that other classes will inherit
class AbstractObject{
    
    public:
        //AbstractObject(){
        //}
        int getPoints();
        void setPoints(int);
        string getName();
        void setName(string);
        int getRank();
        void setRank(int);

    protected:
        int points;
        int rank = 0;
        string name;
};

// abstract object methods
int AbstractObject::getPoints(){
    return points;
}
void AbstractObject::setPoints(int num){
    points = num;
}
string AbstractObject::getName(){
    return name;
}
void AbstractObject:: setName(string myName){
    name = myName;
}
int AbstractObject::getRank(){
    return rank;
}
void AbstractObject::setRank(int myRank){
    rank = myRank;
}

// node class for linked list
class Node{
    public: 
        AbstractObject newObject;
        Node* next;
        Node* prev;

        Node(){
            next = nullptr;
            prev = nullptr;
        }

};

// player class that inherits abstract object
class Player: public virtual AbstractObject{    
    public:
        // variables
        string lastName;
        int playerNumber;

        // constructor methods
        Player(){
        }
        Player(string newName, int num){
            lastName = newName;
            name = newName;

            playerNumber = num;
            points = num;
            
        }
        Player(string newName){
            lastName = newName;
            name = newName;
            playerNumber = 0;
            points = 0;
        }

        // test print method
        void printNameAndNum();
};
// test print method
void Player::printNameAndNum(){
    cout<<lastName <<": "<<playerNumber<<endl;
}


// linked list class
class LinkedList: public virtual AbstractObject{
    Node* head;
    public:
        LinkedList(){
            head = nullptr;
        }
        string teamName;

        // methods
        string getTeamName();

        void setTeamName(string);

        void addObjectToTail(AbstractObject);

        void printObjectList();

        int sumTeamScores();

        void setNewScores();

        LinkedList returnWinner(LinkedList, LinkedList);

/*
        void insertNode(string);

        void deleteNode(string);

        void search(string);

        void bubbleSort();
*/

};

string LinkedList::getTeamName(){
    return teamName;
}

void LinkedList::setTeamName(string newTeamName){
    teamName = newTeamName;
}

// method to add a node to the end of the linked list
void LinkedList::addObjectToTail(AbstractObject myObject){
    //Node* newNode = new Node(newObject);
    Node* newNode = new Node();
    newNode->newObject = myObject;

    //cout<<"Adding object to linked list"<< endl;
    //cout<<newNode->newObject.getName()<<": "<<newNode->newObject.getPoints()<<endl;

    if (head == nullptr){
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// print linked list
void LinkedList::printObjectList(){
    Node* temp = head;

    if (head == nullptr){
        cout << "List is empty!" << endl;
        return;
    }
    while (temp != nullptr){
        cout<< temp->newObject.getName()<<" scored: "<< temp->newObject.getPoints() << " points"<<endl;
        if (temp->newObject.getRank() != 0){
            cout<<"Rank: "<<temp->newObject.getRank()<<endl;
        }
        cout<<endl;
        temp = temp->next;
    }
}

// sum a team's scores
int LinkedList::sumTeamScores(){
    Node* temp = head;

    int sum = 0;

    if (head == nullptr){
        cout << "List is empty!" << endl;
        return 0;
    }

    while (temp != nullptr){
        sum += temp->newObject.getPoints();
        temp = temp->next;
    }

    return sum;
}

// determine winning team of a game
LinkedList LinkedList::returnWinner(LinkedList team1, LinkedList team2){
    LinkedList temp1 = team1;
    LinkedList temp2 = team2;
    
    cout<<temp1.getTeamName() << " scored: " <<temp1.sumTeamScores()<<" points"<<endl;
    cout<<temp2.getTeamName() << " scored: " <<temp2.sumTeamScores()<<" points"<<endl;
    
    if (temp1.sumTeamScores() >= temp2.sumTeamScores()){
        cout<<temp1.getTeamName()<< " wins!"<<endl;
        cout<<endl;
        return temp1;
    }
    else{
        cout<<temp2.getTeamName()<< " wins!"<<endl;
        cout<<endl;
        return temp2;
    }
}

/*
void LinkedList::setNewScores(int nums[]){
    Node* temp = head;
    int i = 0;
    while (temp != nullptr){
        temp->newObject.setPoints(nums[i]);
        i++;
        temp = temp->next;
    }
}
*/

/*
// assign ranks in the league
void LinkedList::bubbleSortRank(){

}
*/



// main
int main(){

    cout<<endl;

    // import vector of 1000 player names
    ifstream newfile("lastNames.txt");
    vector<string> listOfNames;
    if (newfile.is_open()){
        string newString;
        while(getline(newfile, newString)){
            listOfNames.push_back(newString);
        }
        newfile.close();
    }

    // import vector of team names
    ifstream file("teamNames.txt");
    vector<string> listOfTeams;
    if (file.is_open()){
        string newString;
        while(getline(file, newString)){
            listOfTeams.push_back(newString);
        }
        file.close();
    }

    // create vector of 1000 random numbers, (between 1-1000)
    vector<int> listOfNums;
    for (int i = 0; i < 1000; i++){
        //srand((unsigned) time(NULL));
        //srand(time(0));
        listOfNums.push_back(rand()%1000);
    }
    // create vector of 1000 random scores, (between 5-20)
    vector<int> listOfScores;
    for (int i = 0; i < 1000; i++){
        listOfScores.push_back(5 + rand()%15);
    }
/*
    // test print listOfNums
    for (int i = 0; i < 10; i++){
        cout<<listOfNums.at(i)<<endl;
    }

    // test print listOfScores
    for (int i = 0; i < 10; i++){
        cout<<listOfScores.at(i)<<endl;
    }
*/
    int n;
    int x;
    bool validTournament = false;


    cout<<"How many teams are in your basketball tournament?"<<endl;
    cout<<"(it must be a power of 2 (i.e. 2,4,8,16,32,64,etc and max of 512)"<<endl;
    while (validTournament == false){
        cout<<"Enter the number of teams: ";
        cin>>n;
        x = n;

        if (x > 0){
            while (x % 2 == 0){
                x = x / 2;
            }
            if ( x == 1){
                cout<< n << " teams is a valid tournament"<<endl;
                cout<<endl;
                validTournament = true;
                break;
            }
            else{
                cout<< n << " is not a power of 2, please enter a number that is a power of 2 (i.e. 2,4,8,16,32,64, and max of 128) "<<endl;
            }
        }

        else {
            cout << "Enter a valid positive number" <<endl;
        }
    }



    // count to iterate through listOfNames, listOfNums, and listOfScores
    int count = 0;



// POSSIBLY CREATE A VECTOR OF teams INSTEAD OF AN ARRAY
    LinkedList teams[n];
    for (int i = 0; i < n; i++){
        teams[i].setTeamName(listOfTeams.at(listOfNums.at(count)));
        Player players[5];
        for (int j = 0; j < 5; j++){
            players[j].setPoints(listOfScores.at(listOfNums.at(count)));
            players[j].setName(listOfNames.at(listOfNums.at(count)));
            teams[i].addObjectToTail(players[j]);
            count++;
        }
    }



/////// MAKE A LINKED LIST METHOD THAT RETURNS A LINKED LIST OF THE WINNERS FOR EACH ROUND
//          THEN YOU CAN JUST CALL THAT METHOD A CERTAIN NUMBER OF TIMES DEPENING ON HOW MANY TEAMS ARE IN THE TOURNAMENT

/*
    vector<LinkedList> allTeams;
    for (int i = 0; i < n; i++){
        allTeams.at(i).setTeamName(listOfTeams.at(listOfNums.at(count)));
        Player players[5];
        for (int j = 0; j < 5; j++){
            players[j].setPoints(listOfScores.at(listOfNums.at(count)));
            players[j].setName(listOfNames.at(listOfNums.at(count)));
            allTeams.at(i).addObjectToTail(players[j]);
            count++;
        }
    }

    vector<LinkedList> round1Winners;
    for (int i = 0; i < (n - 1); i+=2){
        LinkedList temp = allTeams.at(i);
        LinkedList temp2 = allTeams.at(i + 1);
        LinkedList winner= winner.returnWinner(temp, temp2);
        //allTeams.at(i)
        round1Winners.push_back(winner);
    }
*/

/*
    int r = 0;
    while (allTeams.size() > 1){
        LinkedList temp = allTeams.at(r);
        LinkedList temp2 = allTeams.at(r + 1);
        if (temp.sumTeamScores() > temp2.sumTeamScores()){
            allTeams.erase(allTeams.begin() + r);
        }
        else {
            allTeams.erase(allTeams.begin() + (r + 1));
        }
        r++;
    }
*/

/*
    for (int i = 0; i < n; i++){
        cout<<endl;
        //teams[i].printObjectList();
        //cout<<teams[i].getTeamName() << " scored " << teams[i].sumTeamScores() << " total points"<<endl;
        cout<<endl;
    }
*/

/*
    // round 1
    vector<LinkedList> round1Winners;
    for (int i = 0; i < n; i += 2){
        LinkedList temp = temp.returnWinner(teams[i], teams[i + 1]);
        round1Winners.push_back(temp);
        //winner.returnWinner(team1, team2);
    }
    // print teams left after round 1
    cout<<"Teams left after round 1: "<<endl;
    for (int i = 0; i < (n/2); i++){
        cout<<round1Winners.at(i).getTeamName()<<endl;
    }

    cout<<endl;
    cout<<endl;

    // round 2
//////////////////////////////////
    for (int i = 0; i < n/2; i++){
        LinkedList temp = round1Winners.at(i);
        while(temp != nullptr){
            
            //temp->newObject.setPoints(listOfScores.at(listOfNums.at(count)));
            count++;
            temp = temp->next;
        }
    }
////////////////////////////////

    vector<LinkedList> round2Winners;
    for (int i = 0; i < (n/2); i += 2){
        LinkedList temp = temp.returnWinner(round1Winners.at(i),round1Winners.at(i+1));
        round2Winners.push_back(temp);
        //winner.returnWinner(team1, team2);
    }
    // print teams left after round 2
    cout<<"Teams left after round 2: "<<endl;
    for (int i = 0; i < (n/4); i++){
        cout<<round2Winners.at(i).getTeamName()<<endl;
    }
    cout<<"Length of round 2 winners: "<<round2Winners.size()<<endl;

    cout<<endl;
    cout<<endl;


    // round 3 
    vector<LinkedList> round3Winners;
    for (int i = 0; i < (n/4); i += 2){
        LinkedList temp = temp.returnWinner(round2Winners.at(i),round2Winners.at(i+1));
        round3Winners.push_back(temp);
        //winner.returnWinner(team1, team2);
    }
    // print teams left after round 3
    cout<<"Teams left after round 3: "<<endl;
    for (int i = 0; i < (n/8); i++){
        cout<<round3Winners.at(i).getTeamName()<<endl;
    }
    cout<<"Length of round 3 winners: "<<round3Winners.size()<<endl;

    cout<<endl;
    cout<<endl;


    // round 4 
    vector<LinkedList> round4Winners;
    for (int i = 0; i < (n/8); i += 2){
        LinkedList temp = temp.returnWinner(round3Winners.at(i),round3Winners.at(i+1));
        round4Winners.push_back(temp);
        //winner.returnWinner(team1, team2);
    }
    // print teams left after round 4
    cout<<"Teams left after round 4: "<<endl;
    for (int i = 0; i < (n/16); i++){
        cout<<round4Winners.at(i).getTeamName()<<endl;
    }
    cout<<"Length of round 4 winners: "<<round4Winners.size()<<endl;
*/


/*
    while ( winners.size() != 1) {
        vector<LinkedList> nextWinners;
        for (int i = 0; i < n; i += 2){
            LinkedList temp = temp.returnWinner(winners.at(i), winners.at(i+1));
            //LinkedList deleteTemp;
            if (temp.sumTeamScores() == winners.at(i).sumTeamScores()){
            //if (temp == winners.at(i)){
                //deleteTemp = winners.at(i+1);
                winners.erase(winners.begin() + (i + 1));
            }
            else{
                winners.erase(winners.begin() + i);
                //deleteTemp = winners.at(i));
            }

            nextWinners.push_back(temp);
            //winners.erase()
            //winner.returnWinner(team1, team2);
        }
    }
*/

/*
    // print team 1
    cout<<endl;
    teams[0].printObjectList();
    cout<<teams[0].getTeamName() << " scored " << teams[0].sumTeamScores() << " total points"<<endl;
    cout<<endl;

    // print team 2
    cout<<endl;
    teams[1].printObjectList();
    cout<<"Team 2 scored " << teams[1].sumTeamScores() << " total points"<<endl;
    cout<<endl;
*/



/*


    // team 1
    LinkedList team1;

    // player 1
    Player team1Player1;
    team1Player1.setPoints(listOfScores.at(listOfNums.at(count)));
    team1Player1.setName(listOfNames.at(listOfNums.at(count)));
    team1.addObjectToTail(team1Player1);
    count++;

    // player 2
    Player team1Player2;
    team1Player2.setPoints(listOfScores.at(listOfNums.at(count)));
    team1Player2.setName(listOfNames.at(listOfNums.at(count)));
    team1.addObjectToTail(team1Player2);
    count++;

    // player 3
    Player team1Player3;
    team1Player3.setPoints(listOfScores.at(listOfNums.at(count)));
    team1Player3.setName(listOfNames.at(listOfNums.at(count)));
    team1.addObjectToTail(team1Player3);
    count++;

    // player 4
    Player team1Player4;
    team1Player4.setPoints(listOfScores.at(listOfNums.at(count)));
    team1Player4.setName(listOfNames.at(listOfNums.at(count)));
    team1.addObjectToTail(team1Player4);
    count++;

    // player 5
    Player team1Player5;
    team1Player5.setPoints(listOfScores.at(listOfNums.at(count)));
    team1Player5.setName(listOfNames.at(listOfNums.at(count)));
    team1.addObjectToTail(team1Player5);
    count++;

    // print team 1
    cout<<endl;
    team1.printObjectList();
    cout<<"Team 1 scored " << team1.sumTeamScores() << " total points"<<endl;
    cout<<endl;



    // team 2
    LinkedList team2;
    Player team2Players[5];

    for (int i = 0; i < 5; i++){
        team2Players[i].setPoints(listOfScores.at(listOfNums.at(count)));
        team2Players[i].setName(listOfNames.at(listOfNums.at(count)));
        team2.addObjectToTail(team2Players[i]);
        count++;
    }

    // print team 2
    cout<<endl;
    team2.printObjectList();
    cout<<"Team 2 scored " << team2.sumTeamScores() << " total points"<<endl;
    cout<<endl;



    // team 3
    LinkedList team3;
    Player team3Players[5];

    for (int i = 0; i < 5; i++){
        team3Players[i].setPoints(listOfScores.at(listOfNums.at(count)));
        team3Players[i].setName(listOfNames.at(listOfNums.at(count)));
        team3.addObjectToTail(team3Players[i]);
        count++;
    }

    // print team 3
    cout<<endl;
    team3.printObjectList();
    cout<<"Team 3 scored " << team3.sumTeamScores() << " total points"<<endl;
    cout<<endl;




    // team 4
    LinkedList team4;
    Player team4Players[5];

    for (int i = 0; i < 5; i++){
        team4Players[i].setPoints(listOfScores.at(listOfNums.at(count)));
        team4Players[i].setName(listOfNames.at(listOfNums.at(count)));
        team4.addObjectToTail(team4Players[i]);
        count++;
    }

    // print team 4
    cout<<endl;
    team4.printObjectList();
    cout<<"Team 4 scored " << team4.sumTeamScores() << " total points"<<endl;
    cout<<endl;

*/





/*
    // league linked list? each node points to the head of a team linked list
    LinkedList league;
    league.addObjectToTail(team1);
    league.addObjectToTail(team2);
    league.addObjectToTail(team3);
    league.addObjectToTail(team4);

    cout<<league.getPoints()<<endl;
*/



/*
    vector<LinkedList> league;
    league.push_back(team1);
    league.push_back(team2);
    league.push_back(team3);
    league.push_back(team4);

    //cout<< league.at(0).sumTeamScores()<<endl;

    for (int i = 0; i < 4; i++){
        cout<< league.at(i).sumTeamScores()<<endl;
    }

    swap(league[0], league[1]);
    cout<<endl;

    for (int i = 0; i < 4; i++){
        cout<< league.at(i).sumTeamScores()<<endl;
    }

    //LinkedList winner = winner.returnWinner(team1, team2);


    vector<LinkedList> tournament;
*/


/*
    LinkedList playerList;
    Player player1("johnny", 24);
    player1.setPoints(24);
    player1.setRank(4);
    cout<<player1.getPoints()<<endl;
    cout<<player1.getName()<<endl;
    //cout<<player1.

    Player player2("Bilbo");
    player2.setPoints(48);
    Player player3("Sol", 17);
    playerList.addObjectToTail(player1);
    playerList.addObjectToTail(player2);
    playerList.addObjectToTail(player3);

    cout<<endl;
    playerList.printObjectList();
    cout<<endl;
*/


    return 0;
}