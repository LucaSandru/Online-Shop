# Luca's Online Shop

Welcome to Luca's Online Shop, a console-based application that allows users to view products, add products to the cart, search for products, and manage their shopping cart.

## Features

- Work in terminal (as user)
- View a list of products
- Add new products
- Add products to the cart
- Search products by name and/or price range
- View and manage the cart

## Project Structure

The project is divided into multiple source files:

- `main.c` - Contains the main function and command-line argument handling.
- `product.c` - Functions for loading, saving, viewing, and adding products.
- `cart.c` - Functions for loading, saving, viewing, and managing the cart.
- `utils.c` - Utility functions for user input and validation.
- `user.c` - Functions for user login and creating user-specific cart files.

## Files

- `products.txt` - Stores the list of products.
- `cart.txt` - Stores the cart items.

## Getting Started

### What you need

- A C compiler (e.g., GCC)
- A development environment (e.g., CLion, Visual Studio Code) - e.g. I worked in *CLion*


### Open User-Terminal

Depends if you have Microsoft, Linux or macOS, you need to open your by-default terminal and access the whole project (copy and paste the correct path). In **Windows**, by using *Command Prompt*, is the following:

```sh
cd <your correct path>
```

### Compilation

Compile the project using the following command:

```sh
gcc -o shop main.c product.c cart.c
```

### Running the Application

You can run the application using the following command:

```sh
shop.exe
```
- This command is the simplest way to run the program - like in console of *CLion* or *VSC*
- But, the application supports several command-line arguments for different operations:
  1.  View the list of products
 
```sh
shop.exe view-products
```

  2. Add a new product

```sh
shop.exe add-product
```

  3. Add a product to the cart

```sh
shop.exe add-to-cart <product_id> <quantity>
```

  4. Search for products

```sh
shop.exe search
```
