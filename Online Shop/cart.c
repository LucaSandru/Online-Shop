#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

CartItem cart[MAX_CART_ITEMS];
int numItemsInCart = 0;

void saveCartToFile() {
    FILE *file = fopen("C:\\Users\\Latex\\CLionProjects\\untitled1\\cart.txt", "w");
    if (file == NULL) {
        printf("Failed to open file cart.txt for writing.\n");
        return;
    }

    for (int i = 0; i < numItemsInCart; i++) {
        fprintf(file, "%d|%s|%.2f|%d\n", cart[i].productId, cart[i].name, cart[i].price, cart[i].quantity);
    }

    fclose(file);
}

void loadCartFromFile() {
    FILE *file = fopen("C:\\Users\\Latex\\CLionProjects\\untitled1\\cart.txt", "r");
    if (file == NULL) {
        printf("Failed to open file cart.txt for reading.\n");
        return;
    }

    numItemsInCart = 0; // Reset cart before loading
    while (fscanf(file, "%d|%499[^|]|%f|%d\n", &cart[numItemsInCart].productId, cart[numItemsInCart].name, &cart[numItemsInCart].price, &cart[numItemsInCart].quantity) == 4) {
        numItemsInCart++;
        if (numItemsInCart >= MAX_CART_ITEMS) {
            printf("Max limit reached for cart items.\n");
            break;
        }
    }

    fclose(file);
}

void addToCart(int productId, int quantity) {
    if (numItemsInCart < MAX_CART_ITEMS) {
        bool found = false;
        for (int i = 0; i < numProducts; i++) {
            if (products[i].id == productId) {
                found = true;
                if (quantity <= 0) {
                    printf("Invalid quantity.\n");
                    return;
                }

                if (products[i].stock < quantity) {
                    printf("Not enough stock available for product '%s'.\n", products[i].name);
                    return;
                }

                bool itemInCart = false;
                for (int j = 0; j < numItemsInCart; j++) {
                    if (cart[j].productId == productId) {
                        cart[j].quantity += quantity;
                        itemInCart = true;
                        break;
                    }
                }

                if (!itemInCart) {
                    cart[numItemsInCart].productId = productId;
                    cart[numItemsInCart].quantity = quantity;
                    strcpy(cart[numItemsInCart].name, products[i].name);
                    cart[numItemsInCart].price = products[i].price;
                    numItemsInCart++;
                }

                products[i].stock -= quantity;

                if (products[i].stock == 0) {
                    for (int j = i; j < numProducts - 1; j++) {
                        products[j] = products[j + 1];
                    }
                    numProducts--;
                }

                printf("Added %d units of product '%s' to cart.\n", quantity, products[i].name);

                saveProductsToFile();

                saveCartToFile();
                return;
            }
        }
        if (!found) {
            printf("Invalid product ID.\n");
        }
    } else {
        printf("Cart is full. Cannot add more items.\n");
    }
}

void viewCart() {
    if (numItemsInCart == 0) {
        printf("Cart is empty.\n");
        return;
    }

    printf("Cart Contents:\n");
    printf("%-5s%-20s%-10s%-10s\n", "ID", "Name", "Price", "Quantity");
    printf("-------------------------------------------------------------\n");

    float totalPrice = 0.0;
    for (int i = 0; i < numItemsInCart; i++) {
        float itemPrice = cart[i].price * cart[i].quantity;
        totalPrice += itemPrice;
        printf("%-5d%-20s$%-9.2f%-10d\n", cart[i].productId, cart[i].name, cart[i].price, cart[i].quantity);
    }

    printf("\nTotal Price: $%.2f\n", totalPrice);
}
