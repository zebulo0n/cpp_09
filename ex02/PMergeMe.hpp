/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:35:57 by zoeschne          #+#    #+#             */
/*   Updated: 2026/03/24 17:02:03 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <sys/time.h>

enum seqName
{
    MAIN,
    PEND
};

template <typename Container>
struct layer
{
    Container main;
    Container pend;
    Container originalMain; // winners before recursive sort, used to bound binary search
    int lvl;
};

template <typename Container>
class PMergeMe
{
private:
    layer<Container> *RecursionLayers;
    int _totalLayers;
    int _seqSpace;
    Container output;
    double execTime;

    // Ford-Johnson algo
    void createAndSortPairs(int seqSize, int lvl);
    void binarySearchInsert(int lvl);
    void insertBaseCase(int lvl);
    void insertPendIntoMain(int lvl);
    Container constructJacobsthalIndexSequence(int pendSize);
    void boundedInsert(Container &mainSeq, const Container &orig, int value, int pendIdx);

    // helper functions
    void parseInput(char **av);
    int jacobsthal(int n);
    int findArraySize(int recursionlvl, int arrName);

    // Canonical Form
    PMergeMe(void);
    PMergeMe(const PMergeMe &other);
    PMergeMe &operator=(const PMergeMe &other);

public:
    PMergeMe(int elementCount);
    ~PMergeMe();

    void FordJohnson(int ac, char **av);
    void printOutput();
    void printTime(std::string type);

    // debug
    void printLayers(void);
    void printRecursionLayer(int recursionLvl, int seqSize);
    void printFlattened3D(const Container &tab, size_t X, size_t Y, size_t Z);
};

template <typename Container>
void printVector(Container output, std::string mess);

#include "canon&Debug.tpp"
#include "helper.tpp"
#include "FordJohnson.tpp"

#endif
