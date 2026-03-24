
// ─────────────────────────────────────────────
//  binarySearchInsert
//
//  Works bottom-up from _totalLayers down to 0.
//
//  At each level:
//    - Recurse deeper first, so lvl+1 is sorted on return.
//    - Pull the sorted winners back up:
//        RecursionLayers[lvl].main = RecursionLayers[lvl+1].main
//      (this is how the sorted sub-sequence propagates upward)
//    - Insert each pend element into main in Jacobsthal order
//      using std::lower_bound, bounded by its paired winner's
//      position to preserve the Ford-Johnson comparison count.
//
//  Base case (_totalLayers):
//    main has 0 or 1 element, pend has 0 or 1.
//    If main is empty (size 0 allocated), the straggler lives
//    in pend[0] — just move it into main.
//    Otherwise insert pend[0] into the 1-element main normally.
//
//  Pairing invariant: pend[i] < main[i] at the level where
//  the pair was created. After the recursive sort the winners
//  are reordered, so we look up each winner by its original
//  index in RecursionLayers[lvl+1].main before insertion.
// ─────────────────────────────────────────────
void PMergeMe::binarySearchInsert(int lvl)
{
    std::vector<int> &m = RecursionLayers[lvl].main;
    std::vector<int> &p = RecursionLayers[lvl].pend;

    // ── Base case: this is the deepest layer createAndSortPairs touched ──
    // That layer always has main.size() == 1 (one winner, fully sorted).
    // Its pend may have 0, 1, or 2 elements depending on odd/even splits.
    // We insert all of them via binary search and return.
    // (The layer below with main.size()==0 is never visited — it only
    //  exists as an allocation artifact for the straggler slot.)
    if ((int)m.size() == 1)
    {
        // Insert every pend element that was actually written.
        // pend is allocated with a fixed size but only the first
        // findArraySize(lvl, PEND) slots were filled; the rest are 0.
        // We use the allocated size as the loop bound — it matches exactly
        // what createAndSortPairs wrote (no over-allocation at this level).
        int ps = findArraySize(lvl, PEND);
        for (int i = 0; i < ps; i++)
        {
            std::vector<int>::iterator pos =
                std::lower_bound(m.begin(), m.end(), p[i]);
            m.insert(pos, p[i]);
        }
        return;
    }

    // ── Recurse first ────────────────────────
    binarySearchInsert(lvl + 1);

    // Save main BEFORE overwriting it with the sorted result from below.
    // This is the list of winners that were directly paired with pend at this level.
    // We need it to bound the binary search for each pend[i].
    RecursionLayers[lvl].originalMain = RecursionLayers[lvl].main;

    // ── Pull sorted winners back up ──────────
    RecursionLayers[lvl].main = RecursionLayers[lvl + 1].main;

    std::vector<int> &mainSeq = RecursionLayers[lvl].main;
    std::vector<int> &pendSeq = RecursionLayers[lvl].pend;

    int pendSize = (int)pendSeq.size();
    if (pendSize == 0)
    {
        if (lvl == 0)
            output = mainSeq;
        return;
    }

    // The pairing invariant: at the level where each pair was created,
    // pend[i] < its partner winner. After recursive sorting the winners
    // are reordered, so winnersSnapshot[i] is NO LONGER pend[i]'s partner.
    //
    // To bound the search correctly we need each pend[i]'s ORIGINAL partner.
    // That value is still sitting in RecursionLayers[lvl+1].pend at index i
    // NO — the original winner for pend[i] at THIS level is the value that
    // was written into RecursionLayers[lvl+1].main[i] by createAndSortPairs.
    // We saved that in a snapshot of lvl+1 main BEFORE recursion touched it.
    //
    // But we already recursed and lvl+1.main is now sorted+merged.
    // Solution: store the pre-recursion winners in a separate snapshot.
    // We do that by reading the pend values from the CURRENT level:
    // createAndSortPairs guarantees:  pend[i] at level L  <  main[i] at level L+1 (pre-sort)
    // So the original winner for pend[i] IS RecursionLayers[lvl+1].main[i]
    // from BEFORE the recursion. Since we overwrote it, we can't get it back.
    //
    // CORRECT approach: don't try to bound. Just search the full mainSeq.
    // The Jacobsthal order already minimises comparisons structurally.
    // Bounding is an optimisation, not a correctness requirement.
    // For a 42 project the full-range binary search is perfectly valid.

    std::vector<int> insertOrder = constructJacobsthalIndexSequence(pendSize);

    for (int k = 0; k < (int)insertOrder.size(); k++)
    {
        int pendIdx = insertOrder[k] - 1;
        if (pendIdx >= pendSize)
            continue;

        int valueToInsert = pendSeq[pendIdx];

        // originalMain[pendIdx] is the winner that was paired with pend[pendIdx]
        // when createAndSortPairs built this level. The invariant guarantees
        // valueToInsert < originalMain[pendIdx], so we bound the search there.
        // We find the winner's current position in the live (growing) mainSeq
        // by value, since inserts may have shifted indices.
        std::vector<int>::iterator searchEnd = mainSeq.end();
        std::vector<int> &orig = RecursionLayers[lvl].originalMain;
        if (pendIdx < (int)orig.size())
        {
            int winner = orig[pendIdx];
            std::vector<int>::iterator winPos =
                std::lower_bound(mainSeq.begin(), mainSeq.end(), winner);
            if (winPos != mainSeq.end())
                searchEnd = winPos + 1;  // include winner as valid upper bound
        }

        std::vector<int>::iterator pos =
            std::lower_bound(mainSeq.begin(), searchEnd, valueToInsert);
        mainSeq.insert(pos, valueToInsert);
    }

    // ── Level 0: write to output ─────────────
    if (lvl == 0)
        output = mainSeq;
}