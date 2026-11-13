using ConsoleApp2;

Console.WriteLine("Hello, World!");

Person p1 = new Person();

p1.setName("name");
p1.setTel("010-1234-1234");
p1.print();

Person p2 = new Person("bbb", "34456");
p2.print();

int[] arr = new int[3];
int[] arr2 = { 1, 2, 3 };
Person[] persons = new Person[3];

for(int i = 0; i < 3; i++)
{    
    Console.Write("name: ");
    string name = Console.ReadLine();
    Console.Write("tel: ");
    string tel = Console.ReadLine();
    persons[i] = new Person(name, tel);
}

for (int i = 0; i < 3; i++)
{
    persons[i].print();
}

// 객체가 통으로 복사되지 않고 참조값만 복사됨
// 객체 하나에 이름이 p, p1 2개인 상황이다.

