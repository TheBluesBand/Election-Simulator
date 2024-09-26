#define _USE_MATH_DEFINES
#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include "header.h"
using namespace std;

//Picks a random int between two values
int BasicRandom::random_Int(int _min, int _max){
    //Generates a number between the min and max including eachother
    return rand()%(_max-_min + 1) + _min;
}

//Picks a random float between two values
float BasicRandom::random_Float(int _min, int _max){
    //Generates a number between the min and max including eachother
    return (rand()%(_max-_min + 1) + _min)/100;
}

//Picks a random boolean value
bool BasicRandom::random_Bool(){
    int boolean = rand()%(2-1 + 1) + 1;
    if (boolean == 1){
        return false;
    } else {
        return true;
    }
}
/*

    Stances are used in either a Party or Electorate as a way
    to represent there stance on an issue

    Approach and Signifcance together makes an x,y coordinate
    on an graph. This is used to show stances on a 2 dimensional
    level.

    Approach: X axis on the graph
    Significance: Y axis on the graph
    Radius: Is used to calculate the size of the dot
    on the graph (Never used in the code but is important)
    if I was to ever add a visual element to this program
*/
Stance::Stance(){
    this->approach = 5.0;
    this->significance = 5.0;
    this->radius = 1.0;
    //CALLS BLANK CONSTRUCTOR FOR Issue 'relatedIssue'
}

Stance::Stance(float a, float s, Issue i){
    this->approach = a;
    this->significance = s;
    this->radius = 0;
    this->RelatedIssue = i;
}

Stance::Stance(float a, float s, float r){
    this->approach = a;
    this->significance = s;
    this->radius = r;
    //CALLS BLANK CONSTRUCTOR FOR Issue 'relatedIssue'
}

Stance::Stance(float a, float s, float r, Issue ri){
    this->approach = a;
    this->significance = s;
    this->radius = r;
    this->RelatedIssue = ri;
}

void Stance::updateRadius(int populatiry){
    this->radius = ((float)populatiry/4000);
}

float Stance::returnSignificance(){return significance;}
void Stance::changeSignificant(float sign){this->significance += sign;}
float Stance::returnApproach(){return approach;}
void Stance::changeApproach(float appro){this->approach += appro;}
float Stance::returnRadius(){return radius;}
void Stance::chanceRelatedIssue(Issues r){RelatedIssue.changeIssueType(r);}
float Stance::calCircumference(){return (2 * M_PI * radius);}
Issue Stance::returnRelatedIssue(){return RelatedIssue;}
//Used to return the Issue enum as a string. Used for display purposes
string Stance::returnRelatedIssueStr(){
    if (RelatedIssue.getIssueType() == ECONOMY_FALLING){
        return "Economy Failing";
    } else if (RelatedIssue.getIssueType() == EDUCATION_REFORM){
        return "Education Reform";
    } else if (RelatedIssue.getIssueType() == UNEMPLOYMENT_RISE){
        return "Unemployment Rise";
    } else if (RelatedIssue.getIssueType() == DEFORESTATION){
        return "Deforestation";
    } else if (RelatedIssue.getIssueType() == MEDICARE){
        return "Medicare";
    } else {
        return "No Issue";
    }
}

/*
    Issues are used as a way to store information on the 5
    issues that are needed to run the simulation.

    Name: The name of the Issue as a string
    IssueCode: Used to create a unique code for each issue
    Type: Usses the Issues enum as another identifying feature
    Description: A description of the given Issue
*/

Issue::Issue(){
    //Hopefully we never reach 999 Issues with our country ;)
    this->name = "NULL";
    this->IssueCode = 999;
    this->type = NO_ISSUE;
    this->description = "BLANK";
    vector<Characteristics> impactingCharaceristics;
}

Issue::Issue(string n, int c, Issues t, string s){
    this->name = n;
    this-> IssueCode = c;
    this-> type = t;
    this-> description = s;
    vector<Characteristics> impactingCharaceristics;
}

int Issue::getCode(){return IssueCode;}
Issues Issue::getIssueType(){return type;}
string Issue::getStatement(){return description;}
string Issue::getName(){return name;}
void Issue::changeIssueType(Issues i){this->type = i;}
void Issue::changeIssueCode(int i){this->IssueCode = i;}
void Issue::add_impacting_characteristics(Characteristics c){impactingCharaceristics.push_back(c);}
vector<Characteristics> Issue::returnImpactChara(){return impactingCharaceristics;}

/*
    Person is used as a superclass for both candidates
    and Leaders to seperate the two rolls
    First Name: First name of the person
    Last Name: Last name of the person
    Popularity: How popular the person is (1 being the least)
*/
Person::Person(){
    this->first_name = "";
    this->last_name = "";
    this->popularity = 1;
    vector<Characteristics> related_characteristics;
}

Person::Person(string fName, string lName){
    this->first_name = fName;
    this->last_name = lName;
    BasicRandom ran;
    this->popularity = 1;
}

string Person::getName(){return first_name + " " + last_name;}
int Person::getPopulatirity(){return popularity;}
void Person::updatePopulatirity(int update){this->popularity = popularity + update;}

/*
    Leader inherits Person adding a Party
    and character attribute
    Party: Name of the party
    Character: A character that the Leader has
*/

Leader::Leader() : Person(){
    this->character = UNDEFINED_CHARACTERISTIC;
    this->party = "";
}

Leader::Leader(string partyName, string fName, string lName, Characteristics c) : Person(fName, lName){
    this->character = c;
    this->party = partyName;
}
string Leader::returnParty(){return party;}
Characteristics Leader::returnCharacter(){return character;}

/*
    Candidate adds an attribute totalVotes
    This is to keep track of his votes within
    an electorate
*/
Candidate::Candidate() : Leader(){
    this->totalVotes = 0;
}

Candidate::Candidate(string partyName, string fName, string lName, Characteristics c) : Leader(partyName, fName, lName, c){
    this->totalVotes = 0;
}

void Candidate::updateVotes(int v){this->totalVotes += v;}
int Candidate::getTotalVotes(){return totalVotes;}

/*
    Managerial Team helps buy spending money
    to keep the election running espically
    funding
    partyFunds: Total dollars the party has
    teamMembers: Number of team memebers the team has
    party: The name of the party they are with

*/
ManagerialTeam::ManagerialTeam(){
    this->partyFunds = 0.0;
    this->teamMembers = 0;
    this->party = "Null";
}

ManagerialTeam::ManagerialTeam(double f, int tm, string p){
    this->partyFunds = f;
    this->teamMembers = tm;
    this->party = p;
}

void ManagerialTeam::addFunds(double money){this->partyFunds = partyFunds + money;}
void ManagerialTeam::spendFunds(double money){this->partyFunds = partyFunds - money;}
int ManagerialTeam::countTeamMembers(){return teamMembers;}
string ManagerialTeam::returnParty(){return party;}
void ManagerialTeam::dailySpending(){
    int rent = 2000;
    int advertising = 1000;
    int transportation = 500;
    int radioApperance = 500;
    partyFunds = partyFunds - rent - advertising - transportation - radioApperance;
}


/*
    Electorate is used to store the different electorates
    and associated values
    Name: Name of the electorate
    Code: Code for the electorate
    Geographical Area: Area the electorate is in
    Stance List: A vector containing all stances
    Stance Distrubition: a value used in generating stances
    Candidates: a list containing all the candidates in an electorate
*/

Electorate::Electorate(string n, string g, unsigned int c, unsigned int p, int d){
    this->name = n;
    this->code = "C" + to_string(c);
    this->geographicalArea = g;
    this->population = p;
    vector<Stance> stanceList;
    this->stanceDistrubition = d;
    vector<Candidate> candidates;
}

string Electorate::getName(){return name;}
string Electorate::getArea(){return geographicalArea;}
string Electorate::getCode(){return code;}
unsigned int Electorate::getPopulation(){return population;}
void Electorate::add_Stances(Stance s){stanceList.push_back(s);}
vector<Stance> Electorate::returnStanceList(){return stanceList;}
unsigned int Electorate::getStanceDistrubtion(){return stanceDistrubition;}
void Electorate::add_candidates(Candidate c){candidates.push_back(c);}
void Electorate::update_populatiry_index(int i, int k){candidates[i].updatePopulatirity(k);}
void Electorate::update_stance_values(int i, int j){
    //i is the index of the issue
    //j either being a 0 = Increase in interest or 1 = Decrease in interest
    if( (j = 1) && (stanceList[i].returnSignificance() < 10) ){stanceList[i].changeSignificant(1);}
    if( (j = 1) && (stanceList[i].returnApproach() < 10) ){stanceList[i].changeApproach(1);}
    if((j = 2) && (stanceList[i].returnSignificance() > 0)){stanceList[i].changeSignificant(-2);}
    if((j = 2) && (stanceList[i].returnApproach() > 0)){stanceList[i].changeApproach(-2);}
}
Stance Electorate::returnStanceIndex(int i){return stanceList[i];}
vector<Candidate> Electorate::returnCandidates(){return candidates;}
Candidate Electorate::returnCanidateIndex(int i){return candidates[i];}

/*
    Party is used to save all the data for each Party
    Party Name: Name od the party
    Managerial Team: The managerial team
    Local Candidates: The candidates in a particular party
    Standard Deviation: Used to create stances on issues
    Stances: A vector containing all the parties stances
    Votes: Total votes of the party
*/

Party::Party(){
    this->partyName = "BLANK";
    //Calls blank constructor for Candidate and Managerial Team
    std::vector<Candidate> localCandidates;
    this->standardDeviation = 0;
    std::vector<Stance> stances;
    this->votes = 0;
}

Party::Party(string name, Leader l, ManagerialTeam manage, unsigned int i){
    this->partyName = name;
    this->leader = l;
    std::vector<Candidate> localCandidates;
    this->standardDeviation = i;
    std::vector<Stance> stances;
    this->manangement = manage;
    this->votes = 0;
}

string Party::returnPartyName(){return partyName;}
Leader Party::returnLeader(){return leader;}
void Party::add_localCandidates(Candidate c){localCandidates.push_back(c);}
void Party::add_stance(Stance s){stances.push_back(s);}
ManagerialTeam Party::returnMangerialTeam(){return manangement;}
int Party::returnVotes(){return votes;}
void Party::updateVotes(int i){this->votes = votes + i;}
vector<Candidate> Party::returnLocalCandidates(){return localCandidates;}
unsigned int Party::getStanceDistrubtion(){return standardDeviation;}
vector<Stance> Party::returnStances(){return stances;}
Stance Party::returnStanceIndex(int i){return stances[i];}
void Party::update_populatiry(int i){leader.updatePopulatirity(i);}
void Party::dailySpending(){manangement.dailySpending();}

/*
    Campaign is used to run the calculations on who wins the
    election
    campaignDays: Number of days the campaign shall run
    currentDay: Current day number
    todaysEvent: Event that day
*/

Campaign::Campaign(){
    campaignDays = 1;
    currentDay = 1;
    todaysEvent = UNDEFINED_EVENT;
}

Campaign::Campaign(int i){
    int dayCount = 0;
    currentDay = 1;
    campaignDays = i;
}

int Campaign::getCurrentDay(){return currentDay;}
void Campaign::updateCurrentDay(){currentDay++;}
void Campaign::setCurrentDay(int i){currentDay = i;}

//runCampaign takes all the values from Election to calculate the winner of the party
void Campaign::runCampaign(vector<Party> p, vector<Electorate> e, vector<Issue> i, int a){
    //Random engine to get random ints
    BasicRandom b;

    //a = Days to run election
    for (int k = 0; k < a; k++){
        cout << "+=================+";
        cout << "Day " << k+1;
        cout << "+=================+" << endl;

        for (int g = 0; g < p.size(); g++){
            //Daily spending of each party
            p[g].dailySpending();
            /*
            if (p[g].returnMangerialTeam().returnFunds() <= 0){
                cout << p[g].returnPartyName() << "HAS GONE BROKE AND CAN NO LONGER COMPETE\n";
                cout << "-50 popularity to the " << p[g].returnPartyName() << endl;
                //This ruins there chance of winning the election
                p[closest].update_populatiry(-50);
                for (int d = 0; d < e.size(); d++){
                    //Decrease the popularity of each cadidate of that party
                    //so they cannot win
                    e[d].update_populatiry_index(g, -50);
                }
            */
        }

        for (int z = 0; z < e.size(); z++){
            this->currentDay = a;
            int chance = b.random_Int(0,100);

            //If chance <= 50 no event happens that day
            //Else an event happens
            if (chance <= 50){
                //No event for the day
                todaysEvent = UNDEFINED_EVENT;

                //Everyone gets some popularity as the electorate talks amoungst themselves
                for (int i = 0; i < e[z].returnCandidates().size(); i++){
                    e[z].update_populatiry_index(i, b.random_Int(0,1));
                }

            } else {
                cout << "Electorate "<< e[z].getName() << " Events" << endl;
                int eventNum = b.random_Int(1,100);
                //Picks event based on chance 1 -> 100
                //This allows me to give weighting to certain events

                if ( (eventNum <= 30) && (eventNum > 0) ){
                    //Picks a random event out of the 5
                    int currentIssue = b.random_Int(0,4);

                    //Prints out statement of whats happening and with who is there
                    todaysEvent = LOCAL_APPEARANCE;
                    cout << "Our canidates are walking amoungst the public" << endl;
                    cout << e[z].returnCandidates()[0].getName() << ", " << e[z].returnCandidates()[1].getName() << " & "  << e[z].returnCandidates()[2].getName() << " have been\n";
                    cout << "talking to the locals and getting to know them one " << endl;
                    cout << "on one. Espically to see what their stances are on\n";
                    cout << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr();
                    cout << endl;



                    //Finds the party with the closest stance to the electorates stance
                    int closest = 0;
                    double value = 40;
                    for (int g = 0; g < e[z].returnCandidates().size(); g++){
                        double d1 = 0.0;
                        double x1 = e[z].returnStanceList().at(currentIssue).returnApproach();
                        double x2 = p.at(g).returnStances().at(currentIssue).returnApproach();

                        double y1 = e[z].returnStanceList().at(currentIssue).returnSignificance();
                        double y2 = p.at(g).returnStances().at(currentIssue).returnSignificance();

                        //Equation used square root of[ (x2 - x1)^2 + (y2 - y1)^2 ]
                        d1 = sqrt( ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))  );
                        d1 = round(d1*100)/100;

                        //Loop through all the characteristics that affect the candidates stance
                        for(int u = 0; u < e[z].returnStanceList().at(currentIssue).returnRelatedIssue().returnImpactChara().size(); u++){
                            if (e[z].returnCandidates().at(g).returnCharacter() == e[z].returnStanceList().at(currentIssue).returnRelatedIssue().returnImpactChara().at(u) ){
                                //Make there stance 10% closer
                                d1 = d1 * 0.9;
                            }
                        }

                        if (d1 < value){
                            closest = g;
                            value = d1;
                        }
                    }

                    cout << e[z].returnCandidates().at(closest).getName();
                    cout << " understood the electorate and their\nissues the most ";
                    cout << "+1 popularity to " << e[z].returnCandidates().at(closest).getName() << endl;

                    //Update candidate based on index function
                    e[z].update_populatiry_index(closest, 1);

                } else if ( (eventNum > 30) && (eventNum <= 45) ){
                    todaysEvent = PRESS_RELEASE;
                    cout << "A press release has been published." << endl;
                    int currentIssue = b.random_Int(0,4);

                    cout << "The leaders of our political parties are talking" << endl;
                    cout << "about " << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr() << "and how they will work to \naddress this problem" << endl;


                    int closest = 0;
                    double value = 40;
                    for (int g = 0; g < e[z].returnCandidates().size(); g++){
                        double d1 = 0.0;
                        double x1 = e[z].returnStanceList().at(currentIssue).returnApproach();
                        double x2 = p.at(g).returnStances().at(currentIssue).returnApproach();

                        double y1 = e[z].returnStanceList().at(currentIssue).returnSignificance();
                        double y2 = p.at(g).returnStances().at(currentIssue).returnSignificance();

                        d1 = sqrt( ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))  );
                        d1 = round(d1*100)/100;

                        //Loop through all the characteristics that affect the candidates stance
                        for(int u = 0; u < e[z].returnStanceList().at(currentIssue).returnRelatedIssue().returnImpactChara().size(); u++){
                            if (e[z].returnCandidates().at(g).returnCharacter() == e[z].returnStanceList().at(currentIssue).returnRelatedIssue().returnImpactChara().at(u) ){
                                //Make there stance 10% closer
                                d1 = d1 * 0.9;
                            }
                        }

                        //If the new value is closer than save it as the cloest
                        if (d1 < value){
                            closest = g;
                            value = d1;
                        }
                    }

                    //Print who won
                    cout << p.at(closest).returnLeader().getName();
                    cout << " understood the electorate and their issues the most" << endl;
                    cout << "+1 popularity to the leader " << p.at(closest).returnLeader().getName() << endl;

                    //Update candidate based on index function
                    p[closest].update_populatiry(1);

                } else if ( (eventNum > 45) && (eventNum <= 55) ){
                    todaysEvent = ISSUE_CONFERENCE;
                    int currentIssue = b.random_Int(0,4);
                    int value = b.random_Int(1,2);

                    cout << "A conference is happening and talking about " << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr() << endl;
                    cout << "Currently this is how the people are feeling:\n";
                    cout << "\tApproach:\t" << e[z].returnStanceList().at(currentIssue).returnApproach() << endl;
                    cout << "\tSignificance:\t" << e[z].returnStanceList().at(currentIssue).returnSignificance() << endl;

                    //cout << e[z].returnStanceList().at(currentIssue).returnApproach() << "|" << e[z].returnStanceList().at(currentIssue).returnSignificance() << endl;

                    e[z].update_stance_values(currentIssue, value);
                    if (value = 2){
                        cout << "After some careful thinking the electorate now relises they dont care about the issue as much\n";
                    } else {
                        cout << "After some thinking the electorate is now more passionate than ever before!\n";
                    }

                    cout << "\tApproach:\t" << e[z].returnStanceList().at(currentIssue).returnApproach() << endl;
                    cout << "\tSignificance:\t" << e[z].returnStanceList().at(currentIssue).returnSignificance() << endl;

                } else if ( (eventNum > 55) && (eventNum <= 63) ){
                    todaysEvent = INTERVIEW;
                    int currentIssue = b.random_Int(0,4);
                    cout << "A interview is released with all our beloved leaders debating eachother" << endl;
                    cout << "about " << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr() << "and how they will work to address this problem" << endl;

                    int closest = 0;
                    double value = 40;
                    for (int g = 0; g < e[z].returnCandidates().size(); g++){
                        double d1 = 0.0;
                        double x1 = e[z].returnStanceList().at(currentIssue).returnApproach();
                        double x2 = p.at(g).returnStances().at(currentIssue).returnApproach();

                        double y1 = e[z].returnStanceList().at(currentIssue).returnSignificance();
                        double y2 = p.at(g).returnStances().at(currentIssue).returnSignificance();

                        d1 = sqrt( ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))  );
                        d1 = round(d1*100)/100;

                        //The smallest value is the closest point
                        if (d1 < value){
                            closest = g;
                            value = d1;
                        }
                    }

                    cout << p.at(closest).returnLeader().getName();
                    cout << " understood the electorate and their issues the most" << endl;
                    cout << "+1 popularity to the leader " << p.at(closest).returnLeader().getName() << endl;

                    //Update candidate based on index function
                    p[closest].update_populatiry(1);


                } else if ( (eventNum > 63) && (eventNum <= 74) ) {
                    todaysEvent = NEWS_ARTICLE;
                    int currentIssue = b.random_Int(0,4);
                    int value = b.random_Int(1,2);

                    cout << "A news article has just been released and it talks about " << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr() << endl;
                    cout << "Currently this is how the people are feeling:\n";
                    cout << "\tApproach:\t" << e[z].returnStanceList().at(currentIssue).returnApproach() << endl;
                    cout << "\tSignificance:\t" << e[z].returnStanceList().at(currentIssue).returnSignificance() << endl;

                    //cout << e[z].returnStanceList().at(currentIssue).returnApproach() << "|" << e[z].returnStanceList().at(currentIssue).returnSignificance() << endl;

                    e[z].update_stance_values(currentIssue, value);
                    if (value = 2){
                        cout << "After some careful thinking the electorate now relises they dont care about the issue as much\n";
                    } else {
                        cout << "After some thinking the electorate is now more passionate than ever before!\n";
                    }

                    cout << "\tApproach:\t" << e[z].returnStanceList().at(currentIssue).returnApproach() << endl;
                    cout << "\tSignificance:\t" << e[z].returnStanceList().at(currentIssue).returnSignificance() << endl;


                    //int outcome = b.random_Int(1,2);


                } else if ( (eventNum > 74) && (eventNum <= 83) ){
                    todaysEvent = DEBATE;
                    cout << "A debate is happening between our parties!" << endl;
                    cout << "Leaders ";
                    int i;
                    //Prints out the leaders used
                    for (i = 0; i < p.size() - 1; i++){
                        cout << p[i].returnLeader().getName() << ", ";
                    }
                    cout << p[i].returnLeader().getName() << " will be debating eachother." << endl;

                    int first = 0;
                    int second = 0;
                    int third = 0;
                    int performance = -10;
                    int firstIndex, secondIndex, thirdIndex;

                    //Loop through each party and calculate how well they perform

                    for (int i = 0; i < p.size(); i++){
                        performance = b.random_Int(1,100);
                        if(p[i].returnLeader().returnCharacter() == WELL_SPOKEN){
                            //Well spoken leaders get a 15% boast in their performance
                            performance = performance * 1.15;
                        }

                        //Assign their performance from 1st to 3rd
                        if ( performance > first) {
                            third = second;
                            second = first;
                            first = performance;

                            thirdIndex = secondIndex;
                            secondIndex = firstIndex;
                            firstIndex = i;
                            //DEBUGGING
                            cout << "1st:" << first << "|" << second << "|" << third<< endl;
                        } else if (performance > second){
                            third = second;
                            second = performance;

                            thirdIndex = secondIndex;
                            secondIndex = i;
                            //DEBUGGING
                            cout << "2nd:" << first << "|" << second << "|" << third<< endl;
                        } else {
                            third = performance;
                            //DEBUGGING
                            cout << "3rd:" << first << "|" << second << "|" << third<< endl;
                            thirdIndex = i;
                        }
                    }

                    //cout << firstIndex << "|" << secondIndex << "|" << thirdIndex << endl;

                    //Print out their perforamnce and update their popularity
                    cout << p[firstIndex].returnLeader().getName() << " made the best points (+2 popularity)" << endl;
                    cout << "Original popularity:\t" << p[firstIndex].returnLeader().getPopulatirity() << endl;
                    p[firstIndex].update_populatiry(2);
                    cout << "New popularity:\t\t" << p[firstIndex].returnLeader().getPopulatirity() << endl;

                    cout << p[secondIndex].returnLeader().getName() << " made okay points but nothing special (No change in popularity)" << endl;
                    cout << "Original popularity:\t" << p[secondIndex].returnLeader().getPopulatirity() << endl;
                    cout << "New popularity:\t\t" << p[secondIndex].returnLeader().getPopulatirity() << endl;

                    cout << p[thirdIndex].returnLeader().getName() << " made awful points and tripped walking onto the stage (-2 popularity)" << endl;
                    cout << "Original popularity:\t" << p[thirdIndex].returnLeader().getPopulatirity() << endl;
                    p[thirdIndex].update_populatiry(-2);
                    cout << "New popularity:\t\t" << p[thirdIndex].returnLeader().getPopulatirity() << endl << endl;



                } else if ( (eventNum > 83) && (eventNum <= 100) ){
                    todaysEvent = LOCAL_SPEECH;
                    int currentIssue = b.random_Int(0,4);

                    cout << "Each of our candidates are speeking to the public " << endl;
                    cout << e[z].returnCandidates()[0].getName() << ", " << e[z].returnCandidates()[1].getName() << " & "  << e[z].returnCandidates()[2].getName();
                    cout << "\nhave all given speeches about " << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr() << endl;
                    cout << "on one. Espically to see what their stances are on\n";
                    cout << e[z].returnStanceList().at(currentIssue).returnRelatedIssueStr();

                    cout << endl;


                    int closest = 0;
                    double value = 0.0;
                    for (int g = 0; g < e[z].returnCandidates().size(); g++){
                        double d1 = 0.0;
                        double x1 = e[z].returnStanceList().at(currentIssue).returnApproach();
                        double x2 = p.at(g).returnStances().at(currentIssue).returnApproach();

                        double y1 = e[z].returnStanceList().at(currentIssue).returnSignificance();
                        double y2 = p.at(g).returnStances().at(currentIssue).returnSignificance();

                        d1 = sqrt( ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))  );
                        d1 = round(d1*100)/100;

                        //Loop through all the characteristics that affect the candidates stance
                        for(int u = 0; u < e[z].returnStanceList().at(currentIssue).returnRelatedIssue().returnImpactChara().size(); u++){
                            if (e[z].returnCandidates().at(g).returnCharacter() == e[z].returnStanceList().at(currentIssue).returnRelatedIssue().returnImpactChara().at(u) ){
                                //Make there stance 10% closer
                                d1 = d1 * 0.9;
                            }
                        }

                        if (d1 > value){
                            closest = g;
                            value = d1;
                        }
                    }

                    int points = b.random_Int(1,3);

                    e[z].update_populatiry_index(closest, points);

                    cout << e[z].returnCandidates().at(closest).getName();
                    cout << " understood the electorate and their\nissues the most ";
                    cout << "+" << points << " popularity to " << e[z].returnCandidates().at(closest).getName() << endl;

                } else {
                    //Should never occur
                    todaysEvent = UNDEFINED_EVENT;
                }
                cout << endl;
            }
        }
    }

    //Election results
    cout << endl << "Time for the electorates to vote!";

    double totalVotes = 0;

    cout << "Leaders Name, Leaders Popularity\n";
    cout << "Candidates Name, Candidates Popularity" << endl;

    double highestVote = 0;
    int highestParty;

    //Prints out each electorate and the candidates with their populatirty
    for(int h = 0; h < e.size(); h++){
        cout << "-------------------" << endl;
        cout << e[h].getName() << endl;
        for (int c = 0; c < p.size(); c++){
            //totalVotes = 0;
            cout << "-------------------" << endl;
            cout << p[c].returnLeader().getName() << "\t" << p[c].returnLeader().getPopulatirity() << endl;
            cout << e[h].returnCandidates()[c].getName() << "\t" << (e[h].returnCandidates()[c].getPopulatirity() * 1.3) << endl;

            totalVotes = (p[c].returnLeader().getPopulatirity()) + (e[h].returnCandidates()[c].getPopulatirity() * 1.3);

            if (totalVotes > highestVote){
                highestVote = totalVotes;
                highestParty = c;
            }
        }
        cout << "-------------------" << endl;
        cout << p[highestParty].returnPartyName() << " won the votes of the people from " << e[h].getName() << endl << endl;
        p[highestParty].updateVotes(1);
    }

    cout << "-----------------------------------------" << endl;
    cout << "|        Electorate Information         |" << endl;
    cout << "-----------------------------------------" << endl;
    //cout << "Name\t\tCode\t\tArea\t\tPopulation" << endl;
    for(int z = 0; z < e.size(); z++){
        string tabs = "\t\t\t";

        if (e[z].getName().size() < 9){
            tabs += "\t";
        }

        cout << "|Name: " << e[z].getName() << tabs << "|" << endl;
        cout << "|Code: " << e[z].getCode() << "\t\t\t\t|" << endl;
        cout << "|Area: " <<  e[z].getArea() << "\t\t\t\t|" << endl;
        cout << "|Population: " <<  e[z].getPopulation() << "\t\t\t|"  << endl;
        cout << "| Local Candidates\t| Party Name\t|" << endl;

        string output;
        for (int k = 0; k < e[z].returnCandidates().size(); k++){
            output = "| - ";
            output += e[z].returnCanidateIndex(k).getName();
            tabs = "\t";

            if (e[z].returnCanidateIndex(k).getName().size() < 12){
                tabs += "\t";
            }
            cout << output << tabs << "| " << e[z].returnCanidateIndex(k).returnParty() << "\t|" << endl;
        }
        for (int f = 0; f < e[z].returnStanceList().size(); f++){
            cout << "|Issue Code:" << i[f].getCode() << "\t\t\t\t|" << endl;
            cout << "|   " << "Approach:\t\t" << to_string(e[z].returnStanceIndex(f).returnApproach()) << "\t|" << endl;
            cout << "|   " << "Significance:\t" << to_string(e[z].returnStanceIndex(f).returnSignificance()) << "\t|" << endl;
            cout << "|\t\t\t\t\t|" << endl;
        }
        cout << "-----------------------------------------" << endl;
    }
    cout << endl << endl;

    highestVote = 0;
    highestParty = 0;
    for (int i = 0; i < p.size(); i++){
        cout << p[i].returnPartyName() << "\thas a total of\t" << p[i].returnVotes() << endl;
        if ( p[i].returnVotes() > highestVote){
            highestParty = i;
            highestVote = p[i].returnVotes();
        }
    }

    cout << endl << p.at(highestParty).returnPartyName() << " HAS WON THE ELECTION WITH A TOTAL OF " << p[highestParty].returnVotes() << endl;
    p.clear();
    e.clear();
    i.clear();
}

/*
    The election is used to store all the values needed for
    a campaign to run

    electoratesNum: Number of electorates
    campaingDays: The length the campaign shall run
    parties: Vector of all Party's in the election
    electorates: Vector of all the Electorates in the election
    issues: Vector of all the Issues relavent to the election
    randomGene: The random engine used to get random values
*/


Election::Election(int e, int c){
    this->electoratesNum = e;
    this->campaingDays = c;
    vector<Party> parties;
    vector<Electorate> electorates;
    vector<Issue> issues;
    BasicRandom randomGene;
}

int Election::returnPartyNum(){return partyNum;}
int Election::returnElectoratesNum(){return electoratesNum;}
void Election::addParties(Party c){parties.push_back(c);}
vector<Party> Election::returnParties(){return parties;}
Party Election::returnIndexParty(int i){return parties[i];}
vector<Electorate> Election::returnElectorates(){return electorates;}
vector<Issue> Election::returnIssueVector(){return issues;}
int Election::returnCampaignLength(){return campaingDays;}
BasicRandom Election::returnGene(){return randomGene;}

//Loads all the parties to the election
void Election::loadParties(){
    //
    parties.clear();
    unsigned int SD;

    Leader Jake_McCoy("Red Party", "Jake", "McCoy", WELL_SPOKEN);
    ManagerialTeam RedManagers(200000, 3, "Red Party");
    SD = randomGene.random_Int(1,5);
    Party Red_Party("Red party", Jake_McCoy, RedManagers, SD);
    parties.push_back(Red_Party);

    Leader Samson_Cox("Blue Party", "Samson", "Cox", ECONOMIC_EXP);
    ManagerialTeam BlueManagers(180000, 4, "Blue Party");
    SD = randomGene.random_Int(1,5);
    Party Blue_Party("Blue Party", Samson_Cox, BlueManagers, SD);
    parties.push_back(Blue_Party);

    Leader Zachery_Fletcher("Green Party", "Zac", "Fletcher", EMPLOYMENT_EXP);
    ManagerialTeam GreenManagers(150000, 3, "Green Party");
    SD = randomGene.random_Int(1,5);
    Party Green_Party("Green Party", Zachery_Fletcher, GreenManagers, SD);
    parties.push_back(Green_Party);
}

//Load all the Electorates and their information
void Election::loadElectortes(int i){
    //Clear all values in electorates so it doesnt get run twice and generate double ups
    electorates.clear();

    //Create electorates
    Electorate Tomboye  ("Tomboye",     "NSW", 100, 6001,   randomGene.random_Int(1,5));
    Electorate Braidwood("Braidwood",   "NSW", 110, 5301,   randomGene.random_Int(1,5));
    Electorate Bomaderry("Bomaderry",   "NSW", 120, 7051,   randomGene.random_Int(1,5));
    Electorate Goulbourn("Goulbourn",   "NSW", 130, 6201,   randomGene.random_Int(1,5));
    Electorate Jindabyne("Jindabyne",   "NSW", 140, 10001,  randomGene.random_Int(1,5));
    Electorate Dubbo    ("Dubbo",       "NSW", 150, 5501,   randomGene.random_Int(1,5));
    Electorate Ulladulla("Ulladulla",   "NSW", 160, 3001,   randomGene.random_Int(1,5));
    Electorate Woonona  ("Woonona",     "NSW", 170, 8501,   randomGene.random_Int(1,5));
    Electorate Appin    ("Appin",       "NSW", 180, 101,    randomGene.random_Int(1,5));
    Electorate Como     ("Como",        "NSW", 190, 9201,   randomGene.random_Int(1,5));

    //Adds all the electorates to a temp vector
    vector<Electorate> temp;
    temp.push_back(Tomboye);
    temp.push_back(Braidwood);
    temp.push_back(Bomaderry);
    temp.push_back(Goulbourn);
    temp.push_back(Jindabyne);
    temp.push_back(Dubbo);
    temp.push_back(Ulladulla);
    temp.push_back(Woonona);
    temp.push_back(Appin);
    temp.push_back(Como);

    //Adds electorates to the main vector passed on command line arguments
    for (int k = 0; k < i; k++){
        electorates.push_back(temp[k]);
    }

    //Clears all the values from the temp file
    temp.clear();
}

//Load all the issues and their information
void Election::loadIssues(){
    //Clears vector so we dont double up on issues
    issues.clear();

    //Create Issues
    Issue Unemployment      ("Unemployment Rise",   100, UNEMPLOYMENT_RISE,    "Unemployement is on the rise in \nNSW. We need to get people into\njobs before this effects the\neconomy.");
    Issue Deforestation     ("Deforestation",       110, DEFORESTATION,        "More big companies are destorying\nanciet australian land that we\ncannot fix later on. This needs\nto be addressed.");
    Issue Medicare          ("Medicare",            120, MEDICARE,             "Medicare is vital for healthcare\nin Australia and with the growing\npopulation we need to rethink \nour stratergies inorder for \nmedicare to continue to work.");
    Issue Education_Reform  ("Education Reform",    130, EDUCATION_REFORM,     "The education department is \nfailing its Primary school and \nHigh school students they need to\nrethink stratergies to teach a\nbrighter generation.");
    Issue Economy_Falling   ("Economy Failing",     140, ECONOMY_FALLING,      "The economy of Australia is \nfalling and needs to be talked \nabout. If this continues australia\nwill turn into a Mad Max\nwasteland. Which would be cool...");

    //Adding the characteristics that impact this specific event
    Unemployment.add_impacting_characteristics(BUSINESS_CONNECTIONS);
    Unemployment.add_impacting_characteristics(ECONOMIC_EXP);
    Unemployment.add_impacting_characteristics(EMPLOYMENT_EXP);
    Unemployment.add_impacting_characteristics(POPULAR);

    Deforestation.add_impacting_characteristics(ENVIRONMENTAL_EXP);
    Deforestation.add_impacting_characteristics(POPULAR);

    Medicare.add_impacting_characteristics(HEALTHCARE_EXP);
    Medicare.add_impacting_characteristics(POPULAR);

    Education_Reform.add_impacting_characteristics(EMPLOYMENT_EXP);
    Education_Reform.add_impacting_characteristics(BUSINESS_CONNECTIONS);

    Economy_Falling.add_impacting_characteristics(BUSINESS_CONNECTIONS);
    Economy_Falling.add_impacting_characteristics(ECONOMIC_EXP);
    Economy_Falling.add_impacting_characteristics(EMPLOYMENT_EXP);
    Economy_Falling.add_impacting_characteristics(POPULAR);

    //Load Issues to vector
    issues.push_back(Unemployment);
    issues.push_back(Deforestation);
    issues.push_back(Medicare);
    issues.push_back(Education_Reform);
    issues.push_back(Economy_Falling);
}

//Load all the candidates based on number of electorates
void Election::loadCandidates(){
    vector<Candidate> redCandidates;
    vector<Candidate> blueCandidates;
    vector<Candidate> greenCandidates;
    vector<vector<Candidate>> partyCandidates;

    vector<Candidate> electorate1;
    vector<Candidate> electorate2;
    vector<Candidate> electorate3;
    vector<Candidate> electorate4;
    vector<Candidate> electorate5;
    vector<Candidate> electorate6;
    vector<Candidate> electorate7;
    vector<Candidate> electorate8;
    vector<Candidate> electorate9;
    vector<Candidate> electorate10;

    vector<vector<Candidate>> electorateCandidates;

    Candidate can11("Red Party", "Noor", "Beevors", HEALTHCARE_EXP);
    Candidate can12("Blue Party", "Ella", "Cole", DEBATE_EXP);
    Candidate can13("Green Party", "Angus", "Farley", EMPLOYMENT_EXP);

    electorate1.push_back(can11);
    electorate1.push_back(can12);
    electorate1.push_back(can13);

    redCandidates.push_back(can11);
    blueCandidates.push_back(can12);
    greenCandidates.push_back(can13);

    Candidate can21("Red Party", "Nathan", "Phillis", BUSINESS_CONNECTIONS);
    Candidate can22("Blue Party", "Hayden", "Phillis", POPULAR);
    Candidate can23("Green Party", "Niel", "Phillies", SCANDEL_EXP);

    electorate2.push_back(can21);
    electorate2.push_back(can22);
    electorate2.push_back(can23);

    redCandidates.push_back(can21);
    blueCandidates.push_back(can22);
    greenCandidates.push_back(can23);

    Candidate can31("Red Party", "Amy", "Hooper", ECONOMIC_EXP);
    Candidate can32("Blue Party", "Phoebe", "Potts", INFLUENTIAL);
    Candidate can33("Green Party", "Liam", "Hicox", DEBATE_EXP);

    electorate3.push_back(can31);
    electorate3.push_back(can32);
    electorate3.push_back(can33);

    redCandidates.push_back(can31);
    blueCandidates.push_back(can32);
    greenCandidates.push_back(can33);

    Candidate can41("Red Party", "Eddie", "Merdez", HEALTHCARE_EXP);
    Candidate can42("Blue Party", "Andrew", "Beevors", EMPLOYMENT_EXP);
    Candidate can43("Green Party", "Liam", "Hicox", ENVIRONMENTAL_EXP);

    electorate4.push_back(can41);
    electorate4.push_back(can42);
    electorate4.push_back(can43);

    redCandidates.push_back(can41);
    blueCandidates.push_back(can42);
    greenCandidates.push_back(can43);

    Candidate can51("Red Party", "Alex", "Posco", DEBATE_EXP);
    Candidate can52("Blue Party", "Georgia", "Green", ENVIRONMENTAL_EXP);
    Candidate can53("Green Party", "Mike", "Smith", POPULAR);

    electorate5.push_back(can51);
    electorate5.push_back(can52);
    electorate5.push_back(can53);

    redCandidates.push_back(can51);
    blueCandidates.push_back(can52);
    greenCandidates.push_back(can53);

    Candidate can61("Red Party", "Johny", "Guitar", HEALTHCARE_EXP);
    Candidate can62("Blue Party", "Cal", "Scruby", ECONOMIC_EXP);
    Candidate can63("Green Party", "Snoop", "Dog", BUSINESS_CONNECTIONS);

    electorate6.push_back(can61);
    electorate6.push_back(can62);
    electorate6.push_back(can63);

    redCandidates.push_back(can61);
    blueCandidates.push_back(can62);
    greenCandidates.push_back(can63);

    Candidate can71("Red Party", "Harry", "Styles", ENVIRONMENTAL_EXP);
    Candidate can72("Blue Party", "Cal", "Scruby", EMPLOYMENT_EXP);
    Candidate can73("Green Party", "Marty", "Robbins", DEBATE_EXP);

    electorate7.push_back(can71);
    electorate7.push_back(can72);
    electorate7.push_back(can73);

    redCandidates.push_back(can71);
    blueCandidates.push_back(can72);
    greenCandidates.push_back(can73);

    Candidate can81("Red Party", "Dua", "Lipa", ENVIRONMENTAL_EXP);
    Candidate can82("Blue Party", "Lil", "Bo Weep", HEALTHCARE_EXP);
    Candidate can83("Green Party", "Peggy", "Lee", BUSINESS_CONNECTIONS);

    electorate8.push_back(can81);
    electorate8.push_back(can82);
    electorate8.push_back(can83);

    redCandidates.push_back(can81);
    blueCandidates.push_back(can82);
    greenCandidates.push_back(can83);

    Candidate can91("Red Party", "Billie", "Eilish", SCANDEL_EXP);
    Candidate can92("Blue Party", "Zac", "Brown", DEBATE_EXP);
    Candidate can93("Green Party", "Frank", "Ocean", BUSINESS_CONNECTIONS);

    electorate9.push_back(can91);
    electorate9.push_back(can92);
    electorate9.push_back(can93);

    redCandidates.push_back(can91);
    blueCandidates.push_back(can92);
    greenCandidates.push_back(can93);

    Candidate can101("Red Party", "Mall", "Rat", ECONOMIC_EXP);
    Candidate can102("Blue Party", "Morgan", "Evans", HEALTHCARE_EXP);
    Candidate can103("Green Party", "Sam", "Tompkins", ENVIRONMENTAL_EXP);

    electorate10.push_back(can101);
    electorate10.push_back(can102);
    electorate10.push_back(can103);

    redCandidates.push_back(can101);
    blueCandidates.push_back(can102);
    greenCandidates.push_back(can103);

    electorateCandidates.push_back(electorate1);
    electorateCandidates.push_back(electorate2);
    electorateCandidates.push_back(electorate3);
    electorateCandidates.push_back(electorate4);
    electorateCandidates.push_back(electorate5);
    electorateCandidates.push_back(electorate6);
    electorateCandidates.push_back(electorate7);
    electorateCandidates.push_back(electorate8);
    electorateCandidates.push_back(electorate9);
    electorateCandidates.push_back(electorate10);

    partyCandidates.push_back(redCandidates);
    partyCandidates.push_back(blueCandidates);
    partyCandidates.push_back(greenCandidates);

    //Loop through the vector of vectors to get the electorates
    //for each electorate. Then add each electorate.
    for (int k = 0; k < electorates.size(); k++){
        for (int i = 0; i < electorateCandidates[k].size(); i++){
            electorates[k].add_candidates(electorateCandidates[k][i]);
        }
    }

    for (int j = 0; j < parties.size(); j++){
        for (int a = 0; a < partyCandidates[j].size(); a++){
            parties[j].add_localCandidates(partyCandidates[j][a]);
        }
    }

    redCandidates.clear();
    blueCandidates.clear();
    greenCandidates.clear();
    partyCandidates.clear();
    electorate1.clear();
    electorate2.clear();
    electorate3.clear();
    electorate4.clear();
    electorate5.clear();
    electorate6.clear();
    electorate7.clear();
    electorate8.clear();
    electorate9.clear();
    electorate10.clear();
    electorateCandidates.clear();
}

//Generates the electorates stances
void Election::generateElectorateStance(){
    for (int i = 0; i < electorates.size(); i++){
        for(int k = 0; k < issues.size(); k++){
            //Get the electorates stance distribution
            int SD = electorates[i].getStanceDistrubtion();

            //Create an upper and lower value of it
            int upper = 5 + SD;
            int lower = 5 - SD;

            //Generate the approach and signifcance based the upper and lower values
            int approach = randomGene.random_Int(lower, upper);
            int significance = randomGene.random_Int(lower, upper);


            //Create a temp Stance and assign its values
            Stance temp;

            if (k == 0){
                temp.chanceRelatedIssue(EDUCATION_REFORM);
            } else if (k == 1){
                temp.chanceRelatedIssue(EDUCATION_REFORM);
            } else if (k == 2){
                temp.chanceRelatedIssue(UNEMPLOYMENT_RISE);
            } else if (k == 3){
                temp.chanceRelatedIssue(DEFORESTATION);
            } else if (k == 4){
                temp.chanceRelatedIssue(MEDICARE);
            }


            temp.changeSignificant(significance);
            temp.changeApproach(approach);

            //Debugging code
            //cout << temp.returnRelatedIssueStr() << endl;
            //cout << temp.returnRelatedIssue().getCode() << endl << endl;

            //Add the stance to the electorate
            electorates[i].add_Stances(temp);
        }
    }
}

//Same as generateElectorateStance only instead applying it to the parties
void Election::generatePartyStance(){
    for (int i = 0; i < parties.size(); i++){
        for (int k = 0; k < issues.size(); k++){
            int SD = parties[i].getStanceDistrubtion();
            int upper = 5 + SD;
            int lower = 5 - SD;

            int approach = randomGene.random_Int(lower, upper);
            int significance = randomGene.random_Int(lower, upper);

            Issues tempI;

            if (k == 0){
                tempI = ECONOMY_FALLING;
            } else if (k == 1){
                tempI = EDUCATION_REFORM;
            } else if (k == 2){
                tempI = UNEMPLOYMENT_RISE;
            } else if (k == 3){
                tempI = DEFORESTATION;
            } else if (k == 4){
                tempI = MEDICARE;
            }

            Stance temp(approach, significance, tempI);
            //cout << tempI << endl;

            //Parties stances dont need a size
            temp.updateRadius(0);
            //cout << to_string(temp.returnApproach()) << endl;

            parties[i].add_stance(temp);
        }
    }
}

//Prints out the Parties information
void Election::partiesReport(){
    cout << "-----------------------------------------" << endl;
    cout << "|            Party Information          |" << endl;
    cout << "-----------------------------------------" << endl;

    for(int i = 0; i < parties.size(); i++){
        cout << "|Party Name:\t" << parties[i].returnPartyName() << "\t\t|" << endl;
        cout << "|Party Leader:\t" << parties[i].returnLeader().getName() << " \t\t|" << endl;
        cout << "|Total Votes:\t" << parties[i].returnVotes() << "\t\t\t|" << endl;
        cout << "|Issue Stances:\t\t\t\t|" << endl;
        for (int z = 0; z < parties[i].returnStances().size(); z++){
            cout << "|Issue Code:" << issues[z].getCode() << "\t\t\t\t|" << endl;
            cout << "|   " << "Approach:\t\t" << to_string(parties[i].returnStanceIndex(z).returnApproach()) << "\t|" << endl;
            cout << "|   " << "Significance:\t" << to_string(parties[i].returnStanceIndex(z).returnSignificance()) << "\t|" << endl;
            cout << "|\t\t\t\t\t|" << endl;
        }
        cout << "-----------------------------------------" << endl;
    }
    cout << endl;
}

//Prints out the electorates information
void Election::electoratesReport(){
    cout << "-----------------------------------------" << endl;
    cout << "|        Electorate Information         |" << endl;
    cout << "-----------------------------------------" << endl;
    //cout << "Name\t\tCode\t\tArea\t\tPopulation" << endl;
    for(int i = 0; i < electorates.size(); i++){
        string tabs = "\t\t\t";

        if (electorates[i].getName().size() < 9){
            tabs += "\t";
        }

        cout << "|Name: " << electorates[i].getName() << tabs << "|" << endl;
        cout << "|Code: " << electorates[i].getCode() << "\t\t\t\t|" << endl;
        cout << "|Area: " <<  electorates[i].getArea() << "\t\t\t\t|" << endl;
        cout << "|Population: " <<  electorates[i].getPopulation() << "\t\t\t|"  << endl;
        cout << "| Local Candidates\t| Party Name\t|" << endl;

        string output;
        for (int k = 0; k < electorates[i].returnCandidates().size(); k++){
            output = "| - ";
            output += electorates[i].returnCanidateIndex(k).getName();
            tabs = "\t";

            if (electorates[i].returnCanidateIndex(k).getName().size() < 12){
                tabs += "\t";
            }
            cout << output << tabs << "| " << electorates[i].returnCanidateIndex(k).returnParty() << "\t|" << endl;
        }
        for (int z = 0; z < electorates[i].returnStanceList().size(); z++){
            cout << "|Issue Code:" << issues[z].getCode() << "\t\t\t\t|" << endl;
            cout << "|   " << "Approach:\t\t" << to_string(electorates[i].returnStanceIndex(z).returnApproach()) << "\t|" << endl;
            cout << "|   " << "Significance:\t" << to_string(electorates[i].returnStanceIndex(z).returnSignificance()) << "\t|" << endl;
            cout << "|\t\t\t\t\t|" << endl;
        }
        cout << "-----------------------------------------" << endl;
    }
    cout << endl << endl;
}

//Prints out the issues and their information
void Election::issueReport(){
    for(int i = 0; i < issues.size(); i++){
        cout << "---------------------------------" << endl;
        cout << "|\tIssues Information\t|" << endl;
        cout << "---------------------------------" << endl;
        cout << "| Issue Code:\t" << issues[i].getCode() << "\t\t|" << endl;
        cout << "---------------------------------" << endl;
        cout << "Issue Description:" << endl;
        cout << issues[i].getStatement() << endl << endl;
    }
    cout << endl;
}


