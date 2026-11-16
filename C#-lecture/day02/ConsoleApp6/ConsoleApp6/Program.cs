using ConsoleApp6;

Console.WriteLine("Hello, World!");

Circle c = new Circle(new Point(100, 200), 3);
//c.draw();
Rectangle r = new Rectangle(new Point(1, 2), new Point(3, 4));
//r.draw();
Triangle t = new Triangle(new Point(1, 2), new Point(3, 4), new Point(5, 6));
//t.draw();

Shape[] shapes = { c, r, t };

if(r is Rectangle rect)
    rect[1] = new Point(2, 300);

foreach (Shape s in shapes)
    s.draw();