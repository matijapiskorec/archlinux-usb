# Ledger double accounting system from command line

Ledger is a powerfull double accounting system from the command line. Install it with:
```
sudo pacman -Syu ledger
```

Create your journal file where you will keep all your financial transactions. By convention it has `.dat` extension, but you can use whatever.
```
vim ledger.dat
```

Financial records have a very flexible format. The only requirements are the following:
1. Start of the transaction (typically a date) is at the start of the line.
2. Accounts are intended by at least one space.
3. There must be at least two spaces, or a tab, between an account and the amount.

A typical transaction looks like this:
```
2021/2/7 Payee - to whom the payment was done
    ; Optional comment on the transaction
    Expenses:Groceries:Bread       100 USD
    Expenses:Groceries:Milk         20 USD
    Assets:BankAccount
```

Transaction should have a zero sum - if you leave exactly one entry without a sum it is assumed it balances the transaction. The currency is arbitrary, it can be whatever you want (USD, HRK, apples), with positive or negative values.

Definition of assets/expenses/liabilities is also arbitrary, you can write whatever you want, with as many subcategories as you need. A recommendation is that at the highest level you have five sorts of accounts:
1. Expenses: where money goes,
2. Assets: where money sits,
3. Income: where money comes from,
4. Liabilities: money you owe,
5. Equity: the real value of your property.

In addition to these I add couple of my own definitions:
6. Funds: virtual accounts for tracking money to spend
7. Budget: virtual accounts for tracking money spent

And some subcategories:
8. Income:Receivables: money you received from someone, usually for a specific purpose
9. Assets:Reimbursements: money that someone owns to you because you made an expense

An example of how to initialize your ledger with an initial state:
```
2021/2/7 Initial bank account balance 
    Assets:Bank:Account1        -5.021 HRK
    Assets:Bank:Account2         1.100,27 EUR
    Expenses:Cash                  142 HRK
    Equity:Initial
```

As you can see, initial state can even be negative:-)

When you make an expense, just enter it in the way described above, making sure to put your money source as the last entry. As you can see above if you are dealing with cash it is easier to just regard it as an expense right away. In general if you withdraw cash from ATM you record it as this:
```
2021/2/7 ATM
    Expenses:Cash       500 HRK
    Assets:Bank:Account1
```

If at some point to you want to track a specific cash expenditure you can simply move it from the `Expenses:Cash` to a corresponding category:
```
2021/2/7 Pizza restaurant
    Expenses:Dining         75 HRK
    Expenses:Cash
```

NOTE: Actually, I'm back at designating cash as an asset instead of an expense! Reports are a bit less confusing in that way, but I'll see. Another solution (proposed [here](https://rolfschr.github.io/gswl-book/latest.html)) is to define cash account as `Expenses:Unknown` so that there is less confusion, by getting money in cash form you consider it unkown by default, and then you transfer from it if you want to track some big cash expenditure.

If at some point you loose track of any of your accounts, for example because you didn't enter transactions for a while, you can reset it by setting it to a specific amount via the balance assignment:
```
2021/2/9 Adjustment
    Assets:Cash                 = 72 HRK
    Equity:Adjustments
```

The balance assignment (`= 72 HRK`) is otherwise used for assertions of how much we expect our account to be worth after the transaction - if the assertion is not satisfied then an error is thrown. Here, this balance assignment is used to set the account to a specific value, instead of simply adding or subtracting some value from it. This is the only case where it is allowed to have a transaction with two empty values (both values for Assets:Cash and Equity:Adjustments are undefined)!

Ledger can be run in interactive mode, call it with a file name argument but without any other arguments:
```
ledger -f ledger.dat
```

In the interactive mode all commands are identical to the one in terminal. The only expection is composing long boolean expressions, your shell might have problems parsing this. For example, in the interactive mode you can output balance with the expression like this:
```
balance not Equity and not Beer
balance Assets Expenses ; This works in non-interactive mode as well!
balance Expenses and not Bills
```

I will use the shell syntax (non-interacitve mode) in the remainder of this tutorial.

To check you balances, assuming your journal file is `ledger.dat`:
```
ledger -f ledger.dat balance
ledger -f ledger.dat balance Assets Expenses
ledger -f ledger.dat balance !Equity
```

As you can see, you can define which categories you want to include or not - the example with `!Equity` (works only in the interactive mode, you can use `not Equity` in both modes) is usefull because we disregard the initial state, as well as large equity holdings which are not important for the current finances (for example, owning a house).

This is how you enter your salary:
```
2021/2/7 Salary
    Assets:Bank:Account1        7.010,12 HRK
    Income:Salary
```

This is how you enter your liability, for example if you have a credit card:
```
2021/2/7 Restaurant
    Expenses:Dining         150 HRK
    Liabilities:Mastercard
```

To show all transactions and a running total you have to register a report:
```
ledger -f ledger.dat register
ledger -f ledger.dat register Expenses
ledger -f ledger.dat register not Equity
```

Instead of `not Equity` you can use `!Equity`. You can use multiple accounts names or even payees (designated with `payee name` or `@name`:
```
ledger -f ledger.dat register Beer Wine
ledger -f ledger.dat register Beer @Pub
```

To print all accounts in your journal file: `ledger -f ledger.dat accounts`
To print all payees in your journal file: `ledger -f ledger.dat payees`
To filter and print all payees in your journal file: `ledger -f ledger.dat payees @Pub`

Useful command `xact` helps to generate new transactions by using just a couple of keywords and comparing it with already present transactions. For example, try generating a new transaction with this:
```
ledger -f ledger.dat xact 2021/2/10 restaurant dining 150 cash
```

You can even ommit the date and it will use the current date, or part of the date (year for example) and it will fill in the information using current date.

For example, you just came from the store and spent 150 HRK for groceries in cash, and you want to append that to your ledger (date will be set to today):
```
ledger -f ledger.dat xact shopping groceries 150 cash >> ledger.dat
```

Now, if you want to specify that 50 HRK of those were actually beer, and you want to track that:
```
ledger -f ledger.dat xact shopping beer 50 groceries >> ledger.dat
```

Print transactions:
```
ledger -f ledger.dat print
```

Print transactions beginning (`-b` or `--begin`, inclusive) and/or ending (`-e` or `--end`, exclusive) at specific date:
```
ledger -f ledger.dat -b 2021/2/7 -e 2021/3/1 print
ledger -f ledger.dat -b 2021 -e 2022 print
```

The same date selection can be used with `balance` and `register` commands as well. Instead of begin/end period you can also define period directly with the `--period` or `-p` option, with many possible period expressions:
```
ledger -f ledger.dat -p "this month" print
```

Examples of period expressions:
```
weekly this month
daily this month
monthly this year
monthly in 2020
this week
this month
last week
last month
next week
from 10/1 to 10/5
from sep to oct
to tomorrow ; basically a period which includes today and everything before
to today ; does not include today!
```

Calculate monthly expenses, optionally with each month's expenses sorted by the amount:
```
ledger -f ledger.dat -M register Expenses
ledger -f ledger.dat -M --period-sort "(amount)" register Expenses
```

## Commodities

Following examples for purchases and selling of commodities are designed so that it is easy to track FIFO (First-In-First-Out) principle (also known as longest-held-first) for calculating capital gains, for example for taxation purposes.
```
2021/2/7 Stock purchase
    Assets:Broker           10 AAPL @ 25,00 EUR
    Assets:Broker                                 

2021/2/8 Stock purchase
    Assets:Broker           10 AAPL @ 35,00 EUR 
    Assets:Broker                                  

2021/2/9 Stock purchase
    Assets:Broker           3 AAPL @ 25,00 EUR 
    Assets:Broker                                  

2021/2/10 Stock purchase
    Assets:Broker           2 AAPL @ 25,00 EUR 
    Assets:Broker                                  

2021/2/11 Stock sale
    Assets:Broker              -10 AAPL {25,00 EUR} [2021/2/7] @ 50,00 EUR
    Assets:Broker               -5 AAPL {35,00 EUR} [2021/2/8] @ 50,00 EUR
    Assets:Broker              750 EUR              
    Income:Capital Gain
```

Tip: You can additionaly also calculate expenses for the transaction, for example under `Expenses:Broker:Commission`.
Tip: Instead of `Assets:Broker` you can also use your bank account, depending from where do your funds come from and where do they go.

The example above corresponds to the case where we bought a commodity in four separate purchases at two different prices, and then decided to sell some of them at the current price. Notice how we keep track of the basis price (in curly braces) as well as the reference date (in square braces) and the sale price (after the `@` sign) in our sale transaction. We have to do this manually as Ledger does not have any way of explicitly tracking transactions by FIFO principle.

Note that the actual price of the stock sale (`@ 50,00 EUR`) is not immediatelly applied - what is applied is rather the basis price in the curly braces (`{25,00 EUR}` for the first posting and `{35,00 EUR}` for the second). However, the actual price is not completelly ignored - ledger will still consider it as the most current price for the commodity, and will use it as such if there is no corresponding entry in the pricedb file. You can check that by running balance command with `--market` option (without specifying `--price-db` file) - the price of the remaining commodities in our portfolio will be assumed to be 50,00 EUR!
```
ledger -f ledger.dat --price-db pricedb.dat balance --market
```

In general, commodity purchases are easy as you only need to enter the ammount and the buying price. Ledger implicitly tracks identical commodities through lots - an ammount of commodity with its associated price and purchase date. You can confirm this by running balance command with `--lot-prices` and/or `--lot-dates` options (or `--lots` to include both):
```
ledger -f ledger.dat --price-db pricedb.dat balance --lots Broker Capital
```

For the commodity sale (if you want to follow FIFO principle) you have to manually track which lot of the commodity to include in your selling transaction. The FIFO principle states that you first have to sell the lots which you held the longest, and use their price as the basis price. The sale transaction above has an amount of commodity, its basis price (in curly braces), lot date (in square braces) and the final price at which we sold it. Note that the basis price will be the one that is actually applied, so the commodities will be sold for their basis price! As we defined a final amount which we received from the sale, which is obviously more than that, the remaining amount will be deducted from the capital expenses account. We can then apply an automatic taxation transaction to the capital gain account (for example, 0.12 which corresponds to the 12% rate).

For commodities where prices change through time you can define a pricedb file with prices which looks like this:
```
P 2021/2/11 BTC 38737,81 EUR
P 2021/2/11 ETH 1462,42 EUR
```

And include it in the following way:
```
ledger -f ledger.dat --price-db pricedb.dat 
```

For example, to see the balance in terms of market value of commodities:
```
ledger -f ledger.dat --price-db pricedb.dat balance --market
```

See the documentation for `--download` (`-Q`) option where you define a script which downloads the prices if needed and appends them to the pricedb file.

## Periodic and automatic transactions

You can define periodic transaction which are used for budgeting and forecasting:
```
~ Monthly
    Expenses:Bills:Phone        220 HRK
    Expenses:Dining             500 HRK
    Assets
```

Now when you run monthly (`-M` or `--monthly`) register or balance report with `--budget` option you will get deviation from your specified budget instead!
```
ledger -f ledger.dat --budget -M balance Expenses
ledger -f ledger.dat --budget -M register Expenses
```

You can define automatic transactions which are automatically executed if certain conditions are met:
```
= /Dining|Groceries/
    (Budget:Food)                  1
```

If there is no currency next to the number then it is considered as a multiplier - in this case exact amount will be added to the virtual account (posting) for food budget from every transaction containing account with names dining or groceries. The use of round brackets `()` for a virtual posting allows that the transaction does not balance to zero - this is needed in this case because budget for food is a virtual account, no physical money is moved there, it serves as a record how much money we spent for food (an expense which is otherwise attributed to different actual expense accounts). So a transaction with the virtual budget account like the one above will not belance to zero because expenses for food are credited (in equal amounts) to two accounts, one actual and one virtual.

If you want to impose a requirement that virtual postings balance, you can use square brackets `[]` instead of round ones.

You can use these automatic transactions for tracking funds - virtual accounts which track how much money you have for spending for certain purposes. For example, the following example assigns 10% of your income to the investment fund and it subtracts from it each time you actually invest funds to the appropriate account:
```
= /Income/
    (Funds:Investing)               -0.1

= /Assets:Investing/
    (Funds:Investing)               -1

; 10% of this income will be transfered to the virtual fund
2021/02/10 Salary
    Current
    Income:Salary               -7.010,00 HRK

; Full ammount of this investing will be deducted from the virtual fund
2021/02/10 Investing
    Assets:Investing            300 HRK
    Current
```

You can be more expressive in your automated transactions, for example you can reference the account name with `$account`: 
```
= expr account =~ /Expenses:Rent/ and payee =~ /Scrooge/
    $account                                $-150
    Receivables:Flatmates                   $150
```

In this example you are paying the rent for yourself and your roomate. The actual payment is for the full amount, but you want that the roomate's rent is automatically deducted from your expenses and transfered to the receivables, where they can then be transfered to your cash or banking account depending on how they payed you.

More expressive automated transactions are useful when you want to restrict them by date - for example, your income or expenses go up and you want to adjust your automatic transactions accordingly, but you don't want to change your previous transactions which are valid for their time period:
```
= /Income:Salary/ and expr date >= [2015/04/01] && date < [2015/06/01]
    * Assets:Funds:Water         $50.00
    * Liabilities:Funds:Water   $-50.00
```

## Good practices

Recording a simple transaction with only one posting can be done in one of the following ways:
```
2021/2/11 * Shopping
    Expenses:Groceries    10,00 HRK
    Assets:Cash          -10,00 HRK 
    
2021/2/11 * Shopping
    Expenses:Groceries    10,00 HRK
    Assets:Cash           

2021/2/11 * Shopping
    Expenses:Groceries    
    Assets:Cash           -10,00 HRK
```

The second way is preferable in most situations, but the third one comes in handy when we want to write something like this:
```
2021/2/11 * Shopping
    Expenses:Groceries    
    Expenses:Groceries:Beer  6,00 HRK
    Assets:Cash              -10,00 HRK
```

This is more convenient when we want to record some items separatelly (like beer in this example) but do not want to manually subtract the amount of these items from the final bill. The bill we have makes it easy to specify amounts for separate items as well as the final bill, so we can just let ledger calculate the remainder for all other items.

## Useful options

Show only accounts up to depth 2, and aggregate the rest: `--depth 2`
Flatten the output of the balance: `--flat`
Show only cleared (`*`) transactions: `--cleared`, `-C`
Show only pending (`!`) transactions: `--pending`
Show only uncleared transactions: `--uncleared`
Show only actual postings, not automated ones: `--actual`
Show only real posting, not virtual ones: `--real`, `-R`
Collapse all postings in register report to subtotals: `--subtotal`, `-s`
Displays posting which are related to all matched postings: `--related`, `-r`
Do not display total balance at the end (it's uninformative): `--no-total`
Set date format: `--date-format "%Y/%m/%d"`

Display current (`-c`) state, only real (`-R`) postings and cleared (`-C`) postings:
```
ledger -f ledger.dat -cCR --no-total not Equity
```

Display current state as of today:
```
ledger -f ledger.dat -c --no-total not Equity
```

## Archiving

The `equity` command prints out balances in the format of transactions, so it easy to use them for starting the new journal file (for example, after archiving older years):
```
ledger -f ledger.dat equity
```

To archive older journal entries (here, everything before 2021) you can print the older transactions into a separate file:
```
ledger -f ledger.dat -e 2021 print > ledger-older.dat
```

Now you can use print command to copy all entries in 2021 and after into a new working journal file, and initialize it with the output of equity command:
```
ledger -f ledger.dat -e 2021 equity > ledger-new.dat
ledger -f ledger.dat -b 2021 print >> ledger-new.dat
```

## Syntax highlighting in Vim

If you want syntax highlighting and autocompletion install vim-ledger plugin from Github:
```
https://github.com/ledger/vim-ledger
```

I'm using Vundle, so I put following lines in my `.vimrc`:
```
Plugin 'ledger/vim-ledger'
au BufReadPost *.dat set syntax=ledger
```

Then run `:PluginInstall` in Vim to install the newly added plugin. The second line is to recognize `.dat` files as ledger journal, otherwise use `.journal` or `.ldg`.

## Other plain text accounting programs

For the list of other plain text accounting programs see:
<https://plaintextaccounting.org/>

For example, beancount which is implemented in Python:
<http://furius.ca/beancount/>

hledger is a Haskell implementation of ledger:
<https://hledger.org/>

The Full Fledged hledger - usefull tips and tutorials for hledger:
<https://github.com/adept/full-fledged-hledger>

Cashier, an offline mobile app for entering transactions:
<https://cashier.alensiljak.eu.org/>

Getting started with Ledger:
<https://rolfschr.github.io/gswl-book/latest.html>

Useful articles on using ledger:
<https://www.petekeen.net/finance>

For example, how to implement envelope budgeting:
<https://www.petekeen.net/program-your-finances-envelope-budgeting>

Hint - create virtual accounts Assets:Funds and fill them automatically with a certain percent of your income. Then make automatic transactions to deduct from these funds every time you make an actual expense of corresponding category. These funds (envelopes, or budgets) keep track how much money did you dedicate for each particular category of expense.

Trading with Beancount, with useful information on how to track and calculate capital gains and profit/loss:
<https://docs.google.com/document/d/1WjARst_cSxNE-Lq6JnJ5CC41T3WndEsiMw4d46r2694/edit#>

