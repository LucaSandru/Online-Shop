#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Product products[MAX_PRODUCTS];
int numProducts = 0;

int getIntegerInput() {
    char input[100];
    while (true) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            char *newline = strchr(input, '\n');
            if (newline != NULL) *newline = '\0';

            bool isValid = true;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i])) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                return atoi(input);
            } else {
                printf("Invalid input. Please enter a number: ");
            }
        } else {
            printf("Invalid input. Please enter a number: ");
        }
    }
}

float getFloatInput() {
    char input[100];
    while (true) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            char *newline = strchr(input, '\n');
            if (newline != NULL) *newline = '\0';

            bool isValid = true;
            for (int i = 0; input[i] != '\0'; i++) {
                if (!isdigit(input[i]) && input[i] != '.') {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                return atof(input);
            } else {
                printf("Invalid input. Please enter a number: ");
            }
        } else {
            printf("Invalid input. Please enter a number: ");
        }
    }
}

void loadProductsFromFile() {
    FILE *file = fopen("C:\\Users\\Latex\\CLionProjects\\untitled1\\products.txt", "r");
    if (file == NULL) {
        printf("Failed to open file products.txt\n");
        return;
    }

    while (fscanf(file, "%d|%499[^|]|%1999[^|]|%f|%d\n", &products[numProducts].id, products[numProducts].name, products[numProducts].description, &products[numProducts].price, &products[numProducts].stock) == 5) {
        numProducts++;
        if (numProducts >= MAX_PRODUCTS) {
            printf("Max products limit reached.\n");
            break;
        }
    }

    fclose(file);
}

void saveProductsToFile() {
    FILE *file = fopen("C:\\Users\\Latex\\CLionProjects\\untitled1\\products.txt", "w");
    if (file == NULL) {
        printf("Failed to open file products.txt for writing.\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        products[i].id = i;  // Update IDs to be sequential
        fprintf(file, "%d|%s|%s|%.2f|%d\n", products[i].id, products[i].name, products[i].description, products[i].price, products[i].stock);
    }

    fclose(file);
}

void seeProducts() {
    if (numProducts == 0) {
        printf("No products available.\n");
        return;
    }

    printf("List of Products:\n");
    printf("%-5s%-20s%-30s%-10s%-10s\n", "ID", "Name", "Description", "Price", "Stock");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < numProducts; i++) {
        printf("%-5d%-20s%-30s%-10.2f%-10d\n", products[i].id, products[i].name, products[i].description, products[i].price, products[i].stock);
    }
}

void addProduct() {
    if (numProducts >= MAX_PRODUCTS) {
        printf("Cannot add more products. Max limit reached.\n");
        return;
    }

    int maxId = -1;
    for (int i = 0; i < numProducts; i++) {
        if (products[i].id > maxId) {
            maxId = products[i].id;
        }
    }

    Product newProduct;
    newProduct.id = maxId + 1;  // Assign the new product ID
    printf("Enter product name: ");
    fgets(newProduct.name, MAX_NAME_LENGTH, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;  // Remove newline character

    printf("Enter product description: ");
    fgets(newProduct.description, MAX_DESCRIPTION_LENGTH, stdin);
    newProduct.description[strcspn(newProduct.description, "\n")] = 0;  // Remove newline character

    printf("Enter product price: ");
    newProduct.price = getFloatInput();

    printf("Enter product stock: ");
    newProduct.stock = getIntegerInput();

    products[numProducts] = newProduct;
    numProducts++;

    saveProductsToFile();
    printf("Product added successfully with ID %d.\n", newProduct.id);
}

void searchProducts() {
    char searchName[MAX_NAME_LENGTH] = "";
    float minPrice = 0.0, maxPrice = 0.0;
    int choice;

    printf("Do you want to search by:\n");
    printf("1. Name\n");
    printf("2. Price Range\n");
    printf("3. Both Name and Price Range\n");
    printf("Enter your choice: ");
    choice = getIntegerInput();

    if (choice == 1 || choice == 3) {
        printf("Enter product name to search: ");
        fgets(searchName, MAX_NAME_LENGTH, stdin);
        searchName[strcspn(searchName, "\n")] = 0;  // Remove newline character
    }

    if (choice == 2 || choice == 3) {
        printf("Enter minimum price: ");
        minPrice = getFloatInput();
        printf("Enter maximum price: ");
        maxPrice = getFloatInput();
    }

    bool found = false;
    printf("Search Results:\n");
    printf("%-5s%-20s%-30s%-10s%-10s\n", "ID", "Name", "Description", "Price", "Stock");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < numProducts; i++) {
        bool nameMatch = (choice == 1 || choice == 3) ? (strstr(products[i].name, searchName) != NULL) : true;
        bool priceMatch = (choice == 2 || choice == 3) ? (products[i].price >= minPrice && products[i].price <= maxPrice) : true;

        if (nameMatch && priceMatch) {
            printf("%-5d%-20s%-30s%-10.2f%-10d\n", products[i].id, products[i].name, products[i].description, products[i].price, products[i].stock);
            found = true;
        }
    }

    if (!found) {
        printf("No products found");
        if (choice == 1 || choice == 3) printf(" with name '%s'", searchName);
        if (choice == 2 || choice == 3) printf(" in the price range $%.2f - $%.2f", minPrice, maxPrice);
        printf(".\n");
    }
}
