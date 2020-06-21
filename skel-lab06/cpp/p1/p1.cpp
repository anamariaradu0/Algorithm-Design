// skel PA 2017

#include <iostream>
#include <vector>

#include "nim.h"

#define HEAPS_SIZE 3
Move::Move(int amount = 0, int heap = -1): amount(amount), heap(heap)
{
}

Nim::Nim()
{
    heaps[0] = 3;
    heaps[1] = 4;
    heaps[2] = 5;
}

/**
 * Returneaza o lista cu mutarile posibile
 * care pot fi efectuate de player
 */
std::vector<Move>
Nim::get_moves(int player)
{
    std::vector<Move> ret;
    for (int i = 0; i < 3; i++)
        for (int k = 1; k <= 3; k++)
            if (k <= heaps[i])
                ret.push_back(Move(k, i));
    return ret;
}

/**
 * Intoarce true daca jocul este intr-o stare finala
 */
bool
Nim::ended()
{
    /**
     * TODO Determinati daca jocul s-a terminat
     */
    for (int i = 0; i < HEAPS_SIZE; ++i) {
        if (heaps[i] > 0) {
            return false;
        }
    }

    return true;
}

/**
 * Functia de evaluare a starii curente a jocului
 * Evaluarea se face din perspectiva jucatorului
 * aflat curent la mutare (player)
 */
int
Nim::eval(int player)
{
    /**
     * TODO Implementati o functie de evaluare
     * pentru starea curenta a jocului
     *
     * Aceasta trebuie sa intoarca:
     * Inf daca jocul este terminat in favoarea lui player
     * -Inf daca jocul este terminat in defavoarea lui player
     *
     * In celelalte cazuri ar trebui sa intoarca un scor cu atat
     * mai mare, cu cat player ar avea o sansa mai mare de castig
     */
    int objects = 0;
    for (int i = 0; i < HEAPS_SIZE; ++i) {
        objects += heaps[i];
    }

    switch (objects) {
        case 0:
            return Inf;
        default:
            return objects;
    }
}

/**
 * Aplica o mutarea a jucatorului asupra starii curente
 * Returneaza false daca mutarea e invalida
 */
bool
Nim::apply_move(const Move &move)
{
    /**
     * TODO Realizati efectuarea mutarii
     * (scadeti move.amount din multimea corespunzatoare
     */
    if (move.heap < 0 || move.heap > 2 || // indice invalid
        move.amount <= 0 || move.amount > 3 || //nr invalid de bile
        heaps[move.heap] < move.amount) { // daca incerc sa iau prea multe bile din multime
            return false;
        }
    heaps[move.heap] -= move.amount;
    return true;
}

/**
 * Afiseaza starea jocului
 */
void
Nim::print()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << i << ":";
        for (int j = 0; j < heaps[i]; j++)
            std::cout << " *";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Nim::undo(const Move &move)
{
    /**
     * TODO Realizati efectuarea mutarii
     * (scadeti move.amount din multimea corespunzatoare
     */
    heaps[move.heap] += move.amount;
}

/**
 * Implementarea algoritmului minimax (negamax)
 * Intoarce o pereche <x, y> unde x este cel mai bun scor
 * care poate fi obtinut de jucatorul aflat la mutare,
 * iar y este mutarea propriu-zisa
 */
std::pair<int, Move>
minimax(Nim init, int player, int depth)
{   
    // oprire daca jocul s-a terminat sau daca am atins depth minim
    if (init.ended() || depth == 0) {
        return std::make_pair(init.eval(player), Move(0, 0));
    }

    std::vector<Move> moves = init.get_moves(player);

    int max_score = -Inf;

    std::pair<int, Move> best_move;
    int i = 0;

    while (i < moves.size()) {
        ++i;
        // daca miscarea e ilegala, se trece la urmatoarea
        if (init.apply_move(moves[i]) == false) {
            continue;
        }

        // altfel, se calculeaza cel mai bun scor posibil
        int score = -minimax(init, -player, depth - 1).first;

        if (score > max_score) {
            max_score = score;
            best_move = std::make_pair(score, moves[i]);
        }

    }

    return best_move;
}

/**
 * Implementarea de negamax cu alpha-beta pruning
 * Intoarce o pereche <x, y> unde x este cel mai bun scor
 * care poate fi obtinut de jucatorul aflat la mutare,
 * iar y este mutarea propriu-zisa
 */
std::pair<int, Move>
minimax_abeta(Nim init, int player, int depth, int alfa, int beta)
{
    /**
     * TODO Implementati conditia de oprire
     */

    std::vector<Move> moves = init.get_moves(player);

    /**
     * TODO Determinati cel mai bun scor si cea mai buna mutare
     * folosind algoritmul minimax cu alfa-beta pruning
     */

    return std::pair<int, Move>(-Inf, Move());
}

int main()
{
    Nim nim;

    nim.heaps[0] = 5;
    nim.heaps[1] = 10;
    nim.heaps[2] = 20;

    nim.print();

    /* Choose here if you want COMP vs HUMAN or COMP vs COMP */
    bool HUMAN_PLAYER = true;
    int player = 1;

    while (!nim.ended())
    {
        std::pair<int, Move> p;
        if (player == 1)
        {
            p = minimax(nim, player, 6);
            // p = minimax_abeta(nim, player, 13, -Inf, Inf);

            std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
            nim.apply_move(p.second);
        }
        else
        {
            if (!HUMAN_PLAYER)
            {
                p = minimax(nim, player, 6);
                // p = minimax_abeta(nim, player, 13, -Inf, Inf);

                std::cout << "Player " << player << " evaluates to " << p.first << std::endl;
                nim.apply_move(p.second);
            }
            else
            {
                bool valid = false;
                while (!valid)
                {
                    int am, h;
                    std::cout << "Insert amount [1, 2 or 3] and heap [0, 1 or 2]: ";
                    std::cin >> am >> h;
                    valid = nim.apply_move(Move(am, h));
                }
            }
        }

        nim.print();
        player *= -1;
    }

    int w = nim.heaps[0] + nim.heaps[1] + nim.heaps[2];
    if (w == 0)
        std::cout << "Player " << player << " WON!" << std::endl;
    else
        std::cout << "Player " << player << " LOST!" << std::endl;
}
