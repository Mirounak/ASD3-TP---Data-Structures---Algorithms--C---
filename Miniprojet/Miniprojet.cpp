#include <iostream>
#include <vector>
using namespace std;

struct product{
    string name; //Product name (e.g.,"Keyboard")
    string category; //Category (Peripheral, Storage, Audio,etc.)
    float priceDA; //Price in Algerian Dinars
    int quantity; //Quantity in stock
    string brand; //Brand name (e.g., HP, Logitech,etc.)
    string modelNumber; //Model or reference number
};

int partition(vector<product>& products, int low, int high) {
    float pivot = products[high].priceDA; 
    int i = (low - 1); 

    for (int j = low; j < high; j++) {
        if (products[j].priceDA < pivot || 
           (products[j].priceDA == pivot && products[j].quantity > products[high].quantity)) {
            i++;
            swap(products[i], products[j]);
        }
    }
    swap(products[i + 1], products[high]);
    return (i + 1);
}



void quickSortProductsPriceA_QuantityD(vector<product>& products, int low, int high) {
    if (low >= high) return;
    if (low < high) {
        int pi = partition(products, low, high);

        quickSortProductsPriceA_QuantityD(products, low, pi - 1);
        quickSortProductsPriceA_QuantityD(products, pi + 1, high);
}
}

void selectionSortProductsByNameOrModel(vector<product>& products,char criterion){
    int n = products.size();
  if (criterion == 'n' || criterion == 'N' ){
    for (int i=0; i<n; i++){
        int min = i;
        for (int j=i; j<n; j++){
            if (products[j].name <= products[min].name){
                min = j;
            }
        }
        product temp = products[min];
        products[min] = products[i];
        products[i] = temp;
    }
} else {
    for (int i=0; i<n; i++){
        int min = i;
        for (int j=i; j<n; j++){
            if (products[j].modelNumber <= products[min].modelNumber){
                min = j;
            }
        }
        product temp = products[min];
        products[min] = products[i];
        products[i] = temp;
    }
}
     
}

void displayProducts(const vector<product>& products) {
    cout << "\nName\t        Category     Price(DA)  Qty\tBrand\t        Model\n";
    cout << "--------------------------------------------------------------------------\n";
    for (const auto& p : products) {
        cout << p.name << "\t"
             << p.category << "\t"
             << p.priceDA << "\t"
             << p.quantity << "\t"
             << p.brand << "\t"
             << p.modelNumber << endl;
    }
}


int main(){
    vector<product> products = {
        {"Keyboard", "Peripheral", 2500.0, 15, "Logitech", "K120"},
        {"Mouse", "        Peripheral", 1500.0, 30, "HP", "        M100"},
        {"External HDD", "Storage       ", 8000.0, 10, "Seagate", "        ST1000DM010"},
        {"Headphones", "Audio      ", 3000.0, 20, "Sony", "        MDR-ZX110"},
        {"Webcam", "        Peripheral", 4500.0, 5, "Logitech", "C270"},
        {"Monitor", "        Display      ", 12000.0, 8, "Dell", "        U2419H"},
        {"Graphic card", "Component", 75000.0, 3, "NVIDIA", "        RTX3060"}
    };

    int n = products.size();
    float prices[n];
    for(int i = 0; i < n; i++){
        prices[i] = products[i].priceDA;
    }
    cout << "before sort by price :" << endl;
    displayProducts(products);
    quickSortProductsPriceA_QuantityD(products, 0, n - 1);
    cout << " " << endl;
    cout << "After Sort Ascending:" << endl;
    displayProducts(products);
    cout << "before sort by name :" << endl;
    displayProducts(products);
    cout << "Sort by Name or ModelNumber? enter N/M" << endl;
    char criterion;
    cin >> criterion;
    selectionSortProductsByNameOrModel(products, criterion);
    cout << " " << endl;
    cout << "After Sort Ascending:" << endl;
    displayProducts(products);
    return 0;
}