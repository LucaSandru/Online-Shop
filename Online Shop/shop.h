#ifndef SHOP_H
#define SHOP_H

#include <stdbool.h>

#define MAX_PRODUCTS 10000
#define MAX_NAME_LENGTH 500
#define MAX_DESCRIPTION_LENGTH 2000
#define MAX_CART_ITEMS 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    float price;
    int stock;
} Product;

typedef struct {
    int productId;
    int quantity;
    char name[MAX_NAME_LENGTH];
    float price;
} CartItem;

extern Product products[MAX_PRODUCTS];
extern int numProducts;
extern CartItem cart[MAX_CART_ITEMS];
extern int numItemsInCart;

int getIntegerInput();
float getFloatInput();
void loadProductsFromFile();
void saveProductsToFile();
void saveCartToFile();
void loadCartFromFile();
void addToCart(int productId, int quantity);
void viewCart();
void seeProducts();
void addProduct();
void searchProducts();

#endif // SHOP_H
