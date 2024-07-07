#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printUsage() {
    printf("Usage:\n");
    printf("  shop.exe view-products\n");
    printf("  shop.exe add-product\n");
    printf("  shop.exe add-to-cart <product_id> <quantity>\n");
    printf("  shop.exe search\n");
    printf("  shop.exe view-cart\n");
}

void handleCommandLineArguments(int argc, char *argv[]) {
    if (argc < 2) {
        printUsage();
        return;
    }

    loadProductsFromFile(); 
    loadCartFromFile(); 

    if (strcmp(argv[1], "view-products") == 0) {
        seeProducts();
    } else if (strcmp(argv[1], "add-product") == 0) {
        addProduct();
    } else if (strcmp(argv[1], "add-to-cart") == 0) {
        if (argc != 4) {
            printUsage();
            return;
        }
        int productId = atoi(argv[2]);
        int quantity = atoi(argv[3]);
        addToCart(productId, quantity);
    } else if (strcmp(argv[1], "search") == 0) {
        searchProducts();
    } else if (strcmp(argv[1], "view-cart") == 0) {
        viewCart();
    } else {
        printUsage();
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        handleCommandLineArguments(argc, argv);
    } else {
        loadProductsFromFile();
        loadCartFromFile();
        int choice;
        do {
            printf("\n=========================================\n");
            printf("       Welcome to Luca's Online Shop       \n");
            printf("=========================================\n");
            printf("1. View Products\n");
            printf("2. Add Product\n");
            printf("3. Add to Cart\n");
            printf("4. Search Products\n");
            printf("5. View Cart and Checkout\n");
            printf("6. Exit\n");
            printf("-----------------------------------------\n");
            printf("Enter your choice: ");
            choice = getIntegerInput();

            switch (choice) {
                case 1:
                    seeProducts();
                    break;
                case 2:
                    addProduct();
                    break;
                case 3: {
                    int productId, quantity;
                    printf("Enter the ID of the product you want to add to cart: ");
                    productId = getIntegerInput();
                    printf("Enter the quantity: ");
                    quantity = getIntegerInput();
                    addToCart(productId, quantity);
                    break;
                }
                case 4:
                    searchProducts();
                    break;
                case 5:
                    viewCart();
                    break;
                case 6:
                    printf("\nExiting...\n");
                    break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
            }
        } while (choice != 6);
    }

    return 0;
}
