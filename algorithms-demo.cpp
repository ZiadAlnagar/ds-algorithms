#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

const int TitleArrMax = 10
, ProductArrMax = 100
, QuantityMax = 500
, ValueMax = 100;
const float PriceMax = 100.0;

bool interact = true;
int gui_goto = 0, ExitList_Gui = -1;;
int ProductsLast = 0
, Budget;
float GivenAmount;
string line = "                                   _________________________________________________\n";
string endline = "                                  |_________________________________________________|\n";
string spacing = "                                  |                                                 |\n";
string spacingr = "                                  |         ";
string spacingl = "           |\n";
string position = "         ";

float MoneyValues[] = { 500, 100, 50, 10, 5, 1, .50, .25 };
int MoneyArrLen = *(&MoneyValues + 1) - MoneyValues;
string ProductTitle[TitleArrMax] = { "Eggs", "Soap", "bars", "aspirin", "soap", "Mouthwash", "Tissues", "Cheese", "Pepper", "Milk" };

struct Product
{
    unsigned int Id;
    string Title;
    float Price;
    int Quantity;
    int Value;
    bool exist;
} Products[ProductArrMax], ProductsSorted[ProductArrMax];

string ItemsSold[] = { "Eggs", "Tissues", "aspirin", "Eggs", "Soap", "Milk", "Pepper", "Eggs", "Milk", "Eggs", "Mouthwash", "Soap", "Milk", "Cheese", "Cheese", "Eggs", "Eggs" };
int ISold_Len = *(&ItemsSold + 1) - ItemsSold;

void Clear()
{
    system("cls");
}

void Gui(int gui);

float SetPrice()
{
    float x = roundf((static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / PriceMax))) * 100) / 100.0;
    return x;
};

int SetRandom(int Max)
{
    int x = rand() / (RAND_MAX / Max);
    return x;
}

void CalcChange(float amount)
{
    vector<float> Change;
    int occurnce = 1;

    for (int i = 0; i < MoneyArrLen; i++)
    {
        while (amount >= MoneyValues[i])
        {
            amount -= MoneyValues[i];
            Change.push_back(MoneyValues[i]);
        }
    }
    for (int i = 0; i < Change.size(); i++)
    {
        if (i + 1 == Change.size() && occurnce == 1)
        {
            cout << "\n                                   " << occurnce << " paper(s) of type " << Change[i] << "$";
            break;
        }
        else if (i + 1 == Change.size())
        {
            cout << occurnce << " paper(s) of type " << Change[i] << "$";
            break;
        }
        if (Change[i] == Change[i + 1])
        {
            occurnce++;
        }
        else
        {
            if (i == 0)
                cout << "                                   " << occurnce << " paper(s) of type " << Change[i] << "$"
                << " + ";
            else
                cout << occurnce << " paper(s) of type " << Change[i] << "$"
                << " + ";
            occurnce = 1;
        };
    }
}

void ViewProductsList(Product Products[])
{
    Clear();
    for (int i = 0; i < ProductArrMax; i++)
    {
        if (!Products[i].exist)
            break;
        cout << "                                   " << "ID:        " << Products[i].Id << endl;
        cout << "                                   " << "Title:     " << Products[i].Title << endl;
        cout << "                                   " << "Price:     " << Products[i].Price << endl;
        cout << "                                   " << "Quantity:  " << Products[i].Quantity << endl
            << endl << line << endl;
    }
    cout << "\n\n                                   [0] Go to Main Menu\n\n";
    cout << "\n                                   Enter Your Choice : ";
    cin >> ExitList_Gui;
}

void Swap(Product* x, Product* y)
{
    Product tmp = *x;
    *x = *y;
    *y = tmp;
}

int Divide(Product Products[], int Low, int High)
{
    int Piv = Products[High].Quantity;
    int i = (Low - 1);

    for (int x = Low; x <= High - 1; x++)
    {
        if (Products[x].Quantity < Piv)
        {
            i++;
            Swap(&Products[i], &Products[x]);
        }
    }
    Swap(&Products[i + 1], &Products[High]);
    return (i + 1);
}

void QuickSort(Product Products[], int Low, int High)
{
    if (Low < High)
    {
        int i = Divide(Products, Low, High);
        QuickSort(Products, Low, i - 1);
        QuickSort(Products, i + 1, High);
    }
}

void ViewSortedProductsList()
{
    copy(begin(Products), Products + ProductsLast + 1, begin(ProductsSorted));
    QuickSort(ProductsSorted, 0, ProductsLast);
}

int Restock(int Budget, Product PPrice[], Product PVal[], int ArrLen)
{
    int i, w;
    vector<vector<int>> K(ArrLen, vector<int>(Budget));
    for (i = 0; i < ArrLen; i++)
    {
        for (w = 0; w < Budget; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (PPrice[i - 1].Price <= w)
                K[i][w] = max(PVal[i - 1].Value +
                    K[i - 1][w - PPrice[i - 1].Price],
                    K[i - 1][w]);

            else
                K[i][w] = K[i - 1][w];
        }
    }
    return K[ArrLen - 1][Budget - 1];
}

void GetMostSold(string Sold[], int Sold_Len)
{
    int j = 0;
    vector<int> SoldCnt;
    string MostSold;
    int MostSold_Cnt = 0;
    sort(Sold, Sold + Sold_Len);
    for (int i = 0; i < Sold_Len; i++) {
        if (i == 0) SoldCnt.push_back(0);
        if (!((i + 1) == Sold_Len)) {
            if (Sold[i].compare(Sold[i + 1]) == 0)
            {
                SoldCnt[j]++;
            }
            else {
                if (j == 0) { MostSold = Sold[i]; MostSold_Cnt = SoldCnt[j]; }
                else {
                    if (MostSold_Cnt < SoldCnt[j]) {
                        MostSold = Sold[i];
                        MostSold_Cnt = SoldCnt[j];
                    }
                }
                SoldCnt.push_back(0);
                j++;
            }
            if (i == (Sold_Len - 2)) {
                Clear();
                cout << "\n\n\n                                   Most Sold Item is " << MostSold
                    << "\n\n                                   Sold Count: " << MostSold_Cnt + 1 << endl << line;
            }
        }
    }
}

void main()
{
    srand(time(0));

    Product* ptr = &Products[0];

    for (int i = 0; i < TitleArrMax; i++)
    {
        ptr->Id = i;
        ptr->Title = ProductTitle[i];
        ptr->Price = SetPrice();
        ptr->Quantity = SetRandom(QuantityMax);
        ptr->Value = SetRandom(ValueMax);
        ptr->exist = true;
        ptr++;
        ProductsLast = i;
    }

    while (interact)
        Gui(gui_goto);
}

void Gui(int gui)
{
    interact = false;
    int ClacChange_Gui = -1, ViewList_Gui = -1, MostSold_Gui = -1, Restock_Gui = -1;
    ExitList_Gui = -1;
    switch (gui)
    {
    case 0:
        Clear();
        cout << line << spacing << spacing
            << spacingr << "[1] Casher: Change Calculator" << spacingl << spacing
            << spacingr << "[2] List Products            " << spacingl << spacing
            << spacingr << "[3] List Amount of Sold Items" << spacingl << spacing
            << spacingr << "[4] Restock Value Calculator " << spacingl << spacing
            << spacing << endline;
        break;

    case 1:
        Clear();
        cout << "\n\n                                   "
            << "Enter Given Amount: ";
        cin >> GivenAmount;
        cout << endl
            << line << "\n\n";
        CalcChange(GivenAmount);
        cout << "\n\n\n"
            << line << "\n\n";
        cout << "                                   "
            << "[1] Another one!\n\n"
            << "                                   "
            << "[0] Go to Main Menu\n\n";
        cout << "\n                                   Enter Your Choice : ";
        cin >> ClacChange_Gui;
        break;

    case 2:
        Clear();
        cout << "\n\n\n                                   "
            << "[1] View Products List\n\n"
            << "                                   "
            << "[2] List Products Sorted by Quantity (Ascending)\n\n"
            << "                                   "
            << "[0] Go to Main Menu\n\n";
        cout << "\n                                   Enter Your Choice : ";
        cin >> ViewList_Gui;
        if (ViewList_Gui == 1) ViewProductsList(Products);
        else if (ViewList_Gui == 2) {
            ViewSortedProductsList();
            ViewProductsList(ProductsSorted);
        };
        break;

    case 3:
        GetMostSold(ItemsSold, ISold_Len);
        cout << "\n\n                                   [0] Go to Main Menu\n\n";
        cout << "\n                                   Enter Your Choice : ";
        cin >> MostSold_Gui;
        break;

    case 4:
        Clear();
        cout << "\n\n                                   "
            << "Enter Budget: ";
        cin >> Budget;
        cout << endl
            << line << "\n\n";
        cout << "                                   Effective Value of Restock is " << Restock(Budget, Products, Products, ProductsLast);
        cout << "\n\n                                   Minimum Required is (500) if below, please consider increasing the budget!";
        cout << "\n\n\n" << line
             << "\n\n\n                                   [0] Go to Main Menu";
        cout << "\n\n\n                                   Enter Your Choice : ";
        cin >> Restock_Gui;
        break;

    default:
        break;
    }
    cout << "\n                                   Enter Your Choice : ";
    if (ClacChange_Gui == 1)
        gui_goto = 1;
    else if (ClacChange_Gui == 0 || ViewList_Gui == 0 || ExitList_Gui == 0 || MostSold_Gui == 0 || Restock_Gui == 0)
        gui_goto = 0;
    else
        cin >> gui_goto;
    interact = true;
}