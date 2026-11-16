using ConsoleApp2;

Console.WriteLine("Hello, World!");

var cart = new ShoppingCart();

cart.addItem("Coat", 0);

Console.WriteLine(cart.getItem(0));

cart[1] = "Dress";
Console.WriteLine(cart[1]);