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



    return 0;
}