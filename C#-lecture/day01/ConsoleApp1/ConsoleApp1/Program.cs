using ConsoleApp1;


//#if 0
//Console.WriteLine("Hello, World!"); // 최상위 문, main 내용

//Class1 c; // 참조 변수 ~= 포인터 // 참조 값은 (주소를 대리하는 난수);
//c = new Class1(); // 객체 생성 모든 객체는 힙에 생성
//c.name = "Kahn";
//c.age = 2;
//Console.WriteLine(c.age);
//#endif

Person p1 = new Person(1, "Kahn", 30);

Person p2 = p1;

p1.print();
p2.print();

p1.print2(p2);

Console.WriteLine(p1 + " / " + p1.GetHashCode());
Console.WriteLine(p2 + " / " + p2.GetHashCode());

Person p3 = new Person(2, "bbb", 67);
p3.print2(p1);