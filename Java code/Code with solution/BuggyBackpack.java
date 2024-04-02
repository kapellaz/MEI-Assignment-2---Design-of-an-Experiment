import java.util.*;
import java.util.stream.Collectors;

// This code creates represents a backpack, which can be packed with items using different strategies.
// Each item has a type, name and weight in Kg and is unique.
// The backpack class stores the items.
// The backpack can be packed with random items, lightest items first,
// heaviest items first, or with a special rule that packs food items separately.
// Bugs can be of the following types:
// 1. Logical bug
// 2. Performance bug
// 3. Variable type bug
// 4. Memory managment bug

// The review should take no longer than 10 minutes.
//Review starts on line 61 and ends on line 160.
public class BuggyBackpack {

  // type of items
  public enum ItemType {
    FOOD, CLOTHING, BOOK, TOY
  }

  // Create item class
  public static class Item {
    private ItemType type;
    private String name;
    private double weight;

    public Item(ItemType type, String name, double weight) {
      this.type = type;
      this.name = name;
      this.weight = weight;
    }

    public ItemType getType() {
      return type;
    }

    public String getName() {
      return name;
    }

    public double getWeight() {
      return weight;
    }

    @Override
    public String toString() {
      return name + " (" + type + ", " + weight + " kg)";
    }
  }

  // Packing strategy
  public enum Strategy {
    RANDOM, // Pack random items
    HEAVY_FIRST, // Pack the heaviest items first
    LIGHT_FIRST // Pack the lightest items first
  }

  // START THE REVIEW HERE
  // Create backpack class
  public static class Backpack {
    private List<Item> items;

    public Backpack() {
      this.items = new ArrayList<>();
    }

    public void addItem(Item item) {
      items.add(item);
    }

    // Sorts items by weight
    public void sortItemsByWeight() {
      items.sort(Comparator.comparingDouble(Item::getWeight));
    }

    // Displays backpack contents
    public void displayContents() {
      System.out.println("Backpack Contents:");
      for (Item item : items) {
        System.out.println("- " + item);
      }
      // Bug #1: Displaying the object address because toString is not implemented
      System.out.println(this);
    }

    // Packs food items separately from non-food items
    // Bug #2: Doesnt check if food items to pack are more than the total items to
    // pack
    public void packItemsWithSpecialRules(List<Item> availableItems, int totalItemsToPack, int foodItemsToPack) {
      // Simulate a scenario where FOOD items need special handling
      List<Item> foodItems = availableItems.stream()
          .filter(item -> item.getType() == ItemType.FOOD)
          .collect(Collectors.toList());

      List<Item> nonFoodItems = availableItems.stream()
          .filter(item -> item.getType() != ItemType.FOOD)
          .collect(Collectors.toList());

      // Ensure that FOOD items are packed separately to maintain freshness
      int numFoodItemsToPack = foodItemsToPack;
      int numNonFoodItemsToPack = totalItemsToPack - numFoodItemsToPack;

      packRandomItems(nonFoodItems, numNonFoodItemsToPack);
      packRandomItems(foodItems, numFoodItemsToPack);

      // Display a message indicating the special packing scenario
      System.out.println("Packing items with special rules:");
      System.out.println("Non-FOOD items packed: " + numNonFoodItemsToPack);
      System.out.println("FOOD items packed: " + numFoodItemsToPack);
    }

    public void packItems(List<Item> availableItems, Strategy strategy, int totalItemsToPack) {
      switch (strategy) {
        case RANDOM:
          packRandomItems(availableItems, totalItemsToPack);
          break;
        case HEAVY_FIRST:
          packHeaviestItemsFirst(availableItems, totalItemsToPack);
          break;
        case LIGHT_FIRST:
          packLightestItemsFirst(availableItems, totalItemsToPack);
          break;
      }
    }

    private void packRandomItems(List<Item> availableItems, int totalItemsToPack) {
      Random random = new Random();
      // Bug #3: not preventing from adding the same item more than once
      for (int i = 0; i < totalItemsToPack; i++) {
        Item randomItem = availableItems.get(random.nextInt(availableItems.size()));
        addItem(randomItem);
      }
    }

    private void packHeaviestItemsFirst(List<Item> availableItems, int totalItemsToPack) {
      // Bug #4: Incorrect sorting logic
      availableItems.sort(Comparator.comparingDouble(Item::getWeight));
      addItemRange(availableItems, totalItemsToPack);
    }

    private void packLightestItemsFirst(List<Item> availableItems, int totalItemsToPack) {
      // Bug #5: Incorrect sorting logic
      availableItems.sort(
          Comparator.comparingDouble(Item::getWeight).reversed());
      addItemRange(availableItems, totalItemsToPack);
    }

    private void addItemRange(List<Item> itemsToAdd, int totalItemsToPack) {
      for (int i = 0; i < itemsToAdd.size(); i++) {
        // Bug #6: Incorrect loop condition. Using size of itemsToAdd
        // when should be using totalItemsToPack (number of items to add defined by
        // caller)
        addItem(itemsToAdd.get(i));
      }
    }
  }
  // REVIEW ENDS HERE

  public static void main(String[] args) {
    Backpack backpack1 = new Backpack();
    Backpack backpack2 = new Backpack();
    Backpack backpack3 = new Backpack();
    Backpack backpack4 = new Backpack();
    List<Item> availableItems = generateAvailableItems();

    // Pack items using different strategies
    backpack1.packItems(availableItems, Strategy.RANDOM, 3);
    backpack2.packItems(availableItems, Strategy.HEAVY_FIRST, 4);
    backpack3.packItems(availableItems, Strategy.LIGHT_FIRST, 4);
    backpack4.packItemsWithSpecialRules(availableItems, 5, 2);

    // Display the contents of the backpack
    backpack1.displayContents();
    backpack2.displayContents();
    backpack3.displayContents();
    backpack4.displayContents();
  }

  private static List<Item> generateAvailableItems() {
    return Arrays.asList(new Item(ItemType.FOOD, "Apple", 0.2),
        new Item(ItemType.FOOD, "Sandwich", 0.5),
        new Item(ItemType.CLOTHING, "T-shirt", 0.3),
        new Item(ItemType.CLOTHING, "Jeans", 0.7),
        new Item(ItemType.BOOK, "Novel", 0.8),
        new Item(ItemType.BOOK, "Notebook", 0.4),
        new Item(ItemType.TOY, "Teddy Bear", 0.6),
        new Item(ItemType.TOY, "Toy Car", 0.3));
  }
}
