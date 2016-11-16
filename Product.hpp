#include <string>
#include <vector>

struct Product
{
    int currentQty;
    int initialQty;
    int price;
    std::string description;
    std::string SKU;

    Product();
    Product(std::string SKUIn, int initialQtyIn, int priceIn, std::string descriptionIn);
    Product(std::string SKUIn, int initialQtyIn, std::vector<Product> &database);
};

