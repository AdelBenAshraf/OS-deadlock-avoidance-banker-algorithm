#include <iostream>
#include <vector>
using namespace std;

bool isSafe();
void request();
void release();
void copy();
void recover();
void printData(const vector<vector<int>>&, const vector<vector<int>>&, const vector<vector<int>>&, const vector<int>&);
void bankerMain();
int n, m;

vector<int> available;

vector<vector<int>> maximum;

vector<vector<int>> allocation;

vector<vector<int>> need;

vector<vector<int>> copyOfNeed;

vector<int> copyOfAvailable;

vector<vector<int>> copyOfAllocation;

vector<vector<int>> copyOfMaximum;

vector<int> copyOfAvailableTry;


int main() {

    cout << "Please enter the number of processes\n";
    cin >> n;
    cout << "Please enter the number of resources\n";
    cin >> m;
    available = copyOfAvailable = copyOfAvailableTry = vector<int>(m);
    maximum = allocation = need = copyOfAllocation = copyOfNeed = copyOfMaximum = vector<vector<int>>(n, vector<int>(m));

    cout << "Please enter the the available resources separated with spaces\n";
    for (int i = 0; i < m; i++)
    {
        cin >> available[i];
        copyOfAvailable[i] = available[i];
    }

    cout << "Please enter the maximum allocations of each process\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maximum[i][j];
            copyOfMaximum[i][j] = maximum[i][j];
        }
    }

    cout << "Please enter the allocations of each process\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
            copyOfAllocation[i][j] = allocation[i][j];
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            copyOfNeed[i][j] = need[i][j];
        }
    }


    bankerMain();

    return 0;
}


bool isSafe()
{

    vector<vector<int>> copyOfNeedSafe(n, vector<int>(m));

    vector<int> copyOfAvailableSafe(m);

    vector<vector<int>> copyOfAllocationSafe(n, vector<int>(m));

    vector<vector<int>> copyOfMaximumSafe(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            copyOfAllocationSafe[i][j] = copyOfAllocation[i][j];
            copyOfNeedSafe[i][j] = copyOfNeed[i][j];
            copyOfAvailableSafe[j] = copyOfAvailable[j];
            copyOfMaximumSafe[i][j] = copyOfMaximum[i][j];
        }
    }

    printData(copyOfAllocationSafe, copyOfMaximumSafe, copyOfNeedSafe, copyOfAvailableSafe);
    vector<bool> isFinished(n, false);
    int finished = 0;
    int dead = 0;

    for (int i = 0; i < n && finished < n; i = (i + 1) % n)
    {
        int lessOrEqual = 0;
        if (dead == n)
        {
            cout << "The system is unsafe." << endl;
            return false;
        }
        if (isFinished[i])
        {
            dead++;
            continue;
        }
        cout << "P" << i << " requesting resources\n\n";

        for (int j = 0; j < m; j++)
        {
            if (copyOfNeedSafe[i][j] <= copyOfAvailableSafe[j])
                lessOrEqual++;
        }
        if (lessOrEqual != m)
        {
            cout << "Request denied\n\n";
            dead++;
        }
        else
        {
            for (int j = 0; j < m; j++)
            {
                copyOfAvailableSafe[j] += copyOfAllocationSafe[i][j];
                copyOfAllocationSafe[i][j] = 0;
                copyOfNeedSafe[i][j] = 0;
            }
            isFinished[i] = true;
            finished++;
            dead = 0;
            cout << "P" << i << " approved\n\n";
            printData(copyOfAllocationSafe, copyOfMaximumSafe, copyOfNeedSafe, copyOfAvailableSafe);


        }
    }
    cout << "The system is safe.\n" << endl;
    copyOfAvailableTry = copyOfAvailableSafe;
    return true;
}

void copy()
{
//    copyOfAllocation = allocation;
//    copyOfNeed = need;
//    copyOfMaximum = maximum;
//    copyOfAvailable = available;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            copyOfAllocation[i][j] = allocation[i][j];
            copyOfNeed[i][j] = need[i][j];
            copyOfMaximum[i][j] = maximum[i][j];
            copyOfAvailable[j] = available[j];
        }
    }
}

void request()
{
    copy();
    int processNum = 0;
    vector<int> requests;
    int resource = 0;
    cout << "Please enter the process number you want it to request more resources: ";
    cin >> processNum;
    cout << "Please enter the amount of each resource you want to request: ";

    for (int i = 0; i < m; i++)
    {
        cin >> resource;
        requests.push_back(resource);
    }
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        if (requests[i] + copyOfMaximum[processNum][i] <= copyOfAvailableTry[i])
            count++;
    }

    if (count == m)
    {
        for (int i = 0; i < m; i++)
        {
            copyOfNeed[processNum][i] += requests[i];
            copyOfMaximum[processNum][i] += requests[i];
        }
        bankerMain();
    }
    else
    {
        cout << "You want to request resources more than the system can handle\n";
        return;
    }



}

void release()
{
    copy();
    vector<int> release;
    int processNum;
    int resource;
    cout << "Please enter the process number you want it to release resources: ";
    cin >> processNum;
    cout << "Please enter the amount of each resource you want to release: ";
    for (int i = 0; i < m; i++)
    {
        cin >> resource;
        release.push_back(resource);
    }
    int count = 0;
    for (int i = 0; i < m; i++)
    {
        if (release[i] <= copyOfAllocation[processNum][i])
            count++;
    }
    if (count == m)
    {
        for (int i = 0; i < m; i++)
        {
            copyOfAllocation[processNum][i] -= release[i];
            copyOfNeed[processNum][i] += release[i];
            copyOfAvailable[i] += release[i];
        }
        bankerMain();
    }
    else
    {
        cout << "You want to release more resource than the already allocated\n";
        return;
    }
}

void recover()
{
    cout << "There is a deadlock we are recovering it\n";
    cout << "The victim is the one who has the greatest allocation\n";
    int max_allocation = 0, victim = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += copyOfAllocation[i][j];
        }
        if (sum > max_allocation) {
            max_allocation = sum;
            victim = i;
        }
    }
    for (int j = 0; j < m; j++)
    {
        copyOfAvailable[j] += copyOfAllocation[victim][j];
        copyOfNeed[victim][j] += copyOfAllocation[victim][j];
        copyOfAllocation[victim][j] = 0;
    }
}

void printData(const vector<vector<int>>& alloc, const vector<vector<int>>& max, const vector<vector<int>>& ne, const vector<int>& avail)
{

    bool flag = true;
    cout << " Process        Allocation           Max              Need           Available\n";
    cout << "=========      ============        ========         ========        ============\n";
    for (int i = 0; i < n; i++)
    {
        cout << "    P" << i << "            ";

        for (int j = 0; j < m; j++)
            cout << alloc[i][j] << " ";

        cout << "            ";
        for (int j = 0; j < m; j++)
            cout << max[i][j] << " ";
        cout << "            ";

        for (int j = 0; j < m; j++)
            cout << ne[i][j] << " ";
        cout << "           ";
        if (flag)
        {
            for (int j = 0; j < m; j++)
                cout << avail[j] << " ";
            flag = false;
        }

        cout << "\n";
    }
    cout << "\n\n";
}

void bankerMain()
{
    while (!isSafe())
    {
        recover();
    }
    int input = 0;
    while (input != 3)
    {
        cout << "Please enter a number for the function you want to make: \n";
        cout << "1- Request\n2- Release\n3- Quit\n";
        cin >> input;
        if (input == 1)
            request();
        else if (input == 2)
            release();
        else if (input == 3)
            exit(0);
    }
}

/*
 not safe testcase:

available = 0 0 0

maximum =
0 0 0
4 0 2
3 0 4
3 1 1
0 0 4

allocation =
0 0 0
2 0 0
3 0 3
2 1 1
0 0 2

safe testcases:

available = 0 0 0

maximum =
0 0 0
4 0 2
3 0 3
3 1 1
0 0 4

allocation =
0 0 0
2 0 0
3 0 3
2 1 1
0 0 2
//////////////////////////////////////////////////

available = 3 3 2

maximum =
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

allocation =
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
*/