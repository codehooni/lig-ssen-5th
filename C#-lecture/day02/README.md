# Day2 — 속성, 인덱서, 상속과 다형성

> 2026-11-16 학습 정리

## C# 프로그램의 기본 구조
- 모든 코드는 클래스 안에 있어야 한다. 그래서 **전역 변수와 전역 함수가 없다**. 프로그램은 `static void Main()`에서 시작한다.
  - `Program.cs`에 문장을 바로 쓰면(최상위 문) 컴파일러가 `Main`으로 감싸 준다.
- 클래스 변수는 **참조 변수**다. 객체는 `new`로 힙에만 만들고, `new`를 하지 않으면 객체가 없다. 멤버 접근은 `->` 없이 항상 `.`이다.
- `using 네임스페이스;`를 써 두면 `네임스페이스.` 없이 클래스 이름만으로 쓸 수 있다.
- 모든 클래스는 `object`를 상속한다. 그래서 어떤 객체든 `ToString()`, `Equals()`, `GetHashCode()`를 쓸 수 있다.
- 추상 클래스, 인터페이스, 델리게이트:
  - **추상 클래스**: `abstract`를 붙인 클래스. 객체를 만들 수 없고 상속해서 쓴다.
  - **인터페이스**: 구현 없이 메서드 목록만 정한 것. 클래스는 여러 인터페이스를 구현할 수 있다.
  - **delegate**: 메서드를 가리키는 타입. 함수 포인터처럼 대신 호출해 준다(UI 이벤트에서 많이 쓴다).

## 매개변수 전달 방법
```csharp
void Swap(ref int a, ref int b) { int t = a; a = b; b = t; }
bool TryDivide(int a, int b, out int result) { /* result에 반드시 값을 넣어야 함 */ }
void Print(in BigStruct s) { /* s를 수정할 수 없음 */ }
int Sum(params int[] nums) { /* Sum(1, 2, 3)처럼 호출 */ }
```
| 키워드 | 의미 | 호출할 때 |
|---|---|---|
| `ref` | 변수 자체를 넘긴다(C++의 `int&`). 메서드 안에서 바꾸면 원본이 바뀐다 | `Swap(ref x, ref y)` |
| `out` | 결과를 돌려받는 용도. 여러 값을 반환할 때 쓴다 | `TryDivide(10, 2, out int r)` |
| `in` | 읽기 전용 참조. 큰 구조체를 복사 없이 넘길 때 쓴다(C++의 `const T&`) | `Print(in s)` 또는 `Print(s)` |
| `params` | 가변 인자. 개수가 정해지지 않은 인자를 배열로 받는다 | `Sum(1, 2, 3)` |

- 참조 변수를 그냥 넘기면 객체의 멤버는 바꿀 수 있다. 다만 메서드 안에서 `p = new Person()`으로 새 객체를 대입해도 호출한 쪽 변수는 그대로다. 호출한 쪽 변수까지 바꾸려면 `ref`가 필요하다.

## 클래스 기본
- **오버로딩**: 이름은 같고 매개변수의 개수나 타입이 다른 메서드를 여러 개 만든다. 가독성과 유연성이 좋아진다. **반환 타입만 다른 것은 오버로딩이 아니다**(컴파일 오류).
- **생성자/소멸자**: 생성자는 C++과 같다. 메모리는 GC가 해제하므로 소멸자(종료자, `~Person()`)는 거의 쓰지 않는다.
- **this**: 자기 자신을 가리키는 참조. **base**: 부모 쪽 멤버를 가리키는 참조(`base.draw()`, `: base(name)`).
- **static**: 객체가 아니라 클래스에 속한다. static 메서드에는 `this`가 없어서 static 필드와 static 메서드만 바로 쓸 수 있다.
- **접근 제한자**: 멤버마다 따로 붙인다. 생략하면 멤버는 `private`, 클래스는 `internal`이다.

| 제한자 | 접근 범위 |
|---|---|
| `public` | 어디서나 |
| `internal` | 같은 어셈블리(같은 프로젝트) 안에서만 |
| `protected` | 자기 클래스와 자식 클래스 |
| `private` | 자기 클래스 안에서만 |

## 속성 (property)
코드: [ConsoleApp1/Program.cs](ConsoleApp1/ConsoleApp1/Program.cs), [Person.cs](ConsoleApp1/ConsoleApp1/Person.cs)

```csharp
public class Person
{
    private int age;          // 실제 데이터는 숨김

    public int Age            // 외부에서 접근하는 창구
    {
        get { return age; }
        set { if (value >= 0) age = value; }  // 값을 쓸 때 검사 가능
    }

    // 자동 구현 속성: 컴파일러가 숨겨진 필드를 만들어 준다
    public string Name { get; set; }
    public int Id { get; init; }   // 객체를 만들 때만 설정 가능
}

p.Age = 20;                    // set 호출
Console.WriteLine(p.Age);      // get 호출
```
- 메서드처럼 `getAge()`로 부르지 않고 public 필드처럼 `p.Age`로 쓰지만, 실제로는 get/set 메서드가 호출된다.
- 쓰는 이유:
  - **캡슐화**: `{ get; private set; }`처럼 읽기와 쓰기 권한을 나눌 수 있다.
  - **유지보수**: 나중에 검사 로직을 넣어도 쓰는 쪽 코드가 바뀌지 않는다.
  - **관례**: 데이터 바인딩, JSON 직렬화, 인터페이스는 필드가 아닌 속성을 기준으로 동작한다.
- 공개 데이터는 속성으로, 내부 데이터는 `private` 필드로 쓰고 `public` 필드는 거의 쓰지 않는다.
- 타입은 `String`보다 C# 키워드인 `string`을 쓰는 것이 관례다(같은 타입).

```
Hello, World!
John
Kan
Julia
```
- 실습 코드의 `Person`에서 자동 속성 `Name`과 필드 `name`은 **서로 다른 변수**다. 생성자와 `setName()`은 필드 `name`을 바꾸고, `p.Name = "Julia"`는 숨겨진 다른 필드를 바꾼다. 그래서 `getName()`은 여전히 `"Kan"`을 반환한다. 둘 중 하나만 남겨야 한다.

## 객체 배열과 foreach
```csharp
Person[] p = new Person[3];     // 참조 3칸만 생김. 모두 null
for (int i = 0; i < 3; i++)
    p[i] = new Person();        // 객체를 하나씩 만들어 넣어야 함

Person[] people =
{
    new Person { Name = "철수", Age = 20 },   // 객체 이니셜라이저
    new Person { Name = "영희", Age = 25 },
};
foreach (Person person in people)
    Console.WriteLine($"이름: {person.Name}, 나이: {person.Age}");
```
- **객체 배열을 만들기만 하면 안에 객체가 없다.** 이게 제일 중요하다. 객체를 넣지 않고 `p[0].Name`에 접근하면 `NullReferenceException`이 난다.
- 메모리 모양:
  - `new Person[3]` 직후: 스택에 `p`(참조 1개), 힙에 참조 3칸짜리 배열
  - `p[i] = new Person()` 이후: 힙에 `Person` 객체 3개가 더 생기고 배열 칸이 각각을 가리킨다
  - 참조 하나의 크기는 64비트 환경에서 8바이트다(32비트에서는 4바이트).
- `$"..."`는 **문자열 보간**이다. `{}` 안에 변수나 식을 바로 쓸 수 있다.
- 객체를 만드는 세 가지 방법:
```csharp
var cart = new ShoppingCart();           // 타입 추론
ShoppingCart cart = new ShoppingCart();  // 전체 표기
ShoppingCart cart = new();               // 대상 타입 new
```

## 인덱서 (indexer)
코드: [ConsoleApp2/ShoppingCart.cs](ConsoleApp2/ConsoleApp2/ShoppingCart.cs), [ConsoleApp3/AddressBook.cs](ConsoleApp3/ConsoleApp3/AddressBook.cs)

```csharp
public class ShoppingCart
{
    private string[] _items = new string[10];

    public string this[int index]
    {
        get => _items[index];
        set => _items[index] = value;
    }
}

cart[1] = "Dress";
Console.WriteLine(cart[1]);   // Dress
```
- 객체를 배열처럼 `[]`로 접근하게 해 준다. C++의 `operator[]` 오버로딩과 비슷하다.
- 속성처럼 get/set으로 만들고, 이름 대신 `this[매개변수]`를 쓴다.
- 인덱스 타입은 `int`가 아니어도 된다. `AddressBook`은 내부에 `Dictionary<int, Person>`을 두고, 없는 키를 읽으면 `null`을 반환한다.
- `Person`에서 `ToString()`을 재정의(`override`)했기 때문에 `Console.WriteLine(ab[0])`이 `name: Alex, tel: ...`로 출력된다.

## 객체 사이의 관계 — 포함 (has a)
코드: [ConsoleApp4/Car.cs](ConsoleApp4/ConsoleApp4/Car.cs)

```csharp
public class Car
{
    private Engine engine;
    public Car(Engine engine) { this.engine = engine; }
    public void drive() { engine.start(); }
}

Car c1 = new(new Engine());
```
- Car **has a** Engine. 다른 객체를 멤버로 가지고 그 기능을 빌려 쓴다.
- `Car`가 구체 클래스 `Engine`에 직접 의존하면 **강한 결합**이 된다. `Engine`이 바뀌면 `Car`도 영향을 받고, 다른 엔진(`Motor`)으로 바꾸기도 어렵다.
- 해결 방법:
  - **의존성 역전(DIP)**: `Car`가 구체 클래스가 아닌 `IEngine` 같은 **인터페이스**에 의존하게 한다.
  - **의존성 주입(DI)**: 필요한 객체를 안에서 `new` 하지 않고 생성자로 받는다. 실습 코드가 이미 이 방식이다. 매개변수 타입을 인터페이스로 바꾸면 엔진을 자유롭게 교체할 수 있다.

## 객체 사이의 관계 — 상속 (is a)
코드: [ConsoleApp5/Animal.cs](ConsoleApp5/ConsoleApp5/Animal.cs)

```csharp
abstract class Animal
{
    public string Name { get; set; }
    public Animal(string name) { Name = name; Console.WriteLine("Animal 생성자"); }
    public void eat() { Console.WriteLine("밥 먹음"); }
}

class Dog : Animal
{
    public Dog(string name) : base(name) { Console.WriteLine("Dog 생성자"); }
    public new void eat() { Console.WriteLine("Dog 밥 먹음"); }
}

Animal dog = new Dog("Poppy");
dog.eat();
```
```
Animal 생성자
Dog 생성자
밥 먹음
```
- Dog **is a** Animal. `class Dog : Animal`로 상속한다.
- 부모 생성자는 `: base(인자)`로 호출한다(C++의 초기화 리스트 `: Animal(name)`). **부모 생성자가 먼저** 실행된다.
- `eat()`는 `virtual`이 아니고 `new`로 숨겼기 때문에, 변수 타입이 `Animal`이면 부모의 `eat()`가 호출된다.
- 상속 규칙:
  1. **단일 상속**: 클래스는 부모를 하나만 가질 수 있다. 대신 인터페이스는 여러 개 구현할 수 있다.
  2. **접근 제한자**: 부모의 `private` 멤버는 자식에서 접근할 수 없다. 자식에게만 열어 주려면 `protected`를 쓴다.
  3. **sealed**: `sealed class`는 상속할 수 없다.

## 가상 함수와 숨기기 (override vs new)
코드: [ConsoleApp7/Parent.cs](ConsoleApp7/ConsoleApp7/Parent.cs)

```csharp
public class Parent
{
    public void f1() { Console.WriteLine("부모 f1()"); }
    public virtual void f2() { Console.WriteLine("부모 f2()"); }
}
public class Child : Parent
{
    public new void f1() { Console.WriteLine("자식 f1()"); }       // 숨기기
    public override void f2() { Console.WriteLine("자식 f2()"); }  // 재정의
}

Parent p1 = new();
Parent p2 = new Child();
Child p3 = new();
```
| 호출 | 결과 | 이유 |
|---|---|---|
| `p1.f1()` / `p1.f2()` | 부모 / 부모 | 실제 객체가 `Parent` |
| `p2.f1()` | **부모 f1()** | 일반 함수 → 정적 바인딩. 변수 타입(`Parent`)을 따른다 |
| `p2.f2()` | **자식 f2()** | 가상 함수 → 동적 바인딩. 실제 객체(`Child`)를 따른다 |
| `p3.f1()` / `p3.f2()` | 자식 / 자식 | 변수 타입도 실제 객체도 `Child` |

- C#에서는 부모에 `virtual`, 자식에 `override`를 **둘 다** 써야 재정의가 된다.
- `virtual` 없이 같은 이름을 만들면 **숨기기**가 된다. 컴파일러가 경고하므로 의도한 것이면 `new`를 붙인다.
- C++과 비교:
  - C++도 `virtual`이 없으면 정적 바인딩이라서 부모 포인터로 호출하면 부모 함수가 불린다. 동작은 같다.
  - C++은 자식에 `override`를 쓰지 않아도 재정의가 되지만, C#은 반드시 써야 해서 실수를 막아 준다.
  - 부모 함수 직접 호출: C++ `Parent::f2()` / C# `base.f2()`
- 용어 정리: **오버로딩**은 같은 이름에 매개변수만 다른 것이고, **오버라이딩**은 부모 메서드를 자식이 같은 시그니처로 재정의하는 것이다.

## 다형성 — 업캐스팅과 다운캐스팅
코드: [ConsoleApp6/Program.cs](ConsoleApp6/ConsoleApp6/Program.cs), [Test.cs](ConsoleApp6/ConsoleApp6/Test.cs)

```csharp
public class Shape
{
    public string Name { set; get; }
    public virtual void draw() { Console.WriteLine($"{Name}을 그린다."); }
}
public class Circle : Shape
{
    private Point p;   // 포함 관계
    private int r;
    public override void draw()
    {
        base.draw();   // 부모 draw()를 먼저 실행
        Console.WriteLine("Center of Circle: (" + p.X + "," + p.Y + ")");
        Console.WriteLine("Radius: " + r);
    }
}

Shape[] shapes = { c, r, t };      // 업캐스팅

if (r is Rectangle rect)           // 다운캐스팅 (타입 검사 + 변환)
    rect[1] = new Point(2, 300);

foreach (Shape s in shapes)
    s.draw();                      // 각자 재정의된 draw() 실행
```
```
Circle을 그린다.
Center of Circle: (100,200)
Radius: 3
Rectangle을 그린다.
0: Vertex1 of Rectangle: (1,2)
1: Vertex1 of Rectangle: (2,300)
Triangle을 그린다.
...
```
- **다형성**: 같은 `s.draw()` 호출이 실제 객체에 따라 다르게 동작한다.
- **업캐스팅**: 자식 객체를 부모 타입 변수에 담는 것. 자동으로 된다.
  - `virtual` 메서드를 재정의했다면, 변수 타입이 부모여도 동적 바인딩으로 **재정의된 메서드**가 실행된다.
  - 변수 타입이 부모라서 **부모에 정의된 멤버만** 쓸 수 있다. `Shape` 변수로는 `Rectangle`의 인덱서를 쓸 수 없다.
- **다운캐스팅**: 업캐스팅된 객체를 원래 타입으로 되돌리는 것. 자식에만 있는 멤버에 접근할 때 쓴다.
  - `(Rectangle)s`: 캐스팅 연산자. 타입이 틀리면 `InvalidCastException`이 난다.
  - `s as Rectangle`: 타입이 틀리면 `null`을 돌려준다.
  - `s is Rectangle rect`: 타입이 맞을 때만 `rect`에 담아 준다. 가장 안전해서 많이 쓴다.
- 자식 클래스들이 공통 부분은 `base.draw()`로 재사용하고, 자기 부분만 덧붙인다.
- `v.Index()`는 `(인덱스, 값)` 쌍으로 순회하는 LINQ 메서드다(.NET 9 이상).

## 추상 클래스
코드: [ConsoleApp8/Parent.cs](ConsoleApp8/ConsoleApp8/Parent.cs)

```csharp
abstract class Shape
{
    public abstract void draw();   // 구현 없음. 자식이 반드시 override
}
class Circle : Shape
{
    public override void draw() { Console.WriteLine("원을 그림"); }
}
class Brush
{
    public void action(Shape s) { s.draw(); }  // 어떤 도형이든 받을 수 있음
}

new Brush().action(new Circle());   // 원을 그림
```
- **추상 메서드**: `abstract`를 붙이고 몸체 없이 선언한다. C++의 순수 가상 함수(`virtual void draw() = 0;`)와 같다. 자동으로 virtual이라서 자식은 `override`로 구현해야 한다.
- **추상 클래스**: 클래스에 `abstract`를 붙여야 한다.
  - C++은 순수 가상 함수가 하나라도 있으면 자동으로 추상 클래스가 되지만, C#은 클래스에도 `abstract`를 **직접 써야** 한다.
  - 추상 메서드가 하나도 없어도 추상 클래스로 만들 수 있다(ConsoleApp5의 `Animal`).
- 추상 클래스로는 **객체를 만들 수 없다**(`new Shape()` 불가). 부모 타입 변수로는 쓸 수 있다.
- `Brush.action(Shape s)`처럼 부모 타입으로 받으면, 새 도형이 추가되어도 `Brush`를 고칠 필요가 없다.

## 실습: 포켓몬
코드: [Poketmon/Program.cs](Poketmon/Poketmon/Program.cs), [Poketmon.cs](Poketmon/Poketmon/Poketmon.cs)

```csharp
if (!int.TryParse(Console.ReadLine(), out int select)) select = 1;

Poketmon p = select switch
{
    1 => new Pikachu("Pikachu", 1, 100, 0),
    2 => new Squirtle("Squirtle", 1, 100, 0),
    3 => new Bulbasaur("Bulbasaur", 1, 100, 0),
    _ => new Pikachu("Pikachu", 1, 100, 0)   // 기본값
};

p.skill();   // 선택한 포켓몬의 skill() 실행
```
```
1. Pikachu  2. Squirtle  3. Bulbasaur
> 2
Squirtle's WaterCannon
```
- `Poketmon`에 공통 상태(HP, 레벨, 경험치)와 행동(`eat`, `sleep`, `exercise`, `play`)을 두고, `skill()`만 `virtual`로 열어 각 포켓몬이 `override`한다.
- `int.TryParse(문자열, out int 변수)`: 숫자로 바꿀 수 있으면 `true`를 반환하고 `out`으로 값을 넘겨준다. `out`을 실제로 쓰는 예다.
- **switch 식**: `값 switch { 패턴 => 결과, ... }` 형태로 값을 바로 만든다. `_`는 default에 해당한다.
- 고칠 점:
  - 자식 생성자 세 개가 같은 대입을 반복한다. 부모 생성자를 재사용하면 된다: `public Pikachu(string name, int level, int hp, int exp) : base(name, level, hp, exp) { }`
  - `Exp > 100`이면 경험치가 정확히 100일 때 레벨업하지 않는다. `>=`가 맞다.
  - `Name + "is Died"`, `Name + "level up~!"`은 이름 뒤에 공백이 없어서 붙어서 출력된다.
  - `RazorReaf` → `RazorLeaf`
