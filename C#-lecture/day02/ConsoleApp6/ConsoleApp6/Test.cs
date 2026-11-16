using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp6
{

    public class Point // 각 도형이 포함관계로 갖는 클래스
    {
        public int X { set; get; }
        public int Y { set; get; }
        public Point() { }
        public Point(int x, int y)
        {
            X = x; Y = y;
        }
    }

    public class Shape
    {
        public string Name { set; get; }
        public Shape() { }
        public Shape(string name)
        {
            Name = name;
        }
        public virtual void draw()
        {
            Console.WriteLine($"{Name}을 그린다.");
        }
    }

    public class Circle : Shape
    {
        private Point p;
        private int r;
        public Circle() { Name = "Circle"; p = new Point(0, 0); }
        public Circle(Point p, int r) {
            Name = "Circle";
            this.p = p; this.r = r; 
        }
        public override void draw() {
            base.draw();
            Console.WriteLine("Center of Circle: (" + p.X + "," + p.Y + ")");
            Console.WriteLine("Radius: " + r);
        }
    }

    public class Rectangle : Shape
    {
        private Point[] v = new Point[2];
        public Rectangle() { 
            Name = "Rectangle"; 
            for(int i = 0; i < 2; i++)
            {
                v[i] = new Point(0, 0);
            }
        }
        public Rectangle(Point p1, Point p2) { Name = "Rectangle"; v[0] = p1; v[1] = p2; }

        public Point this[int index]
        {
            get => v[index];
            set => v[index] = value;
        }

        public override void draw()
        {
            base.draw();
            foreach(var (i, p) in v.Index())
                Console.WriteLine($"{i}: Vertex1 of Rectangle: (" + p.X + "," + p.Y + ")");
        }
    }

    public class Triangle : Shape
    {
        private Point vertex1;
        private Point vertex2;
        private Point vertex3;
        public Triangle() { Name = "Triangle"; vertex1 = new Point(0, 0); vertex2 = new Point(0, 0); vertex3 = new Point(0, 0); }
        public Triangle(Point p1, Point p2, Point p3) { Name = "Triangle"; vertex1 = p1; vertex2 = p2; vertex3 = p3; }

        public override void draw()
        {
            base.draw();
            Console.WriteLine("Vertex1 of Triangle: (" + vertex1.X + "," + vertex1.Y + ")");
            Console.WriteLine("Vertex2 of Triangle: (" + vertex2.X + "," + vertex2.Y + ")");
            Console.WriteLine("Vertex3 of Triangle: (" + vertex3.X + "," + vertex3.Y + ")");
        }
    }

    public class Test
    {
        
    }
}
