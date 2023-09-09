#include <iostream>
#include<string>
#include "picosha.h"

using namespace std;

class block
{
    public :

    int Block; //to store block number
    string Timestamp; //to store date & time
    string Previous_hash; //to store hash of previous block
    string Current_hash; //to store has of current block
    string Info; // to store info

    //Constructor - will be called automatically when object of block created
    block(int Block, string Previous_hash, string Timestamp, string Info)
    {
        this->Block = Block;
        this->Timestamp = Timestamp;
        this->Previous_hash = Previous_hash;
        this->Current_hash = calculateHash();
        this->Info = Info;

    }

    //function to calculate hash of given string using library picosha2
    string calculateHash()
    {
        string source = to_string(Block) + Timestamp + Info + Previous_hash;
        string hash;
        picosha2::hash256_hex_string(source, hash);
        return hash;
    }
//Referenced from github project (included in report)
};

class blockchain
{

public:
    vector <block> chain;
    blockchain() //Constructor
    {
        chain.push_back(createGenesisBlock());
    }
    block createGenesisBlock() //Function to create Genesis block
    {
        block b(1,"de0d00898d2d90344866e6e670d91d796accf0437f43d3537b2934d8b5769ae2","06/01/2022 10:05 AM","Stage 1: Battery Cell Manufacturing | Company: Panasonic | Job ID: PCM056902 |Location: Panasonic Nevada,USA");
        return b;

    }
    void addBlock(block b) //Method to add new block to blockchain
    {
        b.Previous_hash = getLatestBlock().Current_hash;
        b.Current_hash = b.calculateHash();
        chain.push_back(b);
    }
    block getLatestBlock() //Function to get last block from blockchain
    {
        return chain [this -> chain.size()-1];
    }

    string isChainValid() //validation of blockchain
    {
       for (int i=1; i< chain.size()- 1; i++)
       {
        block currentBlock = chain[i];
        block previousBlock = chain[i-1];
        if (currentBlock.Current_hash != currentBlock.calculateHash())
        {
            return "Data on block is altered, so invalid blockchain";
        }
        if (currentBlock.Previous_hash != previousBlock.Current_hash)
        {
            return "Data on block is altered, so invalid blockchain";
        }
       }
    return "No data tempered. This is valid blockchain";
    }
};


int main(int argc, const char * argv[]) {

    blockchain coin; //object of blockchain
    coin.addBlock(block(2,"02/01/2018","09/01/2022 1:50 PM ","Stage 2: Forming a Battery Module - Attachment of battery cells | Company: Panasonic | Job ID: PM056902 |        Location: Panasonic Nevada, USA")); //New block added
    coin.addBlock(block(3,"03/01/2018","15/01/2022 11:35 AM","Stage 3: Building the Battery Pack - Final Stage of EV battery production | Company: Panasonic | Job ID: PP056902|  Location: Panasonic Nevada, USA")); //New block added
    coin.addBlock(block(4,"04/01/2018","25/01/2022 2:12 PM","Stage 4: Packaging of Battery Pack | Company: Alpha Packaging | Job ID: 2201002 | Location: 4455 Paradise St, Las Vegas")); //New block added
    coin.addBlock(block(5,"04/01/2018","28/01/2022 9:06 PM","Stage 5: Shipment of Battery Pack | Company: United Van Lines and Cargo. | Job ID: 743021B2 | Location: 4505 Maryland, Las Vegas")); //New block added
    coin.addBlock(block(6,"04/01/2018","25/02/2022 12:21 PM","Stage 6: Assembly of EV battery to vehicle | Company: Tesla | Job ID: TA005821 | Location: Tesla Factory Fremont, California")); //New block added


    //Uncomment following lines to check invalid blockchain use case
    //coin.chain[1].data = "1000 Coins";
    //coin.chain[1].hash = coin.chain[1].calculateHash();

    for (int i=0; i<=coin.chain.size()- 1; i++)
    {
        cout << "Block: " + to_string(coin.chain[i].Block);
        cout << "\n";
        cout << "Timestamp : " + (coin.chain[i].Timestamp);
        cout << "\n";
        cout << "Info : " + (coin.chain[i].Info);
        cout << "\n";
        cout << "Previous Hash : " + (coin.chain[i].Previous_hash);
        cout << "\n";
        cout << "Hash : " + (coin.chain[i].Current_hash);
        cout << "\n\n";
    }

    cout << coin.isChainValid();
    cout << "\n\n\n";
    return 0;
}
