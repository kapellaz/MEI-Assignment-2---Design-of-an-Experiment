import java.util.*;

// This code creates represents a pharmacy, which has a stock of products that can be purchased by users.
// The stock class stores the products and their quantities.
// Bugs can be of the following types:
// 1. Logical bug
// 2. Performance bug
// 3. Variable type bug
// 4. Memory managment bug

// The review should take no longer than 5 minutes.
// Please write down the bugs you find and the type of bug.
// The review starts on line 47.

public class BuggyPharmacyReview {

    // create product class
    public static class Product {
        private String name;
        private double price;
        private String barcode;

        public Product(String name, double price, String barcode) {
            this.name = name;
            this.price = price;
            this.barcode = barcode;
        }

        public String getName() {
            return name;
        }

        public double getPrice() {
            return price;
        }

        public String getBarcode() {
            return barcode;
        }

        @Override
        public String toString() {
            return name + " (Barcode: " + barcode + ", Price: $" + price + ")";
        }
    }

    // START THE REVIEW HERE

    // create stock class, which has a map of products and their quantities
    public static class Stock {
        private Map<Product, Integer> products;

        public Stock() {
            this.products = new HashMap<>();
        }

        // add a certain quantity of product to stock
        public void addProduct(Product product, int quantity) {
            products.put(product, quantity);
        }

        public void removeProduct(Product product) {
            products.remove(product);
        }

        // updates the product quantity on stock
        public void updateQuantity(Product product, int quantity) {
            products.put(product, quantity + 1);
        }

        // purchase products from stock
        public void purchase(User user, Map<Product, Integer> productsToPurchase) {
            System.out.println(user.getName() +
                    " is purchasing the following products:");
            for (Map.Entry<Product, Integer> productEntry : productsToPurchase.entrySet()) {
                int availableQuantity = products.get(productEntry.getKey());
                if (availableQuantity > 0) {
                    System.out.println("- " + productEntry.getKey() +
                            " (Quantity: " + productEntry.getValue() + ")");
                    updateQuantity(productEntry.getKey(), availableQuantity - 1);
                } else {
                    System.out.println("- " + productEntry.getKey() + " (Out of stock)");
                }
            }
        }

        @Override
        public String toString() {
            return "Stock: " + products;
        }
    }

    // create user class
    public static class User {
        private String name;
        private String phone;
        private float fiscalNumber;

        public User(String name, String phone, float fiscalNumber) {
            this.name = name;
            this.phone = phone;
            this.fiscalNumber = fiscalNumber;
        }

        public String getName() {
            return name;
        }

        public String getPhone() {
            return phone;
        }

        public float getFiscalNumber() {
            return fiscalNumber;
        }

        @Override
        public String toString() {
            return "User: " + name + " (Phone: " + phone +
                    ", Fiscal Number: " + fiscalNumber + ")";
        }
    }

    public static void main(String[] args) {
        // Sample products
        Product paracetamol = new Product("Paracetamol", 5.99, "123456");
        Product aspirin = new Product("Aspirin", 3.49, "789012");

        // Sample Stock
        Stock Stock = new Stock();
        Stock.addProduct(paracetamol, 50);
        Stock.addProduct(aspirin, 30);

        // Sample user
        User customer = new User("John Doe", "+123456789", 39288123);

        Map<Product, Integer> productsToPurchase = new HashMap<BuggyPharmacyReview.Product, Integer>();
        productsToPurchase.put(aspirin, 2);
        productsToPurchase.put(paracetamol, 1);
        Stock.purchase(customer, productsToPurchase);
    }
}
