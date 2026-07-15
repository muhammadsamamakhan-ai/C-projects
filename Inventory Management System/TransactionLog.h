#ifndef TRANSACTIONLOG_H
#define TRANSACTIONLOG_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class TransactionLog
{
private:
    string logHistory[100];
    int logCount;

public:
    TransactionLog() : logCount(0) {}

    void recordAction(string action)
    {
        if (logCount < 100)
        {
            logHistory[logCount] = "Action: " + action;
            logCount++;
        }
    }

    void printAuditTrail()
    {
        cout << "\n===== AUDIT TRAIL =====" << endl;
        if (logCount == 0)
            cout << "No transactions recorded." << endl;
        else
            for (int i = 0; i < logCount; i++)
                cout << "[" << i + 1 << "] " << logHistory[i] << endl;
        cout << "=======================" << endl;
    }

    int totalLogs() { return logCount; }
};

#endif
