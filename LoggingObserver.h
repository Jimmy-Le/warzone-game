//
// Created by Keishaun on 2025-11-10.
//

#ifndef WARZONE_GAME_LOGGINGOBSERVER_H
#define WARZONE_GAME_LOGGINGOBSERVER_H

#include <vector>
#include <memory>
#include <string>

using namespace std;

class ILoggable
{
    public:
        ILoggable();
        virtual ~ILoggable();
        virtual std::string stringToLog() = 0;
};

class Observer
{
    public:
        Observer();
        virtual ~Observer();
        virtual void update(ILoggable* loggable) = 0;
};

class Subject
{
    public:
        Subject();
        virtual ~Subject();
        virtual void attach(Observer* observer);
        virtual void detach(Observer* observer);
        virtual void notify(ILoggable* loggable);
    private:
        std::shared_ptr<std::vector<Observer*>> observers;
};

class LogObserver : public Observer
{
    public:
        LogObserver();
        ~LogObserver() override;
        void update(ILoggable* loggable) override;
};

#endif //WARZONE_GAME_LOGGINGOBSERVER_H