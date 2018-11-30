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

    // flags for monkey or no monkey, defaults to false
    bool monkey = false;

    // check args for --monkey-filters flag
    for (int i = 1; i < argc; ++i) { // loop through arguments checking for flags
        if (strcmp(argv[i], "--monkey-filters") == 0) {
            monkey = true;
            std::cout << "Monkey filters in use." << std::endl;
        }
    }

    // string for opening db to insert and test
    std::string db_file = "./monkey.db";

    // clean up old db before running tests
    std::string rm;
    rm += "rm -rf ";
    rm += db_file;
    system(rm.c_str());

    // Set up database connection information and open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    // bits per entry for default leveldb implementation
    options.filter_policy = leveldb::NewBloomFilterPolicy(5, monkey);

    // open the given db object
    leveldb::DB::Open(options, db_file, &db);

    // the 1kb value used for testing
    std::string value_string = "3353ZSt8TukolvuFuodXvliCdrf6N4kgO3Yv0tuNCwsMei1zROLp1Jg5XmMICe8ZFv2lOhuX9y939CPHWtjnYiP0B1jf2xD39CwPCq0gP3Iitr3Ze1YlMy0xBhDz1iqPqNgAlrbzUerxUll0dxoJ7DCdjvOErVoUZrRP7OdWjfjzPRVgEr0twJFoeUMA5oIuqPMdev71I8AnL4d3KODNYVaRGn58IjF6n3DL9kHD5W5JBfbluKVIXAqJXhewbBIhb5FOyhdt5NA3FjcZLrxG8LwezRtp9734iQPnrROXK6agAI2O8oYmWqEZmJbafnL0TEapMyka1uC26pVqcLMfU3tRFgxnXVmfEMEX9kqOiW9tFcxdAfUJlfbQIeuUkUvkTO2AgldkPetBPdFnn3Uutcn7zsPk7ag5HorwpYeeprgzJP8SI7EjpiZgNxV1VIsgCSW8RZIi98LHc32j4U3bNVIeKy3N4Qrzr3Flg9r014RikQtIVU6pYbKt4vtJ4bhCi1mkGaiJpRb16jXQoHC8YEUsmjAKNHquvmEjCMZ0EClkNCB5vIJSwmnhrbRAPHM2KIyQNUbuuzibvqg4E7b1n7cB7VA9elo9drNJAIZXmUTuQ5AkJ5WINKBCUfy6Xmp1E8cYRZ0eakvDVLRcGmQX9zAUA0smjeLLqxEfHywnvBLwVka5k2KgngfXRd4BsdlMwflSI2ecmDjbn590Izkmj16rEpTkrmsZG6SGL8EcrsJ1L6KMABGuA71dLC781mjsClbQfCdLLC8JG6misJzAt3nITUtZaBHCvMOrLPAtht80DMEaEQ3W4xVckR1Ebh0QIt1WZkXI9LVPl7oBBbBQTk7O4uIP5tIwlctATkg7GI83GFVcWhmcEtZ0ThvjpWRRHTRcPZmawjAKbtOzPHNlvnmI7w69dmMAf3d0bWQyziJC3j2lp35otgEIS4EBi6JZqmZeVvTeLfJ8tvHgy0jopMprrkyeu2HSyj4uoqsO";

    // number of keys, default is 1 million keys as per the paper
    int num_keys = 1000000;
    
    // Add num_keys key value pairs to the database
    leveldb::WriteOptions writeOptions;
    for (unsigned int i = 0; i < num_keys; ++i)
    {
        ostringstream keyStream;
        keyStream << "Key" << i;
        
        ostringstream valueStream;
        valueStream << value_string << i;
        
        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }

    // number of gets to perform for the test run, default to 16K for the given research info
    int num_gets = 16000;
    
    // read options, default
    leveldb::ReadOptions readOptions;

    // dummy string for performing the get operations on the db
    std::string str;

    // total time that is the amount of time for all of the aggregated gets
    std::chrono::duration<double> total_time = std::chrono::duration<double>(0);

    for (int i = 0; i < num_gets; ++i) {
        int r = rand() % num_gets;

        // time point for before the get
        std::chrono::high_resolution_clock::time_point t1 = 
            std::chrono::high_resolution_clock::now();

        // get operation that will not return a value
        db->Get(readOptions, "DNE" + std::to_string(r), &str);

        // time point for after the get
        std::chrono::high_resolution_clock::time_point t2 = 
            std::chrono::high_resolution_clock::now();

        // time span between the two points
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

        // total time is aggregated of time_span
        total_time += time_span;
    }

    std::cout << "It took me " 
        << std::chrono::duration_cast<std::chrono::microseconds>(total_time).count()/((double) num_gets)
        //<< total_time.count()/num_gets
        << " milliseconds on average for " << num_gets << " zero-point lookups.";
    std::cout << std::endl;

    // Close the database
    delete db;
}