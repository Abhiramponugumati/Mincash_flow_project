# Welcome to the Enhanced Cash Flow Minimizer System README !!

This system minimizes the *number of transactions* among multiple banks in the different corners of the world that use *different modes of payment* and *different currencies*. There is one world bank (with all payment modes and currencies) to act as an intermediary between banks that have no common mode of payment or different currencies.

# Getting Started

Let's take an example. say we have the following banks:
1. World_Bank (World bank)
2. Goldman_Sachs
3. Wells_Fargo
4. Royal_Bank_of_Canada
5. Westpac
6. National_Australia_Bank

Following are the payments to be done:\
&emsp;&emsp;&emsp;    *Debtor Bank&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;                **Creditor Bank* &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; *Amount*
1. Goldman_Sachs   &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;             World_Bank &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;             $100
2. Goldman_Sachs   &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;              Wells_Fargo &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;                $300
3. Goldman_Sachs   &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;              Royal_Bank_of_Canada  &emsp;&emsp;&emsp;&emsp;&nbsp;      $100
4. Goldman_Sachs   &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;              Westpac &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp; $100
5. National_Australia_Bank &emsp;&emsp;&nbsp;&nbsp;       World_Bank &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp; $300
6. National_Australia_Bank &emsp;&emsp;&nbsp;&nbsp;       Royal_Bank_of_Canada &emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; $100
7. World_Bank         &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;       Wells_Fargo &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp; $400
8. Wells_Fargo             &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;       Royal_Bank_of_Canada &emsp;&emsp;&emsp;&emsp;&nbsp; $200
9. Royal_Bank_of_Canada    &emsp;&emsp;&nbsp;&nbsp;&nbsp;&nbsp;      Westpac &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp; $500

*But there's a catch!!*
Each Bank only supports a set of modes of payments and operates in a specific currency. Banks can make or receive payments *only* via those modes and in their currency. Only World Bank supports *all* modes of payments and *all* currencies.

In our current example we have three payment modes and multiple currencies:
*Payment Modes:*
1. Google_Pay
2. AliPay
3. Paytm

*Currencies:*
1. USD (US Dollar)
2. CAD (Canadian Dollar)
3. AUD (Australian Dollar)

Following is the list of Banks with their currencies and supported payment modes:
1. World_Bank &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;- &emsp; USD &emsp; Google_Pay, AliPay, Paytm
2. Goldman_Sachs &emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;- &emsp; USD &emsp; Paytm
3. Wells_Fargo &emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&emsp;&nbsp;- &emsp; USD &emsp; Google_Pay, AliPay
4. Royal_Bank_of_Canada &nbsp;&emsp;&nbsp;&nbsp;&nbsp;- &emsp; CAD &emsp; AliPay
5. Westpac &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;&nbsp;&nbsp;&nbsp; - &emsp; AUD &emsp; Google_Pay, Paytm
6. National_Australia_Bank &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - &emsp; AUD &emsp; AliPay, Paytm

To pick the first Bank, we calculate the *net amount* for every Bank by using the below formula and store them in list:

net amount = [Sum of all *credits(amounts to be received)] - [Sum of all **debits*(amounts to pay)]

Now the idea is that we are finding the bank which has minimum net amount(max debtor) (say Bank X, net amount x) and then finding the bank which has the maximum net amount( max creditor) (say Bank Y, net amount y) and also has a common payment mode (say M1) *and same currency* with the former bank. Then we find minimum of absolute value of x and y, lets call it z.\
Now X pays the amount z to Y. 

*If no common payment mode or different currency exists, then World Bank acts as intermediary. X pays to World Bank, and World Bank pays to Y. A **2% fee* is charged by World Bank for this service.

Then 3 cases may arrive:
1. If (magnitude of x) < y  =>  X is completely settled and so removed from the list.
2. If (magnitude of x) > y  =>  Y is completely settled and so removed from the list.
3. If (magnitude of x) = y  =>  X and Y both are completely settled and so both are removed from the list.

The same process is repeated for the remaining banks.\
For the current example, the transactions for minimum cash flow are as follows:

*Goldman_Sachs pays $600 to World_Bank via Paytm*\
*World_Bank pays $400 to Wells_Fargo via Google_Pay*\
*World_Bank pays $200 to Royal_Bank_of_Canada via AliPay*\
*National_Australia_Bank pays $400 to World_Bank via Paytm*\
*World_Bank pays $400 to Westpac via Google_Pay*

*Total fee paid to World Bank: $24.00*

The system also generates a *DOT file* for graph visualization using Graphviz.

# How to Use?
This system is completely *menu-driven*. So when you will run the C++ Application, it will guide you and show you the final output.\
The system will ask for:
1. Number of banks
2. For each bank: name, currency, number of payment modes, and the payment modes
3. Number of transactions
4. For each transaction: debtor bank, creditor bank, amount

The system will then display:
- Optimized transaction list
- Total fees paid to World Bank
- Generate a DOT file for visualization

*To visualize the graph:*

dot -Tpng transactions.dot -o graph.png


*Enhanced Features:*
- Multi-currency support
- Transaction fee calculation
- Automatic graph generation
- World Bank intermediary system
- Payment mode compatibility checking

Thank you!!
Happy learning :)
