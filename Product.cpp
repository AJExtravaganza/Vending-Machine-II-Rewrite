#include "Product.hpp"

Product::Product(): currentQty(0), initialQty(0), price(0), description("Error: Uninitialised Product"), SKU("None")
{

}

Product::Product(std::string SKUIn, int initialQtyIn, int priceIn, std::string descriptionIn): currentQty(initialQty), initialQty(initialQtyIn), price(priceIn), description(descriptionIn), SKU(SKUIn)
{

}

Product::Product(std::string SKUIn, int initialQtyIn, std::vector<Product> &database): currentQty(0), initialQty(0), price(0), description("Error: Uninitialised Product"), SKU("None")
{
    bool productUninitialised = true;

    for (unsigned int i = 0; ((i < database.size()) && productUninitialised); i++)
    {
        if(SKUIn == database[i].SKU)
        {
            initialQty = initialQtyIn;
            currentQty = initialQty;
            price = database[i].price;
            SKU = database[i].SKU;
            description = database[i].description;
            productUninitialised = false;
        }
    }
}

