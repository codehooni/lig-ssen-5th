using PoketmonGame;
Console.Write("1. Pikachu  2. Squirtle  3. Bulbasaur\n> ");
if (!int.TryParse(Console.ReadLine(), out int select)) select = 1;

Poketmon p = select switch
{
    1 => new Pikachu("Pikachu", 1, 100, 0),
    2 => new Squirtle("Squirtle", 1, 100, 0),
    3 => new Bulbasaur("Bulbasaur", 1, 100, 0),
    _ => new Pikachu("Pikachu", 1, 100, 0)   // 기본값 꼭 넣기
};

p.skill();
