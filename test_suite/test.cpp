#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <ratio>
#include <chrono>
#include <time.h>
#include <stdlib.h>

#include "leveldb/db.h"
#include "leveldb/filter_policy.h"
#include "leveldb/env.h"

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));

    // Set up database connection information and open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    options.filter_policy = leveldb::NewBloomFilterPolicy(10);

    leveldb::Status status = leveldb::DB::Open(options, "./leveldb-10k-1kb-1gb", &db);

    if (false == status.ok())
    {
        cerr << "Unable to open/create test database './testdb'" << endl;
        cerr << status.ToString() << endl;
        return -1;
    }
    
    // Add 256 values to the database
    leveldb::WriteOptions writeOptions;
    /*for (unsigned int i = 0; i < 1000000; ++i)
    {
        ostringstream keyStream;
        keyStream << "Key" << i;
        
        ostringstream valueStream;
        valueStream << "3353ZSt8TukolvuFuodXvliCdrf6N4kgO3Yv0tuNCwsMei1zROLp1Jg5XmMICe8ZFv2lOhuX9y939CPHWtjnYiP0B1jf2xD39CwPCq0gP3Iitr3Ze1YlMy0xBhDz1iqPqNgAlrbzUerxUll0dxoJ7DCdjvOErVoUZrRP7OdWjfjzPRVgEr0twJFoeUMA5oIuqPMdev71I8AnL4d3KODNYVaRGn58IjF6n3DL9kHD5W5JBfbluKVIXAqJXhewbBIhb5FOyhdt5NA3FjcZLrxG8LwezRtp9734iQPnrROXK6agAI2O8oYmWqEZmJbafnL0TEapMyka1uC26pVqcLMfU3tRFgxnXVmfEMEX9kqOiW9tFcxdAfUJlfbQIeuUkUvkTO2AgldkPetBPdFnn3Uutcn7zsPk7ag5HorwpYeeprgzJP8SI7EjpiZgNxV1VIsgCSW8RZIi98LHc32j4U3bNVIeKy3N4Qrzr3Flg9r014RikQtIVU6pYbKt4vtJ4bhCi1mkGaiJpRb16jXQoHC8YEUsmjAKNHquvmEjCMZ0EClkNCB5vIJSwmnhrbRAPHM2KIyQNUbuuzibvqg4E7b1n7cB7VA9elo9drNJAIZXmUTuQ5AkJ5WINKBCUfy6Xmp1E8cYRZ0eakvDVLRcGmQX9zAUA0smjeLLqxEfHywnvBLwVka5k2KgngfXRd4BsdlMwflSI2ecmDjbn590Izkmj16rEpTkrmsZG6SGL8EcrsJ1L6KMABGuA71dLC781mjsClbQfCdLLC8JG6misJzAt3nITUtZaBHCvMOrLPAtht80DMEaEQ3W4xVckR1Ebh0QIt1WZkXI9LVPl7oBBbBQTk7O4uIP5tIwlctATkg7GI83GFVcWhmcEtZ0ThvjpWRRHTRcPZmawjAKbtOzPHNlvnmI7w69dmMAf3d0bWQyziJC3j2lp35otgEIS4EBi6JZqmZeVvTeLfJ8tvHgy0jopMprrkyeu2HSyj4uoqsO" << i;
        
        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }*/
    
    // Iterate over each item in the database and print them
    //leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    
    /*for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        cout << it->key().ToString() << " : " << it->value().ToString() << endl;
    }*/

    leveldb::ReadOptions readOptions;

    std::string str;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 1000000; ++i) {
        int r = rand() % 10000000;
        db->Get(readOptions, "Key" + std::to_string(r), &str);
    }
    
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "It took me " << time_span.count()/1000000 << " seconds.";
    std::cout << std::endl;

    //std::cout << str << std::endl;


    
    /*if (false == it->status().ok())
    {
        cerr << "An error was found during the scan" << endl;
        cerr << it->status().ToString() << endl; 
    }*/
    
    // delete it;
    
    // Close the database
    delete db;
}