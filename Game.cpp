#include <iostream>
#include <vector>
#include <time.h>
#include <random>

using namespace std;

int GAME_STATE = -1;
int PLAYER_STATE = -1;
int BOT_STATE = -1;
int CURRENT = -1;
const int JIMMI = 0;
const int BOT = 1;

/*
Game logic: first of all we inialize global variable (GAME_STATE,PLAYER_STATE,BOT_STATE,CURRENT). Further 
game set first player (Ogre or Jimmi) and in the process swaps them (function gswap). When player do move 
he enter one of the number to do action (below). 

When we set PLAYER_STATE and CURRENT we can call function game which distributes the functions 
of impact, protection and treatment for current player.

*/


/*

Game states
1(2)13 - lose (Jimmi, Bot) 
19 - in process

Players states
27 - hit
70 - defense
103 - heal
666 - exit

Current player
0 - Jimmi
1 - Bot

*/



vector<int> bot_move = {27, 70, 103};

vector<int> player_hit(7);
vector<int> player_defense(5);
vector<int> player_healing(3);
int player_health;


vector<int> bot_hit(7);
vector<int> bot_defense(5);
vector<int> bot_healing(3);
int bot_health;

void init_array(vector<int>& arr, int n = 11); // Fill array random numbers
void hit(vector<int> from); // from - this is attacker
void defend(vector<int> defense);
void heal(vector<int>& heals);
void check_hp(); // Check Ogre and Jimmi health, then update GAME_STATS 
void game(); // Logical core
void gswap(int& val); // Change current player (0 to 1 or 1 to 0)
void show_array(vector<int> arr); 
void show_game(); // Show all playes and bot characteristics
void initialize_game(); // Initialize global game variables

int main() {
	
	initialize_game();

	int tmp = 0;

	cout << "Здравствуй, путник! Я великий маг северного Королевства! Мне нужна твоя помощь для того, чтобы добраться до далекого царства, но мне"
			"мешает злой огр, преграждающий мне путь к мосту. Убей его и тогда награда не заставит себя ждать." << endl;
	cout << "Вы подходите к огру и он без раздумий бежит на вас, замахнувшись большой дубиной! Кто ударит первым? Решать будет только судьба!" << endl;

	
	if (CURRENT == 0)
	{
		cout << "Вам повезло и вы увернулись от первой атаки огра, теперь можно и атаковать. Или вы выберете что-то другое? (Ударить - 27, защититься - 70, восстановить здоровье - 103)" << endl;
		cin >> tmp;
		PLAYER_STATE = tmp;
	}
	else {
		cout << "Ну что же, вам не повезло, но ничего, в следующий раз удача точно повернется к вам лицом." << endl;
		BOT_STATE = 27;
	}
	game();
	while (true)
	{
		check_hp();
		if (GAME_STATE == 19) {
			cout << "Бой идёт." << endl;
		}
		if (GAME_STATE == 113) {
			cout << "Ты ,истекая кровью, видишь уродливое лицо огра, а потом его пятку." << endl;
			break;
		}
		if (GAME_STATE == 213) {
			cout << "Огр на последних силах пытается защищаться, но вы нанесли ему смертельные раны. Огр пал, "
					"маг дал вам волшебный свиток, на котором была нарисована карта, а ней только красная точка в горах..." << endl;
			break;
		}
		gswap(CURRENT);
		if (CURRENT == JIMMI)
		{
			cout << "Готов юный воин? Давай закончим начатое или ты хочешь сбежать с поля боя как последний трус( выход 666 )" << endl;
			cin >> tmp;
			PLAYER_STATE = tmp;
			if (PLAYER_STATE == 666)
			{
				cout << "Ты пахнешь слабостью!" << endl;
				break;
			}
		}
		if (CURRENT == BOT)
		{
			cout << "Твой противник что-то задумал. Интересно что?" << endl;
			BOT_STATE = bot_move[rand()%bot_move.size()];
		}
		game();
		show_game();
	}

	return 0;
}

void initialize_game() {
	setlocale(LC_ALL, "Russian");
	srand((unsigned)time(NULL));
	init_array(player_defense);
	init_array(player_healing, 99);
	init_array(player_hit);

	init_array(bot_defense);
	init_array(bot_healing, 99);
	init_array(bot_hit);

	player_health = 100;
	bot_health = 100;

	GAME_STATE = 19;

	CURRENT = 1;
}

void show_array(vector<int> arr) {
	for (auto iter = arr.begin(); iter != arr.end(); iter++)
	{
		cout << *iter << " ";
	}
}

void show_game() {
	cout << "----------------------------------" << endl<< endl;

	cout << "Здоровье Джима: " << player_health << endl;

	cout << "Щиты Джима: ";
	show_array(player_defense);
	cout << endl;
	cout << "Зелья Джима: ";
	show_array(player_healing);
	cout << endl;
	cout << "Мечи Джима: ";
	show_array(player_hit);
	cout << endl;

	cout << "Здоровье Огра: " << bot_health << endl;

	cout << "Щиты Огра: ";
	show_array(bot_defense);
	cout << endl;
	cout << "Снадобья Огра: ";
	show_array(bot_healing);
	cout << endl;
	cout << "Дубины огра: ";
	show_array(bot_hit);
	cout << endl;

	cout << "----------------------------------" << endl<< endl;
}

void gswap(int& val) {
	val = val == 0 ? 1 : 0;
}

void game() {
	if (CURRENT == JIMMI)
	{
		switch (PLAYER_STATE)
		{
		case 27:
			hit(player_hit);
			cout << "Клинок, сияя на солнце, проходит как ветер по телу огра!" << endl;
			return;
		case 70:
			defend(player_defense);
			cout << "Щит подареный твоим отцом отлично защищает не только от ударов, но и от стрел" << endl;
			return;
		case 103:
			heal(player_healing);
			cout << "Здоровье превыше всего! Но думаю лишняя пинта не помешает" << endl;
			return;
		default:
			cout << " Что-то странное. Ты точно всё правильно сделал? " << endl;
			return;
		}
	}
	if (CURRENT == BOT)
	{
		switch (BOT_STATE)
		{
		case 27:
			hit(bot_hit);
			cout << "ААААААААаааа!" << endl;
			return;
		case 70:
			defend(bot_defense);
			cout << "Твой противник прикрывается куском камня." << endl;
			return;
		case 103:
			heal(bot_healing);
			cout << "Аамням-мням..." << endl;
			return;
		default:
			cout << " Что-то странное. Ты точно всё правильно сделал? " << endl;
			return;
		}
	}
}

void init_array(vector<int>& arr, int n) {
	for (size_t i = 0; i < arr.size(); i++)
	{
		arr[i] = rand() % n;
	}
}

void hit(vector<int> from) {
	int n = rand() % from.size();
	switch (CURRENT)
	{
	case JIMMI:
		bot_health -= from[n];
		return;
	case BOT:
		player_health -= from[n];
		return;
	default:
		cout << " Что-то странное. Ты точно всё правильно сделал? " << endl;
		return;
	}
}

void heal(vector<int>& heals) {
	if (heals.size()==0)
	{
		return;
	}
	int n = rand()%heals.size();
	switch (CURRENT)
	{
	case JIMMI:
		player_health += heals[n];
		if (player_health > 100)
		{
			player_health -= player_health % 100;
		}
		heals.erase(heals.begin() + n);
		return;
	case BOT:
		bot_health += heals[n];
		if (bot_health > 100)
		{
			bot_health -= bot_health % 100;
		}
		heals.erase(heals.begin() + n);
		if (heals.size()==0)
		{
			bot_move.pop_back();
		}
		return;
	default:
		cout << " Что-то странное. Ты точно всё правильно сделал? " << endl;
		return;
	}
}

void defend(vector<int> defense) {
	if (PLAYER_STATE == 27 or BOT_STATE == 27) {
		int n1 = rand() % defense.size();
		int n2 = rand() % player_hit.size();
		int n3 = rand() % bot_hit.size();
		switch (CURRENT)
		{
			case JIMMI:
				if (defense[n1] - player_hit[n2] < 0)
				{
					bot_health -= abs(defense[n1] - player_hit[n2]);
				}
				return;
			case BOT:
				if (defense[n1] - bot_hit[n2] < 0)
				{
					player_health -= abs(defense[n1] - bot_hit[n3]);
				}
				return;
			default:
				cout << " Что-то странное. Ты точно всё правильно сделал? " << endl;
				return;
		}
	}
}

void check_hp() {
	if (bot_health <= 0)
	{
		GAME_STATE = 213;
	}
	if (player_health <= 0)
	{
		GAME_STATE = 113;
	}
}
