//
// Created by Keishaun on 2025-11-10.
//

#include "LoggingObserver.h"
#include <algorithm>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <memory>
#include <ostream>

using namespace std;

Subject::Subject()
{
    observers = std::make_shared<std::vector<Observer*>>();
}

Subject::~Subject()
{
    observers->clear();
}

void Subject::attach(Observer* observer)
{
    observers->push_back(observer);
}

void Subject::detach(Observer* observer)
{
    observers->erase(std::remove(observers->begin(), observers->end(), observer), observers->end());
}

void Subject::notify(ILoggable* loggable)
{
    for (auto* observer : *observers)
    {
        observer -> update(loggable);
    }
}

LogObserver::LogObserver() = default;

LogObserver::~LogObserver() = default;

void LogObserver::update(ILoggable* loggable)
{
    static bool firstOpen = true;

    std::ios_base::openmode mode = std::ios::app;

    if (firstOpen) {
        mode = std::ios::trunc;   // clear file the first time
        firstOpen = false;
    }
    std::ofstream logFile("gamelog.txt", mode);
    if (logFile.is_open())
    {
        logFile << loggable -> stringToLog() << endl;
        logFile.close();
    }
    else
    {
        std::cerr << "Error: Could not open gamelog.txt" << endl;
    }
}

ILoggable::ILoggable() = default;

ILoggable::~ILoggable() = default;

Observer::Observer() = default;

Observer::~Observer() = default;



