#include "Product.hpp"
//DEBUG #include <iostream>

Product::Product(): currentQty(0), initialQty(0), price(0), description("Error: Uninitialised Product"), SKU("None")
{

}

Product::Product(std::string SKUIn, int initialQtyIn, int priceIn, std::string descriptionIn): currentQty(initialQtyIn), initialQty(initialQtyIn), price(priceIn), description(descriptionIn), SKU(SKUIn)
{

}

Product::Product(Product* warehouseStock, int requestedQty): currentQty(0), initialQty(0), price(warehouseStock->price), description(warehouseStock->description), SKU(warehouseStock->SKU)
{
    //DEBUG std::cout << warehouseStock->currentQty << warehouseStock->description << " before load.\n";

    initialQty = ((requestedQty <= warehouseStock->currentQty) ? requestedQty : warehouseStock->currentQty);
    currentQty = initialQty;
    warehouseStock->currentQty -= initialQty;

    //DEBUG std::cout << initialQty << description << " loaded from warehouse.\n";
    //DEBUG std::cout << warehouseStock->currentQty << warehouseStock->description << " after load.\n";
}

