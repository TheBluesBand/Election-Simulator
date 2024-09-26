#include <vector>
enum Issues {
    ECONOMY_FALLING=1,
    EDUCATION_REFORM=2,
    UNEMPLOYMENT_RISE=3,
    DEFORESTATION=4,
    MEDICARE=5,

    //Undefined event
    NO_ISSUE=7
};

enum Events {
    DEBATE=1,
    //Events 2 & 3 are Candiate Events
    LOCAL_APPEARANCE=2,
    LOCAL_SPEECH=3,
    //4 & 5 are Leaders Events
    PRESS_RELEASE=4,
    INTERVIEW=5,
    //6 & 7 are Issues Events
    ISSUE_CONFERENCE=6,
    NEWS_ARTICLE=7,

    //8 is undefined
    UNDEFINED_EVENT=9
};

enum Characteristics {
    BUSINESS_CONNECTIONS=1,
    ECONOMIC_EXP=2,
    ENVIRONMENTAL_EXP=3,
    EMPLOYMENT_EXP=4,
    SCANDEL_EXP=5,
    HEALTHCARE_EXP=6,
    INFLUENTIAL=7,
    POPULAR=8,
    DEBATE_EXP=9,
    WELL_SPOKEN=10,

    //Undefined Characteristic
    UNDEFINED_CHARACTERISTIC=12
};

class BasicRandom{
    public:
        int random_Int(int, int);
        float random_Float(int, int);
        bool random_Bool();
};


class Issue {
    private:
        std::string name;
        Issues type;
        int IssueCode;
        std::string description;
        std::vector<Characteristics> impactingCharaceristics;
    public:
        Issue();
        Issue(std::string, int, Issues, std::string);
        int getCode();
        Issues getIssueType();
        std::string getStatement();
        std::string getName();
        void changeIssueType(Issues);
        void changeIssueCode(int);
        void add_impacting_characteristics(Characteristics);
        std::vector<Characteristics> returnImpactChara();
};

class Stance{
    private:
        float approach;
        float significance;
        float radius;
        Issue RelatedIssue;
    public:
        Stance();
        Stance(float, float, Issue);
        Stance(float, float, float);
        Stance(float, float, float, Issue);
        void updateRadius(int);
        float returnSignificance();
        void changeSignificant(float);
        float returnApproach();
        void changeApproach(float);
        float returnRadius();
        void chanceRelatedIssue(Issues);
        float calCircumference();
        Issue returnRelatedIssue();
        std::string returnRelatedIssueStr();
};

class Person{
    private:
        std::string first_name;
        std::string last_name;
        unsigned int popularity;
    public:
        Person();
        Person(std::string, std::string);
        std::string getName();
        int getPopulatirity();
        void updatePopulatirity(int);

};

class Leader : public Person{
    private:
        Characteristics character;
        std::string party;
    public:
        Leader();
        Leader(std::string, std::string, std::string, Characteristics);
        std::string returnParty();
        Characteristics returnCharacter();
};

class Candidate : public Leader{
    private:
        unsigned int totalVotes;
    public:
        Candidate();
        Candidate(std::string, std::string, std::string, Characteristics);
        void updateVotes(int);
        int getTotalVotes();
};

class ManagerialTeam{
    private:
        double partyFunds;
        unsigned int teamMembers;
        std::string party;
    public:
        ManagerialTeam();
        ManagerialTeam(double, int, std::string);
        void addFunds(double);
        void spendFunds(double);
        int countTeamMembers();
        std::string returnParty();
        void dailySpending();
};

class Electorate{
    private:
        std::string name;
        std::string code;
        std::string geographicalArea;
        unsigned int population;
        std::vector<Stance> stanceList;
        unsigned int stanceDistrubition;
        std::vector<Candidate> candidates;
    public:
        Electorate(std::string, std::string, unsigned int, unsigned int, int);
        std::string getName();
        std::string getArea();
        std::string getCode();
        unsigned int getPopulation();
        std::vector<Stance> returnStanceList();
        unsigned int getStanceDistrubtion();
        void add_Stances(Stance);
        void add_candidates(Candidate);
        void update_populatiry_index(int, int);
        void update_stance_values(int, int);
        std::vector<Candidate> returnCandidates();
        Candidate returnCanidateIndex(int);
        Stance returnStanceIndex(int i);
};

class Party{
    private:
        std::string partyName;
        Leader leader;
        std::vector<Candidate> localCandidates;
        unsigned int standardDeviation;
        std::vector<Stance> stances;
        ManagerialTeam manangement;
        unsigned int votes;
    public:
        Party();
        Party(std::string, Leader, ManagerialTeam, unsigned int);
        std::string returnPartyName();
        Leader returnLeader();
        void add_localCandidates(Candidate);
        void add_stance(Stance);
        ManagerialTeam returnMangerialTeam();
        int returnVotes();
        void updateVotes(int);
        std::vector<Candidate> returnLocalCandidates();
        unsigned int getStanceDistrubtion();
        std::vector<Stance> returnStances();
        Stance returnStanceIndex(int i);
        void update_populatiry(int);
        void dailySpending();
};
class Campaign{
    private:
        unsigned int campaignDays;
        unsigned int currentDay;
        Events todaysEvent;
    public:
        Campaign();
        Campaign(int);
        int getCurrentDay();
        void updateCurrentDay();
        void setCurrentDay(int);
        void runCampaign(std::vector<Party>, std::vector<Electorate>, std::vector<Issue>, int);
};

class Election{
    private:
        const unsigned int partyNum = 3;
        unsigned int electoratesNum;
        std::vector<Party> parties;
        std::vector<Electorate> electorates;
        std::vector<Issue> issues;
        int campaingDays;
        BasicRandom randomGene;
    public:
        Election(int, int);
        int returnPartyNum();
        int returnElectoratesNum();
        std::vector<Party> returnParties();
        Party returnIndexParty(int);
        std::vector<Electorate> returnElectorates();
        std::vector<Issue> returnIssueVector();
        int returnCampaignLength();
        BasicRandom returnGene();

        void addParties(Party);
        void addElectorates(Electorate);

        void loadParties();
        void loadElectortes(int);
        void loadIssues();
        void loadCandidates();

        void generateElectorateStance();
        void generatePartyStance();

        void partiesReport();
        void electoratesReport();
        void issueReport();

};
