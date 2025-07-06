#include <bits/stdc++.h>
using namespace std;

class bank {
public:
    string name;
    string currency;
    int netAmount;
    set<string> types;
};

const double FEE_PERCENTAGE = 2.0;

int getMinIndex(bank listOfNetAmounts[], int numBanks) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;
        if (listOfNetAmounts[i].netAmount < min) {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(bank listOfNetAmounts[], int numBanks) {
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;
        if (listOfNetAmounts[i].netAmount > max) {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

pair<int, string> getMaxIndex(bank listOfNetAmounts[], int numBanks, int minIndex, bank input[], int maxNumTypes) {
    int max = INT_MIN, maxIndex = -1;
    string matchingType;

    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount <= 0 || i == minIndex) continue;

        if (input[i].currency != input[minIndex].currency) continue;

        vector<string> v(maxNumTypes);
        auto ls = set_intersection(
            listOfNetAmounts[minIndex].types.begin(), listOfNetAmounts[minIndex].types.end(),
            listOfNetAmounts[i].types.begin(), listOfNetAmounts[i].types.end(),
            v.begin());

        if ((ls - v.begin()) > 0 && listOfNetAmounts[i].netAmount > max) {
            max = listOfNetAmounts[i].netAmount;
            maxIndex = i;
            matchingType = *(v.begin());
        }
    }

    return make_pair(maxIndex, matchingType);
}

void generateDOT(vector<vector<pair<int, string>>> &ansGraph, bank input[], int numBanks) {
    ofstream fout("transactions.dot");
    fout << "digraph Transactions {\n";
    fout << "    rankdir=LR;\n";
    for (int i = 0; i < numBanks; ++i) {
        for (int j = 0; j < numBanks; ++j) {
            if (ansGraph[i][j].first > 0) {
                fout << "    \"" << input[i].name << "\" -> \"" << input[j].name << "\" [label=\"Rs "
                     << ansGraph[i][j].first << " via " << ansGraph[i][j].second << "\"];\n";
            }
        }
    }
    fout << "}\n";
    fout.close();
    cout << "\nDOT file 'transactions.dot' generated for Graphviz visualization.\n";
}

void printAns(vector<vector<pair<int, string>>> ansGraph, int numBanks, bank input[], double &totalFee) {
    cout << "\nThe transactions for minimum cash flow are as follows:\n\n";
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (i == j) continue;

            if (ansGraph[i][j].first != 0) {
                cout << input[i].name << " pays Rs " << ansGraph[i][j].first
                     << " to " << input[j].name << " via " << ansGraph[i][j].second << endl;

                // Fee for using World Bank as intermediary
                if (input[i].name != "World_Bank" && input[j].name != "World_Bank" &&
                    (ansGraph[i][j].second == "" || input[i].currency != input[j].currency)) {
                    double fee = ansGraph[i][j].first * (FEE_PERCENTAGE / 100.0);
                    totalFee += fee;
                }
            }
        }
    }
    cout << "\nTotal fee paid to World Bank: Rs " << fixed << setprecision(2) << totalFee << "\n";
}

void minimizeCashFlow(int numBanks, bank input[], unordered_map<string, int> &indexOf,
                      int numTransactions, vector<vector<int>> &graph, int maxNumTypes) {

    bank listOfNetAmounts[numBanks];
    for (int b = 0; b < numBanks; b++) {
        listOfNetAmounts[b].name = input[b].name;
        listOfNetAmounts[b].types = input[b].types;
        listOfNetAmounts[b].currency = input[b].currency;

        int amount = 0;
        for (int i = 0; i < numBanks; i++) amount += graph[i][b];
        for (int j = 0; j < numBanks; j++) amount -= graph[b][j];

        listOfNetAmounts[b].netAmount = amount;
    }

    vector<vector<pair<int, string>>> ansGraph(numBanks, vector<pair<int, string>>(numBanks, {0, ""}));

    int numZeroNetAmounts = 0;
    for (int i = 0; i < numBanks; i++)
        if (listOfNetAmounts[i].netAmount == 0) numZeroNetAmounts++;

    while (numZeroNetAmounts != numBanks) {
        int minIndex = getMinIndex(listOfNetAmounts, numBanks);
        pair<int, string> maxAns = getMaxIndex(listOfNetAmounts, numBanks, minIndex, input, maxNumTypes);
        int maxIndex = maxAns.first;

        if (maxIndex == -1) {
            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numBanks);
            int amount = abs(listOfNetAmounts[minIndex].netAmount);

            ansGraph[minIndex][0].first += amount;
            ansGraph[minIndex][0].second = *(input[minIndex].types.begin());

            ansGraph[0][simpleMaxIndex].first += amount;
            ansGraph[0][simpleMaxIndex].second = *(input[simpleMaxIndex].types.begin());

            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;

            if (listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            if (listOfNetAmounts[simpleMaxIndex].netAmount == 0) numZeroNetAmounts++;

        } else {
            int transactionAmount = min(abs(listOfNetAmounts[minIndex].netAmount),
                                        listOfNetAmounts[maxIndex].netAmount);

            ansGraph[minIndex][maxIndex].first += transactionAmount;
            ansGraph[minIndex][maxIndex].second = maxAns.second;

            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;

            if (listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            if (listOfNetAmounts[maxIndex].netAmount == 0) numZeroNetAmounts++;
        }
    }

    double totalFee = 0;
    printAns(ansGraph, numBanks, input, totalFee);
    generateDOT(ansGraph, input, numBanks);
}

int main() {
    cout << "\n\t\t******** Welcome to Enhanced CASH FLOW MINIMIZER SYSTEM ********\n\n";
    cout << "This system minimizes cash flow with support for:\n";
    cout << "- Common payment modes\n- Currency compatibility\n- World Bank intermediary\n- Transaction fees\n- Graph output\n\n";

    int numBanks;
    cout << "Enter number of banks: ";
    cin >> numBanks;

    bank input[numBanks];
    unordered_map<string, int> indexOf;
    int maxNumTypes;

    cout << "Enter bank details: name currency num_payment_modes mode1 mode2 ...\n";
    for (int i = 0; i < numBanks; i++) {
        cout << "Bank " << i << " : ";
        cin >> input[i].name >> input[i].currency;
        indexOf[input[i].name] = i;

        int numTypes;
        cin >> numTypes;
        if (i == 0) maxNumTypes = numTypes;

        while (numTypes--) {
            string type;
            cin >> type;
            input[i].types.insert(type);
        }
    }

    int numTransactions;
    cout << "Enter number of transactions: ";
    cin >> numTransactions;

    vector<vector<int>> graph(numBanks, vector<int>(numBanks, 0));
    cout << "Enter transactions: debtor creditor amount\n";
    for (int i = 0; i < numTransactions; i++) {
        string s1, s2;
        int amount;
        cin >> s1 >> s2 >> amount;
        graph[indexOf[s1]][indexOf[s2]] = amount;
    }

    minimizeCashFlow(numBanks, input, indexOf, numTransactions, graph, maxNumTypes);
    return 0;
}

