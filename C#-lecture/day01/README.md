# Day1 — C#의 클래스와 참조

> 2026-11-13 학습 정리

## 최상위 문과 참조 변수
코드: [ConsoleApp1/Program.cs](ConsoleApp1/ConsoleApp1/Program.cs), [Person.cs](ConsoleApp1/ConsoleApp1/Person.cs)

```csharp
Console.WriteLine("Hello, World!"); // 최상위 문, main 내용

Class1 c;            // 참조 변수 ~= 포인터 (참조 값은 주소를 대리하는 값)
c = new Class1();    // 객체 생성. 모든 객체는 힙에 생성
c.name = "Kahn";
```
- `Program.cs`에 문장을 바로 쓰면 컴파일러가 `Main` 함수로 감싸 준다(**최상위 문**). 프로젝트에 한 파일만 이렇게 쓸 수 있다.
- C#에서 클래스 변수는 **참조 변수**다. `Class1 c;`만으로는 객체가 생기지 않고, `new`로 만든 힙 객체를 가리킨다. C++의 `Class1* c = new Class1();`과 비슷하다.
- 대신 C++처럼 `delete`가 없다. 아무도 가리키지 않는 객체는 **가비지 컬렉터(GC)**가 알아서 해제한다.
- 멤버 접근은 포인터처럼 `->`가 아니라 항상 `.`이다.

## 참조 복사
```csharp
class Person
{
    public int num;
    public string name;
    public int score;

    public Person(int num, string name, int score)
    {
        this.num = num;
        this.name = name;
        this.score = score;
    }

    public void print()
    {
        Console.WriteLine("num: " + num + ", name: " + name + ", score: " + score);
    }
}

Person p1 = new Person(1, "Kahn", 30);
Person p2 = p1;

p1.print();
p2.print();

Console.WriteLine(p1 + " / " + p1.GetHashCode());
Console.WriteLine(p2 + " / " + p2.GetHashCode());
```
```
num: 1, name: Kahn, score: 30
num: 1, name: Kahn, score: 30
ConsoleApp1.Person / (해시 코드)
ConsoleApp1.Person / (위와 같은 해시 코드)
```
- `Person p2 = p1;`은 객체가 통째로 복사되지 않고 **참조값만 복사**된다. 객체 하나에 이름이 `p1`, `p2` 두 개인 상황이다. C++의 `Point p3 = p1;`(복사 생성자 호출)과 다르다.
- 그래서 `p2.name`을 바꾸면 `p1.name`도 바뀐다. 두 해시 코드가 같은 것으로 같은 객체임을 확인할 수 있다.
- 객체를 문자열과 `+`로 이으면 `ToString()`이 호출되고, 재정의하지 않으면 `네임스페이스.클래스이름`이 나온다.
- 생성자, `this`는 C++과 같다. 다만 `this`는 포인터가 아니라 참조라서 `this.num`으로 쓴다.
- 접근 지정자는 멤버마다 따로 붙인다(`public int num;`). 생략하면 `private`다.
- `print2(Person p)`는 매개변수 `p`를 쓰지 않고 자기 자신을 출력한다. `p.num`, `p.name`을 출력하려던 것이면 고쳐야 한다.

## 캡슐화와 객체 배열
코드: [ConsoleApp2/Program.cs](ConsoleApp2/ConsoleApp2/Program.cs), [Person.cs](ConsoleApp2/ConsoleApp2/Person.cs)

```csharp
internal class Person
{
    private string name;
    private string tel;
    public Person() { }
    public Person(string name, string tel)
    {
        this.name = name;
        this.tel = tel;
    }

    public void setName(string name) { this.name = name; }
    public string getName() { return this.name; }
    /* setTel, getTel, print */
}

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
```
- 필드를 `private`로 숨기고 `set`/`get` 메서드로만 접근한다. C++ Day1과 같은 캡슐화다.
- C#에서는 보통 **속성(property)**으로 쓴다: `public string Name { get; set; }`.
- `internal`은 같은 프로젝트(어셈블리) 안에서만 쓸 수 있다는 뜻이다. 클래스에 지정자를 생략하면 `internal`이다.
- 배열도 객체라서 `new int[3]`으로 힙에 만든다. `arr.Length`로 길이를 알 수 있다.
- `new Person[3]`은 **참조 3칸**만 만든다. 처음에는 모두 `null`이고, `persons[i] = new Person(...)`로 객체를 하나씩 넣어야 한다. C++의 `Point* arr[3]`과 같은 모양이다.
- `Console.ReadLine()`은 `string?`(null일 수 있음)을 반환해서 `<Nullable>enable</Nullable>` 설정에서 경고가 나온다.
