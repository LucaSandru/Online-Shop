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

### Prerequisites

- A C compiler (e.g., GCC)
- A development environment (e.g., CLion, Visual Studio Code)

### Compilation

Compile the project using the following commands:

```sh
gcc -o shop main.c product.c cart.c utils.c user.c
